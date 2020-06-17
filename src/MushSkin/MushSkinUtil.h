//%includeGuardStart {
#ifndef MUSHSKINUTIL_H
#define MUSHSKINUTIL_H
//%includeGuardStart } P1MS7xj1VbWj+jgxypUXJw
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinUtil.h
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
//%Header } SSxw9kEZLLEzMZ6HLE007w
/*
 * $Id: MushSkinUtil.h,v 1.4 2007/04/18 09:23:06 southa Exp $
 * $Log: MushSkinUtil.h,v $
 * Revision 1.4  2007/04/18 09:23:06  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/08/01 17:21:42  southa
 * River demo
 *
 * Revision 1.2  2006/06/07 12:15:22  southa
 * Grid and test textures
 *
 * Revision 1.1  2006/06/05 11:48:26  southa
 * Noise textures
 *
 */

#include "MushSkinStandard.h"

class MushSkinUtil
{
public:
	static void PalettedToRGBA(Mushware::U8 *outpData, const Mushware::tVal *inpData,
							   Mushware::U32 inNumPixels, const MushGLTexture& ioTexture,
							   const Mushware::t2Val& inStartPos, const Mushware::t2Val& inVec);
	
private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
