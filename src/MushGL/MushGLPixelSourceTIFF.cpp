//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLPixelSourceTIFF.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 6LaCCeNx9/4qv9/BPhQY5w
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

MushGLPixelSourceTIFF::MushGLPixelSourceTIFF() :
    m_pTIFF(NULL),
    m_pTIFFData(NULL),
    m_width(0),
    m_height(0)
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
	// Suppress error message on stderr
#ifndef MUSHCORE_DEBUG
    tiffio::TIFFErrorHandler currentHandler = tiffio::TIFFSetErrorHandler(NULL);
#endif
	
    MushFileFile srcFile;
    srcFile.OpenForRead(m_filename);
    
    if (srcFile.SourceIsFile())
    {
        m_pTIFF = tiffio::TIFFOpen(srcFile.PlainFilename().c_str(), "r");
    }
    else if (srcFile.SourceIsMush())
    {
        m_pTIFF = tiffio::TIFFClientOpen(srcFile.Name().c_str(), "rm", // m-> no memory-mapped files
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
    
    if (m_pTIFF == NULL)
    {
        throw MushcoreFileFail(m_filename, "Could not open file");
    }

    try
    {
        // Needs extending for multi image TIFFs
        for (U32 imageNum=0; imageNum < 1; ++imageNum)
        {
            
            tiffio::TIFFGetField(m_pTIFF, TIFFTAG_IMAGEWIDTH, &m_width);
            tiffio::TIFFGetField(m_pTIFF, TIFFTAG_IMAGELENGTH, &m_height);            
            
			// Change the orientation so that we vertically flip the image as we load it
			tiffio::TIFFSetField(m_pTIFF, TIFFTAG_ORIENTATION, ORIENTATION_BOTLEFT);

            U32 numPixels=m_width*m_height;
            m_pTIFFData = reinterpret_cast<tiffio::uint32 *>(tiffio::_TIFFmalloc(sizeof(tiffio::uint32)*m_width*m_height));
            
            if (m_pTIFFData == NULL)
            {
                throw MushcoreRequestFail("Malloc failure for TIFF");
            }
            
            tiffio::TIFFReadRGBAImage(m_pTIFF, m_width, m_height, m_pTIFFData, 0);
            
            tiffio::uint32 *pSrcData = m_pTIFFData;
            U8 *pDestData = reinterpret_cast<U8 *>(m_pTIFFData);
            
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
            MUSHCOREASSERT(pSrcData == m_pTIFFData+m_width*m_height);
            MUSHCOREASSERT(pDestData == reinterpret_cast<U8 *>(m_pTIFFData+m_width*m_height));
            
            outTexture.SizeSet(t4U32(m_width, m_height, 1, 1));
            outTexture.PixelTypeRGBASet();
            outTexture.StorageTypeSet(StorageType());
            outTexture.CompressSet(Compress());

            if (srcFile.SourceIsMush())
            {
                outTexture.SaveableSet(false);
            }
        }
    }
    catch (...)
    {
        if (m_pTIFFData != NULL)
        {
            tiffio::_TIFFfree(m_pTIFFData);
            m_pTIFFData = NULL;
        }
        if (m_pTIFF != NULL)
        {
            tiffio::TIFFClose(m_pTIFF);
            m_pTIFF = NULL;
        }
        throw;
    }
}


void
MushGLPixelSourceTIFF::ToTextureBind(MushGLTexture& outTexture)
{
    try {
        // Bind the texture
        outTexture.PixelDataUse(m_pTIFFData);
    }
    catch (...)
    {
        if (m_pTIFFData != NULL)
        {
            tiffio::_TIFFfree(m_pTIFFData);
            m_pTIFFData = NULL;
        }
        if (m_pTIFF != NULL)
        {
            tiffio::TIFFClose(m_pTIFF);
            m_pTIFF = NULL;
        }
        throw;
    }
    if (m_pTIFFData != NULL)
    {
        tiffio::_TIFFfree(m_pTIFFData);
        m_pTIFFData = NULL;
    }
    if (m_pTIFF != NULL)
    {
        tiffio::TIFFClose(m_pTIFF);
        m_pTIFF = NULL;
    }
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
    ioOut << "filename=" << m_filename << ", ";
    if (m_pTIFFData == NULL)
    {
        ioOut << "pTIFFData=NULL"  << ", ";
    }
    else
    {
        ioOut << "pTIFFData=" << *m_pTIFFData << ", ";
    }
    ioOut << "width=" << m_width << ", ";
    ioOut << "height=" << m_height;
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
    else if (inTagStr == "pTIFFData")
    {
        ioIn >> m_pTIFFData;
    }
    else if (inTagStr == "width")
    {
        ioIn >> m_width;
    }
    else if (inTagStr == "height")
    {
        ioIn >> m_height;
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
    ioOut.TagSet("pTIFFData");
    ioOut << m_pTIFFData;
    ioOut.TagSet("width");
    ioOut << m_width;
    ioOut.TagSet("height");
    ioOut << m_height;
}
//%outOfLineFunctions } wGzQgJ4e29Lgx6vWH018Ug
