/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLTextureClip.cpp,v 1.9 2002/12/20 13:17:36 southa Exp $
 * $Log: GLTextureClip.cpp,v $
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
        COREASSERT(xsize < 0x80000000 && ysize < 0x80000000);

        // cerr << "inX1=" << inX1 << " inY1=" << inY1 << " inX2=" << inX2 << " inY2=" << inY2 << endl;
        // cerr << "xinc=" << xinc << " yinc=" << yinc << " xsize=" << xsize << " ysize=" << ysize << endl;
        
        tSize numPixels=xsize*ysize;
        tSize u32Size=numPixels;

        // TextureDef takes ownership of the block
        GLTextureDef def(new U32[u32Size]);

        def.WidthSet(xsize);
        def.HeightSet(ysize);
        def.PixelFormatSet(GL_RGBA);
        def.PixelTypeSet(GL_UNSIGNED_BYTE);

        U32 *srcBase=inTex.DataPtr();
        U32 srcWidth=inTex.Width();
        U32 srcHeight=inTex.Height();
        U32 *srcPtrLim=srcBase+srcWidth*srcHeight;
        U32 *destPtr=def.DataPtr();
        U32 *destPtrLim=def.DataPtr()+u32Size;

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
                COREASSERT(srcPtr < srcPtrLim);
                COREASSERT(destPtr <= destPtrLim);
            }
        }
        COREASSERT(destPtr == destPtrLim);
        AddTextureDef(def);
    }
}

const char *
GLTextureClip::FiletypeName(void) const
{
    return "Clip";
}
