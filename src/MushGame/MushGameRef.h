//%includeGuardStart {
#ifndef MUSHGAMEREF_H
#define MUSHGAMEREF_H
//%includeGuardStart } ziI+tP+jl6PLF7Qc1iXfMg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRef.h
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
//%Header } CCxyelf1sKwgxIebswB7qA
/*
 * $Id: MushGameRef.h,v 1.1 2005/06/29 09:07:56 southa Exp $
 * $Log: MushGameRef.h,v $
 * Revision 1.1  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 */

#include "MushGameStandard.h"

#include "MushGamePiece.h"

//:generate virtual standard ostream xml1
class MushGameRef : public MushcoreVirtualObject
{
public:
    virtual ~MushGameRef() {}
    virtual MushcoreVirtualObject& Ref() { throw MushcoreLogicFail("Access to MushGameRef"); }
    
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
operator<<(std::ostream& ioOut, const MushGameRef& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } TQqIyWLcyEOjJQf8C983pA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
