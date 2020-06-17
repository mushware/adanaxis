//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECTSUB_H
#define TESTMUSHCOREOBJECTSUB_H
//%includeGuardStart } YhFQVmT3N+jKWLjzvpw11Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSub.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } hBb/w9fJqGzzQgbabuCR4A
/*
 * $Id: TestMushcoreObjectSub.h,v 1.7 2006/06/01 15:40:05 southa Exp $
 * $Log: TestMushcoreObjectSub.h,v $
 * Revision 1.7  2006/06/01 15:40:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/06/20 14:30:40  southa
 * Adanaxis work
 *
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
