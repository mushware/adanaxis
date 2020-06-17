//%includeGuardStart {
#ifndef MUSHGAMEBASE_H
#define MUSHGAMEBASE_H
//%includeGuardStart } afgqIq2jICH50nW8fCra3Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameBase.h
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
//%Header } gNa6R4OsjT1zm3Ee2Ixuug
/*
 * $Id: MushGameBase.h,v 1.9 2006/11/25 21:26:33 southa Exp $
 * $Log: MushGameBase.h,v $
 * Revision 1.9  2006/11/25 21:26:33  southa
 * Display mode definitions
 *
 * Revision 1.8  2006/07/28 16:52:23  southa
 * Options work
 *
 * Revision 1.7  2006/07/28 11:14:28  southa
 * Records for multiple spaces
 *
 * Revision 1.6  2006/07/27 13:51:36  southa
 * Menu and control fixes
 *
 * Revision 1.5  2006/07/26 16:37:23  southa
 * Options menu
 *
 * Revision 1.4  2006/07/12 11:22:42  southa
 * Advanced control menu
 *
 * Revision 1.3  2006/07/07 18:13:58  southa
 * Menu start and stop
 *
 * Revision 1.2  2006/07/04 16:55:27  southa
 * Ruby key handling
 *
 * Revision 1.1  2006/06/30 15:05:35  southa
 * Texture and buffer purge
 *
 */

#include "MushGameStandard.h"

#include "MushGameSaveData.h"
#include "MushGameVolatileData.h"
#include "MushGameClient.h"
#include "MushGameServer.h"
#include "MushGameLogic.h"

class MushGameAppHandler;
class MushGameConfigBase;

//:generate virtual standard ostream xml1
class MushGameBase : public MushcoreVirtualObject
{
public:
    virtual ~MushGameBase() {}
    virtual void Process(MushGameAppHandler& inHandler) {}
    virtual void Display(MushGameAppHandler& inHandler) {}
    virtual void ScriptFunction(const std::string& inName, MushGameAppHandler& inHandler) const {}
    virtual void SwapIn(MushGameAppHandler& inHandler);
    virtual void SwapOut(MushGameAppHandler& inHandler);
    // KeyboardSignal returns true if it consumed the keypress
    virtual bool KeyboardSignal(const GLKeyboardSignal& inSignal, MushGameAppHandler& inHandler);
    virtual void ControlsToDefaultSet(MushGameAppHandler& inHandler);
    virtual MushGameLogic& LogicWRef(void) const { return m_logicRef.WRef(); }
    
    virtual const GLModeDef& DisplayModeDef(void) const;
    virtual void PreviousModeDef(void) {}
    virtual void NextModeDef(void) {}
    virtual void BrightnessSet(Mushware::tVal inValue) {}
    
    virtual const MushGameConfigBase& Config(void) const { throw MushcoreRequestFail("No config available"); }
    virtual MushGameConfigBase& ConfigWRef(void) { throw MushcoreRequestFail("No config available"); }
    virtual bool IsMenuBackdrop(void) const { return false; }
    
private:
    MushcoreDataRef<MushGameSaveData> m_saveDataRef; //:read :wref
    MushcoreDataRef<MushGameVolatileData> m_volatileDataRef; //:read :wref
    MushcoreDataRef<MushGameClient> m_clientRef; //:read :wref
    MushcoreDataRef<MushGameServer> m_serverRef; //:read :wref
    MushcoreDataRef<MushGameLogic> m_logicRef; //:read :wref
    
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameSaveData>& SaveDataRef(void) const { return m_saveDataRef; }
    // Writable reference for m_saveDataRef
    MushcoreDataRef<MushGameSaveData>& SaveDataRefWRef(void) { return m_saveDataRef; }
    const MushcoreDataRef<MushGameVolatileData>& VolatileDataRef(void) const { return m_volatileDataRef; }
    // Writable reference for m_volatileDataRef
    MushcoreDataRef<MushGameVolatileData>& VolatileDataRefWRef(void) { return m_volatileDataRef; }
    const MushcoreDataRef<MushGameClient>& ClientRef(void) const { return m_clientRef; }
    // Writable reference for m_clientRef
    MushcoreDataRef<MushGameClient>& ClientRefWRef(void) { return m_clientRef; }
    const MushcoreDataRef<MushGameServer>& ServerRef(void) const { return m_serverRef; }
    // Writable reference for m_serverRef
    MushcoreDataRef<MushGameServer>& ServerRefWRef(void) { return m_serverRef; }
    const MushcoreDataRef<MushGameLogic>& LogicRef(void) const { return m_logicRef; }
    // Writable reference for m_logicRef
    MushcoreDataRef<MushGameLogic>& LogicRefWRef(void) { return m_logicRef; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } DG4VbAAV5pmYR6lE9IQb2w
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameBase& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } lbrhaFcTrYU0XBzkSpsC+w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
