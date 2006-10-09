//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceKhazi.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } YCa3eNmcxUH2q0Oxh6SpTA
/*
 * $Id: AdanaxisPieceKhazi.cpp,v 1.25 2006/10/05 15:39:17 southa Exp $
 * $Log: AdanaxisPieceKhazi.cpp,v $
 * Revision 1.25  2006/10/05 15:39:17  southa
 * Explosion handling
 *
 * Revision 1.24  2006/10/04 13:35:22  southa
 * Selective targetting
 *
 * Revision 1.23  2006/10/03 14:06:51  southa
 * Khazi and projectile creation
 *
 * Revision 1.22  2006/10/02 20:28:10  southa
 * Object lookup and target selection
 *
 * Revision 1.21  2006/09/09 15:59:27  southa
 * Shader colour calculations
 *
 * Revision 1.20  2006/09/09 11:16:39  southa
 * One-time vertex buffer generation
 *
 * Revision 1.19  2006/08/24 16:30:55  southa
 * Event handling
 *
 * Revision 1.18  2006/08/24 13:04:38  southa
 * Event handling
 *
 * Revision 1.17  2006/08/20 14:19:20  southa
 * Seek operation
 *
 * Revision 1.16  2006/08/19 09:12:09  southa
 * Event handling
 *
 * Revision 1.15  2006/08/17 12:18:10  southa
 * Event handling
 *
 * Revision 1.14  2006/08/17 08:57:11  southa
 * Event handling
 *
 * Revision 1.13  2006/08/01 17:21:25  southa
 * River demo
 *
 * Revision 1.12  2006/07/24 18:46:46  southa
 * Depth sorting
 *
 * Revision 1.11  2006/07/19 14:34:51  southa
 * Flare effects
 *
 * Revision 1.10  2006/07/19 10:22:14  southa
 * World objects
 *
 * Revision 1.9  2006/06/30 15:05:31  southa
 * Texture and buffer purge
 *
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
#include "AdanaxisIntern.h"
#include "AdanaxisPieceProjectile.h"
#include "AdanaxisRuby.h"
#include "AdanaxisUtil.h"

#include "API/mushMushMeshRuby.h"

using namespace Mushware;
using namespace std;

Mushware::tRubyValue AdanaxisPieceKhazi::m_rubyKlass = Mushware::kRubyQnil;

AdanaxisPieceKhazi::AdanaxisPieceKhazi(const std::string& inID, const MushRubyValue& inParams) :
    MushGamePiece(inID),
    m_actionMsec(1)
{
    RubyPieceConstructor(inID, inParams, AdanaxisIntern::Sgl().KlassAdanaxisPieceKhazi());
}

AdanaxisPieceKhazi::~AdanaxisPieceKhazi()
{
    RubyPieceDestructor();
}

void
AdanaxisPieceKhazi::ActionValueHandle(MushGameLogic& ioLogic, const MushRubyValue& inActionValue)
{
    U32 u32Value;

    if (inActionValue.Value() == Mushware::kRubyQnil)
    {
        m_actionMsec = 0;
    }
    else if (inActionValue.Is(u32Value))
    {
        m_actionMsec = ioLogic.GameMsec() + u32Value;
    }
    else if (inActionValue.IsArray())
    {
        // Whenever more than one action is required, use an array
        U32 size = inActionValue.ArraySize();
        for (U32 i=0; i<size; ++i)
        {
            ActionValueHandle(ioLogic, inActionValue.ArrayEntry(i));
        }
    }
    else if (inActionValue.IsHash())
    {
        // Each hash contains a single event or action
        Mushware::tRubyHash hash;
        inActionValue.Hash(hash);
        
        MushRubyValue event(kRubyQnil);
        
        Mushware::tRubyHash::iterator pEnd = hash.end();
        for (Mushware::tRubyHash::iterator p = hash.begin(); p != pEnd; ++p)
        {
            Mushware::tRubyID symbol = p->first.Symbol();
            
            if (symbol == MushRubyIntern::event())
            {
                event = p->second;
            }
            else
            {
                // Unknown hash element.  Assume it's intended for the event handler
            }
        }
        
        if (event.Value() != kRubyQnil)
        {
            // There is an event to dispatch
            EventHandle(ioLogic, event, inActionValue);
        }
    }
    else
    {
        throw MushcoreRequestFail("Bad return value from action function");
    }
}


void
AdanaxisPieceKhazi::EventHandle(MushGameLogic& ioLogic, MushRubyValue inEvent, MushRubyValue inParams)
{
    MushcoreLog::Sgl().InfoLog() << "Event " << inEvent.Call(MushRubyIntern::to_s()) << endl;
}

void
AdanaxisPieceKhazi::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    if (m_actionMsec != 0)
    {
        Mushware::tMsec gameMsec = ioLogic.GameMsec();
        if (m_actionMsec < gameMsec)
        {
            ActionValueHandle(ioLogic, RubyObj().Call(MushRubyIntern::SymbolID("mActionTimer")));
        }
    }
        
    PostWRef().InPlaceVelocityAdd();
}

bool
AdanaxisPieceKhazi::Render(MushGLJobRender& outRender,
                           MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera)
{
    MushRenderSpec renderSpec;
    renderSpec.BuffersRefSet(BuffersRef());
    renderSpec.SharedBuffersRefSet(SharedBuffersRef());

    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), Post());
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), inCamera.Post());
    renderSpec.ViewWRef().InPlaceInvert();
    
    renderSpec.ProjectionSet(inCamera.Projection());

    return inRender.RenderJobCreate(outRender, renderSpec, Mesh());
}

void
AdanaxisPieceKhazi::CollisionFatalConsume(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage)
{
    if (!ExpireFlag())
    {
        HitPointsSet(HitPoints() - 0.1);
        if (HitPoints() <= 0)
        {
            ExpireFlagSet(true);
            Explode(ioLogic, inMessage);
            MediaAudio::Sgl().Play(*MushcoreDataRef<MediaSound>("explode").Get());
        }
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
    
    // Disable for the moment
    numChunks = 0;
    
    for (U32 i=0; i<numChunks; ++i)
    {
        if (i != contactChunk)
        {
            AdanaxisSaveData::tProjectileList& projectileListRef =
            AdanaxisUtil::Logic(ioLogic).SaveData().ProjectileListWRef();
            
            projectileListRef.push_back(AdanaxisPieceProjectile("khazi"+Id()));
            AdanaxisSaveData::tProjectile& projectileRef = projectileListRef.back();
            
            projectileRef.OwnerSet(Id());
            projectileRef.LifeMsecSet(static_cast<U32>(15000*MushMeshTools::Random(0.1,0.5)));
            
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
			// projectileRef.SharedBuffersRefSet(SharedBuffersRef());
        }
    }
    AdanaxisUtil::ExploCreate(dynamic_cast<AdanaxisLogic&>(ioLogic), Post(), 10, 0);
    AdanaxisUtil::FlareCreate(dynamic_cast<AdanaxisLogic&>(ioLogic), Post(), 20, 0);

    for (U32 i=0; i<30; ++i)
    {
        AdanaxisUtil::EmberCreate(dynamic_cast<AdanaxisLogic&>(ioLogic),
                                  Post(),
                                  MushMeshTools::Random(0.1, 2), // size
                                  MushMeshTools::Random(0.1, 2)  // speed
                                  );
    }
}

Mushware::tRubyValue
AdanaxisPieceKhazi::RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    AdanaxisSaveData::tKhaziList& dataRef = AdanaxisRuby::SaveData().KhaziListWRef();
	
	/* This object contains a reference (MushcoreMaptorRef) to an object
     * in SaveData().KhaziList(), which is a MushcoreMaptor<AdanaxisPieceProjectile>.
     * The next line points the MushcoreMaptorRef at that MushcoreMaptor
     */
    AdanaxisSaveData::tKhaziList::key_type key = dataRef.NextKey();
    
    ostringstream idStream;
    idStream << key;
    
	AdanaxisPieceKhazi& objRef = *new AdanaxisPieceKhazi(idStream.str(), MushRubyValue(inArg0));
    dataRef.Give(&objRef, key);

    return objRef.RubyObj().Value();
}

Mushware::tRubyValue
AdanaxisPieceKhazi::Klass(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
        RubyInstall();
    }
    return m_rubyKlass;
}    

void
AdanaxisPieceKhazi::RubyInstall(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
	    m_rubyKlass = MushRubyUtil::SubclassDefine("AdanaxisPieceKhazi", MushGamePiece::Klass());
    }
	MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cCreate", RubyCreate);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(AdanaxisPieceKhazi::RubyInstall);
	}
	MushcoreInstaller install(Install);
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
    ioOut << "actionMsec=" << m_actionMsec;
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
    else if (inTagStr == "actionMsec")
    {
        ioIn >> m_actionMsec;
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
    ioOut.TagSet("actionMsec");
    ioOut << m_actionMsec;
}
//%outOfLineFunctions } XsG9P26QU9OniLdfLEyr7g
