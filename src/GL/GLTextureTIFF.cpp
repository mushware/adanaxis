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
 * $Id: GLTextureTIFF.cpp,v 1.11 2002/12/20 13:17:36 southa Exp $
 * $Log: GLTextureTIFF.cpp,v $
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

using namespace Mushware;
using namespace std;

GLTextureTIFF::GLTextureTIFF(const string& inFilename)
{
    FilenameSet(inFilename);
    uint32 *tiffData=NULL;
    TIFF* pTiff = TIFFOpen(inFilename.c_str(), "r");
    if (pTiff == NULL)
    {
        throw(LoaderFail(inFilename, "Could not open file"));
    }

    try
    {
        // Needs extending for multi image TIFFs
        for (int imageNum=0; imageNum < 1; ++imageNum)
        {
            uint32 width, height;

            TIFFGetField(pTiff, TIFFTAG_IMAGEWIDTH, &width);
            TIFFGetField(pTiff, TIFFTAG_IMAGELENGTH, &height);

            tSize numPixels=width*height;
            tSize u32Size=numPixels;
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
            COREASSERT(srcData != NULL);
            COREASSERT(destBytes != NULL);
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
            COREASSERT(srcData == tiffData+width*height);
            COREASSERT(destBytes == reinterpret_cast<U8 *>(def.DataPtr()+width*height));
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
