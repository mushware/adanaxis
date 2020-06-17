//%includeGuardStart {
#ifndef MUSHGLTIFFUTIL_H
#define MUSHGLTIFFUTIL_H
//%includeGuardStart } 2qBPfecKA56vdDUfoBJAcg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLTIFFUtil.h
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
//%Header } 8F8bXxb7VIUO5cMTtkB9hQ
/*
 * $Id: MushGLTIFFUtil.h,v 1.3 2007/04/18 09:22:36 southa Exp $
 * $Log: MushGLTIFFUtil.h,v $
 * Revision 1.3  2007/04/18 09:22:36  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/07/28 16:52:21  southa
 * Options work
 *
 * Revision 1.1  2006/06/05 11:48:25  southa
 * Noise textures
 *
 */

#include "MushGLStandard.h"

class MushGLTIFFUtil
{
public:
	static void RGBASave(const std::string& inFilename, const std::string& inDesc,
						 const Mushware::t2U32& inSize, const Mushware::U8 *pData);
    static void RGBASave(const std::string& inFilename, const std::string& inDesc,
                         const Mushware::t2U32& inSize, std::vector<Mushware::U8> inData);
	static void ValSave(const std::string& inFilename, const std::string& inDesc,
						const Mushware::t2U32& inSize, const Mushware::tVal *inpData);
	static void TextureSave(const std::string& inFilename, const std::string& inDesc);
    static std::string CreatorGet(const std::string& inFilename);
    
private:
	static void FieldsSet(void *inpTIFF, const std::string& inDesc, const Mushware::t2U32& inSize,
						  Mushware::U32 inRowsPerStrip);
	
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
