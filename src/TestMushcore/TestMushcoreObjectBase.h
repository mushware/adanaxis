//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECTBASE_H
#define TESTMUSHCOREOBJECTBASE_H
//%includeGuardStart } zXDC6OmtG42fwXa0J4rlSw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectBase.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Sz6r4LjP+pJHGm8/heQ+DQ
/*
 * $Id: TestMushcoreObjectBase.h,v 1.1 2004/01/18 18:25:29 southa Exp $
 * $Log: TestMushcoreObjectBase.h,v $
 * Revision 1.1  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreStandard.h"

//:generate standard basic ostream xml1
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
    virtual const char *AutoNameGet(void) const;
    virtual TestMushcoreObjectBase *AutoClone(void) const;
    virtual TestMushcoreObjectBase *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const TestMushcoreObjectBase& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } QWGStK4DSDujT1IwHCKV/Q
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
