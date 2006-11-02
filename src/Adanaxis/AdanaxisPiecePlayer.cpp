//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPiecePlayer.cpp
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
//%Header } gq+r6M5XzKqE/mgjgvunrQ
/*
 * $Id: AdanaxisPiecePlayer.cpp,v 1.8 2006/10/30 17:03:51 southa Exp $
 * $Log: AdanaxisPiecePlayer.cpp,v $
 * Revision 1.8  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.7  2006/10/17 15:28:01  southa
 * Player collisions
 *
 * Revision 1.6  2006/10/12 22:04:47  southa
 * Collision events
 *
 * Revision 1.5  2006/10/09 16:00:16  southa
 * Intern generation
 *
 * Revision 1.4  2006/10/04 13:35:22  southa
 * Selective targetting
 *
 * Revision 1.3  2006/10/03 14:06:51  southa
 * Khazi and projectile creation
 *
 * Revision 1.2  2006/10/02 20:28:10  southa
 * Object lookup and target selection
 *
 * Revision 1.1  2006/10/02 17:25:04  southa
 * Object lookup and target selection
 *
 * Revision 1.27  2006/09/09 11:16:40  southa
 * One-time vertex buffer generation
 *
 * Revision 1.26  2006/08/25 11:06:08  southa
 * Snapshot
 *
 * Revision 1.25  2006/08/01 17:21:26  southa
 * River demo
 *
 * Revision 1.24  2006/07/28 16:52:19  southa
 * Options work
 *
 * Revision 1.23  2006/07/28 11:14:27  southa
 * Records for multiple spaces
 *
 * Revision 1.22  2006/07/26 16:37:21  southa
 * Options menu
 *
 * Revision 1.21  2006/07/24 18:46:47  southa
 * Depth sorting
 *
 * Revision 1.20  2006/07/19 14:34:51  southa
 * Flare effects
 *
 * Revision 1.19  2006/07/12 11:22:41  southa
 * Advanced control menu
 *
 * Revision 1.18  2006/07/11 12:37:51  southa
 * Control configuration
 *
 * Revision 1.17  2006/06/21 12:17:55  southa
 * Ruby object generation
 *
 * Revision 1.16  2006/06/01 15:38:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.15  2005/08/02 14:37:44  southa
 * Adanaxis control demo work
 *
 * Revision 1.14  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.13  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.12  2005/07/14 16:55:08  southa
 * Mesh library work
 *
 * Revision 1.11  2005/07/12 20:39:04  southa
 * Mesh library work
 *
 * Revision 1.10  2005/07/12 12:18:17  southa
 * Projectile work
 *
 * Revision 1.9  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.8  2005/07/08 12:07:07  southa
 * MushGaem control work
 *
 * Revision 1.7  2005/07/07 16:54:17  southa
 * Control tweaks
 *
 * Revision 1.6  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.5  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/23 17:25:24  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/20 14:46:41  southa
 * Adanaxis work
 *
 */

#include "AdanaxisPiecePlayer.h"

#include "AdanaxisConfig.h"
#include "AdanaxisEvents.h"
#include "AdanaxisIntern.h"
#include "AdanaxisMeshLibrary.h"
#include "AdanaxisPieceProjectile.h"
#include "AdanaxisRender.h"
#include "AdanaxisRuby.h"
#include "AdanaxisSaveData.h"
#include "AdanaxisUtil.h"
#include "AdanaxisVolatileData.h"

#include "API/mushMushMeshLibrary.h"
#include "API/mushMushMeshRuby.h"

using namespace Mushware;
using namespace std;

Mushware::tRubyValue AdanaxisPiecePlayer::m_rubyKlass = Mushware::kRubyQnil;

AdanaxisPiecePlayer::AdanaxisPiecePlayer(const std::string& inID, const MushRubyValue& inParams) :
    MushGamePiecePlayer(inID),
	m_projectileMeshRef("projectile")
{
    RubyPieceConstructor(inID, inParams, AdanaxisIntern::Sgl().AdanaxisPiecePlayer());
}

AdanaxisPiecePlayer::~AdanaxisPiecePlayer()
{
    RubyPieceDestructor();
}

void
AdanaxisPiecePlayer::PreControl(MushGameLogic& ioLogic)
{
    PostWRef().VelWRef().ToAdditiveIdentitySet();
    PostWRef().AngVelWRef().ToRotationIdentitySet();
}

void
AdanaxisPiecePlayer::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    MushGamePiece::Move(ioLogic, inFrameslice);

    PostWRef().InPlaceVelocityAdd();
}

void
AdanaxisPiecePlayer::AxisDeltaHandle(Mushware::tVal inDelta, Mushware::U32 inAxisNum)
{
    if (inAxisNum <= AdanaxisConfig::kAxisW)
    {
        t4Val vel;
        vel.ToAdditiveIdentitySet();
        
        switch (inAxisNum)
        {
            case AdanaxisConfig::kAxisX:
                vel = t4Val(inDelta,0,0,0);
                break;
                
            case AdanaxisConfig::kAxisY:
                vel = t4Val(0,inDelta,0,0);
                break;
                
            case AdanaxisConfig::kAxisZ:
                vel = t4Val(0,0,inDelta,0);
                break;
                
            case AdanaxisConfig::kAxisW:
                vel = t4Val(0,0,0,inDelta);
                break;
                
            default:
                throw MushcoreLogicFail("Axis value fault");
        }
        Post().AngPos().VectorRotate(vel);
        PostWRef().VelWRef() += vel;
    }
    else
    {
        tQValPair angVel;
        angVel.ToRotationIdentitySet();

        U32 rotationAxisNum = inAxisNum - AdanaxisConfig::kAxisXY;
        if (rotationAxisNum > 5)
        {
            throw MushcoreDataFail("Bad axis number");
        }
        
        angVel.OuterMultiplyBy(Post().AngPos().Conjugate());
        angVel.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(rotationAxisNum, inDelta));
        angVel.OuterMultiplyBy(Post().AngPos());

        angVel.InPlaceNormalise();
        PostWRef().AngVelWRef().OuterMultiplyBy(angVel);
        PostWRef().AngVelWRef().InPlaceNormalise();
    }
}

void
AdanaxisPiecePlayer::KeyChangeHandle(MushGameLogic& ioLogic, bool inState, Mushware::U32 inKeyNum)
{
    switch (inKeyNum)
    {
        case AdanaxisConfig::kKeyFire:
        {
            if (inState)
            {
                FireStateSet(FireState() | 1);
            }
            else
            {
                FireStateSet(FireState() & ~1);
            }
            ioLogic.QuickPlayerUplinkIsRequired();
        }
        break;
            
        case AdanaxisConfig::kKeyScanner:
        {
            if (inState)
            {
                AdanaxisVolatileData *pVolData = dynamic_cast<AdanaxisVolatileData *>(&ioLogic.VolatileData());

                if (pVolData != NULL)
                {
                    pVolData->ScannerOnSet(!pVolData->ScannerOn());
                }
            }
        }
        break;
            
        default:
            ostringstream message;
            message << "Bad key number: " << inKeyNum;
            throw MushcoreDataFail(message.str());
            break;
    }        
}

void
AdanaxisPiecePlayer::ControlInfoConsume(MushGameLogic& ioLogic, const MushGameMessageControlInfo& inMessage)
{
    Mushware::U32 axisEventsSize = inMessage.AxisEvents().size();
    Mushware::U32 lastAxesSize = m_lastAxes.size();
    
    if (lastAxesSize > 0)
    {
        for (U32 i=0; i<axisEventsSize; ++i)
        {
            U32 axisNum = inMessage.AxisEvents()[i].first;
            tVal axisValue = inMessage.AxisEvents()[i].second;
            
            if (axisNum <= lastAxesSize)
            {
                AxisDeltaHandle(m_lastAxes[axisNum] - axisValue, axisNum);
                m_lastAxes[axisNum] = axisValue;
            }
            else
            {
                throw MushcoreDataFail(std::string("Axis number too high in")+AutoName());
            }
        }
    }
    else
    {
        m_lastAxes.resize(AdanaxisConfig::kNumAxes, 0);
        lastAxesSize = m_lastAxes.size();
        for (U32 i=0; i<axisEventsSize; ++i)
        {
            U32 axisNum = inMessage.AxisEvents()[i].first;
            tVal axisValue = inMessage.AxisEvents()[i].second;
            
            if (axisNum <= lastAxesSize)
            {
                m_lastAxes[axisNum] = axisValue;
            }
        }
    }
    
    Mushware::U32 keyEventsSize = inMessage.KeyEvents().size();
    
    for (U32 i=0; i<keyEventsSize; ++i)
    {
        U32 keyNum = inMessage.KeyEvents()[i].first;
        bool keyState = inMessage.KeyEvents()[i].second;
        
        KeyChangeHandle(ioLogic, keyState, keyNum);
    }
}

void
AdanaxisPiecePlayer::FirePieceCreate(MushGameLogic& ioLogic, const MushGameMessageFire& inMessage)
{
    AdanaxisSaveData::tProjectileList& dataRef =
        AdanaxisUtil::Logic(ioLogic).SaveData().ProjectileListWRef();

    AdanaxisSaveData::tProjectileList::key_type key = dataRef.NextKey();
    
    ostringstream idStream;
    idStream << key;
    
	AdanaxisPieceProjectile& projectileRef = *new AdanaxisPieceProjectile(idStream.str());
    dataRef.Give(&projectileRef, key);
    
    projectileRef.IdSet("f:"+idStream.str());
    projectileRef.OwnerSet(Id());
    projectileRef.LifeMsecSet(15000); // FIXME
    
    // Create projectile in player's coordinates
    projectileRef.PostWRef().ToIdentitySet();
    
    t4Val posOffset = t4Val(1,0,0,0);
    if (inMessage.Count() % 2 == 0)
    {
        posOffset = t4Val(0,0,0,0) - posOffset;
    }

    projectileRef.PostWRef().PosWRef() += posOffset;

    // Get the player forward velocity but not transverse
    t4Val playerVel = inMessage.Post().Vel();
    inMessage.Post().AngPos().Conjugate().VectorRotate(playerVel);
    
    projectileRef.PostWRef().AngVelWRef().ToRotationIdentitySet();
    projectileRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(0, 0.02));
    projectileRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(2, 0.017));
    projectileRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(5, 0.013));
    projectileRef.PostWRef().VelSet(t4Val(0, 0, 0, playerVel.W() - 1.0)); //FIXME
    
    // Now transform to world coordinates
    // Reorientate the player space vectors to world space
    inMessage.Post().AngPos().VectorRotate(projectileRef.PostWRef().PosWRef());
    inMessage.Post().AngPos().VectorRotate(projectileRef.PostWRef().VelWRef());

    // Move to player position
    projectileRef.PostWRef().PosWRef() += inMessage.Post().Pos();
    projectileRef.PostWRef().AngPosWRef().OuterMultiplyBy(inMessage.Post().AngPos());
    
    tQValPair angVel = inMessage.Post().AngPos().Conjugate();
    angVel.OuterMultiplyBy(projectileRef.Post().AngVel());
    angVel.OuterMultiplyBy(inMessage.Post().AngPos());

    projectileRef.PostWRef().AngVelSet(angVel);
    
    // Create the mesh for this object
    projectileRef.MeshWRef() = m_projectileMeshRef.Ref();
	projectileRef.SharedBuffersNameSet(m_projectileMeshRef.Name());
    
    // Create the flare effect
    MushMeshPosticity flarePost = projectileRef.Post();
    flarePost.PosWRef() -= 1 * flarePost.Vel();
    AdanaxisUtil::FlareCreate(dynamic_cast<AdanaxisLogic&>(ioLogic),
                              flarePost,
                              0.5, // size
                              0  // speed
                              );
}

void
AdanaxisPiecePlayer::FireConsume(MushGameLogic& ioLogic, const MushGameMessageFire& inMessage)
{
    MushRubyValue event = AdanaxisEvents::Sgl().EventFireMake(inMessage.Post());
    RubyEventHandle(event);
    
    AdanaxisVolatileData *pVolData = dynamic_cast<AdanaxisVolatileData *>(&ioLogic.VolatileData());
    
    if (pVolData != NULL)
    {
        pVolData->ScannerOnSet(false);
    }
}

Mushware::tRubyValue
AdanaxisPiecePlayer::RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    AdanaxisSaveData::tPlayersList& dataRef = AdanaxisRuby::SaveData().PlayersListWRef();
	
	/* This object contains a reference (MushcoreMaptorRef) to an object
    * in SaveData().PlayersList(), which is a MushcoreMaptor<AdanaxisPieceProjectile>.
    * The next line points the MushcoreMaptorRef at that MushcoreMaptor
    */
    AdanaxisSaveData::tPlayersList::key_type key = dataRef.NextKey();
    
    ostringstream idStream;
    idStream << key;
    
	AdanaxisPiecePlayer& objRef = *new AdanaxisPiecePlayer(idStream.str(), MushRubyValue(inArg0));
    dataRef.Give(&objRef, key);
    
    return objRef.RubyObj().Value();
}

Mushware::tRubyValue
AdanaxisPiecePlayer::Klass(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
        RubyInstall();
    }
    return m_rubyKlass;
}    

void
AdanaxisPiecePlayer::RubyInstall(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
	    m_rubyKlass = MushRubyUtil::SubclassDefine("AdanaxisPiecePlayer", AdanaxisPiece::Klass());
    }
	MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cCreate", RubyCreate);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(AdanaxisPiecePlayer::RubyInstall);
	}
	MushcoreInstaller install(Install);
}


//%outOfLineFunctions {

const char *AdanaxisPiecePlayer::AutoName(void) const
{
    return "AdanaxisPiecePlayer";
}

MushcoreVirtualObject *AdanaxisPiecePlayer::AutoClone(void) const
{
    return new AdanaxisPiecePlayer(*this);
}

MushcoreVirtualObject *AdanaxisPiecePlayer::AutoCreate(void) const
{
    return new AdanaxisPiecePlayer;
}

MushcoreVirtualObject *AdanaxisPiecePlayer::AutoVirtualFactory(void)
{
    return new AdanaxisPiecePlayer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPiecePlayer", AdanaxisPiecePlayer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPiecePlayer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiecePlayer::AutoPrint(ioOut);
    ioOut << "lastAxes=" << m_lastAxes << ", ";
    ioOut << "projectileMeshRef=" << m_projectileMeshRef;
    ioOut << "]";
}
bool
AdanaxisPiecePlayer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "lastAxes")
    {
        ioIn >> m_lastAxes;
    }
    else if (inTagStr == "projectileMeshRef")
    {
        ioIn >> m_projectileMeshRef;
    }
    else if (MushGamePiecePlayer::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisPiecePlayer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiecePlayer::AutoXMLPrint(ioOut);
    ioOut.TagSet("lastAxes");
    ioOut << m_lastAxes;
    ioOut.TagSet("projectileMeshRef");
    ioOut << m_projectileMeshRef;
}
//%outOfLineFunctions } id3utxZnuurbzRNn59r7aQ
