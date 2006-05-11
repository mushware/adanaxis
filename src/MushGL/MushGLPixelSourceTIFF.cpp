//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLPixelSourceTIFF.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } SaBXzXzmz9pA2fL3GoZFMQ
/*
 * $Id: MushGLPixelSourceTIFF.cpp,v 1.2 2005/08/29 18:40:56 southa Exp $
 * $Log: MushGLPixelSourceTIFF.cpp,v $
 * Revision 1.2  2005/08/29 18:40:56  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/08/28 22:41:52  southa
 * MushGLTexture work
 *
 */

#include "MushGLPixelSourceTIFF.h"

#include "MushGLTexture.h"

namespace tiffio
{
#include "tiffio.h"
}

using namespace Mushware;
using namespace std;

void
MushGLPixelSourceTIFF::ValueParameterSet(Mushware::U32 inNum, Mushware::tLongVal inVal)
{
    switch (inNum)
    {
        default:
            MushGLPixelSource::ValueParameterSet(inNum, inVal);
            break;
    }
}

void
MushGLPixelSourceTIFF::StringParameterSet(Mushware::U32 inNum, const std::string& inStr)
{
    switch (inNum)
    {
        case kParamFilename:
            m_filename = inStr;
            break;

        default:
            MushGLPixelSource::StringParameterSet(inNum, inStr);
            break;
    }
}

void
MushGLPixelSourceTIFF::ToTextureCreate(MushGLTexture& outTexture)
{
    tiffio::uint32 *pTIFFData = NULL;

    tiffio::TIFF* pTIFF = tiffio::TIFFOpen(m_filename.c_str(), "r");
    
    if (pTIFF == NULL)
    {
        throw MushcoreFileFail(m_filename, "Could not open file");
    }

    try
    {
        // Needs extending for multi image TIFFs
        for (U32 imageNum=0; imageNum < 1; ++imageNum)
        {
            tiffio::uint32 width, height;
            
            tiffio::TIFFGetField(pTIFF, TIFFTAG_IMAGEWIDTH, &width);
            tiffio::TIFFGetField(pTIFF, TIFFTAG_IMAGELENGTH, &height);            
            
            U32 numPixels=width*height;
            pTIFFData = reinterpret_cast<tiffio::uint32 *>(tiffio::_TIFFmalloc(sizeof(tiffio::uint32)*width*height));
            
            if (pTIFFData == NULL)
            {
                throw MushcoreRequestFail("Malloc failure for TIFF");
            }
            
            tiffio::TIFFReadRGBAImage(pTIFF, width, height, pTIFFData, 0);
            
            tiffio::uint32 *pSrcData = pTIFFData;
            U8 *pDestData = reinterpret_cast<U8 *>(pTIFFData);
            
            // Convert from ABGR words (from tifflib) into RGBA bytes.  Has to work on big
            // and little endian machines
            for (U32 i=0; i<numPixels; i++)
            {
                U32 col=*pSrcData++;
                *pDestData++=col;     // Red
                *pDestData++=col>>8;  // Green
                *pDestData++=col>>16; // Blue
                *pDestData++=col>>24; // Alpha
            }
            MUSHCOREASSERT(pSrcData == pTIFFData+width*height);
            MUSHCOREASSERT(pDestData == reinterpret_cast<U8 *>(pTIFFData+width*height));
            
            // Bind the texture
            outTexture.SizeSet(t4U32(width, height, 1, 1));
            outTexture.PixelTypeRGBASet();
            outTexture.StorageTypeSet(StorageType());
            outTexture.PixelDataUse(pTIFFData);
            
            tiffio::_TIFFfree(pTIFFData);
            pTIFFData=NULL;
        }
    }
    catch (...)
    {
        tiffio::TIFFClose(pTIFF);
        if (pTIFFData != NULL)
        {
            tiffio::_TIFFfree(pTIFFData);
        }
        throw;
    }
    tiffio::TIFFClose(pTIFF);
}

//%outOfLineFunctions {

const char *MushGLPixelSourceTIFF::AutoName(void) const
{
    return "MushGLPixelSourceTIFF";
}

MushcoreVirtualObject *MushGLPixelSourceTIFF::AutoClone(void) const
{
    return new MushGLPixelSourceTIFF(*this);
}

MushcoreVirtualObject *MushGLPixelSourceTIFF::AutoCreate(void) const
{
    return new MushGLPixelSourceTIFF;
}

MushcoreVirtualObject *MushGLPixelSourceTIFF::AutoVirtualFactory(void)
{
    return new MushGLPixelSourceTIFF;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLPixelSourceTIFF", MushGLPixelSourceTIFF::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLPixelSourceTIFF::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "filename=" << m_filename;
    ioOut << "]";
}
bool
MushGLPixelSourceTIFF::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "filename")
    {
        ioIn >> m_filename;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLPixelSourceTIFF::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("filename");
    ioOut << m_filename;
}
//%outOfLineFunctions } Tkm2IzZ5ojau36+Dkqqx5w