//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceProjectile.cpp
 *
 * Copyright: Andy Southgate 2005
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
//%Header } cKEASf8ImtK3tzSM6fwREw
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisPieceProjectile.h"

using namespace Mushware;
using namespace std;

AdanaxisPieceProjectile::AdanaxisPieceProjectile(const std::string& inID) :
    m_id(inID),
    m_initialVelocity(1),
    m_lifeMsec(10000),
    m_expireFlag(false)
{
    PostWRef().ToIdentitySet();
    m_buffersRef.NameSet(MushGLBuffers::NextBufferNumAdvance());
    MushGLBuffers::tData::Sgl().GetOrCreate(m_buffersRef.Name());    
}

void
AdanaxisPieceProjectile::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    PostWRef().InPlaceVelocityAdd();
    if (ioLogic.FrameMsec() > m_expiryMsec)
    {
        ExpireFlagSet(true);
    }
}

void
AdanaxisPieceProjectile::Render(MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera)
{
    MushRenderSpec renderSpec;
    renderSpec.BuffersRefSet(m_buffersRef);
    
    MushMeshPosticity viewOffset;
    MushMeshPosticity viewAng;
    
    viewOffset.ToIdentitySet();
    viewOffset.PosSet(t4Val(0,0,0,0)-inCamera.Post().Pos());
    
    viewAng.ToIdentitySet();
    viewAng.AngPosSet(inCamera.Post().AngPos().ConjugateGet());
    
    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), Post());
    MushMeshOps::PosticityToMattress(renderSpec.SpecialWRef(), viewOffset);
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), viewAng);
    
    renderSpec.ProjectionSet(inCamera.Projection());
    
    inRender.MeshRender(renderSpec, m_mesh);
}
//%outOfLineFunctions {

const char *AdanaxisPieceProjectile::AutoName(void) const
{
    return "AdanaxisPieceProjectile";
}

MushcoreVirtualObject *AdanaxisPieceProjectile::AutoClone(void) const
{
    return new AdanaxisPieceProjectile(*this);
}

MushcoreVirtualObject *AdanaxisPieceProjectile::AutoCreate(void) const
{
    return new AdanaxisPieceProjectile;
}

MushcoreVirtualObject *AdanaxisPieceProjectile::AutoVirtualFactory(void)
{
    return new AdanaxisPieceProjectile;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPieceProjectile", AdanaxisPieceProjectile::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPieceProjectile::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "id=" << m_id << ", ";
    ioOut << "owner=" << m_owner << ", ";
    ioOut << "initialVelocity=" << m_initialVelocity << ", ";
    ioOut << "lifeMsec=" << m_lifeMsec << ", ";
    ioOut << "expiryMsec=" << m_expiryMsec << ", ";
    ioOut << "expireFlag=" << m_expireFlag << ", ";
    ioOut << "mesh=" << m_mesh << ", ";
    ioOut << "buffersRef=" << m_buffersRef;
    ioOut << "]";
}
bool
AdanaxisPieceProjectile::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "id")
    {
        ioIn >> m_id;
    }
    else if (inTagStr == "owner")
    {
        ioIn >> m_owner;
    }
    else if (inTagStr == "initialVelocity")
    {
        ioIn >> m_initialVelocity;
    }
    else if (inTagStr == "lifeMsec")
    {
        ioIn >> m_lifeMsec;
    }
    else if (inTagStr == "expiryMsec")
    {
        ioIn >> m_expiryMsec;
    }
    else if (inTagStr == "expireFlag")
    {
        ioIn >> m_expireFlag;
    }
    else if (inTagStr == "mesh")
    {
        ioIn >> m_mesh;
    }
    else if (inTagStr == "buffersRef")
    {
        ioIn >> m_buffersRef;
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
AdanaxisPieceProjectile::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("id");
    ioOut << m_id;
    ioOut.TagSet("owner");
    ioOut << m_owner;
    ioOut.TagSet("initialVelocity");
    ioOut << m_initialVelocity;
    ioOut.TagSet("lifeMsec");
    ioOut << m_lifeMsec;
    ioOut.TagSet("expiryMsec");
    ioOut << m_expiryMsec;
    ioOut.TagSet("expireFlag");
    ioOut << m_expireFlag;
    ioOut.TagSet("mesh");
    ioOut << m_mesh;
    ioOut.TagSet("buffersRef");
    ioOut << m_buffersRef;
}
//%outOfLineFunctions } cH84tCwMy+3SYNZp2iw3ew
