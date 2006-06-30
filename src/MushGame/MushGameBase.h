//%includeGuardStart {
#ifndef MUSHGAMEBASE_H
#define MUSHGAMEBASE_H
//%includeGuardStart } afgqIq2jICH50nW8fCra3Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameBase.h
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
//%Header } auDv5KzHAtGChacJ2aS7ug
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

class MushGameAppHandler;

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
    
private:        
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
operator<<(std::ostream& ioOut, const MushGameBase& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } lbrhaFcTrYU0XBzkSpsC+w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
