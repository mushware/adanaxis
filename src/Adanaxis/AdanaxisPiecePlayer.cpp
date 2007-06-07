//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPiecePlayer.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } NakSYndAI0IrqBBZFk2p3g
/*
 * $Id: AdanaxisPiecePlayer.cpp,v 1.19 2007/05/22 12:59:09 southa Exp $
 * $Log: AdanaxisPiecePlayer.cpp,v $
 * Revision 1.19  2007/05/22 12:59:09  southa
 * Vortex effect on player
 *
 * Revision 1.18  2007/05/21 17:04:43  southa
 * Player effectors
 *
 * Revision 1.17  2007/05/12 14:20:48  southa
 * Level 16
 *
 * Revision 1.16  2007/05/10 14:06:26  southa
 * Level 16 and retina spin
 *
 * Revision 1.15  2007/04/18 09:22:02  southa
 * Header and level fixes
 *
 * Revision 1.14  2007/04/16 08:41:08  southa
 * Level and header mods
 *
 * Revision 1.13  2007/03/07 16:59:44  southa
 * Khazi spawning and level ends
 *
 * Revision 1.12  2006/12/14 00:46:57  southa
 * Control fix and audio pacing
 *
 * Revision 1.11  2006/12/14 00:33:48  southa
 * Control fix and audio pacing
 *
 * Revision 1.10  2006/11/03 18:46:33  southa
 * Damage effectors
 *
 * Revision 1.9  2006/11/02 09:47:33  southa
 * Player weapon control
 *
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

#include "AdanaxisAppHandler.h"
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
    m_lastAxes.resize(AdanaxisConfig::kNumAxes, 0);
    m_lastAxisValid.resize(AdanaxisConfig::kNumAxes, false);
}

AdanaxisPiecePlayer::~AdanaxisPiecePlayer()
{
    RubyPieceDestructor();
}

void
AdanaxisPiecePlayer::PreControl(MushGameLogic& ioLogic)
{
    if (m_controlReleased)
    {
        // Limit velocity only
        tVal mag = Post().Vel().Magnitude();
        if (mag > 1.0)
        {
            PostWRef().VelWRef() /= mag;
        }
    }
    else
    {
        PostWRef().VelWRef().ToAdditiveIdentitySet();
    }
    
    AdanaxisSaveData& saveData = AdanaxisUtil::Logic(ioLogic).SaveData();
    tVal retinaSpin = saveData.RetinaSpin();
    
    
    if (!saveData.PermanentSpin())
    {
        if (m_controlReleased)
        {
            retinaSpin += 0.03;
            MushcoreUtil::Constrain<tVal>(retinaSpin, 0.1, 10);
            saveData.RetinaSpinSet(retinaSpin);
        }
        else
        {
            saveData.RetinaSpinSet(saveData.RetinaSpin() * 0.95);
        }
    }
    
    if (retinaSpin > 0.001)
    {
        tQValPair angVel = Post().AngPos().Conjugate();
        
        AdanaxisVolatileData& volData = AdanaxisUtil::Logic(ioLogic).VolatileData();
        
        angVel.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisXY, retinaSpin * M_PI/800));
        angVel.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisXZ, retinaSpin * M_PI/740));
        angVel.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisYZ, retinaSpin * M_PI/650));
        if (m_controlReleased)
        {
            angVel.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisXW, retinaSpin * M_PI/3000));
        }
        
        angVel.OuterMultiplyBy(Post().AngPos());
        angVel.InPlaceNormalise();
        PostWRef().AngVelSet(angVel);
        
        if (saveData.PermanentSpin() && volData.JammerCount() == 0)
        {
            // Stop retina spin once countermeasures removed
            saveData.RetinaSpinSet(saveData.RetinaSpin() * 0.99);
        }
    }
    else
    {
        PostWRef().AngVelWRef().ToRotationIdentitySet();
    }
    
    if (m_thrustReleased)
    {
        t4Val vel(0, 0, 0, -0.5 - 0.25*saveData.GameDifficulty());
        Post().AngPos().VectorRotate(vel);
        PostWRef().VelWRef() += vel;
    }
}

void
AdanaxisPiecePlayer::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    if (ExpireFlag())
    {
        PostWRef().VelWRef().ToAdditiveIdentitySet();
    }
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
                if (!m_thrustReleased)
                {
                    vel = t4Val(0,0,0,inDelta);
                }
                break;
                
            default:
                throw MushcoreLogicFail("Axis value fault");
        }

        Post().AngPos().VectorRotate(vel);
        if (vel.Magnitude() < 10.0)
        {
            PostWRef().VelWRef() += vel;
        }
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
            MushRubyValue event = AdanaxisEvents::Sgl().EventKeyStateMake();
            AdanaxisEvents::Sgl().EventKeyStateAddState(event, inKeyNum, inState);
            RubyEventHandle(event);

            break;
    }        
}

void
AdanaxisPiecePlayer::ControlInfoConsume(MushGameLogic& ioLogic, const MushGameMessageControlInfo& inMessage)
{
    Mushware::U32 axisEventsSize = inMessage.AxisEvents().size();
    Mushware::U32 lastAxesSize = m_lastAxes.size();
    
    for (U32 i=0; i<axisEventsSize; ++i)
    {
        U32 axisNum = inMessage.AxisEvents()[i].first;
        tVal axisValue = inMessage.AxisEvents()[i].second;
        
        if (axisNum <= lastAxesSize)
        {
            if (m_lastAxisValid[axisNum])
            {
                AxisDeltaHandle(m_lastAxes[axisNum] - axisValue, axisNum);
            }
            else
            {
                m_lastAxisValid[axisNum] = true;
            }
            m_lastAxes[axisNum] = axisValue;
        }
        else
        {
            throw MushcoreDataFail(std::string("Axis number too high in")+AutoName());
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
AdanaxisPiecePlayer::Load(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Load(inSelf);
    MushRubyUtil::InstanceVarSet(inSelf, AdanaxisIntern::Sgl().ATm_controlReleased(), MushRubyValue(m_controlReleased).Value());    
    MushRubyUtil::InstanceVarSet(inSelf, AdanaxisIntern::Sgl().ATm_thrustReleased(), MushRubyValue(m_thrustReleased).Value());    
}

void
AdanaxisPiecePlayer::Save(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Save(inSelf);
    m_controlReleased = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, AdanaxisIntern::Sgl().ATm_controlReleased())).Bool();
    m_thrustReleased = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, AdanaxisIntern::Sgl().ATm_thrustReleased())).Bool();
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
    ioOut << "lastAxisValid=" << m_lastAxisValid << ", ";
    ioOut << "projectileMeshRef=" << m_projectileMeshRef << ", ";
    ioOut << "controlReleased=" << m_controlReleased << ", ";
    ioOut << "thrustReleased=" << m_thrustReleased;
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
    else if (inTagStr == "lastAxisValid")
    {
        ioIn >> m_lastAxisValid;
    }
    else if (inTagStr == "projectileMeshRef")
    {
        ioIn >> m_projectileMeshRef;
    }
    else if (inTagStr == "controlReleased")
    {
        ioIn >> m_controlReleased;
    }
    else if (inTagStr == "thrustReleased")
    {
        ioIn >> m_thrustReleased;
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
    ioOut.TagSet("lastAxisValid");
    ioOut << m_lastAxisValid;
    ioOut.TagSet("projectileMeshRef");
    ioOut << m_projectileMeshRef;
    ioOut.TagSet("controlReleased");
    ioOut << m_controlReleased;
    ioOut.TagSet("thrustReleased");
    ioOut << m_thrustReleased;
}
//%outOfLineFunctions } okU9DNgnBZkd0o+IfTu+9Q
