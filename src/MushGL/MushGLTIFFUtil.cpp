//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLTIFFUtil.cpp
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
//%Header } EzhJwVdbrpgkBRj83y0y9w
/*
 * $Id: MushGLTIFFUtil.cpp,v 1.5 2007/04/18 09:22:36 southa Exp $
 * $Log: MushGLTIFFUtil.cpp,v $
 * Revision 1.5  2007/04/18 09:22:36  southa
 * Header and level fixes
 *
 * Revision 1.4  2006/08/03 15:07:58  southa
 * Cache purge fix
 *
 * Revision 1.3  2006/07/28 16:52:21  southa
 * Options work
 *
 * Revision 1.2  2006/06/27 11:58:09  southa
 * Warning fixes
 *
 * Revision 1.1  2006/06/05 11:48:25  southa
 * Noise textures
 *
 */

#include "MushGLTIFFUtil.h"

namespace tiffio
{
#include "tiffio.h"
}

using namespace Mushware;
using namespace std;

void
MushGLTIFFUtil::FieldsSet(void *inpTIFF, const std::string& inDesc, const Mushware::t2U32& inSize,
						  Mushware::U32 inRowsPerStrip)
{
	tiffio::TIFF *pTIFF = reinterpret_cast<tiffio::TIFF *>(inpTIFF);
	
	tiffio::TIFFSetField(pTIFF, TIFFTAG_IMAGEWIDTH, inSize.X());
	tiffio::TIFFSetField(pTIFF, TIFFTAG_IMAGELENGTH, inSize.Y());
	tiffio::TIFFSetField(pTIFF, TIFFTAG_BITSPERSAMPLE, 8);
	tiffio::TIFFSetField(pTIFF, TIFFTAG_SAMPLESPERPIXEL, 4);
	tiffio::TIFFSetField(pTIFF, TIFFTAG_ROWSPERSTRIP, inRowsPerStrip);
#ifdef MUSHCORE_DEBUG
	tiffio::TIFFSetField(pTIFF, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
#else
	tiffio::TIFFSetField(pTIFF, TIFFTAG_COMPRESSION, COMPRESSION_DEFLATE);	
#endif
	tiffio::TIFFSetField(pTIFF, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
	tiffio::TIFFSetField(pTIFF, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
	tiffio::TIFFSetField(pTIFF, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	tiffio::TIFFSetField(pTIFF, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
	tiffio::TIFFSetField(pTIFF, TIFFTAG_XRESOLUTION, 150.0);
	tiffio::TIFFSetField(pTIFF, TIFFTAG_YRESOLUTION, 150.0);
	tiffio::TIFFSetField(pTIFF, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);
	
	short int extraSamples[] = { EXTRASAMPLE_ASSOCALPHA };
	tiffio::TIFFSetField(pTIFF, TIFFTAG_EXTRASAMPLES, static_cast<short>(1), extraSamples);
	
	std::time_t timeNow = std::time(NULL);
	std::vector<char> timeBuffer(64, '0');
	MUSHCOREASSERT(timeBuffer.size() == 64);
	std::strftime(&timeBuffer[0], timeBuffer.size()-1, "%Y:%m:%d %H:%M:%S", std::gmtime(&timeNow));
	tiffio::TIFFSetField(pTIFF, TIFFTAG_DATETIME, &timeBuffer[0]);

    tiffio::TIFFSetField(pTIFF, TIFFTAG_IMAGEDESCRIPTION, inDesc.c_str());
	tiffio::TIFFSetField(pTIFF, TIFFTAG_SOFTWARE, MushcoreInfo::Sgl().PackageID().c_str());
}

void
MushGLTIFFUtil::RGBASave(const std::string& inFilename, const std::string& inDesc,
						 const Mushware::t2U32& inSize, const Mushware::U8 *pData)
{
	const U32 rowsPerStrip = 16;
		
	tiffio::TIFF *pTIFF = tiffio::TIFFOpen(inFilename.c_str(), "w");
	
	if (pTIFF == NULL)
	{
		throw MushcoreFileFail(inFilename, "Could not open TIFF file to write");
	}
		
	FieldsSet(pTIFF, inDesc, inSize, rowsPerStrip);
	
	const U32 bytesPerRow = 4*inSize.X();
	const U32 bytesPerStrip = rowsPerStrip * bytesPerRow;
	const U32 numFullStrips = inSize.Y() / rowsPerStrip;
	const U32 lastStripSize = inSize.Y() % rowsPerStrip;
	
	for (U32 i=0; i < numFullStrips; ++i)
	{
		if (tiffio::TIFFWriteEncodedStrip(pTIFF, i, &const_cast<Mushware::U8 *>(pData)[i*bytesPerStrip], bytesPerStrip) == -1)
		{
			throw MushcoreRequestFail("TIFF write attempt failed");	
		}
	}
	
	if (lastStripSize > 0)
	{
		if (tiffio::TIFFWriteEncodedStrip(pTIFF, numFullStrips, &const_cast<Mushware::U8 *>(pData)[numFullStrips*bytesPerStrip], bytesPerRow * lastStripSize) == -1)
		{
			throw MushcoreRequestFail("TIFF write attempt failed");	
		}
	}
	
	tiffio::TIFFClose(pTIFF);
}

void
MushGLTIFFUtil::RGBASave(const std::string& inFilename, const std::string& inDesc,
						 const Mushware::t2U32& inSize, std::vector<Mushware::U8> inData)
{
    if (inData.size() != 4*inSize.X()*inSize.Y())
    {
        throw MushcoreRequestFail("TIFF dimensions and data size do not match");
    }
    RGBASave(inFilename, inDesc, inSize, &inData[0]);
}    

void
MushGLTIFFUtil::ValSave(const std::string& inFilename, const std::string& inDesc,
						const Mushware::t2U32& inSize, const Mushware::tVal *inpData)
{
	// Debug function, so write file as a single strip
	U32 numPixels = inSize.X() * inSize.Y();
	
	std::vector<U8> rgbaData(numPixels*4);
	
	U8 *pData = &rgbaData[0];
	for (U32 i=0; i<numPixels; ++i)
	{
		tVal value = inpData[i];
		if (value < 0.0) value = 0.0;
		if (value > 1.0) value = 1.0;
		*pData++ = static_cast<U8>(value*255); // red
		*pData++ = static_cast<U8>(value*255); // green
		*pData++ = static_cast<U8>(value*255); // blue
		*pData++ = 255;       // alpha
	}
	
	tiffio::TIFF *pTIFF = tiffio::TIFFOpen(inFilename.c_str(), "w");
	
	if (pTIFF == NULL)
	{
		throw MushcoreFileFail(inFilename, "Could not open TIFF file to write");
	}

	FieldsSet(pTIFF, inDesc, inSize, inSize.Y());
		
	if (tiffio::TIFFWriteEncodedStrip(pTIFF, 0, &rgbaData[0], rgbaData.size()) == -1)
	{
		throw MushcoreRequestFail("TIFF write attempt failed");	
	}

	tiffio::TIFFClose(pTIFF);
}

void
MushGLTIFFUtil::TextureSave(const std::string& inFilename, const std::string& inDesc)
{
	GLint baseLevel = 0;
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &baseLevel);
	GLint width=0, height=0;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, baseLevel, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, baseLevel, GL_TEXTURE_HEIGHT, &height);
	U32 bufferSize = 4*width*height;
	
	std::vector<U8> texData(bufferSize+1);
	texData[bufferSize] = 0xA5;
	
	glGetTexImage(GL_TEXTURE_2D, baseLevel, GL_RGBA, GL_UNSIGNED_BYTE, &texData[0]);
	
	MUSHCOREASSERT(texData[bufferSize] == 0xA5);
	
	RGBASave(inFilename, inDesc, t2U32(width, height), &texData[0]);
}

std::string
MushGLTIFFUtil::CreatorGet(const std::string& inFilename)
{
    tiffio::TIFF *pTIFF = tiffio::TIFFOpen(inFilename.c_str(), "r");
	
	if (pTIFF == NULL)
	{
		throw MushcoreFileFail(inFilename, "Could not open TIFF file to read creator");
	}

    std::string retVal;

    {
        const char *pTag;
        tiffio::TIFFGetField(pTIFF, TIFFTAG_SOFTWARE, &pTag);
    
        if (pTag != NULL)
        {
            retVal = pTag;
        }
        else
        {
            retVal = "";
        }
    }
    tiffio::TIFFClose(pTIFF);
    return retVal;
}
