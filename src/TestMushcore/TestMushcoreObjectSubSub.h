//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECTSUBSUB_H
#define TESTMUSHCOREOBJECTSUBSUB_H
//%includeGuardStart } xOb/gx+IVeWmRjrnLI868Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSubSub.h
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
//%Header } h2htd/bfXcT5h9gUxWwzqA
/*
 * $Id: TestMushcoreObjectSubSub.h,v 1.6 2006/06/01 15:40:05 southa Exp $
 * $Log: TestMushcoreObjectSubSub.h,v $
 * Revision 1.6  2006/06/01 15:40:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/06/20 14:30:40  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/05/19 13:02:24  southa
 * Mac release work
 *
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const TestMushcoreObjectSubSub& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } BJzzuhOjKs87h1vqbsnBpA
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
