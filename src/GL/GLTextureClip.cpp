//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureClip.cpp
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
//%Header } Er+ljE5yOlirGqEXmSsoSQ
/*
 * $Id: GLTextureClip.cpp,v 1.20 2006/06/01 15:38:53 southa Exp $
 * $Log: GLTextureClip.cpp,v $
 * Revision 1.20  2006/06/01 15:38:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.19  2005/08/02 17:11:28  southa
 * win32 build fixes
 *
 * Revision 1.18  2005/08/02 14:37:44  southa
 * Adanaxis control demo work
 *
 * Revision 1.17  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.16  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.15  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.14  2003/08/21 23:08:30  southa
 * Fixed file headers
 *
 * Revision 1.13  2003/02/05 16:19:45  southa
 * Build fixes
 *
 * Revision 1.12  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.11  2003/01/12 17:32:51  southa
 * Mushcore work
 *
 * Revision 1.10  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.9  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.4  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.1  2002/05/28 16:37:40  southa
 * Texture references and decomposer
 *
 */

#include "GLTextureClip.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLTextureClip::GLTextureClip(const GLTexture& inTex, U32 inX1, U32 inY1, U32 inX2, U32 inY2)
{
    FilenameSet(inTex.FilenameGet()+" [clip]");

    // Needs extending for multi image clips
    for (int imageNum=0; imageNum < 1; ++imageNum)
    {
        S32 xinc, yinc;
        U32 xsize, ysize;
        if (inX1>inX2)
        {
            xinc=-1;
            xsize=inX1-inX2;
        }
        else
        {
            xinc=1;
            xsize=inX2-inX1;
        }
        if (inY1>inY2)
        {
            yinc=-1;
            ysize=inY1-inY2;
        }
        else
        {
            yinc=1;
            ysize=inY2-inY1;
        }
        // Overflow check
        MUSHCOREASSERT(xsize < 0x80000000 && ysize < 0x80000000);

        // cerr << "inX1=" << inX1 << " inY1=" << inY1 << " inX2=" << inX2 << " inY2=" << inY2 << endl;
        // cerr << "xinc=" << xinc << " yinc=" << yinc << " xsize=" << xsize << " ysize=" << ysize << endl;
        
        U32 numPixels=xsize*ysize;
        U32 u32Size=numPixels;

        // TextureDef takes ownership of the block
        GLTextureDef def(new U32[u32Size]);

        def.WidthSet(xsize);
        def.HeightSet(ysize);
        def.PixelFormatSet(GL_RGBA);
        def.PixelTypeSet(GL_UNSIGNED_BYTE);

        U32 *srcBase=inTex.DataPtr();
        U32 srcWidth=inTex.Width();
        U32 srcHeight=inTex.Height();
        U32 *destPtr=def.DataPtr();
#ifdef MUSHCORE_DEBUG
        U32 *srcPtrLim=srcBase+srcWidth*srcHeight; // Assertions only
        U32 *destPtrLim=def.DataPtr()+u32Size; // Assertions only
#endif

        for (U32 yLoop = inY1; yLoop != inY2; yLoop += yinc)
        {
            U32 y=yLoop;
            if (y>=srcHeight) y = y % srcHeight;
            
            for (U32 xLoop = inX1; xLoop != inX2; xLoop += xinc)
            {
                U32 x=xLoop;
                if (x>=srcWidth) x = x % srcWidth;

                U32 *srcPtr=srcBase + x + y*srcWidth;
                *destPtr++=*srcPtr;
                MUSHCOREASSERT(srcPtr < srcPtrLim);
                MUSHCOREASSERT(destPtr <= destPtrLim);
            }
        }
        MUSHCOREASSERT(destPtr == destPtrLim);
        AddTextureDef(def);
    }
}

const char *
GLTextureClip::FiletypeName(void) const
{
    return "Clip";
}
