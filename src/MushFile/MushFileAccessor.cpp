//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileAccessor.cpp
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
//%Header } oIIt8j7CK6ZvV6VA5vIqrQ
/*
 * $Id: MushFileAccessor.cpp,v 1.4 2006/12/16 10:57:22 southa Exp $
 * $Log: MushFileAccessor.cpp,v $
 * Revision 1.4  2006/12/16 10:57:22  southa
 * Encrypted files
 *
 * Revision 1.3  2006/12/15 14:03:27  southa
 * File key handling
 *
 * Revision 1.2  2006/11/06 19:27:51  southa
 * Mushfile handling
 *
 * Revision 1.1  2006/11/06 12:56:31  southa
 * MushFile work
 *
 */

#include "MushFileAccessor.h"

#include "MushFileDirEntry.h"
#include "MushFileKeys.h"

using namespace Mushware;
using namespace std;

MushFileAccessor::MushFileAccessor(const std::string& inFilename) :
    m_filename(inFilename),
    m_loaded(false),
    m_readPos(0),
    m_endPos(0)
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
        U8 expectedHeader[kHeaderSize] = {'M', 'U', 'S', 'H', 0, 0, 1, 0};
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

Mushware::tSize
MushFileAccessor::ChunkDataGet(std::vector<Mushware::U8>& ioData, const std::string& inID)
{
    tSize dataSize = 0;
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
        dataSize = chunkLength - kIDSize;

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
    return dataSize;
}

Mushware::tSize
MushFileAccessor::ChunkDataGet(const std::string& inID)
{
    tSize dataSize = ChunkDataGet(m_data, inID);
    m_readPos = 0;
    m_endPos = dataSize;
    return dataSize;
}

void
MushFileAccessor::ChunkDataRelease(void)
{
    m_readPos = 0;
    m_endPos = 0;
    m_data.resize(0);
}

Mushware::tSize
MushFileAccessor::NumberRead(void)
{
    tSize retVal = 0;
    for (U32 i=0; i<kNumberSize; ++i)
    {
        if (m_readPos >= m_endPos)
        {
            throw MushcoreFileFail(m_filename, "Unexpected end of file");
        }
        retVal = (retVal << 8) | m_data[m_readPos];
        ++m_readPos;
    }
    return retVal;
}

std::string
MushFileAccessor::StringRead(void)
{
    tSize length = NumberRead();

    if (m_readPos + length > m_endPos)
    {
        throw MushcoreFileFail(m_filename, "Unexpected end of file");
    }
    std::string retVal(reinterpret_cast<char *>(&m_data[m_readPos]), length);
    m_readPos += length;
    
    m_readPos = (m_readPos + 3) & ~3;
    
    return retVal;
}

void
MushFileAccessor::DataDecrypt(Mushware::U8 *iopData, const Mushware::U8 *inpKey, Mushware::tSize inSize)
{
    for (Mushware::tSize i=0; i<inSize; ++i)
    {
        iopData[i] ^= inpKey[i % MushFileKeys::kKeySize];
    }
}

void
MushFileAccessor::LoadData(std::vector<Mushware::U8>& outData, const MushFileDirEntry& inEntry)
{
    if (!m_loaded)
    {
        Load();
    }
    
    if (m_chunkList.find("DATA") == m_chunkList.end())
    {
        throw MushcoreFileFail(m_filename, "No DATA chunk present");
    }
    tSize pos = m_chunkList["DATA"] + kNumberSize + kIDSize + inEntry.Offset();
    
    FILE *file = std::fopen(m_filename.c_str(), "rb");
    if (file == NULL)
    {
        throw MushcoreFileFail(m_filename, "Cannot open mushfile");
    }
    try
    {
        std::fseek(file, pos, SEEK_SET);
        outData.resize(inEntry.Size());
        if (std::fread(&outData[0], 1, inEntry.Size(), file) != inEntry.Size())
        {
            throw MushcoreFileFail(m_filename, "Unexpected end of file");
        }
        
        const U8 *pKey = NULL;
        
        if (!MushFileKeys::Sgl().Lookup(pKey, inEntry.KeyNum()))
        {
            throw MushcoreFileFail(m_filename, "Could not open file");
        }
        if (pKey != NULL)
        {
            DataDecrypt(&outData[0], pKey, inEntry.Size());
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
    ioOut << "chunkList=" << m_chunkList << ", ";
    ioOut << "data=" << m_data << ", ";
    ioOut << "readPos=" << m_readPos << ", ";
    ioOut << "endPos=" << m_endPos;
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
    else if (inTagStr == "data")
    {
        ioIn >> m_data;
    }
    else if (inTagStr == "readPos")
    {
        ioIn >> m_readPos;
    }
    else if (inTagStr == "endPos")
    {
        ioIn >> m_endPos;
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
    ioOut.TagSet("data");
    ioOut << m_data;
    ioOut.TagSet("readPos");
    ioOut << m_readPos;
    ioOut.TagSet("endPos");
    ioOut << m_endPos;
}
//%outOfLineFunctions } 20r+2Vvqc0I/DMZF/whiKw
