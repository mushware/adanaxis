//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileLibrary.cpp
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
//%Header } x7/Z4FdjiioErIx4ycmNyQ
/*
 * $Id: MushFileLibrary.cpp,v 1.2 2006/11/06 19:27:52 southa Exp $
 * $Log: MushFileLibrary.cpp,v $
 * Revision 1.2  2006/11/06 19:27:52  southa
 * Mushfile handling
 *
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileLibrary.h"

#include "MushFileAccessor.h"

MUSHCORE_SINGLETON_INSTANCE(MushFileLibrary);

using namespace Mushware;
using namespace std;

void
MushFileLibrary::LibraryAdd(const std::string& inFilename)
{
    bool alreadyPresent = false;
    
    for (U32 i=0; i<m_directories.size(); ++i)
    {
        if (m_directories[i].Filename() == inFilename)
        {
            alreadyPresent = true;
        }
    }
    
    if (!alreadyPresent)
    {
        m_directories.push_back(MushFileDirectory(inFilename));
        m_directories.back().Load();
    }
}

bool
MushFileLibrary::Exists(const std::string& inName)
{
    bool found = false;
    for (U32 i=0; i<m_directories.size(); ++i)
    {
        if (m_directories[i].Exists(inName))
        {
            if (found)
            {
                MushcoreLog::Sgl().WarningLog() << "File '" << inName << "' appears in more than one mushfile.  Using " <<
                    m_directories[i].Filename() << " so far" << endl;
            }
            found = true;
        }
    }
            
    return found;
}

void
MushFileLibrary::Load(std::vector<Mushware::U8>& outData, const std::string& inName)
{
    const MushFileDirEntry *pEntry = NULL;
    std::string mushFilename;
    
    for (U32 i=0; i<m_directories.size(); ++i)
    {
        if (m_directories[i].EntryGet(pEntry, inName))
        {
            mushFilename = m_directories[i].Filename();
        }
        
    }
    
    if (pEntry == NULL)
    {
        throw MushcoreFileFail(inName, "File not found within any mushfile");
    }

    MushFileAccessor accessor(mushFilename);
    
    accessor.LoadData(outData, *pEntry);
}

//%outOfLineFunctions {

const char *MushFileLibrary::AutoName(void) const
{
    return "MushFileLibrary";
}

MushcoreVirtualObject *MushFileLibrary::AutoClone(void) const
{
    return new MushFileLibrary(*this);
}

MushcoreVirtualObject *MushFileLibrary::AutoCreate(void) const
{
    return new MushFileLibrary;
}

MushcoreVirtualObject *MushFileLibrary::AutoVirtualFactory(void)
{
    return new MushFileLibrary;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushFileLibrary", MushFileLibrary::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushFileLibrary::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "directories=" << m_directories;
    ioOut << "]";
}
bool
MushFileLibrary::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "directories")
    {
        ioIn >> m_directories;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushFileLibrary::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("directories");
    ioOut << m_directories;
}
//%outOfLineFunctions } qm+WyJ0j8TzqnZs2NU0VRQ
