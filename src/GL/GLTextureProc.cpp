//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureProc.cpp
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
//%Header } tUaKj426kWbSyT3jYNv0rg
/*
 * $Id: GLTextureProc.cpp,v 1.4 2006/06/01 15:38:54 southa Exp $
 * $Log: GLTextureProc.cpp,v $
 * Revision 1.4  2006/06/01 15:38:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.2  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/13 22:44:06  southa
 * Tesseract stuff
 *
 */

#include "GLTextureProc.h"

#include "GLSTL.h"

#include "API/mushMushGL.h"

using namespace Mushware;
using namespace std;

GLTextureProc::GLTextureProc(const MushGLPixelSource& inSource)
{
    t2U32 size(256,256);
    U32 u32Size = size.X()*size.Y();
    
    // TextureDef takes ownership of the block
    GLTextureDef def(new U32[u32Size]);
    
    def.WidthSet(size.X());
    def.HeightSet(size.Y());
    def.PixelFormatSet(GL_RGBA);
    def.PixelTypeSet(GL_UNSIGNED_BYTE);
    
    inSource.BufferFill(def.DataPtr(), size);
    
    AddTextureDef(def);
}

const char *
GLTextureProc::FiletypeName(void) const
{
    return "Proc";
}
