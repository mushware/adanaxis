//%includeGuardStart {
#ifndef MUSHFILEACCESSOR_H
#define MUSHFILEACCESSOR_H
//%includeGuardStart } qlFhJV75Mp0zTHvNwxlUZg
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileAccessor.h
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
//%Header } 9qlzA7r8TZNrD3j9PeHgDQ
/*
 * $Id: MushFileAccessor.h,v 1.3 2006/12/15 14:03:27 southa Exp $
 * $Log: MushFileAccessor.h,v $
 * Revision 1.3  2006/12/15 14:03:27  southa
 * File key handling
 *
 * Revision 1.2  2006/11/06 19:27:51  southa
 * Mushfile handling
 *
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileStandard.h"

class MushFileDirEntry;

//:generate virtual standard ostream xml1
class MushFileAccessor : public MushcoreVirtualObject
{
public:
    typedef std::vector<Mushware::U8> tData;
    explicit MushFileAccessor(const std::string& inFilename = "");
    
    Mushware::tSize ChunkBaseGet(const std::string& inID);
    Mushware::tSize ChunkDataGet(const std::string& inID);
    void ChunkDataRelease(void);
    Mushware::tSize NumberRead(void);
    std::string StringRead(void);
    bool EndOfChunk(void) { return (m_readPos >= m_endPos); }
    void LoadData(std::vector<Mushware::U8>& outData, const MushFileDirEntry& inEntry);

protected:
    enum
    {
        kHeaderSize = 8,
        kNumberSize = 8,
        kIDSize = 4
    };
    Mushware::tSize NumberRead(FILE *inFile);
    std::string IDRead(FILE *inFile);
    void Load(void);
    Mushware::tSize ChunkDataGet(std::vector<Mushware::U8>& ioData, const std::string& inID);

private:
    void DataDecrypt(Mushware::U8 *iopData, const Mushware::U8 *inpKey, Mushware::tSize inSize);

    std::string m_filename; //:readwrite
    bool m_loaded; //:read
    std::map<std::string, Mushware::tSize> m_chunkList;
    tData m_data; //:readwrire
    Mushware::tSize m_readPos; //:read
    Mushware::tSize m_endPos; //:read

//%classPrototypes {
public:
    const std::string& Filename(void) const { return m_filename; }
    void FilenameSet(const std::string& inValue) { m_filename=inValue; }
    const bool& Loaded(void) const { return m_loaded; }
    const Mushware::tSize& ReadPos(void) const { return m_readPos; }
    const Mushware::tSize& EndPos(void) const { return m_endPos; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } y4SuIYQ313IKBFqIJKlU7A
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushFileAccessor& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } koCAKzaWrr9pMQ+AwNhKYQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
