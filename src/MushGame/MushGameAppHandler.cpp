//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAppHandler.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } bC49LKe3G5tsyGqAVa5gyw
/*
 * $Id: MushGameAppHandler.cpp,v 1.13 2006/07/12 11:22:41 southa Exp $
 * $Log: MushGameAppHandler.cpp,v $
 * Revision 1.13  2006/07/12 11:22:41  southa
 * Advanced control menu
 *
 * Revision 1.12  2006/07/11 19:49:05  southa
 * Control menu
 *
 * Revision 1.11  2006/07/11 12:37:52  southa
 * Control configuration
 *
 * Revision 1.10  2006/07/10 16:01:19  southa
 * Control menu work
 *
 * Revision 1.9  2006/07/08 16:05:58  southa
 * Ruby menus and key handling
 *
 * Revision 1.8  2006/07/07 18:13:58  southa
 * Menu start and stop
 *
 * Revision 1.7  2006/07/04 16:55:27  southa
 * Ruby key handling
 *
 * Revision 1.6  2006/06/30 15:05:34  southa
 * Texture and buffer purge
 *
 * Revision 1.5  2006/06/01 15:39:20  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/08/02 11:11:48  southa
 * Adanaxis control demo work
 *
 * Revision 1.3  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.2  2005/07/08 12:07:07  southa
 * MushGaem control work
 *
 * Revision 1.1  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 */

#include "MushGameAppHandler.h"

#include "MushGameMessageControlInfo.h"

#include "API/mushPlatform.h"

using namespace Mushware;
using namespace std;

MushGameAppHandler::MushGameAppHandler(const std::string& inName) :
    MushGLAppHandler(),
    m_appState(kAppStateStartup),
    m_lastTickerMsec(0),
    m_lastAxesValid(false)
{
    GroupingNameSet(inName);
}

void
MushGameAppHandler::Display(void)
{
    if (m_currentRef.Exists())
    {
        m_currentRef.RefGet().Display(*this);
    }
    MushGLAppHandler::Display();
}

void
MushGameAppHandler::CurrentSwapOut(void)
{
    if (m_currentRef.Exists())
    {
        m_currentRef.Get()->SwapOut(*this);
    }
}

void
MushGameAppHandler::CurrentSwapIn(const std::string& inName)
{
    try
    {   
        m_currentRef.NameSet(inName);
        m_currentRef.RefGet().SwapIn(*this);
    }
    catch (exception& e)
    {
        cerr << "Exception during start sequence: " << e.what() << endl;
        
        PlatformMiscUtils::ErrorBox(string("Error: ") + e.what());
        QuitStateEnter();
    }
}


void
MushGameAppHandler::QuitStateEnter(void)
{
    if (m_appState != kAppStateQuitting)
    {
        CurrentSwapOut();
        m_appState = kAppStateQuitting;
        AppQuit(); // Quit immediately
    }
}

void
MushGameAppHandler::ControlsToDefaultSet(void)
{
    if (m_currentRef.Exists())
    {
        m_currentRef.Get()->ControlsToDefaultSet(*this);
    }
}    

Mushware::U32
MushGameAppHandler::DisplayModeNum(void) const
{
    U32 retVal = 0;
    if (m_currentRef.Exists())
    {
        retVal = m_currentRef.Get()->DisplayModeNum();
    }
    return retVal;
}

void
MushGameAppHandler::NextDisplayMode(void)
{
    if (m_currentRef.Exists())
    {
        m_currentRef.Get()->NextDisplayMode();
    }
}

void
MushGameAppHandler::DisplayReset(void)
{
    CurrentSwapOut();
    CurrentSwapIn(m_groupingName);
}

void
MushGameAppHandler::GroupingNameSet(const std::string& inName)
{
    m_groupingName = inName;
    std::string controlMailboxName = inName+"-controlmailbox";
    MushcoreData<MushGameMailbox>::Sgl().GetOrCreate(controlMailboxName);
    m_controlMailboxRef.NameSet(controlMailboxName);
}

const MushGameAxisDef&
MushGameAppHandler::AxisDef(Mushware::U32 inAxisNum) const
{
    if (inAxisNum >= m_axisDefs.size())
    {
        throw MushcoreDataFail("Axis number too high");
    }
    
    return m_axisDefs[inAxisNum];
}

const MushGameKeyDef&
MushGameAppHandler::KeyDef(Mushware::U32 inKeyNum) const
{
    if (inKeyNum >= m_keyDefs.size())
    {
        throw MushcoreDataFail("Key number too high");
    }
    
    return m_keyDefs[inKeyNum];
}

MushGameAxisDef&
MushGameAppHandler::AxisDefWRef(Mushware::U32 inAxisNum)
{
    if (inAxisNum >= m_axisDefs.size())
    {
        throw MushcoreDataFail("Axis number too high");
    }
    
    return m_axisDefs[inAxisNum];
}

MushGameKeyDef&
MushGameAppHandler::KeyDefWRef(Mushware::U32 inKeyNum)
{
    if (inKeyNum >= m_keyDefs.size())
    {
        throw MushcoreDataFail("Key number too high");
    }
    
    return m_keyDefs[inKeyNum];
}

void
MushGameAppHandler::AxisDefSet(const MushGameAxisDef& inAxisDef, Mushware::U32 inAxisNum)
{
    if (inAxisNum > 64)
    {
        throw MushcoreDataFail("Axis number too high");
    }
    if (inAxisNum >= m_axisDefs.size())
    {
        m_axisDefs.resize(inAxisNum+1);
    }
    m_axisDefs[inAxisNum] = inAxisDef;
}

void
MushGameAppHandler::KeyDefSet(const MushGameKeyDef& inKeyDef, Mushware::U32 inKeyNum)
{
    if (inKeyNum > 64)
    {
        throw MushcoreDataFail("Key number too high");
    }
    if (inKeyNum >= m_keyDefs.size())
    {
        m_keyDefs.resize(inKeyNum+1);
    }
    m_keyDefs[inKeyNum] = inKeyDef;
}

void
MushGameAppHandler::AxisPurge(Mushware::U32 inDeviceNum, Mushware::U32 inAxisNum)
{
    for (U32 i=0; i < m_axisDefs.size(); ++i)
    {
        if (m_axisDefs[i].DeviceNum() == inDeviceNum &&
            m_axisDefs[i].DeviceAxisNum() == inAxisNum)
        {
            m_axisDefs[i].DeviceNumSet(0);
        }
    }
}

void
MushGameAppHandler::KeyPurge(Mushware::U32 inKeyNum)
{
    for (U32 i=0; i < m_axisDefs.size(); ++i)
    {
        if (m_axisDefs[i].UpKey() == inKeyNum) m_axisDefs[i].UpKeySet(0);
        if (m_axisDefs[i].DownKey() == inKeyNum) m_axisDefs[i].DownKeySet(0);
        // Required keys can be reused so don't get purged
    }
    
    for (U32 i=0; i < m_keyDefs.size(); ++i)
    {
        if (m_keyDefs[i].KeyValue() == inKeyNum) m_keyDefs[i].KeyValueSet(0);
    }
}    

void
MushGameAppHandler::FillControlPipe(void)
{
    typedef MushGameMessageControlInfo tMessage;
    std::auto_ptr<MushGameMessageControlInfo> aControlInfo;
    
    tMsec msecNow = LogicWRef().GameMsec();
    
    for (U32 i=0; i<m_axisDefs.size(); ++i)
    {
        MushGameAxisDef& axisDefRef = m_axisDefs[i];
        if (axisDefRef.PosHasMoved())
        {
            if (aControlInfo.get() == NULL)
            {
                aControlInfo.reset(new MushGameMessageControlInfo);
                aControlInfo->TimestampSet(msecNow);
            }
            aControlInfo->AxisEventsWRef().push_back(tMessage::tAxisEvent(i, axisDefRef.Pos()));
            axisDefRef.PosHasMovedSet(false);
        }
    }
    
    for (U32 i=0; i<m_keyDefs.size(); ++i)
    {
        MushGameKeyDef& keyDefRef = m_keyDefs[i];
        if (keyDefRef.StateHasChanged())
        {
            if (aControlInfo.get() == NULL)
            {
                aControlInfo.reset(new MushGameMessageControlInfo);
                aControlInfo->TimestampSet(msecNow);
            }
            aControlInfo->KeyEventsWRef().push_back(tMessage::tKeyEvent(i, keyDefRef.State()));
            keyDefRef.StateHasChangedSet(false);
        }
    }
    
    if (aControlInfo.get() != NULL)
    {
        m_controlMailboxRef.WRef().Give(aControlInfo.release());
    }
}

void
MushGameAppHandler::AxisFromDeviceUpdate(MushGameAxisDef& ioAxisDef, Mushware::tVal inAmount)
{
    static tVal lastMouseX = 0;
    static tVal lastMouseY = 0;
    
    switch (ioAxisDef.DeviceNum())
    {
        case MushGameAxisDef::kDeviceMouse0:
        {
            // Mouse device
            switch (ioAxisDef.DeviceAxisNum())
            {
                case 0:
                {
                    if (m_lastAxesValid)
                    {
                        ioAxisDef.DeviceAccelerate(inAmount * (ScaledUnboundedMouseX() - lastMouseX));
                    }
                    lastMouseX = ScaledUnboundedMouseX();
                }
                break;
                    
                case 1:
                {
                    if (m_lastAxesValid)
                    {
                        ioAxisDef.DeviceAccelerate(inAmount * (ScaledUnboundedMouseY() - lastMouseY));
                    }
                    lastMouseY = ScaledUnboundedMouseY();
                }
                break;
                    
                default:
                    throw MushcoreDataFail("Bad control axis number");
            }
        }
        break;
            
        case MushGameAxisDef::kDeviceStick0:
        case MushGameAxisDef::kDeviceStick1:
        {
            U32 deviceNum = ioAxisDef.DeviceNum() - MushGameAxisDef::kDeviceStick0;
            U32 axisNum = ioAxisDef.DeviceAxisNum();
            tVal axisValue = DeviceAxis(deviceNum, axisNum);
            ioAxisDef.DeviceSet(axisValue * std::fabs(axisValue));
        }
        break;
            
        default:
            throw MushcoreDataFail("Bad control device number");
            break;
    }
}    

void
MushGameAppHandler::AxisTicker(Mushware::tMsec inTimeslice)
{
    m_axisNames = "";
    tVal amount = inTimeslice / 1000.0;
    
    
    /* Loop through axes and apply the device movements that
     * match their required key.  Unclaimed device movements will
     * be claimed in the next pass
     */  
    for (U32 i=0; i<m_axisDefs.size(); ++i)
    {
        MushGameAxisDef& axisDefRef = m_axisDefs[i];
        if (axisDefRef.UseDevice())
        {
            U32 requiredKey = axisDefRef.RequiredKey();
            if (requiredKey != 0 && KeyStateGet(requiredKey))
            {
                AxisFromDeviceUpdate(axisDefRef, amount);
            }
        }        
    }
    
    // Loop through axes and apply the effect of keys
    for (U32 i=0; i<m_axisDefs.size(); ++i)
    {
        MushGameAxisDef& axisDefRef = m_axisDefs[i];
        bool decelerate = true;
        S32 keyMoved = 0;
        
        if (axisDefRef.UseKeys())
        {
            bool upState = KeyStateGet(axisDefRef.UpKey());
            bool downState = KeyStateGet(axisDefRef.DownKey());
            if (upState && !downState)
            {
                axisDefRef.Accelerate(amount);
                decelerate = false;
                keyMoved += 1;
            }
            else if (downState && !upState)
            {
                axisDefRef.Accelerate(-amount);
                decelerate = false;
                keyMoved -= 1;
            }
        }
        
        if (decelerate)
        {
            axisDefRef.Decelerate(amount);
        }
        
        if (axisDefRef.UseDevice() && axisDefRef.RequiredKey() == 0)
        {
            AxisFromDeviceUpdate(axisDefRef, amount);
        } 
        
        if (axisDefRef.Integrate() || axisDefRef.DeviceNum() > 0)
        {
            axisDefRef.ApplyIntegration(amount);
        }
        if (keyMoved != 0) 
        {
            if (m_axisNames != "")
            {
                m_axisNames += ",";
            }
            m_axisNames += (keyMoved == 1)?"+":"-";
            m_axisNames += axisDefRef.AxisName();
        }
    }
    m_lastAxesValid = true;
}

void
MushGameAppHandler::KeyTicker(Mushware::tMsec inTimeslice)
{
    for (U32 i=0; i<m_keyDefs.size(); ++i)
    {
        MushGameKeyDef& keyDefRef = m_keyDefs[i];
        U32 keyValue = keyDefRef.KeyValue();
        bool keyState = KeyStateGet(keyValue);
        if (keyState != keyDefRef.State())
        {
            keyDefRef.StateSet(keyState);
            keyDefRef.StateHasChangedSet(true);
        }
    }
}

void
MushGameAppHandler::GameIdle(void)
{
    tMsec msecNow = LogicWRef().GameMsec();
    
    tMsec timesliceMsec = msecNow - m_lastTickerMsec;
    
    MushcoreUtil::Constrain<tMsec>(timesliceMsec, 0, 1000);
        
    // Input is read on a 10ms (or greater) tick
    if (timesliceMsec >= 10)
    {
        if (m_lastTickerMsec != 0)
        {
            AxisTicker(timesliceMsec);
            KeyTicker(timesliceMsec);
            FillControlPipe();
        }
        m_lastTickerMsec = msecNow;
    }
    
    try
    {
        if (m_currentRef.Exists())
        {
            m_currentRef.RefGet().Process(*this);
        }
        else
        {
            // Lost game - nothing to do but quit
            QuitStateEnter();
        }
    }
    catch (exception& e)
    {
            MushcoreLog::Sgl().ErrorLog() << "Exception in idle handler: " << e.what() << endl;
            
            PlatformMiscUtils::ErrorBox(string("Error: ") + e.what());
            QuitStateEnter();
    }
}

void
MushGameAppHandler::NewGameCreate(const std::string& inName)
{
    throw MushcoreLogicFail("Replacement for MushGameAppHandler must override NewGameCreate");
}

void
MushGameAppHandler::GameRestart(void)
{
    CurrentSwapOut();
    NewGameCreate(m_groupingName);
    
    CurrentSwapIn(m_groupingName);
}

void
MushGameAppHandler::Idle(void)
{
    switch (m_appState)
    {
        case kAppStateStartup:
        {
            CurrentSwapOut();
            NewGameCreate(m_groupingName);
            CurrentSwapIn(m_groupingName);
            m_appState = kAppStateRunning;
        }
        break;
            
        case kAppStateRunning:
        {
            GameIdle();
        }
        break;
            
        default:
            break;
    }
    MushGLAppHandler::Idle();
}

void
MushGameAppHandler::KeyboardSignal(const GLKeyboardSignal& inSignal)
{
    bool keyHandled=false;
    
    if (inSignal.KeyValue() == 27 &&
        MediaKeyboard::HasModifier(inSignal.KeyModifier(), MediaKeyboard::kModCtrl) &&
        inSignal.KeyDown())
    {
        // Emergency quit
        QuitStateEnter();
        keyHandled=true;
    }
    else if (m_currentRef.Exists())
    {
        keyHandled = m_currentRef.RefGet().KeyboardSignal(inSignal, *this);
    }
    else if (inSignal.KeyValue() == 27 && inSignal.KeyDown())
    {
        // Used when there is no current game
        QuitStateEnter();
        keyHandled=true;
    }
    
    if (!keyHandled)
    {
        MushGLAppHandler::KeyboardSignal(inSignal);
    }
}
