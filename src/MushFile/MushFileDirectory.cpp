//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileDirectory.cpp
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
//%Header } w7E0fT2jMm6nn3HLuj+ttQ
/*
 * $Id$
 * $Log$
 */

#include "MushFileDirectory.h"

#include "MushFileAccessor.h"

using namespace Mushware;
using namespace std;

MushFileDirectory::MushFileDirectory(const std::string& inFilename) :
    m_filename(inFilename)
{
}

void
MushFileDirectory::Load(void)
{
    MushFileAccessor accessor(m_filename);
    m_dataOffset = accessor.ChunkBaseGet("DATA");
    MushcoreLog::Sgl().XMLInfoLog() << accessor;
    
    std::vector<U8> dirData;
    accessor.ChunkDataGet(dirData, "DIRC");
    cout << "data=" << dirData << endl;
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
    ioOut << "entries=" << m_entries << ", ";
    ioOut << "dataOffset=" << m_dataOffset;
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
    else if (inTagStr == "entries")
    {
        ioIn >> m_entries;
    }
    else if (inTagStr == "dataOffset")
    {
        ioIn >> m_dataOffset;
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
    ioOut.TagSet("entries");
    ioOut << m_entries;
    ioOut.TagSet("dataOffset");
    ioOut << m_dataOffset;
}
//%outOfLineFunctions } eL7cyFXJByfmTiRt3y0uUg
