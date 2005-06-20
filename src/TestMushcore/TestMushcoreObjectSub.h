//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECTSUB_H
#define TESTMUSHCOREOBJECTSUB_H
//%includeGuardStart } YhFQVmT3N+jKWLjzvpw11Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSub.h
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
//%Header } x9hluL6ZFcAi9PglYClnbA
/*
 * $Id: TestMushcoreObjectSub.h,v 1.5 2005/05/19 13:02:24 southa Exp $
 * $Log: TestMushcoreObjectSub.h,v $
 * Revision 1.5  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.4  2005/03/25 22:04:51  southa
 * Dialogue and MushcoreIO fixes
 *
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } BcmLPI73fiB95KGMmZEE5A
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
