//%includeGuardStart {
#ifndef MUSHGAMEADDRESS_H
#define MUSHGAMEADDRESS_H
//%includeGuardStart } L8/7BLdqwh1+COyQm5NWvw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAddress.h
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
//%Header } iS+4snq1fCZHJspcXX7qxg
/*
 * $Id: MushGameAddress.h,v 1.2 2005/06/23 11:58:28 southa Exp $
 * $Log: MushGameAddress.h,v $
 * Revision 1.2  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 */

#include "MushGameStandard.h"

class MushGameLink;

//:generate virtual standard ostream xml1
class MushGameAddress : public MushcoreVirtualObject
{
public:
    MushGameAddress() {}
    explicit MushGameAddress(const std::string& inName);
    virtual ~MushGameAddress() {}
    const std::string& Name(void) const { return m_name; }
    virtual void NameSet(const std::string& inValue) { m_name=inValue; m_linkRef.NameSet(m_name); }
    
private:
    std::string m_name;
    MushcoreDataRef<MushGameLink> m_linkRef; //:readwrite :wref

//%classPrototypes {
public:
    const MushcoreDataRef<MushGameLink>& LinkRef(void) const { return m_linkRef; }
    void LinkRefSet(const MushcoreDataRef<MushGameLink>& inValue) { m_linkRef=inValue; }
    // Writable reference for m_linkRef
    MushcoreDataRef<MushGameLink>& LinkRefWRef(void) { return m_linkRef; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } M40yAD0sQnsx4C7/XGw2AQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameAddress& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } hRmbmkNx+6bS+4XgtVFp+Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
