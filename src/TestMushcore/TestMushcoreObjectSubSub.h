//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECTSUBSUB_H
#define TESTMUSHCOREOBJECTSUBSUB_H
//%includeGuardStart } xOb/gx+IVeWmRjrnLI868Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSubSub.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ebT8Z6FXlkdJnQOv6a9uvQ
/*
 * $Id$
 * $Log$
 */

#include "TestMushcoreStandard.h"

#include "TestMushcoreObjectBase.h"
#include "TestMushcoreObjectSub.h"

//:xml1base TestMushcoreObjectSub
//:generate standard basic ostream xml1
class TestMushcoreObjectSubSub : public TestMushcoreObjectSub
{
public:
    TestMushcoreObjectSubSub() : m_subSubObjectValue(3) {}
    virtual ~TestMushcoreObjectSubSub() {}
    
private:
    Mushware::U32 m_subSubObjectValue; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& SubSubObjectValueGet(void) const { return m_subSubObjectValue; }
    void SubSubObjectValueSet(const Mushware::U32& inValue) { m_subSubObjectValue=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual TestMushcoreObjectSubSub *AutoClone(void) const;
    virtual TestMushcoreObjectSubSub *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const TestMushcoreObjectSubSub& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } k8yMTcKUDrgaa74nYXE4+A
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
