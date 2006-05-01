//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinNoise.cpp
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
//%Header } stZjV2zH0hRmAqmLipntXQ
/*
 * $Id: MushSkinNoise.cpp,v 1.2 2005/09/06 12:15:35 southa Exp $
 * $Log: MushSkinNoise.cpp,v $
 * Revision 1.2  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 * Revision 1.1  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 */

#include "MushSkinNoise.h"

using namespace Mushware;
using namespace std;

MushSkinNoise::MushSkinNoise() :
    m_pullInRatio(1.0)
{
}

Mushware::tVal
MushSkinNoise::MultiplierForTile(Mushware::U32 inNumVertices)
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
    return multiplier;
}

void
MushSkinNoise::DivideSize(Mushware::t2U32& outSizes, Mushware::U32 inNumFacets)
{
    if (inNumFacets < 1)
    {
        throw MushcoreDataFail("Cannot divide texture for zero facets");
    }
    
    outSizes.XSet(static_cast<U32>(std::floor(0.5+std::sqrt((tVal) inNumFacets))));
    outSizes.YSet((inNumFacets + outSizes.X() - 1) / outSizes.X());
}

void
MushSkinNoise::TexCoordsGenerate(MushMesh4Mesh& ioMesh)
{
    U32 numFacets = ioMesh.NumFacets();
    MushMesh4Mesh::tTexCoords& texCoordsWRef = ioMesh.TexCoordsWRef();
    
    t2U32 divideSize;
    DivideSize(divideSize, numFacets);
    
    t2Val uvScale(1.0/divideSize.X(), 1.0/divideSize.Y());

    // Tile count.  Progresses through the texture as we use them up
    U32 texTileNum = 0;
    
    // Index to add new texture coordinates
    U32 texCoordNum = ioMesh.TexCoordCounter();
    
    // Lower limit of the number of new textuere coordinates required
    U32 texCoordSizeGuess = texCoordNum + 3 * numFacets;
    
    // Reserve that number in advance.  Speed optimisation only
    if (texCoordsWRef.size() < texCoordSizeGuess)
    {
        texCoordsWRef.resize(texCoordSizeGuess);
    }

    // Iterate through all faces in the mesh
    for (U32 faceNum = 0; faceNum < ioMesh.FaceCounter(); ++faceNum)
    {
        MushMesh4Face& faceWRef = ioMesh.FaceWRef(faceNum);
        const MushMesh4Face::tVertexList& vgsRef = faceWRef.VertexGroupSize();
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
            t2Val uvBase(texTileNum % divideSize.X(), texTileNum / divideSize.Y());
            uvBase.InPlaceElementwiseMultiply(uvScale);            
            
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
}

void
MushSkinNoise::TextureGenerate(MushMesh4Mesh& ioMesh)
{
    
}

//%outOfLineFunctions {

const char *MushSkinNoise::AutoName(void) const
{
    return "MushSkinNoise";
}

MushcoreVirtualObject *MushSkinNoise::AutoClone(void) const
{
    return new MushSkinNoise(*this);
}

MushcoreVirtualObject *MushSkinNoise::AutoCreate(void) const
{
    return new MushSkinNoise;
}

MushcoreVirtualObject *MushSkinNoise::AutoVirtualFactory(void)
{
    return new MushSkinNoise;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinNoise", MushSkinNoise::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinNoise::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "pullInRatio=" << m_pullInRatio;
    ioOut << "]";
}
bool
MushSkinNoise::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushSkinNoise::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("pullInRatio");
    ioOut << m_pullInRatio;
}
//%outOfLineFunctions } PSQhE0UBcj6jYUYw9jopmw
