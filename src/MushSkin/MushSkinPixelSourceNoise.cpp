//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceNoise.cpp
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
//%Header } IHi2qaicNzVbb+bqL7ZTVw
/*
 * $Id: MushSkinPixelSourceNoise.cpp,v 1.7 2006/06/02 18:14:36 southa Exp $
 * $Log: MushSkinPixelSourceNoise.cpp,v $
 * Revision 1.7  2006/06/02 18:14:36  southa
 * Texture caching
 *
 * Revision 1.6  2006/06/01 20:13:00  southa
 * Initial texture caching
 *
 * Revision 1.5  2006/05/03 00:58:44  southa
 * Texturing updates
 *
 * Revision 1.4  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.3  2006/05/01 17:39:01  southa
 * Texture generation
 *
 * Revision 1.2  2006/04/11 23:30:11  southa
 * Created MushRuby from ruby-1.8.4
 *
 * Revision 1.1  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 */

#include "MushSkinPixelSourceNoise.h"

using namespace Mushware;
using namespace std;

void
MushSkinPixelSourceNoise::ValueParameterSet(Mushware::U32 inNum, Mushware::tLongVal inVal)
{
    switch (inNum)
    {

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
MushSkinPixelSourceNoise::StringParameterSet(Mushware::U32 inNum, const std::string& inStr)
{
    switch (inNum)
    {
        case kParamSourceName:
            m_meshName = inStr;
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
MushSkinPixelSourceNoise::ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue)
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
	else
	{
		MushGLPixelSource::ParamDecode(inName, inValue);
	}
}

void 
MushSkinPixelSourceNoise::TileLineGenerate(Mushware::U8 *inpTileData, const MushMesh4Mesh::tTextureTile& inTileRef,
                                           Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos)
{
    U8 *pTileData = inpTileData;
    t4Val objectPos = inStartPos;
    t4Val objectPosStep;
    
    objectPosStep = (inEndPos - inStartPos) / inNumPixels;
        
    if (m_pPaletteTexture != NULL)
    {
        for (U32 i=0; i<inNumPixels; ++i)
        {
            tVal paletteValue1 =
				0.5*pow(sin(2*objectPos.X()), 2) +
            	0.5*pow(sin(2*objectPos.Y()), 2)
            ;

			
            tVal paletteValue2 = 
				0.5*pow(sin(2*objectPos.Z()), 2) +
				0.5*pow(sin(2*objectPos.W()), 2)
				;
			
            t4Val pixelCol = m_pPaletteTexture->U8RGBALookup(m_paletteStart +
															 paletteValue1 * m_paletteVector1 +
															 paletteValue2 * m_paletteVector2);
            
            // if (tileSourceFace < 6) pixelCol.WSet(0);
            
            *pTileData++ = static_cast<U8>(pixelCol.X()); // Red
            *pTileData++ = static_cast<U8>(pixelCol.Y()); // Green
            *pTileData++ = static_cast<U8>(pixelCol.Z()); // Blue
            *pTileData++ = static_cast<U8>(pixelCol.W()); // Alpha
            
            objectPos += objectPosStep;
        }
    }
    else
    {
        for (U32 i=0; i<inNumPixels; ++i)
        {
            *pTileData++ = 255; // Red
            *pTileData++ = 255; // Green
            *pTileData++ = 255; // Blue
            *pTileData++ = (static_cast<U32>(objectPos.X()+objectPos.Y()+objectPos.Z()+objectPos.W()) % 8 == 0)?255:0; // Alpha
            objectPos += objectPosStep;
        }            
    }
    
    MUSHCOREASSERT(pTileData <= inpTileData + 4*inNumPixels);
}

void
MushSkinPixelSourceNoise::ToTextureCreate(MushGLTexture& outTexture)
{
    U32 pixelDataSize = 4*Size().X()*Size().Y();
    std::vector<U8> pixelData(pixelDataSize, 0);
    
    MushMesh4Mesh *p4Mesh = MushcoreData<MushMesh4Mesh>::Sgl().Get(m_meshName);
    
    const MushMesh4Mesh::tTextureTiles& texTilesRef = p4Mesh->TextureTiles();
    U32 numTexTiles = texTilesRef.size();
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
            U8 *pTileData = &pixelData[pixelOffset];

            tileRef.Transform(objectPos, t2Val(static_cast<tVal>(startX) / Size().X(), static_cast<tVal>(y) / Size().Y()));
            tileRef.Transform(objectEndPos, t2Val(static_cast<tVal>(endX) / Size().X(), static_cast<tVal>(y) / Size().Y()));
            
            if (endX > startX)
            {
                {
                    static U32 ctr=1;
                    if (ctr==0)
                    {
                        MushcoreLog::Sgl().InfoLog() << "objectPos=" << objectPos << ", objectEndPos=" << objectEndPos << endl;;
                    }
                    ++ctr;
                }
                
                TileLineGenerate(pTileData, tileRef, endX - startX, objectPos, objectEndPos);
            }
            
            MUSHCOREASSERT(pTileData <= &pixelData[pixelDataSize]);
        }
    }

    m_pPaletteTexture = NULL;
    
    // Bind the texture
    outTexture.SizeSet(t4U32(Size().X(), Size().Y(), 1, 1));
    outTexture.PixelTypeRGBASet();
    outTexture.StorageTypeGLSet();
    outTexture.PixelDataUse(&pixelData[0]);
}

//%outOfLineFunctions {

const char *MushSkinPixelSourceNoise::AutoName(void) const
{
    return "MushSkinPixelSourceNoise";
}

MushcoreVirtualObject *MushSkinPixelSourceNoise::AutoClone(void) const
{
    return new MushSkinPixelSourceNoise(*this);
}

MushcoreVirtualObject *MushSkinPixelSourceNoise::AutoCreate(void) const
{
    return new MushSkinPixelSourceNoise;
}

MushcoreVirtualObject *MushSkinPixelSourceNoise::AutoVirtualFactory(void)
{
    return new MushSkinPixelSourceNoise;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinPixelSourceNoise", MushSkinPixelSourceNoise::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinPixelSourceNoise::AutoPrint(std::ostream& ioOut) const
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
    ioOut << "meshName=" << m_meshName << ", ";
    ioOut << "paletteName=" << m_paletteName;
    ioOut << "]";
}
bool
MushSkinPixelSourceNoise::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "meshName")
    {
        ioIn >> m_meshName;
    }
    else if (inTagStr == "paletteName")
    {
        ioIn >> m_paletteName;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushSkinPixelSourceNoise::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("paletteStart");
    ioOut << m_paletteStart;
    ioOut.TagSet("paletteVector1");
    ioOut << m_paletteVector1;
    ioOut.TagSet("paletteVector2");
    ioOut << m_paletteVector2;
    ioOut.TagSet("pPaletteTexture");
    ioOut << m_pPaletteTexture;
    ioOut.TagSet("meshName");
    ioOut << m_meshName;
    ioOut.TagSet("paletteName");
    ioOut << m_paletteName;
}
//%outOfLineFunctions } OS6PtKYB0iRl5hMCEN66YA

