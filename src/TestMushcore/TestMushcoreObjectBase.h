//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECTBASE_H
#define TESTMUSHCOREOBJECTBASE_H
//%includeGuardStart } zXDC6OmtG42fwXa0J4rlSw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectBase.h
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
//%Header } v/ws9iVRmcWhHbNnytTwmA
/*
 * $Id: TestMushcoreObjectBase.h,v 1.6 2006/06/01 15:40:05 southa Exp $
 * $Log: TestMushcoreObjectBase.h,v $
 * Revision 1.6  2006/06/01 15:40:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/06/20 14:30:39  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:23  southa
 * Template fixes
 *
 * Revision 1.2  2005/02/03 21:03:13  southa
 * Build fixes
 *
 * Revision 1.1  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreStandard.h"

//:generate virtual standard basic ostream xml1
class TestMushcoreObjectBase : public MushcoreVirtualObject
{
public:
    TestMushcoreObjectBase() : m_baseObjectValue(1) {}
    virtual ~TestMushcoreObjectBase() {}

private:
    Mushware::U32 m_baseObjectValue; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& BaseObjectValue(void) const { return m_baseObjectValue; }
    void BaseObjectValueSet(const Mushware::U32& inValue) { m_baseObjectValue=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const TestMushcoreObjectBase& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } OdpduZvemRzN2mhi+tZa7A
};
//%inlineHeader {

inline bool
operator==(const TestMushcoreObjectBase& inA, const TestMushcoreObjectBase& inB)
{
    return inA.AutoEquals(inB);
}

inline bool
operator!=(const TestMushcoreObjectBase& inA, const TestMushcoreObjectBase& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const TestMushcoreObjectBase& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 3j7uzSFlr6k9mizGYDUjRw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
