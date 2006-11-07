//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileFilename.cpp
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
//%Header } JW5WNz3kt0Z9OBpLQy+gCQ
/*
 * $Id: MushFileFilename.cpp,v 1.2 2006/11/06 19:27:51 southa Exp $
 * $Log: MushFileFilename.cpp,v $
 * Revision 1.2  2006/11/06 19:27:51  southa
 * Mushfile handling
 *
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */


#include "MushFileFilename.h"

#include "MushFileLibrary.h"

using namespace Mushware;
using namespace std;

MushFileFilename::MushFileFilename(const std::string& inName) :
    m_name(inName),
    m_resolved(false),
    m_sourceType(MushFile::kSourceTypeInvalid)
{
}

void
MushFileFilename::AssertResolved(void)
{
    if (!m_resolved)
    {
        throw MushcoreRequestFail("MushFileFilename not resolved before access");
    }
}

void
MushFileFilename::SplitNames(std::vector<std::string>& outNames, const std::string& inName)
{
    outNames.clear();
    std::string::size_type startPos = 0;
    std::string::size_type endPos = 0;
    
    while (endPos != std::string::npos)
    {
        endPos = inName.find("|", startPos);
        outNames.push_back(inName.substr(startPos, endPos - startPos));
        startPos = endPos+1;
    }
}

void
MushFileFilename::ResolveForRead(void)
{
    std::vector<std::string> filenames;
    SplitNames(filenames, m_name);
    m_sourceType = MushFile::kSourceTypeNone;
    for (U32 i=0; i<filenames.size() && m_sourceType == MushFile::kSourceTypeNone; ++i)
    {
        if (filenames[i].substr(0, 5) == "mush:")
        {
            U32 startPos = 5;
            if (filenames[i].substr(5, 2) == "//")
            {
                startPos = 7;
            }
            if (MushFileLibrary::Sgl().Exists(filenames[i].substr(startPos)))
            {
                m_resolvedName = filenames[i].substr(startPos);
                m_sourceType = MushFile::kSourceTypeMush;
            }
        }
        else
        {
            FILE *file = fopen(filenames[i].c_str(), "rb");
            if (file != NULL)
            {
                std::fclose(file);
                m_resolvedName = filenames[i];
                m_sourceType = MushFile::kSourceTypeFile;
            }
        }
    }
    m_resolved = true;
}

bool
MushFileFilename::SourceIsFile(void)
{
    AssertResolved();
    return (m_sourceType == MushFile::kSourceTypeFile);
}

bool
MushFileFilename::SourceIsMush(void)
{
    AssertResolved();
    return (m_sourceType == MushFile::kSourceTypeMush);
}

bool
MushFileFilename::SourceExists(void)
{
    AssertResolved();
    return (m_sourceType == MushFile::kSourceTypeMush || m_sourceType == MushFile::kSourceTypeFile);
}

//%outOfLineFunctions {

const char *MushFileFilename::AutoName(void) const
{
    return "MushFileFilename";
}

MushcoreVirtualObject *MushFileFilename::AutoClone(void) const
{
    return new MushFileFilename(*this);
}

MushcoreVirtualObject *MushFileFilename::AutoCreate(void) const
{
    return new MushFileFilename;
}

MushcoreVirtualObject *MushFileFilename::AutoVirtualFactory(void)
{
    return new MushFileFilename;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushFileFilename", MushFileFilename::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushFileFilename::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "name=" << m_name << ", ";
    ioOut << "resolved=" << m_resolved << ", ";
    ioOut << "sourceType=" << m_sourceType << ", ";
    ioOut << "resolvedName=" << m_resolvedName;
    ioOut << "]";
}
bool
MushFileFilename::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "resolved")
    {
        ioIn >> m_resolved;
    }
    else if (inTagStr == "sourceType")
    {
        ioIn >> m_sourceType;
    }
    else if (inTagStr == "resolvedName")
    {
        ioIn >> m_resolvedName;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushFileFilename::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("name");
    ioOut << m_name;
    ioOut.TagSet("resolved");
    ioOut << m_resolved;
    ioOut.TagSet("sourceType");
    ioOut << m_sourceType;
    ioOut.TagSet("resolvedName");
    ioOut << m_resolvedName;
}
//%outOfLineFunctions } V6Pq2Rvt2pgvpbzgt+CkDw
