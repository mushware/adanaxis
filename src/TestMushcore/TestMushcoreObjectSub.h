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
 * $Id: TestMushcoreObjectSub.h,v 1.3 2005/02/10 12:34:24 southa Exp $
 * $Log: TestMushcoreObjectSub.h,v $
 * Revision 1.3  2005/02/10 12:34:24  southa
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

//:xml1base TestMushcoreObjectBase
//:generate virtual standard ostream xml1
class TestMushcoreObjectSub : public TestMushcoreObjectBase
{
public:
    TestMushcoreObjectSub() : m_subObjectValue(2) {}
    virtual ~TestMushcoreObjectSub() {}
    
private:
    Mushware::U32 m_subObjectValue; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& SubObjectValue(void) const { return m_subObjectValue; }
    void SubObjectValueSet(const Mushware::U32& inValue) { m_subObjectValue=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } DKJ/iUTG1jb5YPjlcxpI4A
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const TestMushcoreObjectSub& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } OnTOvSw7d2ebv+9/fZWOCQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
