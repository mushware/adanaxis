//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECTSUBSUB_H
#define TESTMUSHCOREOBJECTSUBSUB_H
//%includeGuardStart } xOb/gx+IVeWmRjrnLI868Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSubSub.h
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
//%Header } ChZbqo5Xh+H1bQdVOh2LhQ
/*
 * $Id: TestMushcoreObjectSubSub.h,v 1.3 2005/02/10 12:34:25 southa Exp $
 * $Log: TestMushcoreObjectSubSub.h,v $
 * Revision 1.3  2005/02/10 12:34:25  southa
 * Template fixes
 *
 * Revision 1.2  2005/02/03 21:03:13  southa
 * Build fixes
 *
 * Revision 1.1  2004/01/18 18:25:30  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreStandard.h"

#include "TestMushcoreObjectBase.h"
#include "TestMushcoreObjectSub.h"

//:xml1base TestMushcoreObjectSub
//:generate virtual standard basic ostream xml1
class TestMushcoreObjectSubSub : public TestMushcoreObjectSub
{
public:
    TestMushcoreObjectSubSub() : m_subSubObjectValue(3) {}
    virtual ~TestMushcoreObjectSubSub() {}
    
private:
    Mushware::U32 m_subSubObjectValue; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& SubSubObjectValue(void) const { return m_subSubObjectValue; }
    void SubSubObjectValueSet(const Mushware::U32& inValue) { m_subSubObjectValue=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const TestMushcoreObjectSubSub& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } atlwBupO4rzB1mc/K0J4kw
};
//%inlineHeader {

inline bool
operator==(const TestMushcoreObjectSubSub& inA, const TestMushcoreObjectSubSub& inB)
{
    return inA.AutoEquals(inB);
}

inline bool
operator!=(const TestMushcoreObjectSubSub& inA, const TestMushcoreObjectSubSub& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const TestMushcoreObjectSubSub& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 0RuTjVO5A3Iwww+Gr3xMTw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
