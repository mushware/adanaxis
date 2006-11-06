//%includeGuardStart {
#ifndef MUSHFILEFILENAME_H
#define MUSHFILEFILENAME_H
//%includeGuardStart } nTV/TjscWTyMll1/46RlKQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileFilename.h
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
//%Header } wYzIfal8N7te9nm4yfNTcg
/*
 * $Id: MushFileFilename.h,v 1.1 2006/11/06 12:56:32 southa Exp $
 * $Log: MushFileFilename.h,v $
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileStandard.h"

//:generate virtual standard ostream xml1
class MushFileFilename : public MushcoreVirtualObject
{
public:
    MushFileFilename() {}
    explicit MushFileFilename(const std::string& inName);
    virtual ~MushFileFilename() {}
    
    void ResolveForRead(void);
    bool SourceIsFile(void);
    bool SourceIsMush(void);
    void AssertResolved(void);
    void SplitNames(std::vector<std::string>& outNames, const std::string& inName);            
    
private:
    std::string m_name; //:readwrite
    bool m_resolved; //:read
    MushFile::tSourceType m_sourceType; //:read
    std::string m_resolvedName; //:read
    
//%classPrototypes {
public:
    const std::string& Name(void) const { return m_name; }
    void NameSet(const std::string& inValue) { m_name=inValue; }
    const bool& Resolved(void) const { return m_resolved; }
    const MushFile::tSourceType& SourceType(void) const { return m_sourceType; }
    const std::string& ResolvedName(void) const { return m_resolvedName; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 5sAJVoTd0DzDH9JA04NKng
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushFileFilename& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } OLBR427Uqjzl0RpOs+OVjQ

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
