//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLPixelSourceTIFF.cpp
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
//%Header } b2R9I21mLtaCUT6e0Rfwuw
/*
 * $Id: MushGLPixelSourceTIFF.cpp,v 1.9 2007/04/18 09:22:35 southa Exp $
 * $Log: MushGLPixelSourceTIFF.cpp,v $
 * Revision 1.9  2007/04/18 09:22:35  southa
 * Header and level fixes
 *
 * Revision 1.8  2006/11/09 23:53:59  southa
 * Explosion and texture loading
 *
 * Revision 1.7  2006/11/07 11:08:54  southa
 * Texture loading from mushfiles
 *
 * Revision 1.6  2006/06/07 12:15:19  southa
 * Grid and test textures
 *
 * Revision 1.5  2006/06/06 17:58:32  southa
 * Ruby texture definition
 *
 * Revision 1.4  2006/06/02 18:14:35  southa
 * Texture caching
 *
 * Revision 1.3  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.2  2005/08/29 18:40:56  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/08/28 22:41:52  southa
 * MushGLTexture work
 *
 */

#include "MushGLPixelSourceTIFF.h"

#include "MushGLTexture.h"

#include "API/mushMushFile.h"

namespace tiffio
{
#include "tiffio.h"
}

using namespace Mushware;
using namespace std;

MushGLPixelSourceTIFF::MushGLPixelSourceTIFF()
{
	// Don't cache TIFFs by default
	CacheableSet(false);	
}


// Veneers matching tifflib types to MushFile types (because the size of tsize_t varies)
static tiffio::tsize_t
MushGLPixelSourceTIFFRead(tiffio::thandle_t inHandle, tiffio::tdata_t inData, tiffio::tsize_t inSize)
{
    return MushFileFile::TIFFRead(inHandle, inData, inSize);
}

static tiffio::tsize_t
MushGLPixelSourceTIFFWrite(tiffio::thandle_t inHandle, tiffio::tdata_t inData, tiffio::tsize_t inSize)
{
    return MushFileFile::TIFFRead(inHandle, inData, inSize);
}

static tiffio::toff_t
MushGLPixelSourceTIFFSeek(tiffio::thandle_t inHandle, tiffio::toff_t inOffset, int inFrom)
{
   return MushFileFile::TIFFSeek(inHandle, inOffset, inFrom);
}

static int
MushGLPixelSourceTIFFClose(tiffio::thandle_t inHandle)
{
   return MushFileFile::TIFFClose(inHandle);
}

static tiffio::toff_t
MushGLPixelSourceTIFFSize(tiffio::thandle_t inHandle)
{
    return MushFileFile::TIFFSize(inHandle);
}

static int
MushGLPixelSourceTIFFMapFileProc(tiffio::thandle_t inHandle, tiffio::tdata_t *inData, tiffio::toff_t *inOffset)
{
    throw MushcoreLogicFail("TIFFMapFileProc called");
}

static void
MushGLPixelSourceTIFFUnmapFileProc(tiffio::thandle_t inHandle, tiffio::tdata_t inData, tiffio::toff_t inOffset)
{
    throw MushcoreLogicFail("TIFFUnmapFileProc called");
}

void
MushGLPixelSourceTIFF::ToTextureCreate(MushGLTexture& outTexture)
{
    tiffio::uint32 *pTIFFData = NULL;

	// Suppress error message on stderr
#ifndef MUSHCORE_DEBUG
    tiffio::TIFFErrorHandler currentHandler = tiffio::TIFFSetErrorHandler(NULL);
#endif
	
	tiffio::TIFF* pTIFF = NULL;
    
    MushFileFile srcFile;
    srcFile.OpenForRead(m_filename);
    
    if (srcFile.SourceIsFile())
    {
        pTIFF = tiffio::TIFFOpen(srcFile.PlainFilename().c_str(), "r");
    }
    else if (srcFile.SourceIsMush())
    {
        pTIFF = tiffio::TIFFClientOpen(srcFile.Name().c_str(), "rm", // m-> no memory-mapped files
                                       reinterpret_cast<tiffio::thandle_t>(&srcFile), // Handle
                                       MushGLPixelSourceTIFFRead,  // readproc
                                       MushGLPixelSourceTIFFWrite, // writeproc
                                       MushGLPixelSourceTIFFSeek,  // seekproc
                                       MushGLPixelSourceTIFFClose, // closeproc
                                       MushGLPixelSourceTIFFSize,  // sizeproc
                                       MushGLPixelSourceTIFFMapFileProc,  // mapproc
                                       MushGLPixelSourceTIFFUnmapFileProc); //unmapproc
    }
    
#ifndef MUSHCORE_DEBUG
	tiffio::TIFFSetErrorHandler(currentHandler);
#endif
    
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
            
			// Change the orientation so that we vertically flip the image as we load it
			tiffio::TIFFSetField(pTIFF, TIFFTAG_ORIENTATION, ORIENTATION_BOTLEFT);

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
            outTexture.CompressSet(Compress());
            outTexture.PixelDataUse(pTIFFData);
            if (srcFile.SourceIsMush())
            {
                outTexture.SaveableSet(false);
            }
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

void
MushGLPixelSourceTIFF::ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue)
{
	std::string nameStr = inName.String();
	
	if (nameStr == "filename")
    {
		m_filename = inValue.String();
	}
	else
	{
		MushGLPixelSource::ParamDecode(inName, inValue);
	}
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
