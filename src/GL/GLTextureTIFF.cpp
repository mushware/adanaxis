/*
 * $Id: GLTextureTIFF.cpp,v 1.2 2002/05/28 16:37:40 southa Exp $
 * $Log: GLTextureTIFF.cpp,v $
 * Revision 1.2  2002/05/28 16:37:40  southa
 * Texture references and decomposer
 *
 * Revision 1.1  2002/05/28 13:07:00  southa
 * Command parser extensions and TIFF loader
 *
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
            tSize u32Size=numPixels;
            tiffData=reinterpret_cast<uint32 *>(_TIFFmalloc(sizeof(uint32)*width*height));

            // TextureDef takes ownership of the block
            TextureDef def(new U32[u32Size]);
           
            def.WidthSet(width);
            def.HeightSet(height);
            def.PixelFormatSet(GL_RGBA);
            def.PixelTypeSet(GL_UNSIGNED_BYTE);

            TIFFReadRGBAImage(pTiff, width, height, tiffData, 0);

            uint32 *srcData=tiffData;
            U32 *destData=def.DataPtr();
            COREASSERT(srcData != NULL);
            COREASSERT(destData != NULL);
            // Convert from ABGR (from tifflib) into RGBA
            for (U32 i=0; i<numPixels; i++)
            {
                U32 col=*srcData++;
                U8 *bytePtr=(U8 *)destData;
                *bytePtr++=col;
                *bytePtr++=col>>8;
                *bytePtr++=col>>16;
                *bytePtr++=col>>24;
                destData++;
#if 0
#ifdef WORDS_BIGENDIAN
                *destData++=
                    (col & 0xff) << 24 |
                    (col & 0xff00) << 8 |
                    (col & 0xff0000) >> 8 |
                    (col & 0xff000000)>> 24;
#else
                *destData++=col;
#endif
#endif
                    
            }
            COREASSERT(srcData == tiffData+width*height);
            COREASSERT(destData == def.DataPtr()+width*height);
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
