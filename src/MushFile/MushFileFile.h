//%includeGuardStart {
#ifndef MUSHFILEFILE_H
#define MUSHFILEFILE_H
//%includeGuardStart } U8Wny/NgDaZcUKp90ToMcQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileFile.h
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
//%Header } w82jSOxswBBNCzY2U55tjg
/*
 * $Id: MushFileFile.h,v 1.4 2007/04/18 09:22:32 southa Exp $
 * $Log: MushFileFile.h,v $
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

#include "MushFileStandard.h"

#include "MushFileFilename.h"

//:generate virtual standard ostream xml1
class MushFileFile : public MushcoreVirtualObject
{
public:
    MushFileFile() : m_sourceType(MushFile::kSourceTypeInvalid), m_seekPos(0) {} 
    
    void OpenForRead(const std::string& inName);
    std::string PlainFilename(void);
    std::string Name(void) const;
    bool SourceIsNull(void) { return m_filename.SourceIsNull(); }
    bool SourceIsFile(void) { return m_filename.SourceIsFile(); }
    bool SourceIsMush(void) { return m_filename.SourceIsMush(); }
    Mushware::U8 *DataStart(void);
    Mushware::tSize DataSize(void);
    
    static Mushware::S32 TIFFRead(void *inHandle, void *inData, Mushware::S32 inSize);
    static Mushware::S32 TIFFWrite(void *inHandle, void *inData, Mushware::S32 inSize);
    static Mushware::U32 TIFFSeek(void *inHandle, Mushware::U32 inOffset, int inFrom);
    static int TIFFClose(void *inHandle);    
    static Mushware::U32 TIFFSize(void *inHandle);

protected:
    Mushware::tSize DataRead(void *outData, Mushware::tSize inSize);
    void DataSeek(Mushware::tSize inSeekPos);
    
private:
    MushFileFilename m_filename; //:readwrite
    MushFile::tSourceType m_sourceType; //:read
    std::vector<Mushware::U8> m_data; //:read
    Mushware::tSize m_seekPos; //:read
    
//%classPrototypes {
public:
    const MushFileFilename& Filename(void) const { return m_filename; }
    void FilenameSet(const MushFileFilename& inValue) { m_filename=inValue; }
    const MushFile::tSourceType& SourceType(void) const { return m_sourceType; }
    const std::vector<Mushware::U8>& Data(void) const { return m_data; }
    const Mushware::tSize& SeekPos(void) const { return m_seekPos; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Sod5M3huMJ4DhomB8ugDlQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushFileFile& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } zXFsWrMH/ki90eoqqIiCtA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
