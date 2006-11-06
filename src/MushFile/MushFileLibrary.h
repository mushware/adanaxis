//%includeGuardStart {
#ifndef MUSHFILELIBRARY_H
#define MUSHFILELIBRARY_H
//%includeGuardStart } +2l5qSMDRH2B2NYap8Ld1Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileLibrary.h
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
//%Header } ENiRe4h/NdtvEV4FlxENHQ
/*
 * $Id$
 * $Log$
 */

#include "MushFileStandard.h"

#include "MushFileDirectory.h"

//:generate virtual standard ostream xml1
class MushFileLibrary : public MushcoreVirtualObject, public MushcoreSingleton<MushFileLibrary>
{
public:
    void LibraryAdd(const std::string& inFilename);
    
private:
    std::vector<MushFileDirectory> m_directories; //:read
    
//%classPrototypes {
public:
    const std::vector<MushFileDirectory>& Directories(void) const { return m_directories; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } /l/NwxIZDXHmcWC3eg5UTw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushFileLibrary& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Z4DxOdtYs1azc1ZuKYdOnw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
