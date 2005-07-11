//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPlayer.cpp
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
//%Header } ow0iEi0s5HhumBjS38PxOA
/*
 * $Id: AdanaxisPlayer.cpp,v 1.8 2005/07/08 12:07:07 southa Exp $
 * $Log: AdanaxisPlayer.cpp,v $
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

using namespace Mushware;
using namespace std;

AdanaxisPlayer::AdanaxisPlayer(const std::string& inPlayerID) :
    MushGamePlayer(inPlayerID)
{
    PostWRef().PosSet(t4Val(0,0,0,20));
}

void
AdanaxisPlayer::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    PostWRef().InPlaceVelocityAdd();
    PostWRef().VelWRef().ToAdditiveIdentitySet();
    PostWRef().AngVelWRef().ToRotationIdentitySet();
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
        Post().AngPos().InPlaceRotate(vel);
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
        
        angVel.OuterMultiplyBy(Post().AngPos().ConjugateGet());
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
    ioOut << "lastAxes=" << m_lastAxes;
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
}
//%outOfLineFunctions } db2HxbL5n1vrtyu4ZQLaRw
