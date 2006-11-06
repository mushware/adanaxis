//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileLibrary.cpp
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
//%Header } c3ylueSV/lJwBs7EptLXFQ
/*
 * $Id$
 * $Log$
 */

#include "MushFileLibrary.h"

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
