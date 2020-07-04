//%includeGuardStart {
#ifndef GAMEREG_H
#define GAMEREG_H
//%includeGuardStart } 7ESVWff3zgjU3PTrURBO6w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameReg.h
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
//%Header } BvQRFgC/srrnObMn/JzFHQ
/*
 * $Id: GameReg.h,v 1.5 2006/06/01 15:38:59 southa Exp $
 * $Log: GameReg.h,v $
 * Revision 1.5  2006/06/01 15:38:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.2  2005/04/11 23:31:41  southa
 * Startup and registration screen
 *
 * Revision 1.1  2005/04/10 00:09:22  southa
 * Registration
 *
 */

#include "mushMushcore.h"

#include "GameBase.h"
#include "GameCode.h"

//:generate virtual standard ostream xml1 
class GameReg : public GameBase
{
public:
    GameReg();
    virtual void Process(GameAppHandler& inAppHandler);
    virtual void Display(GameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const;
    virtual void SwapIn(GameAppHandler& inAppHandler);
    virtual void SwapOut(GameAppHandler& inAppHandler);

protected:
    bool CodeVerify(const std::string& inCode);
    void SaveToFile(void);

private:
    typedef enum
    {
        kCodeValidUnknown,
        kCodeValidFail,
        kCodeValidPass,
    } tCodeValid;
    
    std::string m_regURL;
    std::string m_regCode; //:ignore
    Mushware::U32 m_regCodeLength;
    Mushware::U32 m_authValue;
    tCodeValid m_codeValid; //:ignore
    Mushware::tVal m_currentMsec; //:ignore
    Mushware::tVal m_lastCheckMsec; //:ignore

//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const GameReg& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } s/jMBuCeP0yvb7aPzuhwZA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
