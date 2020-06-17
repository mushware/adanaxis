//%includeGuardStart {
#ifndef GLTEXTUREPROC_H
#define GLTEXTUREPROC_H
//%includeGuardStart } h07cy255ooQoRIKB503C5Q
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureProc.h
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
//%Header } L6cEhQYFU4S7uawDtWVJgg
/*
 * $Id: GLTextureProc.h,v 1.4 2006/06/01 15:38:54 southa Exp $
 * $Log: GLTextureProc.h,v $
 * Revision 1.4  2006/06/01 15:38:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.2  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/13 22:44:07  southa
 * Tesseract stuff
 *
 */

#include "GLTexture.h"

class MushGLPixelSource;

class GLTextureProc : public GLTexture
{
public:
    GLTextureProc(const MushGLPixelSource& inSource);
    GLTextureProc *Clone(void) const {return new GLTextureProc(*this);}
    
protected:
        
private:
    const char *FiletypeName(void) const;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
