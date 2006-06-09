//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinTiledMethod1.cpp
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
//%Header } laoI+u342ww6781VOJd2rA
/*
 * $Id$
 * $Log$
 */

#include "MushSkinTiledMethod1.h"


using namespace Mushware;
using namespace std;

MushSkinTiledMethod1::MushSkinTiledMethod1() :
    m_pullInRatio(0.97)
{
}

Mushware::tVal
MushSkinTiledMethod1::MultiplierForTile(Mushware::U32 inNumVertices)
{
    tVal multiplier = 1.0;
    if (inNumVertices < 3)
    {
        throw MushcoreRequestFail("MultiplierForTile: Facet with <3 vertices");
    }
    else if (inNumVertices == 4)
    {
        multiplier = 0.7071;
    }
    else
    {
        for (U32 i=0; i<inNumVertices; ++i)
        {
            tVal angle = (i + 0.5) * (2*M_PI) / inNumVertices;
            tVal sinAngle = sin(angle);
            
            if (sinAngle > 0.5)
            {
                tVal newMultiplier = 0.5 / sinAngle;
                if (newMultiplier < multiplier)
                {
                    multiplier = newMultiplier;   
                }
            }
            if (sinAngle < -0.5)
            {
                tVal newMultiplier = -0.5 / sinAngle;
                if (newMultiplier < multiplier)
                {
                    multiplier = newMultiplier;   
                }
            }
            tVal cosAngle = cos(angle);
            if (cosAngle > 0.5)
            {
                tVal newMultiplier = 0.5 / cosAngle;
                if (newMultiplier < multiplier)
                {
                    multiplier = newMultiplier;   
                }
            }
            
            if (cosAngle < -0.5)
            {
                tVal newMultiplier = -0.5 / cosAngle;
                if (newMultiplier < multiplier)
                {
                    multiplier = newMultiplier;   
                }
            }
        }
        
        MUSHCOREASSERT(multiplier <= 1.0);
        MUSHCOREASSERT(multiplier >= 0.0);
    }
    return m_pullInRatio * multiplier;
}

void
MushSkinTiledMethod1::DivideSize(Mushware::t2U32& outSizes, Mushware::U32 inNumFacets)
{
    if (inNumFacets < 1)
    {
        throw MushcoreDataFail("Cannot divide texture for zero facets");
    }
    
    outSizes.XSet(static_cast<U32>(std::floor(0.5+std::sqrt((tVal) inNumFacets))));
    outSizes.YSet((inNumFacets + outSizes.X() - 1) / outSizes.X());
}

void
MushSkinTiledMethod1::TexCoordsGenerate(MushMesh4Mesh& ioMesh)
{
    U32 numFacets = ioMesh.NumFacets();
    const MushMesh4Mesh::tVertices& verticesRef = ioMesh.Vertices();
    MushMesh4Mesh::tTexCoords& texCoordsWRef = ioMesh.TexCoordsWRef();
    MushMesh4Mesh::tTextureTiles& texTilesWRef = ioMesh.TextureTilesWRef();
    
    t2U32 divideSize;
    DivideSize(divideSize, numFacets);

    t2Val uvScale(1.0/divideSize.X(), 1.0/divideSize.Y());

    // Tile count.  Progresses through the texture as we use them up
    U32 texTileNum = 0;
    
    U32 textureErrorCount = 0;
    
    // Index to add new texture coordinates
    U32 texCoordNum = ioMesh.TexCoordCounter();
    
    // Lower limit of the number of new textuere coordinates required
    U32 texCoordSizeGuess = texCoordNum + 3 * numFacets;
    
    // Reserve that number in advance.  Speed optimisation only
    if (texCoordsWRef.size() < texCoordSizeGuess)
    {
        texCoordsWRef.resize(texCoordSizeGuess);
    }

    // Resize the texture tile list
    texTilesWRef.resize(numFacets);
    
    // Iterate through all faces in the mesh
    for (U32 faceNum = 0; faceNum < ioMesh.FaceCounter(); ++faceNum)
    {
        MushMesh4Face& faceWRef = ioMesh.FaceWRef(faceNum);
        const MushMesh4Face::tVertexList& vlRef = faceWRef.VertexList();
        const MushMesh4Face::tVertexGroupSize& vgsRef = faceWRef.VertexGroupSize();
        MushMesh4Face::tTexCoordList& texCoordListWRef = faceWRef.TexCoordListWRef();
        
        // Base for adding texture coordinates
        // Used to support more than one texture coordinate per vertex in the future
        U32 texCoordBase = 0;
        
        /* The texture coordinate list contains index values to the texture coordinates.
         * For a single texture coordinate per vertex, it is the same size as the
         * vertex list
         */
        if (texCoordListWRef.size() < texCoordBase + faceWRef.VertexList().size())
        {
            texCoordListWRef.resize(texCoordBase + faceWRef.VertexList().size());
        }

        // Iterate through each facet, using a vertex base and the vertex group size list as usual
        U32 vertexBase = 0;
        for (U32 vgsIndex = 0; vgsIndex < vgsRef.size(); ++vgsIndex)
        {
            U32 verticesInFacet = vgsRef[vgsIndex];
            
            tVal multiplier = MultiplierForTile(verticesInFacet);
            
            // Get the uv coordinates of the lower left corner of the tile we're about to use
            t2Val uvBase(texTileNum % divideSize.X(), texTileNum / divideSize.X());
            uvBase.InPlaceElementwiseMultiply(uvScale);            
            
            U32 tileTexCoordBase = texCoordNum;
            
            // For each vertex in the facet...
            for (U32 i=0; i<verticesInFacet; ++i)
            {
                tVal angle = (i + 0.5) * (2*M_PI) / verticesInFacet;
                t2Val uvVector(0.5 + multiplier * sin(angle), 0.5 + multiplier * cos(angle));
                
                // Move and scale to position in texture
                uvVector.InPlaceElementwiseMultiply(uvScale);
                uvVector += uvBase;
                
                MUSHCOREASSERT(uvVector.X() > -0.01 && uvVector.X() < 1.01);
                MUSHCOREASSERT(uvVector.Y() > -0.01 && uvVector.Y() < 1.01);
                
                // Add the new texture coordinate to mesh
                if (texCoordNum >= texCoordsWRef.size())
                {
                    texCoordsWRef.resize(texCoordNum + 16);
                }
                MUSHCOREASSERT(texCoordNum < texCoordsWRef.size());
                texCoordsWRef[texCoordNum] = t4Val(uvVector.X(), uvVector.Y(), 0, 1);
                
                // Add reference to that coordinate to face
                MUSHCOREASSERT(texCoordBase + i < texCoordListWRef.size());
                texCoordListWRef[texCoordBase + i] = texCoordNum;
                
                // Advance to the next free texture coordinate slot read for the next one
                ++texCoordNum;
            }
            
            // Generate the tile definition for this tile
            if (texTileNum >= texTilesWRef.size())
            {
                texTilesWRef.resize(texTileNum + 1);
            }
            MushMesh4Mesh::tTextureTile& texTileWRef = texTilesWRef[texTileNum];

            // Choose p0, v0 and v1
            /* Simple algorithm for the moment.  Choose the vector one-quarter of the way
             * through the facet, and adjust so that it isn't the same as the base of v0
             */
            U32 v1Base = verticesInFacet / 4;
            if (v1Base == 0)
            {
                ++v1Base;   
            }
            
            texTileWRef.TileBoxSet(t2BoxVal(uvBase, uvBase + uvScale));
            texTileWRef.SourceFaceNumSet(faceNum);
            texTileWRef.SourceFacetNumSet(vgsIndex);
            
            t4Val tileP0Vec = texCoordsWRef[tileTexCoordBase];
            t4Val tileV0Vec = texCoordsWRef[tileTexCoordBase+1] - texCoordsWRef[tileTexCoordBase];
            t4Val tileV1Vec = texCoordsWRef[tileTexCoordBase+((v1Base + 1) % verticesInFacet)] -
                texCoordsWRef[tileTexCoordBase+v1Base];
            
            // Get the tile vertices (uv on the texture) from the texture coords generated above
            texTileWRef.TileP0Set(t2Val(tileP0Vec.X(), tileP0Vec.Y()));
            texTileWRef.TileV0Set(t2Val(tileV0Vec.X(), tileV0Vec.Y()));
            texTileWRef.TileV1Set(t2Val(tileV1Vec.X(), tileV1Vec.Y()));
            
            // Get object vertices by indirecting through the vertex list
            U32 p0Index = vlRef[vertexBase];
            U32 v0StartIndex = vlRef[vertexBase];
            U32 v0EndIndex = vlRef[vertexBase+1];
            U32 v1StartIndex = vlRef[vertexBase+v1Base];
            U32 v1EndIndex = vlRef[vertexBase+((v1Base+1) % verticesInFacet)];
            
            texTileWRef.ObjectP0Set(verticesRef[p0Index]);
            texTileWRef.ObjectV0Set(verticesRef[v0EndIndex] - verticesRef[v0StartIndex]);
            texTileWRef.ObjectV1Set(verticesRef[v1EndIndex] - verticesRef[v1StartIndex]);
            
            texTileWRef.Make();
            
#ifdef MUSHCORE_DEBUG
            // Only report the first error
            static bool textureError = false;
            
            for (U32 i=0; i<verticesInFacet; ++i)
            {
                t2Val uvPos = t2Val(texCoordsWRef[tileTexCoordBase+i].X(), texCoordsWRef[tileTexCoordBase+i].Y());
                t4Val resultVec, expectedVec;
                
                texTileWRef.Transform(resultVec, uvPos);
                
                expectedVec = verticesRef[vlRef[vertexBase+i]];
				
                if (!expectedVec.ApproxEqual(resultVec, ioMesh.BoundingRadius() / 100))
                {
                    if (textureError)
                    {
                        ++textureErrorCount;
                    }   
                    else
                    {
                        MushcoreLog::Sgl().InfoLog() << "Texture coordinate check failed:" << endl;
                        
                        for (U32 j=0; j<verticesInFacet; ++j)
                        {
                            MushcoreLog::Sgl().InfoLog() << "Vertex " << vlRef[vertexBase+j] << " = " << verticesRef[vlRef[vertexBase+j]] << endl;
                        }
                        // MushcoreLog::Sgl().XMLInfoLog() << faceWRef;
                        // MushcoreLog::Sgl().XMLInfoLog() << texCoordsWRef;
                        MushcoreLog::Sgl().XMLInfoLog() << texTileWRef;
                        
                        MushcoreLog::Sgl().InfoLog() << "i=" << i << ", uvPos=" << uvPos << ", resultVec=" << resultVec <<
                            ", expectedVec=" << expectedVec << endl;
                        
                        textureError = true;
                    }
                }
            }
#endif

            ++texTileNum;
            vertexBase += vgsRef[vgsIndex];
            texCoordBase += vgsRef[vgsIndex];
        }
    }
    ioMesh.TexCoordCounterSet(texCoordNum);
    static U32 ctr=1;
    if (ctr == 0)
    {
        ctr++;
        MushcoreLog::Sgl().XMLInfoLog() << ioMesh;
    }
    if (textureErrorCount)
    {
        MushcoreLog::Sgl().WarningLog() << "Number of texture tile errors: " << textureErrorCount <<
            " in " << texTilesWRef.size() << " tiles" << endl;
    }
    
	
#if 0
    for (U32 j=0; j<8; ++j)
    {
        MushcoreLog::Sgl().InfoLog() << "Vertex " << j << " = " << verticesRef[j] << endl;
    }
    for (U32 j=0; j<24; ++j)
    {
        MushcoreLog::Sgl().InfoLog() << "TexCoord " << j << " = " << texCoordsWRef[j] << endl;
    }
    MushcoreLog::Sgl().XMLInfoLog() << ioMesh.FaceWRef(0);

    for (U32 i=0; i<6; ++i)
    {
        MushcoreLog::Sgl().XMLInfoLog() << texTilesWRef[i];
    }
	
#endif
}
//%outOfLineFunctions {

const char *MushSkinTiledMethod1::AutoName(void) const
{
    return "MushSkinTiledMethod1";
}

MushcoreVirtualObject *MushSkinTiledMethod1::AutoClone(void) const
{
    return new MushSkinTiledMethod1(*this);
}

MushcoreVirtualObject *MushSkinTiledMethod1::AutoCreate(void) const
{
    return new MushSkinTiledMethod1;
}

MushcoreVirtualObject *MushSkinTiledMethod1::AutoVirtualFactory(void)
{
    return new MushSkinTiledMethod1;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinTiledMethod1", MushSkinTiledMethod1::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinTiledMethod1::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "pullInRatio=" << m_pullInRatio;
    ioOut << "]";
}
bool
MushSkinTiledMethod1::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "pullInRatio")
    {
        ioIn >> m_pullInRatio;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushSkinTiledMethod1::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("pullInRatio");
    ioOut << m_pullInRatio;
}
//%outOfLineFunctions } HWGMudW6dFaNPaeC7zxf6Q
