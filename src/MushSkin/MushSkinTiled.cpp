//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinTiled.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 9mFt1bSUFLaYyg1N3XtwoQ
/*
 * $Id: MushSkinTiled.cpp,v 1.12 2006/10/19 15:41:37 southa Exp $
 * $Log: MushSkinTiled.cpp,v $
 * Revision 1.12  2006/10/19 15:41:37  southa
 * Item handling
 *
 * Revision 1.11  2006/08/01 17:21:41  southa
 * River demo
 *
 * Revision 1.10  2006/07/24 18:46:51  southa
 * Depth sorting
 *
 * Revision 1.9  2006/07/18 16:58:39  southa
 * Texture fixes
 *
 * Revision 1.8  2006/07/16 09:19:48  southa
 * Delete mesh before creating
 *
 * Revision 1.7  2006/06/22 19:07:36  southa
 * Build fixes
 *
 * Revision 1.6  2006/06/16 01:02:34  southa
 * Ruby mesh generation
 *
 * Revision 1.5  2006/06/12 11:59:40  southa
 * Ruby wrapper for MushMeshVector
 *
 * Revision 1.4  2006/06/09 21:07:14  southa
 * Tiled skin generation
 *
 * Revision 1.3  2006/06/08 20:17:31  southa
 * Texture tile generation method 2
 *
 * Revision 1.2  2006/06/07 14:25:56  southa
 * Grid texture fixes
 *
 * Revision 1.1  2006/06/07 12:15:22  southa
 * Grid and test textures
 *
 * Revision 1.5  2006/05/03 00:58:43  southa
 * Texturing updates
 *
 * Revision 1.4  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.3  2006/05/01 17:39:01  southa
 * Texture generation
 *
 * Revision 1.2  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 * Revision 1.1  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 */

#include "MushSkinTiled.h"

using namespace Mushware;
using namespace std;

MushSkinTiled::MushSkinTiled() :
    m_pullInRatio(0.95)
{
}

void
MushSkinTiled::DivideSize(Mushware::t2U32& outSizes, Mushware::U32 inNumFacets)
{
    if (inNumFacets < 1)
    {
        throw MushcoreDataFail("Cannot divide texture for zero facets");
    }
    
    outSizes.XSet(static_cast<U32>(std::floor(0.5+std::sqrt((tVal) inNumFacets))));
    outSizes.YSet((inNumFacets + outSizes.X() - 1) / outSizes.X());
}

void
MushSkinTiled::TexCoordsGenerate(MushMesh4Mesh& ioMesh)
{
    U32 numFacets = ioMesh.NumFacets();
    // const MushMesh4Mesh::tVertices& verticesRef = ioMesh.Vertices();
    MushMesh4Mesh::tTexCoords& texCoordsWRef = ioMesh.TexCoordsWRef();
    MushMesh4Mesh::tTextureTiles& texTilesWRef = ioMesh.TextureTilesWRef();
    
    t2U32 divideSize;
    DivideSize(divideSize, numFacets);

    t2Val uvScale(1.0/divideSize.X(), 1.0/divideSize.Y());

    // Tile count.  Progresses through the texture as we use them up
    U32 texTileNum = 0;
    
	// Record errors as we go along
    U32 textureErrorCount = 0;
    
    // Index to add new texture coordinates
    U32 texCoordNum = ioMesh.TexCoordCounter();
    
    // Lower limit of the number of new texture coordinates required
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
         //const MushMesh4Face::tVertexGroupSize& vgsRef = faceWRef.VertexGroupSize();
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
        for (U32 facetNum = 0; facetNum < faceWRef.NumFacets(); ++facetNum)
        {
            // Gather the facet vertices
			MushMeshTools::tFacetVertices facetVertices;
			
			MushMeshTools::VerticesForFacet(facetVertices, ioMesh, faceNum, facetNum);

			// Get the uv coordinates of the lower left corner of the tile we're about to use
            t2Val uvBase(texTileNum % divideSize.X(), texTileNum / divideSize.X());
            uvBase.InPlaceElementwiseMultiply(uvScale);            
			
			// Generate the tile definition for this tile
            if (texTileNum >= texTilesWRef.size())
            {
                texTilesWRef.resize(texTileNum + 1);
            }
            MushMesh4Mesh::tTextureTile& texTileWRef = texTilesWRef[texTileNum];
			texTileWRef.TileBoxSet(t2BoxVal(uvBase, uvBase + uvScale));
            texTileWRef.SourceFaceNumSet(faceNum);
            texTileWRef.SourceFacetNumSet(facetNum);
			texTileWRef.SKSet(0.95);
			
            try
            {
                // Generate the facet-to-texture transformation
                MushMeshTools::FacetToTextureTransformMake(texTileWRef, facetVertices);
			}
            catch (std::exception& e)
            {
                MushcoreLog::Sgl().ErrorLog() << "Faulty mesh was:" << endl;
                MushcoreLog::Sgl().XMLErrorLog() << ioMesh;
                throw;
            }
            U32 tileTexCoordBase = texCoordNum;
            
			U32 numVertices = facetVertices.size();
            for (U32 i=0; i<numVertices; ++i)
            {
                t2Val uvVector;
				texTileWRef.FacetToTexture(uvVector, facetVertices[i]);
                
				t4Val testVec;
				texTileWRef.TextureToFacet(testVec, uvVector);				
				
                if (uvVector.X() < -0.01 || uvVector.X() > 1.01 || uvVector.Y() < -0.01 || uvVector.Y() > 1.01)
				{
					MushcoreLog::Sgl().WarningLog()  << "Bad uv coordinates generated: " << uvVector << endl;
				}
                
                // Add the new texture coordinate to mesh
                if (texCoordNum >= texCoordsWRef.size())
                {
                    texCoordsWRef.resize(texCoordNum + 16);
                }
                MUSHCOREASSERT(texCoordNum < texCoordsWRef.size());
                texCoordsWRef[texCoordNum] = t4Val(uvVector.X(), uvVector.Y(), 0, 1);
                
                // Add a reference to that coordinate to the face
                MUSHCOREASSERT(texCoordBase + i < texCoordListWRef.size());
                texCoordListWRef[texCoordBase + i] = texCoordNum;
                
                // Advance to the next free texture coordinate slot read for the next one
                ++texCoordNum;
            }

            
#ifdef MUSHCORE_DEBUG
            // Only report the first few errors
            static bool textureError = false;
            
            for (U32 i=0; i<numVertices; ++i)
            {
                t2Val uvPos = t2Val(texCoordsWRef[tileTexCoordBase+i].X(), texCoordsWRef[tileTexCoordBase+i].Y());
                t4Val resultVec, expectedVec;
                
                texTileWRef.TextureToFacet(resultVec, uvPos);
                
                expectedVec = facetVertices[i];
				
                if (!expectedVec.ApproxEqual(resultVec, ioMesh.BoundingRadius() / 10))
                {
					++textureErrorCount;
                    if (textureErrorCount < 10)
                    {
                        MushcoreLog::Sgl().InfoLog() << "Texture coordinate check failed:" << endl;
                        MushcoreLog::Sgl().InfoLog() << "i=" << i << ", uvPos=" << uvPos << ", resultVec=" << resultVec <<
                            ", expectedVec=" << expectedVec << endl;
                        
                        textureError = true;
                    }
                }
            }
#endif

            ++texTileNum;
            texCoordBase += numVertices;
        }
    }
    ioMesh.TexCoordCounterSet(texCoordNum);

    if (textureErrorCount)
    {
        MushcoreLog::Sgl().WarningLog() << "Number of texture tile errors: " << textureErrorCount <<
            " in " << texTilesWRef.size() << " tiles" << endl;
    }
}

//%outOfLineFunctions {

const char *MushSkinTiled::AutoName(void) const
{
    return "MushSkinTiled";
}

MushcoreVirtualObject *MushSkinTiled::AutoClone(void) const
{
    return new MushSkinTiled(*this);
}

MushcoreVirtualObject *MushSkinTiled::AutoCreate(void) const
{
    return new MushSkinTiled;
}

MushcoreVirtualObject *MushSkinTiled::AutoVirtualFactory(void)
{
    return new MushSkinTiled;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinTiled", MushSkinTiled::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinTiled::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "pullInRatio=" << m_pullInRatio;
    ioOut << "]";
}
bool
MushSkinTiled::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushSkinTiled::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("pullInRatio");
    ioOut << m_pullInRatio;
}
//%outOfLineFunctions } dSEd05ZOWmX21GbElAx9dw

