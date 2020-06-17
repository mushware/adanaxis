//%includeGuardStart {
#ifndef MUSHFILELIBRARY_H
#define MUSHFILELIBRARY_H
//%includeGuardStart } +2l5qSMDRH2B2NYap8Ld1Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileLibrary.h
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
//%Header } kBlshrIx8ThKj827W9yTXQ
/*
 * $Id: MushFileLibrary.h,v 1.2 2006/11/06 19:27:52 southa Exp $
 * $Log: MushFileLibrary.h,v $
 * Revision 1.2  2006/11/06 19:27:52  southa
 * Mushfile handling
 *
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileStandard.h"

#include "MushFileDirectory.h"

//:generate virtual standard ostream xml1
class MushFileLibrary : public MushcoreVirtualObject, public MushcoreSingleton<MushFileLibrary>
{
public:
    void LibraryAdd(const std::string& inFilename);
    bool Exists(const std::string& inName);
    void Load(std::vector<Mushware::U8>& outData, const std::string& inName);

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
