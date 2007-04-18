//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileDirectory.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } aZccaD7eaim6c8ACjV8WAA
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
