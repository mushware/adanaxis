//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceTileShow.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /n7iHban2HSDlRD4YHGVjQ
/*
 * $Id: MushSkinPixelSourceTileShow.cpp,v 1.1 2006/06/09 21:07:14 southa Exp $
 * $Log: MushSkinPixelSourceTileShow.cpp,v $
 * Revision 1.1  2006/06/09 21:07:14  southa
 * Tiled skin generation
 *
 */

#include "MushSkinPixelSourceTileShow.h"

using namespace Mushware;
using namespace std;

MushSkinPixelSourceTileShow::MushSkinPixelSourceTileShow()
{
}

void
MushSkinPixelSourceTileShow::ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue)
{
	std::string nameStr = inName.String();

	{
		MushSkinPixelSourceProc::ParamDecode(inName, inValue);
	}
}

void
MushSkinPixelSourceTileShow::TileShowLineGenerate(Mushware::U8 *outpTileData,
												  Mushware::U32 inNumPixels, const std::vector<Mushware::t4Val>& texCoords,
												  const Mushware::t4Val& inStartUV, const Mushware::t4Val& inEndUV)
{
	MUSHCOREASSERT(PaletteTextureValid());

	std::vector<tVal> colourValues(inNumPixels);
	
	m_lineGenerator.TileShowLineGenerate(colourValues, inNumPixels, texCoords, inStartUV, inEndUV);
	
	MushSkinUtil::PalettedToRGBA(outpTileData, &colourValues[0], inNumPixels,
								 PaletteTexture(), PaletteStart(), PaletteVector1());																					
}

void
MushSkinPixelSourceTileShow::ToTextureCreate(MushGLTexture& outTexture)
{
    U32 pixelDataSize = 4*Size().X()*Size().Y();
    std::vector<U8> pixelData(pixelDataSize, 0);
    
    const MushMesh4Mesh::tTextureTiles& texTilesRef = Mesh().TextureTiles();
    U32 numTexTiles = texTilesRef.size();
	
    for (U32 tileIndex = 0; tileIndex < numTexTiles; ++tileIndex)
    {
        const MushMesh4Mesh::tTextureTile& tileRef = texTilesRef[tileIndex];
        
		std::vector<t4Val> texCoords;
		MushMeshTools::TextureCoordsForFacet(texCoords, Mesh(), tileRef.SourceFaceNum(), tileRef.SourceFacetNum());
		
        t2Val startPoint = tileRef.TileBox().Start();
        t2Val endPoint = tileRef.TileBox().End();
		
        U32 startX = static_cast<U32>(startPoint.X() * Size().X());
        U32 startY = static_cast<U32>(startPoint.Y() * Size().Y());
        U32 endX = static_cast<U32>(endPoint.X() * Size().X());
        U32 endY = static_cast<U32>(endPoint.Y() * Size().Y());
        MUSHCOREASSERT(endX >= startX);
        MUSHCOREASSERT(endY >= startY);
		
        for (U32 y=startY; y<endY; ++y)
        {
            U32 pixelOffset = 4*(startX+y*Size().Y());
            if (pixelOffset + 4*(endX - startX) > pixelDataSize)
            {
                throw MushcoreDataFail("Pixel data overrun");
            }
            U8 *pTileData = &pixelData[pixelOffset];
			
            if (endX > startX)
            {
                TileShowLineGenerate(pTileData, endX - startX, texCoords,
									 t4Val(startPoint.X(), static_cast<tVal>(y) / Size().Y(), 0, 0),
									 t4Val(endPoint.X(),   static_cast<tVal>(y) / Size().Y(),   0, 0));
            }
            
            MUSHCOREASSERT(pTileData <= &pixelData[pixelDataSize]);
        }
    }
	
    PaletteTextureInvalidate();
    MeshInvalidate();
	
    // Bind the texture
    outTexture.SizeSet(t4U32(Size().X(), Size().Y(), 1, 1));
    outTexture.PixelTypeRGBASet();
    outTexture.StorageTypeGLSet();
    outTexture.PixelDataUse(&pixelData[0]);
}

//%outOfLineFunctions {

const char *MushSkinPixelSourceTileShow::AutoName(void) const
{
    return "MushSkinPixelSourceTileShow";
}

MushcoreVirtualObject *MushSkinPixelSourceTileShow::AutoClone(void) const
{
    return new MushSkinPixelSourceTileShow(*this);
}

MushcoreVirtualObject *MushSkinPixelSourceTileShow::AutoCreate(void) const
{
    return new MushSkinPixelSourceTileShow;
}

MushcoreVirtualObject *MushSkinPixelSourceTileShow::AutoVirtualFactory(void)
{
    return new MushSkinPixelSourceTileShow;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinPixelSourceTileShow", MushSkinPixelSourceTileShow::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinPixelSourceTileShow::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushSkinPixelSourceProc::AutoPrint(ioOut);
    ioOut << "lineGenerator=" << m_lineGenerator;
    ioOut << "]";
}
bool
MushSkinPixelSourceTileShow::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "lineGenerator")
    {
        ioIn >> m_lineGenerator;
    }
    else if (MushSkinPixelSourceProc::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushSkinPixelSourceTileShow::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushSkinPixelSourceProc::AutoXMLPrint(ioOut);
    ioOut.TagSet("lineGenerator");
    ioOut << m_lineGenerator;
}
//%outOfLineFunctions } cT7+XURqzq8BRcoBYbzZfw
