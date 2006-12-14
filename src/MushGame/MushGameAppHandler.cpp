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
 * $Id: MushGameAppHandler.cpp,v 1.22 2006/11/25 21:26:32 southa Exp $
 * $Log: MushGameAppHandler.cpp,v $
 * Revision 1.22  2006/11/25 21:26:32  southa
 * Display mode definitions
 *
 * Revision 1.21  2006/11/08 18:30:54  southa
 * Key and axis configuration
 *
 * Revision 1.20  2006/11/03 18:46:33  southa
 * Damage effectors
 *
 * Revision 1.19  2006/11/02 12:23:22  southa
 * Weapon selection
 *
 * Revision 1.18  2006/08/03 15:07:58  southa
 * Cache purge fix
 *
 * Revision 1.17  2006/07/31 11:01:37  southa
 * Music and dialogues
 *
 * Revision 1.16  2006/07/28 16:52:22  southa
 * Options work
 *
 * Revision 1.15  2006/07/27 13:51:35  southa
 * Menu and control fixes
 *
 * Revision 1.14  2006/07/26 16:37:22  southa
 * Options menu
 *
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
        
        bool permitPurge = true;
        MushcoreScalar textureCachePurge(1);
        if (MushcoreEnv::Sgl().VariableGetIfExists(textureCachePurge, "MUSHGL_TEXTURE_CACHE_PURGE"))
        {
            permitPurge = textureCachePurge.BoolGet();
        }
        if (permitPurge)
        {
            MushGLCacheControl::Sgl().CachePurge();
        }
        
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

const GLModeDef&
MushGameAppHandler::DisplayModeDef(void) const
{
    if (m_currentRef.Exists())
    {
        return m_currentRef.Get()->DisplayModeDef();
    }
    else
    {
        throw MushcoreRequestFail("No mode definition available");
    }
}

void
MushGameAppHandler::PreviousDisplayMode(void)
{
    if (m_currentRef.Exists())
    {
        m_currentRef.Get()->PreviousModeDef();
    }
}

void
MushGameAppHandler::NextDisplayMode(void)
{
    if (m_currentRef.Exists())
    {
        m_currentRef.Get()->NextModeDef();
    }
}

void
MushGameAppHandler::DisplayReset(void)
{
    CurrentSwapOut();
    CurrentSwapIn(m_groupingName);
}

void
MushGameAppHandler::BrightnessSet(Mushware::tVal inValue)
{
    if (m_currentRef.Exists())
    {
        m_currentRef.Get()->BrightnessSet(inValue);
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
        for (U32 j=0; j<m_axisDefs[i].NumUpKeys(); ++j)
        {
            if (m_axisDefs[i].UpKey(j) == inKeyNum) m_axisDefs[i].UpKeySet(0, j);
        }
        for (U32 j=0; j<m_axisDefs[i].NumDownKeys(); ++j)
        {        
            if (m_axisDefs[i].DownKey(j) == inKeyNum) m_axisDefs[i].DownKeySet(0, j);
        }
        // Required keys can be reused so don't get purged
    }
    
    for (U32 i=0; i < m_keyDefs.size(); ++i)
    {
        for (U32 j=0; j<m_keyDefs[i].NumKeyValues(); ++j)
        {
            if (m_keyDefs[i].KeyValue(j) == inKeyNum) m_keyDefs[i].KeyValueSet(0, j);
        }
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
            bool pressed = false;
            for (U32 j=0; j<axisDefRef.NumRequiredKeys(); ++j)
            {
                U32 requiredKey = axisDefRef.RequiredKey(j);
                if (requiredKey != 0 && KeyStateGet(requiredKey))
                {
                    pressed = true;
                }
            }
            if (pressed)
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
            bool upState = false;
            for (U32 j=0; j<axisDefRef.NumUpKeys(); ++j)
            {
                if (KeyStateGet(axisDefRef.UpKey(j)))
                {
                    upState = true;
                }
            }
                    
            bool downState = false;
            for (U32 j=0; j<axisDefRef.NumDownKeys(); ++j)
            {
                if (KeyStateGet(axisDefRef.DownKey(j)))
                {
                    downState = true;
                }
            }
            
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
        
        bool requiredKeysPresent = false;
        for (U32 j=0; j<axisDefRef.NumRequiredKeys(); ++j)
        {
            if (axisDefRef.RequiredKey(j) != 0)
            {
                requiredKeysPresent = true;
            }
        }
        if (axisDefRef.UseDevice() && !requiredKeysPresent)
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
        bool anyKeyDown = false;
        for (U32 j=0; j<m_keyDefs[i].NumKeyValues(); ++j)
        {
            U32 keyValue = keyDefRef.KeyValue(j);
            if (keyValue == MediaKeyboard::kKeyMouse3 ||
                keyValue == MediaKeyboard::kKeyMouse4)
            {
                /* Mouse wheel events are transient and disappear too quickly
                 * to be caught by the ticker.  Since they're always transient
                 * (never 'held down') we can take the latched state to ensure
                 * that the event is reported as a press and immediate release
                 * on the next pass
                 */
                anyKeyDown = anyKeyDown || LatchedKeyStateTake(keyValue);
            }
            else
            {
                anyKeyDown = anyKeyDown || KeyStateGet(keyValue);
            }
        }
        if (anyKeyDown != keyDefRef.State())
        {
            keyDefRef.StateSet(anyKeyDown);
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
//%outOfLineFunctions {

const char *MushGameAppHandler::AutoName(void) const
{
    return "MushGameAppHandler";
}

MushcoreVirtualObject *MushGameAppHandler::AutoClone(void) const
{
    return new MushGameAppHandler(*this);
}

MushcoreVirtualObject *MushGameAppHandler::AutoCreate(void) const
{
    return new MushGameAppHandler;
}

MushcoreVirtualObject *MushGameAppHandler::AutoVirtualFactory(void)
{
    return new MushGameAppHandler;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameAppHandler", MushGameAppHandler::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameAppHandler::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGLAppHandler::AutoPrint(ioOut);
    ioOut << "appState=" << m_appState << ", ";
    ioOut << "currentRef=" << m_currentRef << ", ";
    ioOut << "groupingName=" << m_groupingName << ", ";
    ioOut << "axisDefs=" << m_axisDefs << ", ";
    ioOut << "keyDefs=" << m_keyDefs << ", ";
    ioOut << "lastTickerMsec=" << m_lastTickerMsec << ", ";
    ioOut << "controlMailboxRef=" << m_controlMailboxRef << ", ";
    ioOut << "lastAxesValid=" << m_lastAxesValid << ", ";
    ioOut << "axisNames=" << m_axisNames;
    ioOut << "]";
}
bool
MushGameAppHandler::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "appState")
    {
        ioIn >> m_appState;
    }
    else if (inTagStr == "currentRef")
    {
        ioIn >> m_currentRef;
    }
    else if (inTagStr == "groupingName")
    {
        ioIn >> m_groupingName;
    }
    else if (inTagStr == "axisDefs")
    {
        ioIn >> m_axisDefs;
    }
    else if (inTagStr == "keyDefs")
    {
        ioIn >> m_keyDefs;
    }
    else if (inTagStr == "lastTickerMsec")
    {
        ioIn >> m_lastTickerMsec;
    }
    else if (inTagStr == "controlMailboxRef")
    {
        ioIn >> m_controlMailboxRef;
    }
    else if (inTagStr == "lastAxesValid")
    {
        ioIn >> m_lastAxesValid;
    }
    else if (inTagStr == "axisNames")
    {
        ioIn >> m_axisNames;
    }
    else if (MushGLAppHandler::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameAppHandler::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGLAppHandler::AutoXMLPrint(ioOut);
    ioOut.TagSet("appState");
    ioOut << m_appState;
    ioOut.TagSet("currentRef");
    ioOut << m_currentRef;
    ioOut.TagSet("groupingName");
    ioOut << m_groupingName;
    ioOut.TagSet("axisDefs");
    ioOut << m_axisDefs;
    ioOut.TagSet("keyDefs");
    ioOut << m_keyDefs;
    ioOut.TagSet("lastTickerMsec");
    ioOut << m_lastTickerMsec;
    ioOut.TagSet("controlMailboxRef");
    ioOut << m_controlMailboxRef;
    ioOut.TagSet("lastAxesValid");
    ioOut << m_lastAxesValid;
    ioOut.TagSet("axisNames");
    ioOut << m_axisNames;
}
//%outOfLineFunctions } EN6rf/mfB9F/bV9AIHwa1w
