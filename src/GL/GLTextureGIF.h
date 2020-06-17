//%includeGuardStart {
#ifndef GLTEXTUREGIF_H
#define GLTEXTUREGIF_H
//%includeGuardStart } VMbl1m0z+keYDf3fAr+QjQ
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureGIF.h
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
//%Header } BVzNC5fJU5VhRw0cBkJFdQ
/*
 * $Id: GLTextureGIF.h,v 1.13 2006/06/01 15:38:54 southa Exp $
 * $Log: GLTextureGIF.h,v $
 * Revision 1.13  2006/06/01 15:38:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.11  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.10  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:31  southa
 * Fixed file headers
 *
 * Revision 1.8  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.7  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:21  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:40:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/02/25 23:05:15  southa
 * Subclassed GLTexture
 *
 */

#include "GLTexture.h"

class GLTextureGIF : public GLTexture
{
public:
    GLTextureGIF(const std::string& inFilename);
    GLTextureGIF *Clone(void) const {return new GLTextureGIF(*this);}

protected:

private:
    void ThrowGifError(const std::string& inFilename, int inRC);
    const char *FiletypeName(void) const;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
