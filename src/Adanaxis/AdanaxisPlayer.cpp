//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPlayer.cpp
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
//%Header } 0edG1wrkU5hKeWbu3l1MQA
/*
 * $Id: AdanaxisPlayer.cpp,v 1.16 2006/06/01 15:38:48 southa Exp $
 * $Log: AdanaxisPlayer.cpp,v $
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

#include "AdanaxisPlayer.h"

#include "AdanaxisConfig.h"
#include "AdanaxisMeshLibrary.h"
#include "AdanaxisPieceProjectile.h"
#include "AdanaxisRender.h"
#include "AdanaxisSaveData.h"
#include "AdanaxisUtil.h"
#include "AdanaxisVolatileData.h"

#include "API/mushMushMeshLibrary.h"

using namespace Mushware;
using namespace std;

AdanaxisPlayer::AdanaxisPlayer(const std::string& inPlayerID) :
    MushGamePlayer(inPlayerID),
	m_projectileMeshRef("projectile")
{
    PostWRef().PosSet(t4Val(0,0,0,55));
}

void
AdanaxisPlayer::PreControl(MushGameLogic& ioLogic)
{
    PostWRef().VelWRef().ToAdditiveIdentitySet();
    PostWRef().AngVelWRef().ToRotationIdentitySet();
}

void
AdanaxisPlayer::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    PostWRef().InPlaceVelocityAdd();
}

void
AdanaxisPlayer::AxisDeltaHandle(Mushware::tVal inDelta, Mushware::U32 inAxisNum)
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
AdanaxisPlayer::KeyChangeHandle(MushGameLogic& ioLogic, bool inState, Mushware::U32 inKeyNum)
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
            
        default:
            throw MushcoreDataFail("Bad key number");
            break;
    }        
}

void
AdanaxisPlayer::ControlInfoConsume(MushGameLogic& ioLogic, const MushGameMessageControlInfo& inMessage)
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
        m_lastAxes.resize(AdanaxisConfig::kNumAxes);
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
        
        if (keyNum < AdanaxisConfig::kNumKeys)
        {
            KeyChangeHandle(ioLogic, keyState, keyNum);
        }
        else
        {
            throw MushcoreDataFail(std::string("Key number too high in")+AutoName());
        }
    }
}

void
AdanaxisPlayer::FirePieceCreate(MushGameLogic& ioLogic, const MushGameMessageFire& inMessage)
{
    AdanaxisSaveData::tProjectileList& projectileListRef =
        AdanaxisUtil::Logic(ioLogic).SaveData().ProjectileListWRef();

    projectileListRef.push_back(AdanaxisPieceProjectile("proj"+Id()));
    AdanaxisSaveData::tProjectile& projectileRef = projectileListRef.back();
    
    projectileRef.OwnerSet(Id());
    projectileRef.ExpiryMsecSet(ioLogic.FrameMsec() + projectileRef.LifeMsec());
    
    // Create projectile in player's coordinates
    projectileRef.PostWRef().ToIdentitySet();
    
    t4Val posOffset = t4Val(1,0,0,0);
    if (inMessage.Count() % 2 == 0)
    {
        posOffset = t4Val(0,0,0,0) - posOffset;
    }

    projectileRef.PostWRef().PosWRef() += posOffset;

    
    projectileRef.PostWRef().AngVelWRef().ToRotationIdentitySet();
    projectileRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(0, 0.02));
    projectileRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(2, 0.017));
    projectileRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(5, 0.013));
    projectileRef.PostWRef().VelSet(t4Val(0,0,0,-projectileRef.InitialVelocity()));
    
    // Now transform to world coordinates
    // Reorientate the player space vectors to world space
    inMessage.Post().AngPos().VectorRotate(projectileRef.PostWRef().PosWRef());
    inMessage.Post().AngPos().VectorRotate(projectileRef.PostWRef().VelWRef());

    // Move to player position and velocity
    projectileRef.PostWRef().PosWRef() += inMessage.Post().Pos();
    projectileRef.PostWRef().VelWRef() += inMessage.Post().Vel();
    projectileRef.PostWRef().AngPosWRef().OuterMultiplyBy(inMessage.Post().AngPos());
    
    tQValPair angVel = inMessage.Post().AngPos().Conjugate();
    angVel.OuterMultiplyBy(projectileRef.Post().AngVel());
    angVel.OuterMultiplyBy(inMessage.Post().AngPos());

    projectileRef.PostWRef().AngVelSet(angVel);
    
    // Create the mesh for this object
    projectileRef.MeshWRef() = m_projectileMeshRef.Ref();
	projectileRef.TexCoordBuffersNameSet(m_projectileMeshRef.Name());
}

void
AdanaxisPlayer::FireConsume(MushGameLogic& ioLogic, const MushGameMessageFire& inMessage)
{
    FirePieceCreate(ioLogic, inMessage);
    
    MediaAudio::Sgl().Play(*MushcoreDataRef<MediaSound>("fire").Get());
    
    dynamic_cast<AdanaxisRender&>(ioLogic.SaveData().RenderRef().WRef()).ScannerOnSet(false);
}


//%outOfLineFunctions {

const char *AdanaxisPlayer::AutoName(void) const
{
    return "AdanaxisPlayer";
}

MushcoreVirtualObject *AdanaxisPlayer::AutoClone(void) const
{
    return new AdanaxisPlayer(*this);
}

MushcoreVirtualObject *AdanaxisPlayer::AutoCreate(void) const
{
    return new AdanaxisPlayer;
}

MushcoreVirtualObject *AdanaxisPlayer::AutoVirtualFactory(void)
{
    return new AdanaxisPlayer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPlayer", AdanaxisPlayer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPlayer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePlayer::AutoPrint(ioOut);
    ioOut << "lastAxes=" << m_lastAxes << ", ";
    ioOut << "projectileMeshRef=" << m_projectileMeshRef;
    ioOut << "]";
}
bool
AdanaxisPlayer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (MushGamePlayer::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisPlayer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePlayer::AutoXMLPrint(ioOut);
    ioOut.TagSet("lastAxes");
    ioOut << m_lastAxes;
    ioOut.TagSet("projectileMeshRef");
    ioOut << m_projectileMeshRef;
}
//%outOfLineFunctions } XwoTRjO+3AZqJ0A2xJSzTg
