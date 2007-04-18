//%includeGuardStart {
#ifndef MUSHFILEACCESSOR_H
#define MUSHFILEACCESSOR_H
//%includeGuardStart } qlFhJV75Mp0zTHvNwxlUZg
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileAccessor.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } idVHXbOYZBZaVGEHeCtMOA
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
