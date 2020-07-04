//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECTBASE_H
#define TESTMUSHCOREOBJECTBASE_H
//%includeGuardStart } zXDC6OmtG42fwXa0J4rlSw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectBase.h
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
//%Header } eLq8bdky8b1OaE4d4bVqnA
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
