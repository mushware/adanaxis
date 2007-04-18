//%includeGuardStart {
#ifndef MUSHGAMEMESSAGEWAKE_H
#define MUSHGAMEMESSAGEWAKE_H
//%includeGuardStart } Jz51t5OEmj7qYtarwKnYeQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageWake.h
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
//%Header } J34JWnjkNS8E6RJVNJq40g
/*
 * $Id: MushGameMessageWake.h,v 1.3 2006/06/01 15:39:25 southa Exp $
 * $Log: MushGameMessageWake.h,v $
 * Revision 1.3  2006/06/01 15:39:25  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/06/23 11:58:29  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/21 15:57:48  southa
 * MushGame work
 *
 */

#include "MushGameMessage.h"

//:xml1base MushGameMessage
//:generate virtual standard ostream xml1
class MushGameMessageWake : public MushGameMessage
{
public:
    explicit MushGameMessageWake(const std::string& inID = "") : MushGameMessage(inID) {}
    virtual ~MushGameMessageWake() {}

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
operator<<(std::ostream& ioOut, const MushGameMessageWake& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } H6PAY57qM1NuIL1LtDRlBQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
