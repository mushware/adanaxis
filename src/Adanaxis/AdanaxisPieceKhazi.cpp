//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceKhazi.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Z+ifTSkKrl4GVRxP2YKNlg
/*
 * $Id: AdanaxisPieceKhazi.cpp,v 1.8 2006/06/21 12:17:55 southa Exp $
 * $Log: AdanaxisPieceKhazi.cpp,v $
 * Revision 1.8  2006/06/21 12:17:55  southa
 * Ruby object generation
 *
 * Revision 1.7  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/09/05 12:54:29  southa
 * Solid rendering work
 *
 * Revision 1.5  2005/09/03 17:05:36  southa
 * Material work
 *
 * Revision 1.4  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.3  2005/08/01 17:58:51  southa
 * Object explosion
 *
 * Revision 1.2  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 * Revision 1.1  2005/07/19 10:08:06  southa
 * Adanaxis work
 *
 */

#include "AdanaxisPieceKhazi.h"

#include "AdanaxisData.h"
#include "AdanaxisPieceProjectile.h"
#include "AdanaxisUtil.h"

using namespace Mushware;
using namespace std;

AdanaxisPieceKhazi::AdanaxisPieceKhazi(const std::string& inID) :
    MushGamePiece(inID)
{
}  

void
AdanaxisPieceKhazi::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    PostWRef().InPlaceVelocityAdd();
}

void
AdanaxisPieceKhazi::Render(MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera)
{
    MushRenderSpec renderSpec;
    renderSpec.BuffersRefSet(BuffersRef());
    renderSpec.TexCoordBuffersRefSet(TexCoordBuffersRef());

    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), Post());
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), inCamera.Post());
    renderSpec.ViewWRef().InPlaceInvert();
    
    renderSpec.ProjectionSet(inCamera.Projection());
    
    inRender.MeshRender(renderSpec, Mesh());
}

void
AdanaxisPieceKhazi::CollisionFatalConsume(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage)
{
    if (!ExpireFlag())
    {
        ExpireFlagSet(true);
        Explode(ioLogic, inMessage);
        MediaAudio::Sgl().Play(*MushcoreDataRef<MediaSound>("explode").Get());
    }
}    

void
AdanaxisPieceKhazi::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const MushGameMessageCollisionFatal *pCollisionFatal;
    
    if ((pCollisionFatal = dynamic_cast<const MushGameMessageCollisionFatal *>(&inMessage)) != NULL)
    {
        CollisionFatalConsume(ioLogic, *pCollisionFatal);
    }
    else
    {
        // Pass to base class
        MushGamePiece::MessageConsume(ioLogic, inMessage);
    }
}


void
AdanaxisPieceKhazi::Explode(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage)
{
    U32 numChunks = Mesh().Chunks().size();
    U32 contactChunk = 0;
    if (inMessage.ChunkNumsValid())
    {
        contactChunk = inMessage.ChunkNum2();
    }
    
    tVal objectSize = Mesh().BoundingRadius();
    
    if (objectSize == 0)
    {
        throw MushcoreDataFail("Cannot explode object of zero size");
    }
    
    MushMesh4Mesh::tCentroid contactCentroid = Mesh().ChunkCentroid(contactChunk);
    
    for (U32 i=0; i<numChunks; ++i)
    {
        if (i != contactChunk)
        {
            AdanaxisSaveData::tProjectileList& projectileListRef =
            AdanaxisUtil::Logic(ioLogic).SaveData().ProjectileListWRef();
            
            projectileListRef.push_back(AdanaxisPieceProjectile("khazi"+Id()));
            AdanaxisSaveData::tProjectile& projectileRef = projectileListRef.back();
            
            projectileRef.OwnerSet(Id());
            projectileRef.ExpiryMsecSet(ioLogic.FrameMsec() + projectileRef.LifeMsec());
            
            // Create projectile in Khazi's coordinates
            projectileRef.PostWRef().ToIdentitySet();
            
            t4Val posOffset = Mesh().ChunkCentroid(i);
            
            projectileRef.PostWRef().PosWRef() += posOffset;
            
            projectileRef.PostWRef().AngVelWRef().ToRotationIdentitySet();
            for (U32 j=0; j<6; ++j)
            {
                tVal rot=0.02;
                projectileRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(0, MushMeshTools::Random(-rot, +rot)));
            }
            projectileRef.PostWRef().VelSet((posOffset - contactCentroid) * (MushMeshTools::Random(0.2,2) / objectSize));
            
            // Now transform to world coordinates
            // Reorientate the player space vectors to world space
            Post().AngPos().VectorRotate(projectileRef.PostWRef().PosWRef());
            Post().AngPos().VectorRotate(projectileRef.PostWRef().VelWRef());
            
            // Move to this object's position and velocity
            projectileRef.PostWRef().PosWRef() += Post().Pos();
            projectileRef.PostWRef().VelWRef() += Post().Vel();
            projectileRef.PostWRef().AngPosWRef().OuterMultiplyBy(Post().AngPos());
            
            // Don't inherit angular velocity
            
            // Create the mesh for this object
            MushMesh4Util::ChunkCopy(projectileRef.MeshWRef(), Mesh(), i);
			
			// Can't texture this one yet
			// projectileRef.TexCoordBuffersRefSet(m_texCoordBuffersRef);
        }
    }
}

//%outOfLineFunctions {

const char *AdanaxisPieceKhazi::AutoName(void) const
{
    return "AdanaxisPieceKhazi";
}

MushcoreVirtualObject *AdanaxisPieceKhazi::AutoClone(void) const
{
    return new AdanaxisPieceKhazi(*this);
}

MushcoreVirtualObject *AdanaxisPieceKhazi::AutoCreate(void) const
{
    return new AdanaxisPieceKhazi;
}

MushcoreVirtualObject *AdanaxisPieceKhazi::AutoVirtualFactory(void)
{
    return new AdanaxisPieceKhazi;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPieceKhazi", AdanaxisPieceKhazi::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPieceKhazi::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisPieceKhazi::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGamePiece::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisPieceKhazi::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } UJRpiKhuu/YO//32wwZeSw
