//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECTSUB_H
#define TESTMUSHCOREOBJECTSUB_H
//%includeGuardStart } YhFQVmT3N+jKWLjzvpw11Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSub.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Y0F9VWYPGKbq2uYK6oeomA
/*
 * $Id$
 * $Log$
 */

#include "TestMushcoreStandard.h"

#include "TestMushcoreObjectBase.h"

//:xml1base TestMushcoreObjectBase
//:generate standard basic ostream xml1
class TestMushcoreObjectSub : public TestMushcoreObjectBase
{
public:
    TestMushcoreObjectSub() : m_subObjectValue(2) {}
    virtual ~TestMushcoreObjectSub() {}
    
private:
    Mushware::U32 m_subObjectValue; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& SubObjectValueGet(void) const { return m_subObjectValue; }
    void SubObjectValueSet(const Mushware::U32& inValue) { m_subObjectValue=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual TestMushcoreObjectSub *AutoClone(void) const;
    virtual TestMushcoreObjectSub *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const TestMushcoreObjectSub& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } axTW5khBmmqYf9bYtB5ScQ
};
//%inlineHeader {
inline bool
operator==(const TestMushcoreObjectSub& inA, const TestMushcoreObjectSub& inB)
{
    return inA.AutoEquals(inB);
}
inline bool
operator!=(const TestMushcoreObjectSub& inA, const TestMushcoreObjectSub& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const TestMushcoreObjectSub& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 6EGqVHq6mByjU17P1jJh3A
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
