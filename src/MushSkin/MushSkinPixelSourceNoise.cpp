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
 * $Id: MushSkinPixelSourceNoise.cpp,v 1.5 2006/05/03 00:58:44 southa Exp $
 * $Log: MushSkinPixelSourceNoise.cpp,v $
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
            
        case kParamPaletteVectorX:
            m_paletteVector.XSet(inVal);
            break;
            
        case kParamPaletteVectorY:
            m_paletteVector.YSet(inVal);
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
            tVal paletteValue = pow(sin(4*objectPos.X()), 2) +
            pow(sin(5*objectPos.Y()), 2) +
            pow(sin(6*objectPos.Z()), 2) +
            pow(sin(7*objectPos.W()), 2)
            ;
            
            t4Val pixelCol = m_pPaletteTexture->U8RGBALookup(m_paletteStart + paletteValue * m_paletteVector);
            
            // if (tileSourceFace < 6) pixelCol.WSet(0);
            
            *pTileData++ = static_cast<U8>(pixelCol.X()); // Red
            *pTileData++ = static_cast<U8>(pixelCol.Y()); // Green
            *pTileData++ = static_cast<U8>(pixelCol.Z()); // Blue
            *pTileData++ = static_cast<U8>(pixelCol.Z()); // Alpha
            
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
    U32 pixelDataSize = 4*m_xSize*m_ySize;
    std::vector<U8> pixelData(pixelDataSize, 0);
    
    MushMesh4Mesh *p4Mesh = MushcoreData<MushMesh4Mesh>::Sgl().Get(m_sourceName);
    
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

            tileRef.Transform(objectPos, t2Val(static_cast<tVal>(startX) / m_xSize, static_cast<tVal>(y) / m_ySize));
            tileRef.Transform(objectEndPos, t2Val(static_cast<tVal>(endX) / m_xSize, static_cast<tVal>(y) / m_ySize));
            
            if (endX > startX)
            {
                {
                    static U32 ctr=0;
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
    outTexture.SizeSet(t4U32(m_xSize, m_ySize, 1, 1));
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
    ioOut << "xSize=" << m_xSize << ", ";
    ioOut << "ySize=" << m_ySize << ", ";
    ioOut << "sourceName=" << m_sourceName << ", ";
    ioOut << "paletteName=" << m_paletteName << ", ";
    ioOut << "paletteStart=" << m_paletteStart << ", ";
    ioOut << "paletteVector=" << m_paletteVector << ", ";
    if (m_pPaletteTexture == NULL)
    {
        ioOut << "pPaletteTexture=NULL" ;
    }
    else
    {
        ioOut << "pPaletteTexture=" << *m_pPaletteTexture;
    }
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
    else if (inTagStr == "paletteStart")
    {
        ioIn >> m_paletteStart;
    }
    else if (inTagStr == "paletteVector")
    {
        ioIn >> m_paletteVector;
    }
    else if (inTagStr == "pPaletteTexture")
    {
        ioIn >> m_pPaletteTexture;
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
    ioOut.TagSet("xSize");
    ioOut << m_xSize;
    ioOut.TagSet("ySize");
    ioOut << m_ySize;
    ioOut.TagSet("sourceName");
    ioOut << m_sourceName;
    ioOut.TagSet("paletteName");
    ioOut << m_paletteName;
    ioOut.TagSet("paletteStart");
    ioOut << m_paletteStart;
    ioOut.TagSet("paletteVector");
    ioOut << m_paletteVector;
    ioOut.TagSet("pPaletteTexture");
    ioOut << m_pPaletteTexture;
}
//%outOfLineFunctions } iGrJwMTKfEgbGwQ3RjuX4w
