//%includeGuardStart {
#ifndef GAMEREG_H
#define GAMEREG_H
//%includeGuardStart } 7ESVWff3zgjU3PTrURBO6w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameReg.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } OAqNOiLKaXeT868OyOk4iw
/*
 * $Id$
 * $Log$
 */

#include "mushMushcore.h"

#include "GameBase.h"

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
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } FwEN8XJox/Ejr30NeyHzCg
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
