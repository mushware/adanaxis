/*
 * $Id: GLTexture.cpp,v 1.4 2002/02/23 17:54:45 southa Exp $
 * $Log: GLTexture.cpp,v $
 * Revision 1.4  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.3  2002/02/20 22:57:57  southa
 * Loading GIF data, texture memory handling
 *
 * Revision 1.2  2002/02/18 22:43:11  southa
 * First stage GIF loader
 *
 * Revision 1.1  2002/02/18 22:03:50  southa
 * Initial texture loading
 *
 */

#include "GLTexture.hp"

extern "C"
{
#include "gif_lib.h"
}

GLTexture::GLTexture(const string& inFilename)
{
    GifFileType *gif;

    gif = DGifOpenFileName(inFilename.c_str());

    if (gif == NULL)
    {
        // PrintGifError();
        ThrowGifError(inFilename, GifLastError());
    }

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
            throw("GIF with no colorMap");
        }        
        
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

        GifColorType *colors=colorMap->Colors;
        int colIndexLimit=1 << colorMap->BitsPerPixel;
        Size memSize=4*image->ImageDesc.Width*image->ImageDesc.Height;

        m_textureDefs.push_back(TextureDef(new U8[memSize]));
        TextureDef& def=m_textureDefs.back();
        def.width=image->ImageDesc.Width;
        def.height=image->ImageDesc.Height;
        def.pixelFormat=GL_RGBA;
        def.pixelType=GL_UNSIGNED_BYTE;

        
        for (int y=0; y<def.height; ++y)
        {
            U8 *outputPtr;
            char *inputPtr;
            if (image->ImageDesc.Interlace)
            {
                inputPtr=&image->RasterBits[(def.height-1-y)*def.width];
                outputPtr=&def.dataPtr[y*def.width*4];
            }
            else
            {
                inputPtr=&image->RasterBits[(def.height-1-y)*def.width];
                outputPtr=&def.dataPtr[y*def.width*4];
            }
            for (int x=0; x<def.width; ++x)
            {
                U8 colIndex=*inputPtr++;
                if (colIndex > colIndexLimit)
                {
                    throw(LoaderFail(inFilename, "GIF color index out of range"));
                }
                // Pack data into output buffer in RGB order
                *outputPtr++ = colors[colIndex].Red;
                *outputPtr++ = colors[colIndex].Green;
                *outputPtr++ = colors[colIndex].Blue;
                *outputPtr++ = 255; // Alpha                
            }
            if (outputPtr > def.dataPtr + memSize)
            {
                throw(LoaderFail(inFilename, "Pointer mismatch"));
            }
        }
    }
    
    DGifCloseFile(gif);
//    m_inFilename=inFilename;
}

ostream&
GLTexture::ostreamPrint(ostream& inOut) const
{
    inOut << "source GIF '" << /*m_inFilename << */"'";
    inOut << " images=" << m_textureDefs.size();
    for (Size i=0; i<m_textureDefs.size(); ++i)
    {
        inOut << "[image " << i << ":";
        inOut << " width=" << Width(i);
        inOut << " height=" << Height(i);
        inOut << " pixelFormat=" << PixelFormat(i);
        inOut << " pixelType=" << PixelType(i);
        inOut << " dataPtr=" << DataPtr(i) << "] ";
    }
    return inOut;
}

void
GLTexture::ThrowGifError(const string& inFilename, int inRC)
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
