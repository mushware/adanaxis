//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileDirEntry.cpp
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
//%Header } RLf/+bh5OYWoqJjelFGg7Q
/*
 * $Id: MushFileDirEntry.cpp,v 1.2 2006/12/15 14:03:28 southa Exp $
 * $Log: MushFileDirEntry.cpp,v $
 * Revision 1.2  2006/12/15 14:03:28  southa
 * File key handling
 *
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileDirEntry.h"

//%outOfLineFunctions {

const char *MushFileDirEntry::AutoName(void) const
{
    return "MushFileDirEntry";
}

MushcoreVirtualObject *MushFileDirEntry::AutoClone(void) const
{
    return new MushFileDirEntry(*this);
}

MushcoreVirtualObject *MushFileDirEntry::AutoCreate(void) const
{
    return new MushFileDirEntry;
}

MushcoreVirtualObject *MushFileDirEntry::AutoVirtualFactory(void)
{
    return new MushFileDirEntry;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushFileDirEntry", MushFileDirEntry::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushFileDirEntry::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "filename=" << m_filename << ", ";
    ioOut << "size=" << m_size << ", ";
    ioOut << "offset=" << m_offset << ", ";
    ioOut << "keyNum=" << m_keyNum;
    ioOut << "]";
}
bool
MushFileDirEntry::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "filename")
    {
        ioIn >> m_filename;
    }
    else if (inTagStr == "size")
    {
        ioIn >> m_size;
    }
    else if (inTagStr == "offset")
    {
        ioIn >> m_offset;
    }
    else if (inTagStr == "keyNum")
    {
        ioIn >> m_keyNum;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushFileDirEntry::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("filename");
    ioOut << m_filename;
    ioOut.TagSet("size");
    ioOut << m_size;
    ioOut.TagSet("offset");
    ioOut << m_offset;
    ioOut.TagSet("keyNum");
    ioOut << m_keyNum;
}
//%outOfLineFunctions } LaKJZq3qyqXw+iL0JwwmZA
