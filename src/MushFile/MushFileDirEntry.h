//%includeGuardStart {
#ifndef MUSHFILEDIRENTRY_H
#define MUSHFILEDIRENTRY_H
//%includeGuardStart } /Rcbf9/I9N2G0VRDgNkguQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileDirEntry.h
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
//%Header } 8QONmuw6Vx76hzN6NOLcMg
/*
 * $Id: MushFileDirEntry.h,v 1.3 2006/12/15 14:03:28 southa Exp $
 * $Log: MushFileDirEntry.h,v $
 * Revision 1.3  2006/12/15 14:03:28  southa
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
