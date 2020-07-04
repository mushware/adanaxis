//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureTIFF.cpp
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
//%Header } YcsJ7HWqajOcQtjR2Jhkzg
/*
 * $Id: GLTextureTIFF.cpp,v 1.20 2006/06/01 15:38:54 southa Exp $
 * $Log: GLTextureTIFF.cpp,v $
 * Revision 1.20  2006/06/01 15:38:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.19  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.18  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.17  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.16  2003/08/21 23:08:32  southa
 * Fixed file headers
 *
 * Revision 1.15  2003/02/05 16:19:45  southa
 * Build fixes
 *
 * Revision 1.14  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.13  2003/01/12 17:32:51  southa
 * Mushcore work
 *
 * Revision 1.12  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.11  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.10  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/27 08:56:21  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.6  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.4  2002/05/29 10:22:40  southa
 * Made machine endian independent
 *
 * Revision 1.2  2002/05/28 16:37:40  southa
 * Texture references and decomposer
 *
 * Revision 1.1  2002/05/28 13:07:00  southa
 * Command parser extensions and TIFF loader
 *
 */

#include "GLTextureTIFF.h"

#include "tiffio.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLTextureTIFF::GLTextureTIFF(const string& inFilename)
{
    FilenameSet(inFilename);
    uint32 *tiffData=NULL;
    TIFF* pTiff = TIFFOpen(inFilename.c_str(), "r");
    if (pTiff == NULL)
    {
        throw(MushcoreFileFail(inFilename, "Could not open file"));
    }

    try
    {
        // Needs extending for multi image TIFFs
        for (int imageNum=0; imageNum < 1; ++imageNum)
        {
            uint32 width, height;

            TIFFGetField(pTiff, TIFFTAG_IMAGEWIDTH, &width);
            TIFFGetField(pTiff, TIFFTAG_IMAGELENGTH, &height);

            U32 numPixels=width*height;
            U32 u32Size=numPixels;
            tiffData=reinterpret_cast<uint32 *>(_TIFFmalloc(sizeof(uint32)*width*height));

            // TextureDef takes ownership of the block
            GLTextureDef def(new U32[u32Size]);
           
            def.WidthSet(width);
            def.HeightSet(height);
            def.PixelFormatSet(GL_RGBA);
            def.PixelTypeSet(GL_UNSIGNED_BYTE);

            TIFFReadRGBAImage(pTiff, width, height, tiffData, 0);

            uint32 *srcData=tiffData;
            U8 *destBytes=reinterpret_cast<U8 *>(def.DataPtr());
            MUSHCOREASSERT(srcData != NULL);
            MUSHCOREASSERT(destBytes != NULL);
            // Convert from ABGR words (from tifflib) into RGBA bytes.  Has to work on big
            // and little endian machines
            for (U32 i=0; i<numPixels; i++)
            {
                U32 col=*srcData++;
                *destBytes++=col;     // Red
                *destBytes++=col>>8;  // Green
                *destBytes++=col>>16; // Blue
                *destBytes++=col>>24; // Alpha
            }
            MUSHCOREASSERT(srcData == tiffData+width*height);
            MUSHCOREASSERT(destBytes == reinterpret_cast<U8 *>(def.DataPtr()+width*height));
            _TIFFfree(tiffData);
            tiffData=NULL;
            AddTextureDef(def);
        }
    }
    catch (...)
    {
        TIFFClose(pTiff);
        if (tiffData != NULL)
        {
            _TIFFfree(tiffData);
        }
        throw;
    }
    TIFFClose(pTiff);   
}

const char *
GLTextureTIFF::FiletypeName(void) const
{
    return "TIFF";
}
