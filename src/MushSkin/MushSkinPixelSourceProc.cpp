//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceProc.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 13Ykq61AVzNLZsNvUDFWnw
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
MushSkinPixelSourceProc::ToTextureCreate(MushGLTexture& outTexture)
{
    U32 pixelDataSize = 4*Size().X()*Size().Y();
    m_u8Data = std::vector<U8>(pixelDataSize, 0);
    
    const MushMesh4Mesh::tTextureTiles& texTilesRef = Mesh().TextureTiles();
    U32 numTexTiles = texTilesRef.size();
    t4Val objectPos, objectEndPos;

    for (U32 tileIndex = 0; tileIndex < numTexTiles; ++tileIndex)
    {
        const MushMesh4Mesh::tTextureTile& tileRef = texTilesRef[tileIndex];
        
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
            U8 *pTileData = &m_u8Data[pixelOffset];
			
            // objectEndPos is one pixel beyond the end of the generated data
#if 0
            tileRef.Transform(objectPos, t2Val((0.5+startX) / Size().X(), (0.5+y) / Size().Y()));
            tileRef.Transform(objectEndPos, t2Val((0.5+endX) / Size().X(), (0.5+y) / Size().Y()));
#else
			tileRef.TextureToFacet(objectPos, t2Val((0.5+startX) / Size().X(), (0.5+y) / Size().Y()));
            tileRef.TextureToFacet(objectEndPos, t2Val((0.5+endX) / Size().X(), (0.5+y) / Size().Y()));
#endif
            if (endX > startX)
            {
                LineGenerate(pTileData, endX - startX, objectPos, objectEndPos);
            }
            
            MUSHCOREASSERT(pTileData <= &m_u8Data[pixelDataSize]);
        }
    }
	
	PaletteTextureInvalidate();
	MeshInvalidate();
	
    // Bind the texture
    outTexture.SizeSet(t4U32(Size().X(), Size().Y(), 1, 1));
    outTexture.PixelTypeRGBASet();
    outTexture.StorageTypeGLSet();
    outTexture.PixelDataUse(&m_u8Data[0]);
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
		m_pPaletteTexture->Make();
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
    ioOut << "meshName=" << m_meshName << ", ";
    ioOut << "paletteName=" << m_paletteName << ", ";
    ioOut << "paletteStart=" << m_paletteStart << ", ";
    ioOut << "paletteVector1=" << m_paletteVector1 << ", ";
    ioOut << "paletteVector2=" << m_paletteVector2 << ", ";
    ioOut << "scale=" << m_scale << ", ";
    ioOut << "offset=" << m_offset << ", ";
    ioOut << "numOctaves=" << m_numOctaves << ", ";
    ioOut << "octaveRatio=" << m_octaveRatio << ", ";
    ioOut << "u8Data=" << m_u8Data << ", ";
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
    else if (inTagStr == "u8Data")
    {
        ioIn >> m_u8Data;
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
    ioOut.TagSet("u8Data");
    ioOut << m_u8Data;
    ioOut.TagSet("pPaletteTexture");
    ioOut << m_pPaletteTexture;
    ioOut.TagSet("pMesh");
    ioOut << m_pMesh;
}
//%outOfLineFunctions } ehxN5v5h1cskDbBj8McsqQ
