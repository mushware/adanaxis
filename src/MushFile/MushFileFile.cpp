//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileFile.cpp
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
//%Header } s347TUOP6TwsXJmaLdEs1g
/*
 * $Id: MushFileFile.cpp,v 1.2 2006/11/06 19:27:51 southa Exp $
 * $Log: MushFileFile.cpp,v $
 * Revision 1.2  2006/11/06 19:27:51  southa
 * Mushfile handling
 *
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileFile.h"

#include "MushFileLibrary.h"

using namespace Mushware;
using namespace std;

std::string
MushFileFile::Name(void) const
{
    return m_filename.Name();
}

void
MushFileFile::OpenForRead(const std::string& inName)
{
    m_filename.NameSet(inName);
    m_filename.ResolveForRead();
    
    if (m_filename.SourceIsMush())
    {
        MushFileLibrary::Sgl().Load(m_data, m_filename.ResolvedName());
        m_seekPos = 0;
    }
    else if (m_filename.SourceIsFile())
    {
        
    }
}

Mushware::U8 *
MushFileFile::DataStart(void)
{
    if (!m_filename.SourceIsMush())
    {
        throw MushcoreFileFail(m_filename.Name(), "File is not in a mushfile");
    }

    return &m_data[0];
}

Mushware::tSize
MushFileFile::DataSize(void)
{
    if (!m_filename.SourceIsMush())
    {
        throw MushcoreFileFail(m_filename.Name(), "File is not in a mushfile");
    }
    return m_data.size();
}

Mushware::tSize
MushFileFile::DataRead(void *outData, Mushware::tSize inSize)
{
    tSize readSize = inSize;
    if (m_seekPos >= m_data.size())
    {
        readSize = 0;
    }
    else if (m_seekPos + readSize >= m_data.size())
    {
        readSize = m_data.size() - m_seekPos;
    }
    std::memcpy(outData, &m_data[m_seekPos], readSize);
    m_seekPos += readSize;
    
    return readSize;
}

void
MushFileFile::DataSeek(Mushware::tSize inSeekPos)
{
    m_seekPos = inSeekPos;
    if (m_seekPos >= m_data.size())
    {
        m_seekPos = m_data.size();
    }
}

std::string
MushFileFile::PlainFilename(void)
{
    if (!m_filename.SourceIsFile())
    {
        throw MushcoreFileFail(m_filename.Name(), "File is not a plain file");
    }
    return m_filename.ResolvedName();
}

Mushware::S32
MushFileFile::TIFFRead(void *inHandle, void *inData, Mushware::S32 inSize)
{
    MushFileFile *pFile = reinterpret_cast<MushFileFile *>(inHandle);
    return pFile->DataRead(inData, inSize);
}

Mushware::S32
MushFileFile::TIFFWrite(void *inHandle, void *inData, Mushware::S32 inSize)
{
    return 0; // Always fail
}

Mushware::U32
MushFileFile::TIFFSeek(void *inHandle, Mushware::U32 inOffset, int inFrom)
{
    MushFileFile *pFile = reinterpret_cast<MushFileFile *>(inHandle);
    tSize seekPos = 0;
    
    switch (inFrom)
    {
        case SEEK_SET:
            seekPos = inOffset;
            break;
            
        case SEEK_CUR:
            seekPos = inOffset + pFile->SeekPos();
            break;
            
        case SEEK_END:
            seekPos = pFile->DataSize() - inOffset;
            break;
            
        default:
            throw MushcoreRequestFail("Unknown seek type");
    }
    pFile->DataSeek(seekPos);
    
    return inOffset;
}

int
MushFileFile::TIFFClose(void *inHandle)
{
    return 0;
}

Mushware::U32
MushFileFile::TIFFSize(void *inHandle)
{
    MushFileFile *pFile = reinterpret_cast<MushFileFile *>(inHandle);
    return static_cast<S32>(pFile->DataSize());
}

//%outOfLineFunctions {

const char *MushFileFile::AutoName(void) const
{
    return "MushFileFile";
}

MushcoreVirtualObject *MushFileFile::AutoClone(void) const
{
    return new MushFileFile(*this);
}

MushcoreVirtualObject *MushFileFile::AutoCreate(void) const
{
    return new MushFileFile;
}

MushcoreVirtualObject *MushFileFile::AutoVirtualFactory(void)
{
    return new MushFileFile;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushFileFile", MushFileFile::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushFileFile::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "filename=" << m_filename << ", ";
    ioOut << "sourceType=" << m_sourceType << ", ";
    ioOut << "data=" << m_data << ", ";
    ioOut << "seekPos=" << m_seekPos;
    ioOut << "]";
}
bool
MushFileFile::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "sourceType")
    {
        ioIn >> m_sourceType;
    }
    else if (inTagStr == "data")
    {
        ioIn >> m_data;
    }
    else if (inTagStr == "seekPos")
    {
        ioIn >> m_seekPos;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushFileFile::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("filename");
    ioOut << m_filename;
    ioOut.TagSet("sourceType");
    ioOut << m_sourceType;
    ioOut.TagSet("data");
    ioOut << m_data;
    ioOut.TagSet("seekPos");
    ioOut << m_seekPos;
}
//%outOfLineFunctions } IxS6qDb/CxpIL3yB++2Wdg
