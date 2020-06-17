//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMesh.cpp
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
//%Header } 11x4nUYp5tiJ2MVaLSwpEg
/*
 * $Id: MushRenderMesh.cpp,v 1.8 2006/11/06 20:37:28 southa Exp $
 * $Log: MushRenderMesh.cpp,v $
 * Revision 1.8  2006/11/06 20:37:28  southa
 * Alloc and bounding radius fixes
 *
 * Revision 1.7  2006/09/09 11:16:41  southa
 * One-time vertex buffer generation
 *
 * Revision 1.6  2006/07/25 13:30:58  southa
 * Initial scanner work
 *
 * Revision 1.5  2006/07/24 18:46:50  southa
 * Depth sorting
 *
 * Revision 1.4  2006/06/01 15:39:38  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/07/01 10:36:46  southa
 * MushRender work
 *
 */

#include "MushRenderMesh.h"

using namespace Mushware;
using namespace std;

MushRenderMesh::MushRenderMesh() :
    m_colourZMiddle(t4Val(1.0,1.0,1.0,1.0)),
    m_colourZLeft(t4Val(1.0,1.0,1.0,0.0)),
    m_colourZRight(t4Val(1.0,1.0,1.0,0.0))
{
}

void
MushRenderMesh::MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh)
{
    // No render output
}

bool
MushRenderMesh::RenderJobCreate(MushGLJobRender& outRender,
                                const MushRenderSpec& inSpec,
                                const MushMeshMesh& inMesh)
{
    // Never creates a render job
    return false;
}

void
MushRenderMesh::MeshDelegatesGet(const MushMesh4Mesh *& outpVertexMesh,
                                 const MushMesh4Mesh *& outpColourMesh,
                                 const MushMesh4Mesh *& outpTexCoordMesh,
                                 const MushMesh4Mesh& inMesh)
{
    if (inMesh.VertexDelegate().Name().size() == 0)
    {
        // Name not set, use same mesh
        outpVertexMesh = &inMesh;
    }
    else
    {
        outpVertexMesh = &inMesh.VertexDelegate().Ref();
    }
    
    if (inMesh.ColourDelegate().Name().size() == 0)
    {
        // Name not set, use same mesh
        outpColourMesh = &inMesh;
    }
    else
    {
        outpColourMesh = &inMesh.ColourDelegate().Ref();
    }
    
    if (inMesh.TexCoordDelegate().Name().size() == 0)
    {
        // Name not set, use same mesh
        outpTexCoordMesh = &inMesh;
    }
    else
    {
        outpTexCoordMesh = &inMesh.TexCoordDelegate().Ref();
    }
}

void
MushRenderMesh::DestDelegatesGet(MushGLBuffers *& outpDestVertex,
                                 MushGLBuffers *& outpDestColour,
                                 MushGLBuffers *& outpDestTexCoord,
                                 const MushRenderSpec& inSpec)
{
    if (inSpec.BuffersRef().Name() == 0)
    {
        throw MushcoreDataFail("DestDelegatesGet data name not set");
    }
    if (inSpec.SharedBuffersRef().Name() == "")
    {
        throw MushcoreDataFail("DestDelegatesGet shared data name not set");
    }    
    
    MushGLBuffers& localDestRef = inSpec.BuffersRef().WRef();

    if (inSpec.UseSharedVertices())
    {
        outpDestVertex = &inSpec.SharedBuffersRef().WRef();
    }
    else
    {
        outpDestVertex = &localDestRef;
    }
    
    outpDestColour = &localDestRef;
    
    outpDestTexCoord = &inSpec.SharedBuffersRef().WRef();
}

void
MushRenderMesh::TriangleListBuild(MushGLBuffers::tTriangleList& ioList, const MushMesh4Mesh& inMesh,
                                        tSourceType inSourceType)
{
    ioList.resize(0);
    U32 numFaces = inMesh.Faces().size();
    U32 entryLimit = 0;
    for (U32 faceNum=0; faceNum<numFaces; ++faceNum)
    {
        if (!inMesh.Face(faceNum).Internal())
        { 
            const MushMesh4Face::tVertexList *pSrcList = NULL;
            switch (inSourceType)
            {
                case kSourceTypeVertex:
                    pSrcList = &inMesh.Face(faceNum).VertexList();
                    entryLimit = inMesh.Vertices().size();
                    break;
                    
                case kSourceTypeTexCoord:
                    pSrcList = &inMesh.Face(faceNum).TexCoordList();
                    entryLimit = inMesh.TexCoords().size();
                    break;
                    
                default:
                    throw MushcoreLogicFail("Bad source type selector");
            }
            
            const MushMesh4Face::tVertexList& srcListRef = *pSrcList;
            
            U32 srcListSize = srcListRef.size();
            
            const MushMesh4Face::tVertexGroupSize& srcGroupSizeRef = inMesh.Face(faceNum).VertexGroupSize();
            U32 numFacets = srcGroupSizeRef.size();
            
            U32 srcFaceIndex = 0;
            for (U32 facetNum=0; facetNum<numFacets; ++facetNum)
            {
                // listNum0 is srcFaceIndex
                if (srcFaceIndex >= srcListSize)
                {
                    throw MushcoreDataFail(std::string("Vertex list overrun in ")+AutoName());
                }            
                U32 entryValue0 = srcListRef[srcFaceIndex]; 
                if (entryValue0 >= entryLimit)
                {
                    throw MushcoreDataFail(std::string("Entry index list overrun in ")+AutoName());
                }
                // Add triangles for this facet
                U32 groupSize = srcGroupSizeRef[facetNum];
                
                for (U32 i=1; i+1 < groupSize; ++i)
                {
                    U32 listNum1 = srcFaceIndex + i;
                    U32 listNum2 = srcFaceIndex + i + 1;
                    
                    if (listNum1 >= srcListSize || listNum2 >= srcListSize)
                    {
                        throw MushcoreDataFail(std::string("Vertex list overrun in ")+AutoName());
                    }
                    U32 entryValue1 = srcListRef[listNum1];
                    U32 entryValue2 = srcListRef[listNum2];
                    if (entryValue1 >= entryLimit || entryValue2 >= entryLimit)
                    {
                        throw MushcoreDataFail(std::string("Entry index list overrun in ")+AutoName());
                    }
                    ioList.push_back(entryValue0);
                    ioList.push_back(entryValue1);
                    ioList.push_back(entryValue2);
                }
                srcFaceIndex += groupSize;
            }
        }
    }
}

Mushware::tVal
MushRenderMesh::SortDepth(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh)
{
    t4Val objCentre = inMesh.Centroid();
    objCentre = inSpec.ModelToEyeMattress() * objCentre;
    return objCentre.W();
}

bool
MushRenderMesh::ShouldMeshCull(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh)
{
    // Transform mesh centroid to eye coordinates
    t4Val objCentre = inSpec.ModelToEyeMattress() * inMesh.Centroid();
    tVal boundingRadius = inMesh.BoundingRadius() * inSpec.Scale().Magnitude() / 2.0;
    
    const t4Val& clipMin = inSpec.Projection().ClipMin();
    const t4Val& clipMax = inSpec.Projection().ClipMax();
    const t4Val& brFactor = inSpec.Projection().BoundingRadiusFactor();
    
    /* Cull unless the centre of the object is within a bounding radius of
     * any part of the view frustum
     */
    return (objCentre.W() + boundingRadius < -clipMax.W() ||
            objCentre.W() - boundingRadius > -clipMin.W() ||
            objCentre.X() + boundingRadius * brFactor.X() < clipMin.X() * -objCentre.W() ||
            objCentre.X() - boundingRadius * brFactor.X() > clipMax.X() * -objCentre.W() ||
            objCentre.Y() + boundingRadius * brFactor.Y() < clipMin.Y() * -objCentre.W() ||
            objCentre.Y() - boundingRadius * brFactor.Y() > clipMax.Y() * -objCentre.W() ||
            objCentre.Z() + boundingRadius * brFactor.Z() < clipMin.Z() * -objCentre.W() ||
            objCentre.Z() - boundingRadius * brFactor.Z() > clipMax.Z() * -objCentre.W());
}

void
MushRenderMesh::CentroidToClip(Mushware::t4Val outPos,
                               const MushRenderSpec& inSpec,
                               const MushMesh4Mesh& inMesh)
{
    outPos = inSpec.ModelToClipMattress() * inMesh.Centroid();
}

//%outOfLineFunctions {

const char *MushRenderMesh::AutoName(void) const
{
    return "MushRenderMesh";
}

MushcoreVirtualObject *MushRenderMesh::AutoClone(void) const
{
    return new MushRenderMesh(*this);
}

MushcoreVirtualObject *MushRenderMesh::AutoCreate(void) const
{
    return new MushRenderMesh;
}

MushcoreVirtualObject *MushRenderMesh::AutoVirtualFactory(void)
{
    return new MushRenderMesh;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushRenderMesh", MushRenderMesh::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushRenderMesh::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "colourZMiddle=" << m_colourZMiddle << ", ";
    ioOut << "colourZLeft=" << m_colourZLeft << ", ";
    ioOut << "colourZRight=" << m_colourZRight;
    ioOut << "]";
}
bool
MushRenderMesh::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "colourZMiddle")
    {
        ioIn >> m_colourZMiddle;
    }
    else if (inTagStr == "colourZLeft")
    {
        ioIn >> m_colourZLeft;
    }
    else if (inTagStr == "colourZRight")
    {
        ioIn >> m_colourZRight;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushRenderMesh::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("colourZMiddle");
    ioOut << m_colourZMiddle;
    ioOut.TagSet("colourZLeft");
    ioOut << m_colourZLeft;
    ioOut.TagSet("colourZRight");
    ioOut << m_colourZRight;
}
//%outOfLineFunctions } pslRJMpPdx7pmha/kHkKwg
