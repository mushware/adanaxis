//%includeGuardStart {
#ifndef MUSHFILEFILE_H
#define MUSHFILEFILE_H
//%includeGuardStart } U8Wny/NgDaZcUKp90ToMcQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileFile.h
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
//%Header } TfWDwhULX4Amspgb97Dc5A
/*
 * $Id: MushFileFile.h,v 1.2 2006/11/06 19:27:51 southa Exp $
 * $Log: MushFileFile.h,v $
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
