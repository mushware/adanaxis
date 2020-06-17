//%includeGuardStart {
#ifndef MUSHFILEDIRECTORY_H
#define MUSHFILEDIRECTORY_H
//%includeGuardStart } q0AReiERNSN9wM3Vxm+0yQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileDirectory.h
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
//%Header } rJkQZC8Ye/QrWhIoalluVA
/*
 * $Id: MushFileDirectory.h,v 1.3 2006/12/16 10:57:22 southa Exp $
 * $Log: MushFileDirectory.h,v $
 * Revision 1.3  2006/12/16 10:57:22  southa
 * Encrypted files
 *
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
    typedef std::map<std::string, MushFileDirEntry> tEntries;
    std::string m_filename; //:read
    bool m_loaded; //:read
    tEntries m_entries; //:read
    
//%classPrototypes {
public:
    const std::string& Filename(void) const { return m_filename; }
    const bool& Loaded(void) const { return m_loaded; }
    const tEntries& Entries(void) const { return m_entries; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } L45ScWMZoCj6BQlStqtafw
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
