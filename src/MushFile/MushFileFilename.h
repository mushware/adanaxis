//%includeGuardStart {
#ifndef MUSHFILEFILENAME_H
#define MUSHFILEFILENAME_H
//%includeGuardStart } nTV/TjscWTyMll1/46RlKQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileFilename.h
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
//%Header } GP2kh92tqSwtfl+eSstWOA
/*
 * $Id: MushFileFilename.h,v 1.4 2007/04/18 09:22:32 southa Exp $
 * $Log: MushFileFilename.h,v $
 * Revision 1.4  2007/04/18 09:22:32  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/11/07 11:08:54  southa
 * Texture loading from mushfiles
 *
 * Revision 1.2  2006/11/06 19:27:52  southa
 * Mushfile handling
 *
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
    bool SourceIsNull(void);
    bool SourceIsFile(void);
    bool SourceIsMush(void);
    bool SourceExists(void);
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
