//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSubSub.cpp
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
//%Header } m8wLPDJwzgSUkd46x0CvDQ
/*
 * $Id: TestMushcoreObjectSubSub.cpp,v 1.7 2006/06/01 15:40:05 southa Exp $
 * $Log: TestMushcoreObjectSubSub.cpp,v $
 * Revision 1.7  2006/06/01 15:40:05  southa
 * DrawArray verification and fixes
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
 * Revision 1.2  2005/02/10 12:34:24  southa
 * Template fixes
 *
 * Revision 1.1  2004/01/18 18:25:30  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreObjectSubSub.h"

//%outOfLineFunctions {

const char *TestMushcoreObjectSubSub::AutoName(void) const
{
    return "TestMushcoreObjectSubSub";
}

MushcoreVirtualObject *TestMushcoreObjectSubSub::AutoClone(void) const
{
    return new TestMushcoreObjectSubSub(*this);
}

MushcoreVirtualObject *TestMushcoreObjectSubSub::AutoCreate(void) const
{
    return new TestMushcoreObjectSubSub;
}

MushcoreVirtualObject *TestMushcoreObjectSubSub::AutoVirtualFactory(void)
{
    return new TestMushcoreObjectSubSub;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("TestMushcoreObjectSubSub", TestMushcoreObjectSubSub::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
TestMushcoreObjectSubSub::AutoEquals(const TestMushcoreObjectSubSub& inObj) const
{
    return 1
        && TestMushcoreObjectSub::AutoEquals(inObj)
        && (m_subSubObjectValue == inObj.m_subSubObjectValue)
    ;
}
void
TestMushcoreObjectSubSub::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    TestMushcoreObjectSub::AutoPrint(ioOut);
    ioOut << "subSubObjectValue=" << m_subSubObjectValue;
    ioOut << "]";
}
bool
TestMushcoreObjectSubSub::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "subSubObjectValue")
    {
        ioIn >> m_subSubObjectValue;
    }
    else if (TestMushcoreObjectSub::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
TestMushcoreObjectSubSub::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    TestMushcoreObjectSub::AutoXMLPrint(ioOut);
    ioOut.TagSet("subSubObjectValue");
    ioOut << m_subSubObjectValue;
}
//%outOfLineFunctions } WjnZxyeFgv033VVqckJPCw
