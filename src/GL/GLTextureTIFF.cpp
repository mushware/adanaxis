/*
 * $Id$
 * $Log$
 */

#include "GLTextureTIFF.h"

#include "tiffio.h"

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
            tSize memSize=4*numPixels;
            tiffData=reinterpret_cast<uint32 *>(_TIFFmalloc(sizeof(uint32)*width*height));

            // TextureDef takes ownership of the block
            TextureDef def(new U8[memSize]);
           
            def.WidthSet(width);
            def.HeightSet(height);
            def.PixelFormatSet(GL_RGBA);
            def.PixelTypeSet(GL_UNSIGNED_BYTE);

            TIFFReadRGBAImage(pTiff, width, height, tiffData, 0);

            uint32 *srcData=tiffData;
            U8 *destData=def.DataPtr();
            COREASSERT(srcData != NULL);
            COREASSERT(destData != NULL);
            // Convert from ABGR (from tifflib) into RGBA
            for (U32 i=0; i<numPixels; i++)
            {
                U32 col=*srcData++;
                *destData++=col;
                *destData++=col>>8;
                *destData++=col>>16;
                *destData++=col>>24;
            }
            COREASSERT(srcData == tiffData+width*height);
            COREASSERT(destData == def.DataPtr()+4*width*height);
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
