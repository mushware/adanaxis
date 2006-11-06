//%includeGuardStart {
#ifndef MUSHFILEACCESSOR_H
#define MUSHFILEACCESSOR_H
//%includeGuardStart } qlFhJV75Mp0zTHvNwxlUZg
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileAccessor.h
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
//%Header } k6FUmFChxKsln5+gWstxRQ
/*
 * $Id$
 * $Log$
 */

#include "MushFileStandard.h"

//:generate virtual standard ostream xml1
class MushFileAccessor : public MushcoreVirtualObject
{
public:
    explicit MushFileAccessor(const std::string& inFilename = "");
    
    Mushware::tSize ChunkBaseGet(const std::string& inID);
    void ChunkDataGet(std::vector<Mushware::U8>& ioData, const std::string& inID);
    
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
    
private:
    std::string m_filename; //:readwrite
    bool m_loaded; //:read
    std::map<std::string, Mushware::tSize> m_chunkList;

//%classPrototypes {
public:
    const std::string& Filename(void) const { return m_filename; }
    void FilenameSet(const std::string& inValue) { m_filename=inValue; }
    const bool& Loaded(void) const { return m_loaded; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } L3DrhVgfD4I5I856jbwwRQ
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
