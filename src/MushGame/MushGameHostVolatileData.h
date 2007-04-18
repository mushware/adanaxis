//%includeGuardStart {
#ifndef MUSHGAMEHOSTVOLATILEDATA_H
#define MUSHGAMEHOSTVOLATILEDATA_H
//%includeGuardStart } iqIxhs1tXIDVjt4TfDsZow
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameHostVolatileData.h
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
//%Header } ql+EmkwAVzd8wjaeHLXVsQ
/*
 * $Id: MushGameHostVolatileData.h,v 1.3 2006/06/01 15:39:22 southa Exp $
 * $Log: MushGameHostVolatileData.h,v $
 * Revision 1.3  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/11 14:48:46  southa
 * Uplink work
 *
 * Revision 1.1  2005/06/21 15:57:47  southa
 * MushGame work
 *
 */

#include "MushGameStandard.h"

//:generate virtual standard ostream xml1
class MushGameHostVolatileData : public MushcoreVirtualObject
{
public:
    MushGameHostVolatileData();
    virtual ~MushGameHostVolatileData() {}
    virtual void GroupingNameSet(const std::string& inName) {}

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
operator<<(std::ostream& ioOut, const MushGameHostVolatileData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } ZDxRA8ZiE41if3GELxbxgQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
