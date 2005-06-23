//%includeGuardStart {
#ifndef MUSHGAMEHOSTSAVEDATA_H
#define MUSHGAMEHOSTSAVEDATA_H
//%includeGuardStart } j9WC99Joapgyyf6ZJO818A
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameHostSaveData.h
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
//%Header } KJPGwB9vha6Uq1oSN1g5gg
/*
 * $Id: MushGameHostSaveData.h,v 1.2 2005/06/22 20:01:58 southa Exp $
 * $Log: MushGameHostSaveData.h,v $
 * Revision 1.2  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/21 15:57:47  southa
 * MushGame work
 *
 */

#include "MushGameStandard.h"

#include "MushGameAddress.h"

//:generate virtual standard ostream xml1
class MushGameHostSaveData : public MushcoreVirtualObject
{
public:
    typedef std::vector< MushcoreDataRef<MushGameAddress> > tClientAddrRefs;
    
    MushGameHostSaveData();
    virtual ~MushGameHostSaveData() {}
    virtual void GroupingNameSet(const std::string& inName) {}
    
private:
    tClientAddrRefs m_clientAddrRefs; //:readwrite :wref

//%classPrototypes {
public:
    const tClientAddrRefs& ClientAddrRefs(void) const { return m_clientAddrRefs; }
    void ClientAddrRefsSet(const tClientAddrRefs& inValue) { m_clientAddrRefs=inValue; }
    // Writable reference for m_clientAddrRefs
    tClientAddrRefs& ClientAddrRefsWRef(void) { return m_clientAddrRefs; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } lwIQEhwsqHTrFOihN1IeGQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameHostSaveData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } B6IOtWAQqmeuE/0ZprefTQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
