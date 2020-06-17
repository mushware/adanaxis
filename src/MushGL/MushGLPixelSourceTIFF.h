//%includeGuardStart {
#ifndef MUSHGLPIXELSOURCETIFF_H
#define MUSHGLPIXELSOURCETIFF_H
//%includeGuardStart } nH7Z6maSsLIzcTPVyFNcrQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLPixelSourceTIFF.h
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
//%Header } Ob7bkfLJGNJN+Nf2fAc2qA
/*
 * $Id: MushGLPixelSourceTIFF.h,v 1.5 2006/06/07 12:15:19 southa Exp $
 * $Log: MushGLPixelSourceTIFF.h,v $
 * Revision 1.5  2006/06/07 12:15:19  southa
 * Grid and test textures
 *
 * Revision 1.4  2006/06/06 17:58:32  southa
 * Ruby texture definition
 *
 * Revision 1.3  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/08/29 18:40:56  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/08/28 22:41:52  southa
 * MushGLTexture work
 *
 */

#include "MushGLStandard.h"

#include "MushGLPixelSource.h"

class MushGLTexture;

//:generate virtual standard ostream xml1
class MushGLPixelSourceTIFF : public MushGLPixelSource
{
public:
	MushGLPixelSourceTIFF();
    virtual void ToTextureCreate(MushGLTexture& outTexture);
	virtual void ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue);

private:
    std::string m_filename; //:readwrite
    
//%classPrototypes {
public:
    const std::string& Filename(void) const { return m_filename; }
    void FilenameSet(const std::string& inValue) { m_filename=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } xJVc2BAp9iykej3O+aElGA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLPixelSourceTIFF& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 5BAQQlXQC1ekl4kX6Wc5+Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
