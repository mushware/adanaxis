//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceProc.cpp
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
//%Header } LW05bAXvTemc6spbnKpRYg
/*
 * $Id: MushSkinPixelSourceProc.cpp,v 1.6 2007/06/11 20:06:17 southa Exp $
 * $Log: MushSkinPixelSourceProc.cpp,v $
 * Revision 1.6  2007/06/11 20:06:17  southa
 * Compatibility fixes and level 27
 *
 * Revision 1.5  2007/04/18 09:23:04  southa
 * Header and level fixes
 *
 * Revision 1.4  2006/08/01 17:21:39  southa
 * River demo
 *
 * Revision 1.3  2006/07/18 16:58:39  southa
 * Texture fixes
 *
 * Revision 1.2  2006/06/09 21:07:14  southa
 * Tiled skin generation
 *
 * Revision 1.1  2006/06/07 12:15:21  southa
 * Grid and test textures
 *
 */

#include "MushSkinPixelSourceProc.h"

using namespace Mushware;
using namespace std;


MushSkinPixelSourceProc::MushSkinPixelSourceProc() :
    m_paletteStart(0,0),
    m_paletteVector1(1,0),
    m_scale(1,1,1,1),
    m_offset(0,0,0,0),
    m_numOctaves(1),
    m_octaveRatio(0.5),
    m_edgeProximityDist(0.0),
    m_edgeProximityCol(255, 255, 255, 96),
	m_pPaletteTexture(NULL),
	m_pMesh(NULL)
{}

void
MushSkinPixelSourceProc::ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue)
{
	std::string nameStr = inName.String();
	
	if (nameStr == "meshname")
    {
		m_meshName = inValue.String();
	}
	else if (nameStr == "palette")
    {
		m_paletteName = inValue.String();
	}
	else if (nameStr == "palettestart")
	{
		m_paletteStart = t2Val(inValue.ValVector());
	}
	else if (nameStr == "palettevector")
	{
		m_paletteVector1 = t2Val(inValue.ValVector());
	}
	else if (nameStr == "scale")
	{
		m_scale = t4Val(inValue.ValVector());
	}	
	else if (nameStr == "offset")
	{
		m_offset = t4Val(inValue.ValVector());
	}	
	else if (nameStr == "numoctaves")
	{
		m_numOctaves = inValue.U32();
	}	
    else if (nameStr == "octaveratio")
    {
        m_octaveRatio = inValue.Val();
    }
    else if (nameStr == "edgeproximitydist")
    {
        m_edgeProximityDist = inValue.Val();
    }
    else if (nameStr == "edgeproximitycol")
    {
        m_edgeProximityCol = t4Val(inValue.ValVector());
    }
	else
	{
		MushGLPixelSource::ParamDecode(inName, inValue);
	}
}

void 
MushSkinPixelSourceProc::LineGenerate(Mushware::U8 *inpTileData, Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos)
{
    U8 *pTileData = inpTileData;

    if (PaletteTextureValid())
    {
        for (U32 i=0; i<inNumPixels; ++i)
        {	
            t4Val pixelCol = PaletteTexture().U8RGBALookup(m_paletteStart);

            *pTileData++ = static_cast<U8>(pixelCol.X()); // Red
            *pTileData++ = static_cast<U8>(pixelCol.Y()); // Green
            *pTileData++ = static_cast<U8>(pixelCol.Z()); // Blue
            *pTileData++ = static_cast<U8>(pixelCol.W()); // Alpha
        }
    }
    else
    {
        for (U32 i=0; i<inNumPixels; ++i)
        {
            *pTileData++ = 255; // Red
            *pTileData++ = 255; // Green
            *pTileData++ = 255; // Blue
            *pTileData++ = 255; // Alpha
        }            
    }
    MUSHCOREASSERT(pTileData <= inpTileData + 4*inNumPixels);
}


void
MushSkinPixelSourceProc::LineEdgeEffectGenerate(Mushware::U8 *inpTileData, Mushware::U32 startX, Mushware::U32 endX, Mushware::U32 startY, Mushware::U32 endY, Mushware::U32 y)
{
    U8 *pTileData = inpTileData;
    U32 xSize = endX - startX;
    U32 ySize = endY - startY;

    if (xSize > 0 && ySize > 0 && m_edgeProximityDist > 0) {
        for (U32 x = startX; x < startX + xSize; ++x)
        {
            tVal distFromEdge = std::min(
                std::min(std::fabs(1.0 * startX - x),
                    std::fabs(1.0 * endX - x)) / xSize,
                std::min(std::fabs(1.0 * startY - y),
                    std::fabs(1.0 * endY - y)) / ySize
            );

            tVal effectStrength = std::min(1.0, 1.0 - (distFromEdge / m_edgeProximityDist));
            if (effectStrength > 0) {

                *pTileData++ = static_cast<U8>(*pTileData * (1 - effectStrength) + m_edgeProximityCol.X() * effectStrength); // Red
                *pTileData++ = static_cast<U8>(*pTileData * (1 - effectStrength) + m_edgeProximityCol.Y() * effectStrength); // Green
                *pTileData++ = static_cast<U8>(*pTileData * (1 - effectStrength) + m_edgeProximityCol.Z() * effectStrength); // Blue
                *pTileData++ = static_cast<U8>(*pTileData * (1 - effectStrength) + m_edgeProximityCol.W() * effectStrength); // Alpha
            }
            else {
                pTileData += 4;
            }
        }
    }

    MUSHCOREASSERT(pTileData <= inpTileData + 4 * xSize);
}


std::vector<MediaJobId>
MushSkinPixelSourceProc::PrerequisitesCreate(MushGLTexture& outTexture)
{
    std::vector<MediaJobId> dependencyJobIds;

    if (m_paletteName != "")
    {
        if (!MushcoreData<MushGLTexture>::Sgl().GetIfExists(m_pPaletteTexture, m_paletteName))
        {
            throw MushcoreDataFail("Non-existent palette '" + m_paletteName + "'");
        }
        dependencyJobIds = m_pPaletteTexture->Make();
    }
    return dependencyJobIds;
}

void
MushSkinPixelSourceProc::ToTextureCreate(MushGLTexture& outTexture, volatile bool *pKillSwitch)
{
    t4U32 currentSize = FinalSize() / ReductionFactor();

    U32 pixelDataSize = 4 * currentSize.X()*currentSize.Y();
    m_u8Data.resize(pixelDataSize);

    const MushMesh4Mesh::tTextureTiles& texTilesRef = Mesh().TextureTiles();
    U32 numTexTiles = texTilesRef.size();
    t4Val objectPos, objectEndPos;

    for (U32 tileIndex = 0; tileIndex < numTexTiles; ++tileIndex)
    {


        const MushMesh4Mesh::tTextureTile& tileRef = texTilesRef[tileIndex];

        t2Val startPoint = tileRef.TileBox().Start();
        t2Val endPoint = tileRef.TileBox().End();
        U32 startX = static_cast<U32>(startPoint.X() * currentSize.X());
        U32 startY = static_cast<U32>(startPoint.Y() * currentSize.Y());
        U32 endX = static_cast<U32>(endPoint.X() * currentSize.X());
        U32 endY = static_cast<U32>(endPoint.Y() * currentSize.Y());
        MUSHCOREASSERT(endX >= startX);
        MUSHCOREASSERT(endY >= startY);

        for (U32 y = startY; y < endY; ++y)
        {
            if (pKillSwitch != NULL && *pKillSwitch) {
                throw MushcoreCommandedExit("Killswitch triggered");
            }

            U32 pixelOffset = 4 * (startX + y * currentSize.Y());
            if (pixelOffset + 4 * (endX - startX) > pixelDataSize)
            {
                throw MushcoreDataFail("Pixel data overrun");
            }
            U8 *pTileData = &m_u8Data[pixelOffset];

            // objectEndPos is one pixel beyond the end of the generated data
#if 0
            tileRef.Transform(objectPos, t2Val((0.5 + startX) / currentSize.X(), (0.5 + y) / currentSize.Y()));
            tileRef.Transform(objectEndPos, t2Val((0.5 + endX) / currentSize.X(), (0.5 + y) / currentSize.Y()));
#else
            tileRef.TextureToFacet(objectPos, t2Val((0.5 + startX) / currentSize.X(), (0.5 + y) / currentSize.Y()));
            tileRef.TextureToFacet(objectEndPos, t2Val((0.5 + endX) / currentSize.X(), (0.5 + y) / currentSize.Y()));
#endif
            if (endX > startX)
            {
                LineGenerate(pTileData, endX - startX, objectPos, objectEndPos);

                LineEdgeEffectGenerate(pTileData, startX, endX, startY, endY, y);
            }

            MUSHCOREASSERT(pTileData <= &m_u8Data[pixelDataSize - 1] + 1);


        }
    }

    outTexture.SizeSet(t4U32(currentSize.X(), currentSize.Y(), 1, 1));
    outTexture.PixelTypeRGBASet();
    outTexture.StorageTypeGLSet();

    PaletteTextureInvalidate();
    MeshInvalidate();
}


void
MushSkinPixelSourceProc::ToTextureBind(MushGLTexture& outTexture)
{
    // Bind the texture
    outTexture.PixelDataUse(&m_u8Data[0]);
    m_u8Data.resize(0);
}


void
MushSkinPixelSourceProc::DataCreate(void)
{
}

void
MushSkinPixelSourceProc::DataRelease(void)
{
    m_u8Data.resize(0);
}

const std::vector<Mushware::U8>&
MushSkinPixelSourceProc::DataRGBAU8Get(void) const
{
    return m_u8Data;
}

void
MushSkinPixelSourceProc::PaletteResolve(void) const
{
	if (m_paletteName != "")
	{
		if (!MushcoreData<MushGLTexture>::Sgl().GetIfExists(m_pPaletteTexture, m_paletteName))
		{
			throw MushcoreDataFail("Non-existent palette '"+m_paletteName+"'");
		}
        if (!m_pPaletteTexture->Ready()) {
            throw MushcoreDataFail("Texture palette '" + m_paletteName + "' not ready");
        }
	}
}

void
MushSkinPixelSourceProc::MeshResolve(void) const
{
	if (m_meshName != "")
	{
		if (!MushcoreData<MushMesh4Mesh>::Sgl().GetIfExists(m_pMesh, m_meshName))
		{
			throw MushcoreDataFail("Non-existent palette '"+m_meshName+"'");
		}
	}
}

// Add this class prefix to those searched by the resolver
namespace
{
    void Install(void)
    {
		MushGLResolverPixelSource::Sgl().PrefixAdd("MushSkinPixelSource");
    }
    MushcoreInstaller install(Install);
} // end anonymous namespace

//%outOfLineFunctions {

const char *MushSkinPixelSourceProc::AutoName(void) const
{
    return "MushSkinPixelSourceProc";
}

MushcoreVirtualObject *MushSkinPixelSourceProc::AutoClone(void) const
{
    return new MushSkinPixelSourceProc(*this);
}

MushcoreVirtualObject *MushSkinPixelSourceProc::AutoCreate(void) const
{
    return new MushSkinPixelSourceProc;
}

MushcoreVirtualObject *MushSkinPixelSourceProc::AutoVirtualFactory(void)
{
    return new MushSkinPixelSourceProc;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinPixelSourceProc", MushSkinPixelSourceProc::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinPixelSourceProc::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGLPixelSource::AutoPrint(ioOut);
    ioOut << "u8Data=" << m_u8Data << ", ";
    ioOut << "meshName=" << m_meshName << ", ";
    ioOut << "paletteName=" << m_paletteName << ", ";
    ioOut << "paletteStart=" << m_paletteStart << ", ";
    ioOut << "paletteVector1=" << m_paletteVector1 << ", ";
    ioOut << "paletteVector2=" << m_paletteVector2 << ", ";
    ioOut << "scale=" << m_scale << ", ";
    ioOut << "offset=" << m_offset << ", ";
    ioOut << "numOctaves=" << m_numOctaves << ", ";
    ioOut << "octaveRatio=" << m_octaveRatio << ", ";
    ioOut << "edgeProximityDist=" << m_edgeProximityDist << ", ";
    ioOut << "edgeProximityCol=" << m_edgeProximityCol << ", ";
    if (m_pPaletteTexture == NULL)
    {
        ioOut << "pPaletteTexture=NULL"  << ", ";
    }
    else
    {
        ioOut << "pPaletteTexture=" << *m_pPaletteTexture << ", ";
    }
    if (m_pMesh == NULL)
    {
        ioOut << "pMesh=NULL" ;
    }
    else
    {
        ioOut << "pMesh=" << *m_pMesh;
    }
    ioOut << "]";
}
bool
MushSkinPixelSourceProc::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "u8Data")
    {
        ioIn >> m_u8Data;
    }
    else if (inTagStr == "meshName")
    {
        ioIn >> m_meshName;
    }
    else if (inTagStr == "paletteName")
    {
        ioIn >> m_paletteName;
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
    else if (inTagStr == "scale")
    {
        ioIn >> m_scale;
    }
    else if (inTagStr == "offset")
    {
        ioIn >> m_offset;
    }
    else if (inTagStr == "numOctaves")
    {
        ioIn >> m_numOctaves;
    }
    else if (inTagStr == "octaveRatio")
    {
        ioIn >> m_octaveRatio;
    }
    else if (inTagStr == "edgeProximityDist")
    {
        ioIn >> m_edgeProximityDist;
    }
    else if (inTagStr == "edgeProximityCol")
    {
        ioIn >> m_edgeProximityCol;
    }
    else if (inTagStr == "pPaletteTexture")
    {
        ioIn >> m_pPaletteTexture;
    }
    else if (inTagStr == "pMesh")
    {
        ioIn >> m_pMesh;
    }
    else if (MushGLPixelSource::AutoXMLDataProcess(ioIn, inTagStr))
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
MushSkinPixelSourceProc::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGLPixelSource::AutoXMLPrint(ioOut);
    ioOut.TagSet("u8Data");
    ioOut << m_u8Data;
    ioOut.TagSet("meshName");
    ioOut << m_meshName;
    ioOut.TagSet("paletteName");
    ioOut << m_paletteName;
    ioOut.TagSet("paletteStart");
    ioOut << m_paletteStart;
    ioOut.TagSet("paletteVector1");
    ioOut << m_paletteVector1;
    ioOut.TagSet("paletteVector2");
    ioOut << m_paletteVector2;
    ioOut.TagSet("scale");
    ioOut << m_scale;
    ioOut.TagSet("offset");
    ioOut << m_offset;
    ioOut.TagSet("numOctaves");
    ioOut << m_numOctaves;
    ioOut.TagSet("octaveRatio");
    ioOut << m_octaveRatio;
    ioOut.TagSet("edgeProximityDist");
    ioOut << m_edgeProximityDist;
    ioOut.TagSet("edgeProximityCol");
    ioOut << m_edgeProximityCol;
    ioOut.TagSet("pPaletteTexture");
    ioOut << m_pPaletteTexture;
    ioOut.TagSet("pMesh");
    ioOut << m_pMesh;
}
//%outOfLineFunctions } GrB2i+5vQHM49ei+a19ToQ
