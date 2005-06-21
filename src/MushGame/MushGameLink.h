//%includeGuardStart {
#ifndef MUSHGAMELINK_H
#define MUSHGAMELINK_H
//%includeGuardStart } eq6oZOrSs0esIGJaMi39ug
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLink.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } XtlsEZ8InVWH+g9tXmyfGg
/*
 * $Id: MushGameLink.h,v 1.3 2005/06/20 16:14:30 southa Exp $
 * $Log: MushGameLink.h,v $
 * Revision 1.3  2005/06/20 16:14:30  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameStandard.h"

#include "MushGameDigest.h"

class MushGameLogic;

//:generate virtual standard ostream xml1
class MushGameLink : public MushcoreVirtualObject
{
public:
    virtual ~MushGameLink() {}
    virtual void MessagesPump(MushGameLogic& ioLogic);
    
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
operator<<(std::ostream& ioOut, const MushGameLink& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } lse6rc6/yrBS2SyQc7d5Hg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
