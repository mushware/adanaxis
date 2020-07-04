//%includeGuardStart {
#ifndef TESTMUSHCOREVIRTUALPOINTEROBJECT_H
#define TESTMUSHCOREVIRTUALPOINTEROBJECT_H
//%includeGuardStart } A6gr1bO23FkbXqc8xgtG3Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreVirtualPointerObject.h
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
//%Header } q6q+u9AuuLW2ri8ky0qaNA
/*
 * $Id: TestMushcoreVirtualPointerObject.h,v 1.7 2006/06/01 15:40:06 southa Exp $
 * $Log: TestMushcoreVirtualPointerObject.h,v $
 * Revision 1.7  2006/06/01 15:40:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 * Revision 1.5  2005/06/20 14:30:40  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/05/19 13:02:25  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:26  southa
 * Template fixes
 *
 * Revision 1.2  2005/02/03 21:03:14  southa
 * Build fixes
 *
 * Revision 1.1  2004/01/18 18:25:30  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreStandard.h"

#include "TestMushcoreObjectBase.h"
#include "TestMushcoreObjectSub.h"
#include "TestMushcoreObjectSubSub.h"

//:generate virtual standard basic ostream xml1
class TestMushcoreVirtualPointerObject : public MushcoreVirtualObject
{
public:
    TestMushcoreVirtualPointerObject() :
        m_virtualPointerObjectValue(10),
        m_basePtr(NULL),
        m_subPtr(NULL),
        m_subSubPtr(NULL)
        {}
    
    void PopulateObjects1(void);
    void PopulateObjects2(void);
    void DeleteObjects(void);
    
    virtual ~TestMushcoreVirtualPointerObject() { DeleteObjects(); }
    
private:
    Mushware::U32 m_testValue; //:readwrite
    Mushware::U32 m_virtualPointerObjectValue; //:readwrite
    TestMushcoreObjectBase *m_basePtr;
    TestMushcoreObjectSub *m_subPtr;
    TestMushcoreObjectSubSub *m_subSubPtr;
//%classPrototypes {
public:
    const Mushware::U32& TestValue(void) const { return m_testValue; }
    void TestValueSet(const Mushware::U32& inValue) { m_testValue=inValue; }
    const Mushware::U32& VirtualPointerObjectValue(void) const { return m_virtualPointerObjectValue; }
    void VirtualPointerObjectValueSet(const Mushware::U32& inValue) { m_virtualPointerObjectValue=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const TestMushcoreVirtualPointerObject& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } XqHxlMiqOQt0hvgOq0TOsw
};
//%inlineHeader {

inline bool
operator==(const TestMushcoreVirtualPointerObject& inA, const TestMushcoreVirtualPointerObject& inB)
{
    return inA.AutoEquals(inB);
}

inline bool
operator!=(const TestMushcoreVirtualPointerObject& inA, const TestMushcoreVirtualPointerObject& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const TestMushcoreVirtualPointerObject& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } fjxQ0pKCxxXKAXpc/kMFGw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
