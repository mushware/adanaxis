//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileDirEntry.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } MGQ0Ulmz4XgP1whKx5Pg8w
/*
 * $Id: MushFileDirEntry.cpp,v 1.1 2006/11/06 12:56:32 southa Exp $
 * $Log: MushFileDirEntry.cpp,v $
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
