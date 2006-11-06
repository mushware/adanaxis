//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileAccessor.cpp
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
//%Header } fIyM/XLdEniRZka5Jb+a2A
/*
 * $Id$
 * $Log$
 */

#include "MushFileAccessor.h"

using namespace Mushware;
using namespace std;

MushFileAccessor::MushFileAccessor(const std::string& inFilename) :
    m_filename(inFilename),
    m_loaded(false)
{
    
}

Mushware::tSize
MushFileAccessor::NumberRead(FILE *inFile)
{
    U8 buffer[kNumberSize];
    if (std::fread(buffer, 1, kNumberSize, inFile) != kNumberSize)
    {
        throw MushcoreFileFail(m_filename, "Unexpected end of file");
    }
    tSize retVal = 0;
    for (U32 i=0; i<kNumberSize; ++i)
    {
        retVal = (retVal << 8) | buffer[i];
    }
    return retVal;
}

std::string
MushFileAccessor::IDRead(FILE *inFile)
{
    char buffer[kIDSize];
    if (std::fread(buffer, 1, kIDSize, inFile) != kIDSize)
    {
        throw MushcoreFileFail(m_filename, "Unexpected end of file");
    }

    return std::string(buffer, kIDSize);
}

void
MushFileAccessor::Load(void)
{
    FILE *file = std::fopen(m_filename.c_str(), "rb");
    if (file == NULL)
    {
        throw MushcoreFileFail(m_filename, "Cannot open mushfile");
    }
    try
    {
        std::fseek(file, 0, SEEK_END);
        tSize filesize = std::ftell(file);
        std::rewind(file);
        
        U8 header[kHeaderSize];
        if (std::fread(header, 1, kHeaderSize, file) != kHeaderSize)
        {
            throw MushcoreFileFail(m_filename, "Header not present in mushfile");
        }
        U8 expectedHeader[kHeaderSize] = {'M', 'U', 'S', 'H', 0, 0, 0, 1};
        if (memcmp(header, expectedHeader, kHeaderSize) != 0)
        {
            throw MushcoreFileFail(m_filename, "Bad header in mushfile");
        }
        
        tSize pos = kHeaderSize;
        while (pos+kNumberSize <= filesize)
        {
            std::fseek(file, pos, SEEK_SET);
            tSize chunkLength = NumberRead(file);
            std::string chunkID = IDRead(file);
            
            if (m_chunkList.find(chunkID) != m_chunkList.end())
            {
                throw MushcoreFileFail(m_filename, "Duplicated chunks (ID='"+chunkID+"')");
            }
            m_chunkList[chunkID] = pos;
            pos += kNumberSize+chunkLength;
        }
    }
    catch (std::exception& e)
    {
        if (file != NULL)
        {
            std::fclose(file);
        }
        throw;
    }
    std::fclose(file);
    m_loaded = true;
}

Mushware::tSize
MushFileAccessor::ChunkBaseGet(const std::string& inID)
{
    if (!m_loaded)
    {
        Load();
    }
    
    if (m_chunkList.find(inID) == m_chunkList.end())
    {
        throw MushcoreFileFail(m_filename, "No chunk present with ID='"+inID+"')");
    }
    
    return m_chunkList[inID] + kNumberSize + kIDSize;
}

void
MushFileAccessor::ChunkDataGet(std::vector<Mushware::U8>& ioData, const std::string& inID)
{
    if (!m_loaded)
    {
        Load();
    }
    
    if (m_chunkList.find(inID) == m_chunkList.end())
    {
        throw MushcoreFileFail(m_filename, "No chunk present with ID='"+inID+"')");
    }
    tSize pos = m_chunkList[inID];
    
    FILE *file = std::fopen(m_filename.c_str(), "rb");
    if (file == NULL)
    {
        throw MushcoreFileFail(m_filename, "Cannot open mushfile");
    }
    try
    {
        std::fseek(file, pos, SEEK_SET);
        tSize chunkLength = NumberRead(file);
        tSize dataSize = chunkLength - kIDSize;

        std::string chunkID = IDRead(file);
        if (chunkID != inID || dataSize > chunkLength)
        {
            throw MushcoreFileFail(m_filename, "File misread (ID='"+inID+"')");
        }
        ioData.resize(dataSize);
        if (std::fread(&ioData[0], 1, dataSize, file) != dataSize)
        {
            throw MushcoreFileFail(m_filename, "Unexpected end of file");
        }
    }
    catch (std::exception& e)
    {
        if (file != NULL)
        {
            std::fclose(file);
        }
        throw;
    }
    std::fclose(file);
}

//%outOfLineFunctions {

const char *MushFileAccessor::AutoName(void) const
{
    return "MushFileAccessor";
}

MushcoreVirtualObject *MushFileAccessor::AutoClone(void) const
{
    return new MushFileAccessor(*this);
}

MushcoreVirtualObject *MushFileAccessor::AutoCreate(void) const
{
    return new MushFileAccessor;
}

MushcoreVirtualObject *MushFileAccessor::AutoVirtualFactory(void)
{
    return new MushFileAccessor;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushFileAccessor", MushFileAccessor::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushFileAccessor::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "filename=" << m_filename << ", ";
    ioOut << "loaded=" << m_loaded << ", ";
    ioOut << "chunkList=" << m_chunkList;
    ioOut << "]";
}
bool
MushFileAccessor::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "chunkList")
    {
        ioIn >> m_chunkList;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushFileAccessor::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("filename");
    ioOut << m_filename;
    ioOut.TagSet("loaded");
    ioOut << m_loaded;
    ioOut.TagSet("chunkList");
    ioOut << m_chunkList;
}
//%outOfLineFunctions } XQLLuX66etDMj57TRbT4Mg
