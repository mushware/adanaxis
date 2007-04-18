//%includeGuardStart {
#ifndef GAMEREG_H
#define GAMEREG_H
//%includeGuardStart } 7ESVWff3zgjU3PTrURBO6w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameReg.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } FaIxglpvatX1RyeVgPVRSg
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
