//%includeGuardStart {
#ifndef MUSHGAMEAPPHANDLER_H
#define MUSHGAMEAPPHANDLER_H
//%includeGuardStart } 7ZwYn7TuuYmYE/eLrNwCTw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAppHandler.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } J5LmsZ2/mJXlbw2zq64+qw
/*
 * $Id: MushGameAppHandler.h,v 1.17 2007/04/18 09:22:38 southa Exp $
 * $Log: MushGameAppHandler.h,v $
 * Revision 1.17  2007/04/18 09:22:38  southa
 * Header and level fixes
 *
 * Revision 1.16  2006/11/25 21:26:32  southa
 * Display mode definitions
 *
 * Revision 1.15  2006/07/31 11:01:38  southa
 * Music and dialogues
 *
 * Revision 1.14  2006/07/28 16:52:23  southa
 * Options work
 *
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

//:xml1base MushGLAppHandler
//:generate virtual standard ostream xml1
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
    virtual const GLModeDef& DisplayModeDef(void) const;
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
    
    virtual void Initialise(void);
    virtual void CurrentSwapOut(void);
    virtual void CurrentSwapIn(const std::string& inName);
    
    virtual void AxisFromDeviceUpdate(MushGameAxisDef& ioAxisDef, Mushware::tVal inAmount);
    virtual void AxisTicker(Mushware::tMsec inTimeslice);    
    virtual void KeyTicker(Mushware::tMsec inTimeslice);    
    virtual void FillControlPipe(void);
    virtual void KeyboardSignal(const GLKeyboardSignal& inSignal);
    
    virtual void NewGameCreate(const std::string& inName);
    
private:
    Mushware::U32 m_appState; //:readwrite
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
    const Mushware::U32& AppState(void) const { return m_appState; }
    void AppStateSet(const Mushware::U32& inValue) { m_appState=inValue; }
    const MushcoreDataRef<MushGameMailbox>& ControlMailboxRef(void) const { return m_controlMailboxRef; }
    const bool& LastAxesValid(void) const { return m_lastAxesValid; }
    void LastAxesValidSet(const bool& inValue) { m_lastAxesValid=inValue; }
    const std::string& AxisNames(void) const { return m_axisNames; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } nIzuZaPHaypGXCmfgM9bww
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameAppHandler& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } hHDQl74WSvqQu3Oe6JxiMA

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
