//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceTest.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } z7GIR5rZlSZBeKpGQS4AoQ
/*
 * $Id$
 * $Log$
 */

#include "MushSkinPixelSourceTest.h"

using namespace Mushware;
using namespace std;

MushSkinPixelSourceTest::MushSkinPixelSourceTest() :
	m_xSize(0),
	m_ySize(0),
	m_pPaletteTexture(NULL)
{
    m_lineGenerator.CellNoiseInitialise(0);
}

void
MushSkinPixelSourceTest::ValueParameterSet(Mushware::U32 inNum, Mushware::tLongVal inVal)
{
    switch (inNum)
    {
        case kParamXSize:
            m_xSize = static_cast<U32>(inVal);
            break;
            
        case kParamYSize:
            m_ySize = static_cast<U32>(inVal);
            break;
            
        case kParamPaletteStartX:
            m_paletteStart.XSet(inVal);
            break;
            
        case kParamPaletteStartY:
            m_paletteStart.YSet(inVal);
            break;
            
        case kParamPaletteVector1X:
            m_paletteVector1.XSet(inVal);
            break;
            
        case kParamPaletteVector1Y:
            m_paletteVector1.YSet(inVal);
            break;
            
        case kParamPaletteVector2X:
            m_paletteVector2.XSet(inVal);
            break;
            
        case kParamPaletteVector2Y:
            m_paletteVector2.YSet(inVal);
            break;
            
        default:
            MushGLPixelSource::ValueParameterSet(inNum, inVal);
            break;
    }
}

void
MushSkinPixelSourceTest::StringParameterSet(Mushware::U32 inNum, const std::string& inStr)
{
    switch (inNum)
    {
        case kParamSourceName:
            m_sourceName = inStr;
            break;
            
        case kParamPaletteName:
            m_paletteName = inStr;
            break;
            
        default:
            MushGLPixelSource::StringParameterSet(inNum, inStr);
            break;
    }
}

void 
MushSkinPixelSourceTest::LineGenerate(Mushware::U8 *outpTileData, Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos)
{
    if (m_pPaletteTexture != NULL)
    {
		std::vector<tVal> noiseValues(inNumPixels);
		
		m_lineGenerator.OctavedCellNoiseLineGenerate(noiseValues, inNumPixels, inStartPos, inEndPos, 8);
		
		
		MushSkinUtil::PalettedToRGBA(outpTileData, &noiseValues[0], inNumPixels,
									 *m_pPaletteTexture, m_paletteStart, m_paletteVector1);																							
	}
}

void
MushSkinPixelSourceTest::ToTextureCreate(MushGLTexture& outTexture)
{
    U32 pixelDataSize = 4*m_xSize*m_ySize;
    std::vector<U8> pixelData(pixelDataSize, 0);
    
    t4Val objectPos, objectEndPos;
    
    m_pPaletteTexture = NULL;
    
    if (m_paletteName != "")
    {
        if (!MushcoreData<MushGLTexture>::Sgl().GetIfExists(m_pPaletteTexture, m_paletteName))
        {
            throw MushcoreDataFail("Non-existent palette '"+m_paletteName+"'");
        }
        m_pPaletteTexture->Make();
    }
	
	t2Val startPoint = t2Val(0.0, 0.0);
	t2Val endPoint = t2Val(1.0, 1.0);
	U32 startX = static_cast<U32>(startPoint.X() * m_xSize);
	U32 startY = static_cast<U32>(startPoint.Y() * m_ySize);
	U32 endX = static_cast<U32>(endPoint.X() * m_xSize);
	U32 endY = static_cast<U32>(endPoint.Y() * m_ySize);
	MUSHCOREASSERT(endX >= startX);
	MUSHCOREASSERT(endY >= startY);
	
	for (U32 y=startY; y<endY; ++y)
	{
		U32 pixelOffset = 4*(startX+y*m_ySize);
		if (pixelOffset + 4*(endX - startX) > pixelDataSize)
		{
			throw MushcoreDataFail("Pixel data overrun");
		}
		U8 *pTileData = &pixelData[pixelOffset];
		
		objectPos = 10*t4Val(static_cast<tVal>(startX) / m_xSize, static_cast<tVal>(y) / m_ySize, 0.55, 0.55);
		objectEndPos = 10*t4Val(static_cast<tVal>(endX) / m_xSize, static_cast<tVal>(y) / m_ySize, 0.55, 0.55);
		
		if (endX > startX)
		{
			LineGenerate(pTileData, endX - startX, objectPos, objectEndPos);
		}
		
	}
	
    m_pPaletteTexture = NULL;
    
    // Bind the texture
    outTexture.SizeSet(t4U32(m_xSize, m_ySize, 1, 1));
    outTexture.PixelTypeRGBASet();
    outTexture.StorageTypeGLSet();
    outTexture.PixelDataUse(&pixelData[0]);
	
	MushGLTIFFUtil::TextureSave(MushGLCacheControl::Sgl().TextureCachePlainFilenameMake("testtexture.tiff"), SourceName());
}
//%outOfLineFunctions {

const char *MushSkinPixelSourceTest::AutoName(void) const
{
    return "MushSkinPixelSourceTest";
}

MushcoreVirtualObject *MushSkinPixelSourceTest::AutoClone(void) const
{
    return new MushSkinPixelSourceTest(*this);
}

MushcoreVirtualObject *MushSkinPixelSourceTest::AutoCreate(void) const
{
    return new MushSkinPixelSourceTest;
}

MushcoreVirtualObject *MushSkinPixelSourceTest::AutoVirtualFactory(void)
{
    return new MushSkinPixelSourceTest;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinPixelSourceTest", MushSkinPixelSourceTest::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinPixelSourceTest::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "paletteStart=" << m_paletteStart << ", ";
    ioOut << "paletteVector1=" << m_paletteVector1 << ", ";
    ioOut << "paletteVector2=" << m_paletteVector2 << ", ";
    if (m_pPaletteTexture == NULL)
    {
        ioOut << "pPaletteTexture=NULL"  << ", ";
    }
    else
    {
        ioOut << "pPaletteTexture=" << *m_pPaletteTexture << ", ";
    }
    ioOut << "xSize=" << m_xSize << ", ";
    ioOut << "ySize=" << m_ySize << ", ";
    ioOut << "sourceName=" << m_sourceName << ", ";
    ioOut << "paletteName=" << m_paletteName << ", ";
    ioOut << "lineGenerator=" << m_lineGenerator;
    ioOut << "]";
}
bool
MushSkinPixelSourceTest::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "paletteStart")
    {
        ioIn >> m_paletteStart;
    }
    else if (inTagStr == "paletteVector1")
    {
        ioIn >> m_paletteVector1;
    }
    else if (inTagStr == "paletteVector2")
    {
        ioIn >> m_paletteVector2;
    }
    else if (inTagStr == "pPaletteTexture")
    {
        ioIn >> m_pPaletteTexture;
    }
    else if (inTagStr == "xSize")
    {
        ioIn >> m_xSize;
    }
    else if (inTagStr == "ySize")
    {
        ioIn >> m_ySize;
    }
    else if (inTagStr == "sourceName")
    {
        ioIn >> m_sourceName;
    }
    else if (inTagStr == "paletteName")
    {
        ioIn >> m_paletteName;
    }
    else if (inTagStr == "lineGenerator")
    {
        ioIn >> m_lineGenerator;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushSkinPixelSourceTest::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("paletteStart");
    ioOut << m_paletteStart;
    ioOut.TagSet("paletteVector1");
    ioOut << m_paletteVector1;
    ioOut.TagSet("paletteVector2");
    ioOut << m_paletteVector2;
    ioOut.TagSet("pPaletteTexture");
    ioOut << m_pPaletteTexture;
    ioOut.TagSet("xSize");
    ioOut << m_xSize;
    ioOut.TagSet("ySize");
    ioOut << m_ySize;
    ioOut.TagSet("sourceName");
    ioOut << m_sourceName;
    ioOut.TagSet("paletteName");
    ioOut << m_paletteName;
    ioOut.TagSet("lineGenerator");
    ioOut << m_lineGenerator;
}
//%outOfLineFunctions } BkuebSppyaybAlXH5RqiNQ
