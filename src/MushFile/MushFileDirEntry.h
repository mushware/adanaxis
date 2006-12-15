//%includeGuardStart {
#ifndef MUSHFILEDIRENTRY_H
#define MUSHFILEDIRENTRY_H
//%includeGuardStart } /Rcbf9/I9N2G0VRDgNkguQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileDirEntry.h
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
//%Header } u7HheW/jj+BZx6X2IytANA
/*
 * $Id: MushFileDirEntry.h,v 1.2 2006/11/06 19:27:51 southa Exp $
 * $Log: MushFileDirEntry.h,v $
 * Revision 1.2  2006/11/06 19:27:51  southa
 * Mushfile handling
 *
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileStandard.h"

#include "MushFileDirEntry.h"

//:generate virtual standard ostream xml1
class MushFileDirEntry : public MushcoreVirtualObject
{
public:

private:
    std::string m_filename; //:readwrite
    Mushware::tSize m_size; //:readwrite
    Mushware::tSize m_offset; //:readwrite
    Mushware::U32 m_keyNum; //:readwrite
    
//%classPrototypes {
public:
    const std::string& Filename(void) const { return m_filename; }
    void FilenameSet(const std::string& inValue) { m_filename=inValue; }
    const Mushware::tSize& Size(void) const { return m_size; }
    void SizeSet(const Mushware::tSize& inValue) { m_size=inValue; }
    const Mushware::tSize& Offset(void) const { return m_offset; }
    void OffsetSet(const Mushware::tSize& inValue) { m_offset=inValue; }
    const Mushware::U32& KeyNum(void) const { return m_keyNum; }
    void KeyNumSet(const Mushware::U32& inValue) { m_keyNum=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } bvNzRgZDIXYHfwu3Oy5esw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushFileDirEntry& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Q55TGTVtoMPoShilkf6IAw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
