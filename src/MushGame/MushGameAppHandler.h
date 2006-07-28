//%includeGuardStart {
#ifndef MUSHGAMEAPPHANDLER_H
#define MUSHGAMEAPPHANDLER_H
//%includeGuardStart } 7ZwYn7TuuYmYE/eLrNwCTw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAppHandler.h
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
//%Header } rqKVCOMdajoYPgaQgbClmg
/*
 * $Id: MushGameAppHandler.h,v 1.13 2006/07/27 13:51:35 southa Exp $
 * $Log: MushGameAppHandler.h,v $
 * Revision 1.13  2006/07/27 13:51:35  southa
 * Menu and control fixes
 *
 * Revision 1.12  2006/07/26 16:37:23  southa
 * Options menu
 *
 * Revision 1.11  2006/07/12 11:22:41  southa
 * Advanced control menu
 *
 * Revision 1.10  2006/07/11 19:49:05  southa
 * Control menu
 *
 * Revision 1.9  2006/07/10 16:01:19  southa
 * Control menu work
 *
 * Revision 1.8  2006/07/07 18:13:58  southa
 * Menu start and stop
 *
 * Revision 1.7  2006/06/30 15:05:34  southa
 * Texture and buffer purge
 *
 * Revision 1.6  2006/06/01 15:39:20  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/08/05 10:33:33  southa
 * win32 build fixes
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

#include "MushGameStandard.h"

#include "MushGameAxisDef.h"
#include "MushGameBase.h"
#include "MushGameConfigBase.h"
#include "MushGameKeyDef.h"
#include "MushGameMailbox.h"

#include "API/mushGame.h"

//:generate
class MushGameAppHandler : public MushGLAppHandler
{
public:
    MushGameAppHandler(const std::string& inName = "");
    
    virtual void Display(void);
    virtual void Idle(void);
    virtual void GameIdle(void);
    virtual void QuitStateEnter(void);
    virtual void GameRestart(void);
    virtual void ControlsToDefaultSet(void); // Override this

    virtual void GroupingNameSet(const std::string& inName);
    virtual const MushGameAxisDef& AxisDef(Mushware::U32 inAxisNum) const;
    virtual const MushGameKeyDef& KeyDef(Mushware::U32 inKeyNum) const;
    virtual MushGameAxisDef& AxisDefWRef(Mushware::U32 inAxisNum);
    virtual MushGameKeyDef& KeyDefWRef(Mushware::U32 inKeyNum);
    virtual void AxisDefSet(const MushGameAxisDef& inAxisDef, Mushware::U32 inAxisNum);
    virtual void KeyDefSet(const MushGameKeyDef& inKeyDef, Mushware::U32 inKeyNum);
    virtual void AxisPurge(Mushware::U32 inDeviceNum, Mushware::U32 inAxisNum);
    virtual void KeyPurge(Mushware::U32 inKeyNum);
    virtual Mushware::U32 DisplayModeNum(void) const;
    virtual void PreviousDisplayMode(void);
    virtual void NextDisplayMode(void);
    virtual void DisplayReset(void);
    virtual void BrightnessSet(Mushware::tVal inValue);
    
    virtual MushGameLogic& LogicWRef(void) const { return m_currentRef.Ref().LogicWRef(); }
    virtual const MushGameConfigBase& Config(void) const { return m_currentRef.Ref().Config(); }
    virtual MushGameConfigBase& ConfigWRef(void) const { return m_currentRef.WRef().ConfigWRef(); }
    
protected:
    enum tAppState
    {
        kAppStateInvalid,
        kAppStateStartup,
        kAppStateRunning,
        kAppStateQuitting
    };
    
    virtual void CurrentSwapOut(void);
    virtual void CurrentSwapIn(const std::string& inName);
    
    virtual void AxisFromDeviceUpdate(MushGameAxisDef& ioAxisDef, Mushware::tVal inAmount);
    virtual void AxisTicker(Mushware::tMsec inTimeslice);    
    virtual void KeyTicker(Mushware::tMsec inTimeslice);    
    virtual void FillControlPipe(void);
    virtual void KeyboardSignal(const GLKeyboardSignal& inSignal);
    
    virtual void NewGameCreate(const std::string& inName);
    
private:
    tAppState m_appState; //:readwrite
    MushcoreDataRef<MushGameBase> m_currentRef;
    
    std::string m_groupingName;
    std::vector<MushGameAxisDef> m_axisDefs;
    std::vector<MushGameKeyDef> m_keyDefs;
    Mushware::tMsec m_lastTickerMsec;
    MushcoreDataRef<MushGameMailbox> m_controlMailboxRef; //:read
    bool m_lastAxesValid; //:readwrite
    std::string m_axisNames; //:read
    
//%classPrototypes {
public:
    const tAppState& AppState(void) const { return m_appState; }
    void AppStateSet(const tAppState& inValue) { m_appState=inValue; }
    const MushcoreDataRef<MushGameMailbox>& ControlMailboxRef(void) const { return m_controlMailboxRef; }
    const bool& LastAxesValid(void) const { return m_lastAxesValid; }
    void LastAxesValidSet(const bool& inValue) { m_lastAxesValid=inValue; }
    const std::string& AxisNames(void) const { return m_axisNames; }
//%classPrototypes } 6gtVEQp10KpMF0xzAPw9xQ
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
