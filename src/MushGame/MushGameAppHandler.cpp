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
 * $Id: MushGameAppHandler.cpp,v 1.6 2006/06/30 15:05:34 southa Exp $
 * $Log: MushGameAppHandler.cpp,v $
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
        QuitModeEnter();
    }
}


void
MushGameAppHandler::QuitModeEnter(void)
{
    if (m_appState != kAppStateQuit)
    {
        CurrentSwapOut();
        m_appState = kAppStateQuit;
        AppQuit(); // Quit immediately
    }
}

void
MushGameAppHandler::GroupingNameSet(const std::string& inName)
{
    m_groupingName = inName;
    std::string controlMailboxName = inName+"-controlmailbox";
    MushcoreData<MushGameMailbox>::Sgl().GetOrCreate(controlMailboxName);
    m_controlMailboxRef.NameSet(controlMailboxName);
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
MushGameAppHandler::FillControlPipe(void)
{
    typedef MushGameMessageControlInfo tMessage;
    std::auto_ptr<MushGameMessageControlInfo> aControlInfo;
    
    for (U32 i=0; i<m_axisDefs.size(); ++i)
    {
        MushGameAxisDef& axisDefRef = m_axisDefs[i];
        if (axisDefRef.PosHasMoved())
        {
            if (aControlInfo.get() == NULL)
            {
                aControlInfo.reset(new MushGameMessageControlInfo);
                aControlInfo->TimestampSet(MillisecondsGet());
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
                aControlInfo->TimestampSet(MillisecondsGet());
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
    
    if (ioAxisDef.DeviceNum() == 0)
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
    else
    {
        throw MushcoreDataFail("Bad control device number");
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
            GLKeys requiredKey = axisDefRef.RequiredKey();
            if (requiredKey.Value() != 0 && KeyStateGet(requiredKey))
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
        
        if (axisDefRef.Integrate())
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
        GLKeys keyValue = keyDefRef.KeyValue();
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
    tMsec msecNow = MillisecondsGet();
    
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
            QuitModeEnter();
        }
    }
    catch (exception& e)
    {
            MushcoreLog::Sgl().ErrorLog() << "Exception in idle handler: " << e.what() << endl;
            
            PlatformMiscUtils::ErrorBox(string("Error: ") + e.what());
            QuitModeEnter();
    }
}

void
MushGameAppHandler::Idle(void)
{
    switch (m_appState)
    {
        case kAppStateStartup:
        {
            GameModeEnter(false);
            
            if (m_appState == kAppStateStartup)
            {
                MushcoreLog::Sgl().ErrorLog() << "GameModeEnter didn't change AppState; quitting" << endl;
                QuitModeEnter();
            }
        }
        break;
            
        case kAppStateGame:
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
MushGameAppHandler::GameModeEnter(bool inResume)
{
    MushcoreLog::Sgl().ErrorLog() << "MushGameAppHandler::GameModeEnter not overriden; quitting" << endl;
    QuitModeEnter();
}

void
MushGameAppHandler::KeyboardSignal(const GLKeyboardSignal& inSignal)
{
    bool keyHandled=false;
    if (m_currentRef.Exists())
    {
        keyHandled = m_currentRef.RefGet().KeyboardSignal(inSignal, *this);
    }
    else if (inSignal.keyValue.ValueGet() == 27 && inSignal.keyDown)
    {
        QuitModeEnter();
        keyHandled=true;
    }
    
    if (!keyHandled)
    {
        MushGLAppHandler::KeyboardSignal(inSignal);
    }
}
