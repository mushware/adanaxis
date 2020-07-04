//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileFilename.cpp
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
//%Header } wvutaQMKxhMXTcMsQVAm0w
/*
 * $Id: MushFileFilename.cpp,v 1.4 2007/04/18 09:22:32 southa Exp $
 * $Log: MushFileFilename.cpp,v $
 * Revision 1.4  2007/04/18 09:22:32  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/11/07 11:08:54  southa
 * Texture loading from mushfiles
 *
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
        else if (filenames[i].substr(0, 5) == "null:")
        {
            m_resolvedName = "";
            m_sourceType = MushFile::kSourceTypeNull;
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
MushFileFilename::SourceIsNull(void)
{
    AssertResolved();
    return (m_sourceType == MushFile::kSourceTypeNull);
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
    return (m_sourceType == MushFile::kSourceTypeNull || m_sourceType == MushFile::kSourceTypeMush || m_sourceType == MushFile::kSourceTypeFile);
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
