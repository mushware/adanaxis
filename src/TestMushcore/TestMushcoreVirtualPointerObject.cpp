//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreVirtualPointerObject.cpp
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
//%Header } AVxgEvaNuAD53nB8XOba1w
/*
 * $Id: TestMushcoreVirtualPointerObject.cpp,v 1.8 2006/06/01 15:40:06 southa Exp $
 * $Log: TestMushcoreVirtualPointerObject.cpp,v $
 * Revision 1.8  2006/06/01 15:40:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 * Revision 1.6  2005/07/02 00:42:39  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/06/20 14:30:40  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/16 17:25:41  southa
 * Client/server work
 *
 * Revision 1.3  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.2  2005/02/10 12:34:25  southa
 * Template fixes
 *
 * Revision 1.1  2004/01/18 18:25:30  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreVirtualPointerObject.h"


void
TestMushcoreVirtualPointerObject::PopulateObjects1(void)
{
    DeleteObjects();
    m_basePtr = new TestMushcoreObjectBase;
    m_subPtr = new TestMushcoreObjectSub;
    m_subSubPtr = new TestMushcoreObjectSubSub;
}

void
TestMushcoreVirtualPointerObject::PopulateObjects2(void)
{
    DeleteObjects();
    m_basePtr = new TestMushcoreObjectSubSub;
    m_subPtr = new TestMushcoreObjectSubSub;
    m_subSubPtr = new TestMushcoreObjectSubSub;
}

void
TestMushcoreVirtualPointerObject::DeleteObjects(void)
{
    if (m_basePtr != NULL) { delete m_basePtr; m_basePtr = NULL; }
    if (m_subPtr != NULL) { delete m_subPtr; m_subPtr = NULL; }
    if (m_subSubPtr != NULL) { delete m_subSubPtr; m_subSubPtr = NULL; }
}

//%outOfLineFunctions {

const char *TestMushcoreVirtualPointerObject::AutoName(void) const
{
    return "TestMushcoreVirtualPointerObject";
}

MushcoreVirtualObject *TestMushcoreVirtualPointerObject::AutoClone(void) const
{
    return new TestMushcoreVirtualPointerObject(*this);
}

MushcoreVirtualObject *TestMushcoreVirtualPointerObject::AutoCreate(void) const
{
    return new TestMushcoreVirtualPointerObject;
}

MushcoreVirtualObject *TestMushcoreVirtualPointerObject::AutoVirtualFactory(void)
{
    return new TestMushcoreVirtualPointerObject;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("TestMushcoreVirtualPointerObject", TestMushcoreVirtualPointerObject::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
TestMushcoreVirtualPointerObject::AutoEquals(const TestMushcoreVirtualPointerObject& inObj) const
{
    return 1
        && (m_testValue == inObj.m_testValue)
        && (m_virtualPointerObjectValue == inObj.m_virtualPointerObjectValue)
        && (m_basePtr == inObj.m_basePtr || (m_basePtr != NULL && inObj.m_basePtr != NULL && *m_basePtr == *inObj.m_basePtr))
        && (m_subPtr == inObj.m_subPtr || (m_subPtr != NULL && inObj.m_subPtr != NULL && *m_subPtr == *inObj.m_subPtr))
        && (m_subSubPtr == inObj.m_subSubPtr || (m_subSubPtr != NULL && inObj.m_subSubPtr != NULL && *m_subSubPtr == *inObj.m_subSubPtr))
    ;
}
void
TestMushcoreVirtualPointerObject::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "testValue=" << m_testValue << ", ";
    ioOut << "virtualPointerObjectValue=" << m_virtualPointerObjectValue << ", ";
    if (m_basePtr == NULL)
    {
        ioOut << "basePtr=NULL"  << ", ";
    }
    else
    {
        ioOut << "basePtr=" << *m_basePtr << ", ";
    }
    if (m_subPtr == NULL)
    {
        ioOut << "subPtr=NULL"  << ", ";
    }
    else
    {
        ioOut << "subPtr=" << *m_subPtr << ", ";
    }
    if (m_subSubPtr == NULL)
    {
        ioOut << "subSubPtr=NULL" ;
    }
    else
    {
        ioOut << "subSubPtr=" << *m_subSubPtr;
    }
    ioOut << "]";
}
bool
TestMushcoreVirtualPointerObject::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "testValue")
    {
        ioIn >> m_testValue;
    }
    else if (inTagStr == "virtualPointerObjectValue")
    {
        ioIn >> m_virtualPointerObjectValue;
    }
    else if (inTagStr == "basePtr")
    {
        ioIn >> m_basePtr;
    }
    else if (inTagStr == "subPtr")
    {
        ioIn >> m_subPtr;
    }
    else if (inTagStr == "subSubPtr")
    {
        ioIn >> m_subSubPtr;
    }
    else 
    {
        return false;
    }
    return true;
}
void
TestMushcoreVirtualPointerObject::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("testValue");
    ioOut << m_testValue;
    ioOut.TagSet("virtualPointerObjectValue");
    ioOut << m_virtualPointerObjectValue;
    ioOut.TagSet("basePtr");
    ioOut << m_basePtr;
    ioOut.TagSet("subPtr");
    ioOut << m_subPtr;
    ioOut.TagSet("subSubPtr");
    ioOut << m_subSubPtr;
}
//%outOfLineFunctions } LiYelguxL+/DtcZL24EhWg
