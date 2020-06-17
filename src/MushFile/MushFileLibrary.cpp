//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileLibrary.cpp
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
//%Header } fUgW2n8PkxeieYxwAa/fKQ
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
