//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSub.cpp
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
//%Header } CATH0SWEDYlLEzpOYKyxig
/*
 * $Id: TestMushcoreObjectSub.cpp,v 1.8 2006/06/01 15:40:05 southa Exp $
 * $Log: TestMushcoreObjectSub.cpp,v $
 * Revision 1.8  2006/06/01 15:40:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/02 00:42:39  southa
 * Conditioning tweaks
 *
 * Revision 1.6  2005/06/20 14:30:39  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/06/16 17:25:41  southa
 * Client/server work
 *
 * Revision 1.4  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.3  2005/03/25 22:04:51  southa
 * Dialogue and MushcoreIO fixes
 *
 * Revision 1.2  2005/02/10 12:34:24  southa
 * Template fixes
 *
 * Revision 1.1  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreObjectSub.h"

//%outOfLineFunctions {

const char *TestMushcoreObjectSub::AutoName(void) const
{
    return "TestMushcoreObjectSub";
}

MushcoreVirtualObject *TestMushcoreObjectSub::AutoClone(void) const
{
    return new TestMushcoreObjectSub(*this);
}

MushcoreVirtualObject *TestMushcoreObjectSub::AutoCreate(void) const
{
    return new TestMushcoreObjectSub;
}

MushcoreVirtualObject *TestMushcoreObjectSub::AutoVirtualFactory(void)
{
    return new TestMushcoreObjectSub;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("TestMushcoreObjectSub", TestMushcoreObjectSub::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
TestMushcoreObjectSub::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    TestMushcoreObjectBase::AutoPrint(ioOut);
    ioOut << "subObjectValue=" << m_subObjectValue;
    ioOut << "]";
}
bool
TestMushcoreObjectSub::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "subObjectValue")
    {
        ioIn >> m_subObjectValue;
    }
    else if (TestMushcoreObjectBase::AutoXMLDataProcess(ioIn, inTagStr))
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
TestMushcoreObjectSub::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    TestMushcoreObjectBase::AutoXMLPrint(ioOut);
    ioOut.TagSet("subObjectValue");
    ioOut << m_subObjectValue;
}
//%outOfLineFunctions } jKdWMvn2PupKHBpmwbmlAw
