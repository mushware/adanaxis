//%includeGuardStart {
#ifndef MAURHEENGAME_H
#define MAURHEENGAME_H
//%includeGuardStart } PJDNvu01wwB43OSvfrDDlA
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenGame.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } PPS/HIYTNx/xF3BnuxBKdQ
/*
 * $Id$
 * $Log$
 */

#include "mushMushcore.h"
#include "mushGame.h"
#include "mushGL.h"

//:generate standard xml1 ostream
class MaurheenGame : public GameBase
{
public:
    MaurheenGame();
    virtual ~MaurheenGame();
    virtual void Process(GameAppHandler& inAppHandler);
    virtual void Display(GameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const;
    virtual void SwapIn(GameAppHandler& inAppHandler);
    virtual void SwapOut(GameAppHandler& inAppHandler);
    
    static MushcoreScalar MaurheenLoadGame(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
protected:    
private:
        
//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual MaurheenGame *AutoClone(void) const;
    virtual MaurheenGame *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } uwtJ7cbGh16AtQbbRliYrg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MaurheenGame& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } J9a4pcj4v7Z1RrYy6lz3BQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
