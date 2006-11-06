//%includeGuardStart {
#ifndef MUSHFILEDIRECTORY_H
#define MUSHFILEDIRECTORY_H
//%includeGuardStart } q0AReiERNSN9wM3Vxm+0yQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileDirectory.h
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
//%Header } xn5oNgprtnehV9hRbLEeKQ
/*
 * $Id: MushFileDirectory.h,v 1.1 2006/11/06 12:56:32 southa Exp $
 * $Log: MushFileDirectory.h,v $
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileStandard.h"

#include "MushFileDirEntry.h"

//:generate virtual standard ostream xml1
class MushFileDirectory : public MushcoreVirtualObject
{
public:
    MushFileDirectory() {}
    explicit MushFileDirectory(const std::string& inFilename);
    virtual ~MushFileDirectory() {}

    void Load(void);
    bool Exists(const std::string& inName);
    bool EntryGet(const MushFileDirEntry *& outEntry, const std::string& inName);
    
protected:
    
private:
    std::string m_filename; //:read
    bool m_loaded; //:read
    std::map<std::string, MushFileDirEntry> m_entries; //:read
    
//%classPrototypes {
public:
    const std::string& Filename(void) const { return m_filename; }
    const bool& Loaded(void) const { return m_loaded; }
    const std::map<std::string, MushFileDirEntry>& Entries(void) const { return m_entries; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 9BsVmKvoSwzWL4169BmHfw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushFileDirectory& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 5IQJDju02Blu3fvS4auyfA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
