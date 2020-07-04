//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAddress.cpp
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
//%Header } e7FDJQWrK5J5beQJkWlC3g
/*
 * $Id: MushGameAddress.cpp,v 1.4 2006/06/01 15:39:19 southa Exp $
 * $Log: MushGameAddress.cpp,v $
 * Revision 1.4  2006/06/01 15:39:19  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 */

#include "MushGameAddress.h"

MushGameAddress::MushGameAddress(const std::string& inName)
{
    NameSet(inName);
}

MUSHCORE_DATA_INSTANCE(MushGameAddress);

//%outOfLineFunctions {

const char *MushGameAddress::AutoName(void) const
{
    return "MushGameAddress";
}

MushcoreVirtualObject *MushGameAddress::AutoClone(void) const
{
    return new MushGameAddress(*this);
}

MushcoreVirtualObject *MushGameAddress::AutoCreate(void) const
{
    return new MushGameAddress;
}

MushcoreVirtualObject *MushGameAddress::AutoVirtualFactory(void)
{
    return new MushGameAddress;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameAddress", MushGameAddress::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameAddress::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "name=" << m_name << ", ";
    ioOut << "linkRef=" << m_linkRef;
    ioOut << "]";
}
bool
MushGameAddress::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "name")
    {
        ioIn >> m_name;
    }
    else if (inTagStr == "linkRef")
    {
        ioIn >> m_linkRef;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameAddress::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("name");
    ioOut << m_name;
    ioOut.TagSet("linkRef");
    ioOut << m_linkRef;
}
//%outOfLineFunctions } 8488INjjijNtkp47lRQewg
