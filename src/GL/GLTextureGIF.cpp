/*
 * $Id: GLTextureGIF.cpp,v 1.3 2002/05/24 18:10:43 southa Exp $
 * $Log: GLTextureGIF.cpp,v $
 * Revision 1.3  2002/05/24 18:10:43  southa
 * CoreXML and game map
 *
 * Revision 1.2  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/02/25 23:03:51  southa
 * Subclassed GLTexture
 *
 */

#include "GLTextureGIF.h"

extern "C"
{
// Prevent clash with windows.h
#define DrawTextA gif_lib_DrawTextA
#include "gif_lib.h"
#undef DrawTextA
}

GLTextureGIF::GLTextureGIF(const string& inFilename)
{
    GifFileType *gif;
    FilenameSet(inFilename);

    gif = DGifOpenFileName(inFilename.c_str());

    if (gif == NULL)
    {
        ThrowGifError(inFilename, GifLastError());
    }
    
    // Try block calls DGifCloseFile on fault
    try
    {
        if (DGifSlurp(gif) != GIF_OK)
        {
            ThrowGifError(inFilename, GifLastError());
        }

        for (int imageNum=0; imageNum < gif->ImageCount; ++imageNum)
        {
            struct SavedImage *image = &gif->SavedImages[imageNum];
            ColorMapObject *colorMap = image->ImageDesc.ColorMap;

            if (colorMap == NULL) colorMap=gif->SColorMap;
            if (colorMap == NULL)
            {
                throw(LoaderFail(inFilename, "GIF with no colorMap"));
            }

            GifColorType *colors=colorMap->Colors;
            int colIndexLimit=1 << colorMap->BitsPerPixel;
            tSize u32Size=image->ImageDesc.Width*image->ImageDesc.Height;

            TextureDef def(new U32[u32Size]);

            def.WidthSet(image->ImageDesc.Width);
            def.HeightSet(image->ImageDesc.Height);
            def.PixelFormatSet(GL_RGBA);
            def.PixelTypeSet(GL_UNSIGNED_BYTE);

            for (int y=0; y<def.Height(); ++y)
            {
                U32 *outputPtr;
                char *inputPtr;
                if (image->ImageDesc.Interlace)
                {
                    // Not implemeted
                    throw(LoaderFail(inFilename, "Cannot load interlaced GIF"));
                    inputPtr=&image->RasterBits[(def.Height()-1-y)*def.Width()];
                    outputPtr=&def.DataPtr()[y*def.Width()];
                }
                else
                {
                    inputPtr=&image->RasterBits[(def.Height()-1-y)*def.Width()];
                    outputPtr=&def.DataPtr()[y*def.Width()];
                }
                for (int x=0; x<def.Width(); ++x)
                {
                    U8 colIndex=*inputPtr++;
                    if (colIndex > colIndexLimit)
                    {
                        throw(LoaderFail(inFilename, "GIF color index out of range"));
                    }
                    // Pack data into output buffer in RGB order
                    *outputPtr++ =
                        colors[colIndex].Red << 24 |
                        colors[colIndex].Green << 16 |
                        colors[colIndex].Blue << 8 |
                        255; // Alpha
                }
                if (outputPtr > def.DataPtr() + u32Size)
                {
                    throw(LoaderFail(inFilename, "Pointer mismatch"));
                }
            }
            // This step adds a second reference to the def which stops its memory being
            // freed as it goes out of scope
            AddTextureDef(def);
        }
    }
    catch (...)
    {
        DGifCloseFile(gif);
        throw;
    }
}

const char *
GLTextureGIF::FiletypeName(void) const
{
    return "GIF";
}

void
GLTextureGIF::ThrowGifError(const string& inFilename, int inRC)
{
    switch (inRC)
    {
        case D_GIF_ERR_OPEN_FAILED:
            throw(LoaderFail(inFilename, "GIF file open failed"));
        case D_GIF_ERR_READ_FAILED:
            throw(LoaderFail(inFilename, "GIF file read failed"));
        case D_GIF_ERR_NOT_GIF_FILE:
            throw(LoaderFail(inFilename, "Not a GIF file"));
        case D_GIF_ERR_NO_SCRN_DSCR:
            throw(LoaderFail(inFilename, "GIF no screen description"));
        case D_GIF_ERR_NO_IMAG_DSCR:
            throw(LoaderFail(inFilename, "GIF no image description"));
        case D_GIF_ERR_NO_COLOR_MAP:
            throw(LoaderFail(inFilename, "GIF no colour map"));
        case D_GIF_ERR_WRONG_RECORD:
            throw(LoaderFail(inFilename, "GIF wrong record"));
        case D_GIF_ERR_DATA_TOO_BIG:
            throw(LoaderFail(inFilename, "GIF data too big"));
        case D_GIF_ERR_NOT_ENOUGH_MEM:
            throw(LoaderFail(inFilename, "GIF non enough memory"));
        case D_GIF_ERR_CLOSE_FAILED:
            throw(LoaderFail(inFilename, "GIF close failed"));
        case D_GIF_ERR_NOT_READABLE:
            throw(LoaderFail(inFilename, "GIF not readable"));
        case D_GIF_ERR_IMAGE_DEFECT:
            throw(LoaderFail(inFilename, "GIF image defect"));
        case D_GIF_ERR_EOF_TOO_SOON:
            throw(LoaderFail(inFilename, "GIF EOF too soon"));

        default:
            throw(LoaderFail(inFilename, "Unknown GIF error"));
    }
}


#if 0
// Bin for testing code

cerr << "Image " << imageNum << endl;
cerr << "Left="<< image->ImageDesc.Left;
cerr << " Top="<< image->ImageDesc.Top;
cerr << " Width="<< image->ImageDesc.Width;
cerr << " Height="<< image->ImageDesc.Height;
cerr << " Interlace="<< image->ImageDesc.Interlace;
cerr << endl;

cerr << "Colormap colors=" << colorMap->ColorCount << " bpp=" << colorMap->BitsPerPixel << endl;
for (int i=0; i<colorMap->ColorCount; ++i)
{
    cerr << "R=" << (int)colorMap->Colors[i].Red;
    cerr << " G=" << (int)colorMap->Colors[i].Green;
    cerr << " B=" << (int)colorMap->Colors[i].Blue;
    cerr << endl;
}

#endif