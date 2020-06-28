//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceTileShow.cpp
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
//%Header } 2rKxJURs3w6gc9JAmQhoKw
/*
 * $Id: MushSkinPixelSourceTileShow.cpp,v 1.3 2007/04/18 09:23:05 southa Exp $
 * $Log: MushSkinPixelSourceTileShow.cpp,v $
 * Revision 1.3  2007/04/18 09:23:05  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/08/01 17:21:40  southa
 * River demo
 *
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
    U32 pixelDataSize = 4 * Size().X()*Size().Y();
    m_u8Data.resize(pixelDataSize);

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

        for (U32 y = startY; y < endY; ++y)
        {
            U32 pixelOffset = 4 * (startX + y * Size().Y());
            if (pixelOffset + 4 * (endX - startX) > pixelDataSize)
            {
                throw MushcoreDataFail("Pixel data overrun");
            }
            U8 *pTileData = &m_u8Data[pixelOffset];

            if (endX > startX)
            {
                TileShowLineGenerate(pTileData, endX - startX, texCoords,
                    t4Val(startPoint.X(), static_cast<tVal>(y) / Size().Y(), 0, 0),
                    t4Val(endPoint.X(), static_cast<tVal>(y) / Size().Y(), 0, 0));
            }

            MUSHCOREASSERT(pTileData <= &m_u8Data[pixelDataSize]);
        }
    }

    outTexture.SizeSet(t4U32(Size().X(), Size().Y(), 1, 1));
    outTexture.PixelTypeRGBASet();
    outTexture.StorageTypeGLSet();

    PaletteTextureInvalidate();
    MeshInvalidate();
}


void
MushSkinPixelSourceTileShow::ToTextureBind(MushGLTexture& outTexture)
{
    // Bind the texture
    outTexture.PixelDataUse(&m_u8Data[0]);
    m_u8Data.resize(0);
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
