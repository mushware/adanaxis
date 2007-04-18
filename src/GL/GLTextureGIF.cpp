//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureGIF.cpp
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } js7BlKdU+aF75k2CIbviFg
/*
 * $Id: GLTextureGIF.cpp,v 1.23 2006/06/01 15:38:54 southa Exp $
 * $Log: GLTextureGIF.cpp,v $
 * Revision 1.23  2006/06/01 15:38:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.22  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.21  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.20  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.19  2004/01/01 21:15:45  southa
 * Created XCode project
 *
 * Revision 1.18  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.17  2003/08/21 23:08:31  southa
 * Fixed file headers
 *
 * Revision 1.16  2003/02/05 16:19:45  southa
 * Build fixes
 *
 * Revision 1.15  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.14  2003/01/12 17:32:51  southa
 * Mushcore work
 *
 * Revision 1.13  2003/01/09 14:56:59  southa
 * Created Mushcore
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
 * Revision 1.9  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.6  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.4  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 * Revision 1.3  2002/05/24 18:10:43  southa
 * MushcoreXML and game map
 *
 * Revision 1.2  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/02/25 23:03:51  southa
 * Subclassed GLTexture
 *
 */

#include "GLTextureGIF.h"

#if 0
namespace libgif
{
extern "C"
{
#include "gif_lib.h"
}
}
#endif
#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLTextureGIF::GLTextureGIF(const string& inFilename)
{

    throw(MushcoreFileFail(inFilename, "Could not open file - unsupported format (RiscOS)"));
#if 0
    libgif::GifFileType *gif;
    FilenameSet(inFilename);

    gif = libgif::DGifOpenFileName(inFilename.c_str());

    if (gif == NULL)
    {
        ThrowGifError(inFilename, libgif::GifLastError());
    }
    
    // Try block calls DGifCloseFile on fault
    try
    {
        if (libgif::DGifSlurp(gif) != GIF_OK)
        {
            ThrowGifError(inFilename, libgif::GifLastError());
        }

        for (int imageNum=0; imageNum < gif->ImageCount; ++imageNum)
        {
            struct libgif::SavedImage *image = &gif->SavedImages[imageNum];
            libgif::ColorMapObject *colorMap = image->ImageDesc.ColorMap;

            if (colorMap == NULL) colorMap=gif->SColorMap;
            if (colorMap == NULL)
            {
                throw(MushcoreFileFail(inFilename, "GIF with no colorMap"));
            }

            libgif::GifColorType *colors=colorMap->Colors;
            int colIndexLimit=1 << colorMap->BitsPerPixel;
            U32 u32Size=image->ImageDesc.Width*image->ImageDesc.Height;

            GLTextureDef def(new U32[u32Size]);

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
                    throw(MushcoreFileFail(inFilename, "Cannot load interlaced GIF"));
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
                        throw(MushcoreFileFail(inFilename, "GIF color index out of range"));
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
                    throw(MushcoreFileFail(inFilename, "Pointer mismatch"));
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
#endif
}

const char *
GLTextureGIF::FiletypeName(void) const
{
    return "GIF";
}

void
GLTextureGIF::ThrowGifError(const string& inFilename, int inRC)
{
#if 0
    switch (inRC)
    {
        case D_GIF_ERR_OPEN_FAILED:
            throw(MushcoreFileFail(inFilename, "GIF file open failed"));
        case D_GIF_ERR_READ_FAILED:
            throw(MushcoreFileFail(inFilename, "GIF file read failed"));
        case D_GIF_ERR_NOT_GIF_FILE:
            throw(MushcoreFileFail(inFilename, "Not a GIF file"));
        case D_GIF_ERR_NO_SCRN_DSCR:
            throw(MushcoreFileFail(inFilename, "GIF no screen description"));
        case D_GIF_ERR_NO_IMAG_DSCR:
            throw(MushcoreFileFail(inFilename, "GIF no image description"));
        case D_GIF_ERR_NO_COLOR_MAP:
            throw(MushcoreFileFail(inFilename, "GIF no colour map"));
        case D_GIF_ERR_WRONG_RECORD:
            throw(MushcoreFileFail(inFilename, "GIF wrong record"));
        case D_GIF_ERR_DATA_TOO_BIG:
            throw(MushcoreFileFail(inFilename, "GIF data too big"));
        case D_GIF_ERR_NOT_ENOUGH_MEM:
            throw(MushcoreFileFail(inFilename, "GIF non enough memory"));
        case D_GIF_ERR_CLOSE_FAILED:
            throw(MushcoreFileFail(inFilename, "GIF close failed"));
        case D_GIF_ERR_NOT_READABLE:
            throw(MushcoreFileFail(inFilename, "GIF not readable"));
        case D_GIF_ERR_IMAGE_DEFECT:
            throw(MushcoreFileFail(inFilename, "GIF image defect"));
        case D_GIF_ERR_EOF_TOO_SOON:
            throw(MushcoreFileFail(inFilename, "GIF EOF too soon"));

        default:
            throw(MushcoreFileFail(inFilename, "Unknown GIF error"));
    }
#endif
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
