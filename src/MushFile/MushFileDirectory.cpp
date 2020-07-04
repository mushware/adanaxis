//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileDirectory.cpp
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
//%Header } bzJpLZxXtr3IIWNqalRmZg
/*
 * $Id: MushFileDirectory.cpp,v 1.4 2006/12/16 10:57:22 southa Exp $
 * $Log: MushFileDirectory.cpp,v $
 * Revision 1.4  2006/12/16 10:57:22  southa
 * Encrypted files
 *
 * Revision 1.3  2006/12/15 14:03:28  southa
 * File key handling
 *
 * Revision 1.2  2006/11/06 19:27:51  southa
 * Mushfile handling
 *
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileDirectory.h"

#include "MushFileAccessor.h"
#include "MushFileKeys.h"

using namespace Mushware;
using namespace std;

MushFileDirectory::MushFileDirectory(const std::string& inFilename) :
    m_filename(inFilename),
    m_loaded(false)
{
}

void
MushFileDirectory::Load(void)
{
    m_entries.clear();
    
    MushFileAccessor accessor(m_filename);
    
    accessor.ChunkDataGet("DIRC");
    while (!accessor.EndOfChunk())
    {
        MushFileDirEntry entry;
        entry.OffsetSet(accessor.NumberRead());
        entry.SizeSet(accessor.NumberRead());
        std::string filename = accessor.StringRead();
        entry.FilenameSet(filename);
        entry.KeyNumSet(accessor.NumberRead());
        accessor.NumberRead(); // Spare
        accessor.NumberRead(); // Spare
        if (m_entries.find(filename) != m_entries.end())
        {
            throw MushcoreFileFail(m_filename, "Duplicate file '"+filename+"' within file");
        }
        m_entries[filename] = entry;
    }
    m_loaded = true;
}

bool
MushFileDirectory::Exists(const std::string& inName)
{
    bool retVal = false;
    if (!m_loaded)
    {
        Load();
    }
    
    tEntries::const_iterator p = m_entries.find(inName);
    
    if (p != m_entries.end())
    {
        // If we don't have the key, the file doesn't exist
        if (MushFileKeys::Sgl().Exists(p->second.KeyNum()))
        {
            retVal = true;
        }
    }
    return retVal;
}

bool
MushFileDirectory::EntryGet(const MushFileDirEntry *& outEntry, const std::string& inName)
{
    if (!m_loaded)
    {
        Load();
    }
    std::map<std::string, MushFileDirEntry>::const_iterator p = m_entries.find(inName);
    
    bool retVal;
    if (p != m_entries.end())
    {
        outEntry = &p->second;
        retVal = true;
    }
    else
    {
        retVal = false;
    }
    return retVal;
}


//%outOfLineFunctions {

const char *MushFileDirectory::AutoName(void) const
{
    return "MushFileDirectory";
}

MushcoreVirtualObject *MushFileDirectory::AutoClone(void) const
{
    return new MushFileDirectory(*this);
}

MushcoreVirtualObject *MushFileDirectory::AutoCreate(void) const
{
    return new MushFileDirectory;
}

MushcoreVirtualObject *MushFileDirectory::AutoVirtualFactory(void)
{
    return new MushFileDirectory;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushFileDirectory", MushFileDirectory::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushFileDirectory::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "filename=" << m_filename << ", ";
    ioOut << "loaded=" << m_loaded << ", ";
    ioOut << "entries=" << m_entries;
    ioOut << "]";
}
bool
MushFileDirectory::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "loaded")
    {
        ioIn >> m_loaded;
    }
    else if (inTagStr == "entries")
    {
        ioIn >> m_entries;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushFileDirectory::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("filename");
    ioOut << m_filename;
    ioOut.TagSet("loaded");
    ioOut << m_loaded;
    ioOut.TagSet("entries");
    ioOut << m_entries;
}
//%outOfLineFunctions } ZO0CUJPbOGQI8jzb3tA4Fg
