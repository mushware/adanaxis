/*
 * $Id: GLTexture.cpp,v 1.1 2002/02/18 22:03:50 southa Exp $
 * $Log: GLTexture.cpp,v $
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
        
    m_xSize=100;
    m_ySize=100;
    m_hBytes=m_xSize*4;
    m_data=new U8[m_ySize * m_hBytes];
    U8 col=0;
    for (Size i=0; i<sizeof(U32) * m_ySize * m_hBytes; i++)
    {
        m_data[i] = col++;
    }
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
