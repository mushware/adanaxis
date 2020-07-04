//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryBase.cpp
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
//%Header } B7+XGkVfQAWexR8enVPWUw
/*
 * $Id: MushMeshLibraryBase.cpp,v 1.11 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryBase.cpp,v $
 * Revision 1.11  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
 * Revision 1.10  2006/09/12 15:28:50  southa
 * World sphere
 *
 * Revision 1.9  2006/08/01 17:21:33  southa
 * River demo
 *
 * Revision 1.8  2006/07/17 14:43:40  southa
 * Billboarded deco objects
 *
 * Revision 1.7  2006/06/16 01:02:32  southa
 * Ruby mesh generation
 *
 * Revision 1.6  2006/06/01 15:39:33  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/08/01 17:58:44  southa
 * Object explosion
 *
 * Revision 1.4  2005/07/19 13:44:26  southa
 * MushMesh4Chunk work
 *
 * Revision 1.3  2005/07/16 14:22:59  southa
 * Added diagnostic renderer
 *
 * Revision 1.2  2005/07/14 16:55:09  southa
 * Mesh library work
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshLibraryBase.h"

#include "MushMeshLibraryUtil.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushMeshLibraryBase);

void
MushMeshLibraryBase::UnitTesseractVerticesCreate(MushMesh4Mesh& ioMesh) const
{
    tVal scale = 0.5;
    
    MushMesh4Mesh::tVertices& verticesRef = ioMesh.VerticesWRef();
    
    if (verticesRef.size() < 16)
    {
        verticesRef.resize(16);
    }
    
    // Vertices
    for (U32 i=0; i<16; ++i)
    {
        MushMesh4Mesh::tVertex& vertex = verticesRef[i];
        
        vertex.XSet(((i & 1) == 0)?-scale:scale);
        vertex.YSet(((i & 2) == 0)?-scale:scale);
        vertex.ZSet(((i & 4) == 0)?-scale:scale);
        vertex.WSet(((i & 8) == 0)?-scale:scale);
    }
    ioMesh.VertexCounterSet(16);
}

void
MushMeshLibraryBase::UnitTesseractCreate(MushMesh4Mesh& ioMesh) const
{
    MushMesh4Face *pFace = NULL;
    MushMesh4Face::tVertexList *pVertexList = NULL;
    MushMesh4Face::tVertexGroupSize *pVertexGroupSize = NULL;
    
    // Chunk.  All faces are placed in one chunk
    MushMesh4Util::NewChunkCreate(ioMesh);
    
    // Vertices
    UnitTesseractVerticesCreate(ioMesh);
    
    U32 fixedAxis = 8;
    
    // Faces
    for (U32 i=0; i<8 && fixedAxis > 0; ++i)
    {
        // Creating new faces invalidates references to other faces and their components
        MushMesh4Util::NewFaceCreate(ioMesh, pFace, pVertexList, pVertexGroupSize);
        
        // fixedAxis: 1->x, 2->y, 4->z, 8->w
        
        // fixedAxisOffset: 0->fixed to -scale, fixedAxis->fixed to +scale
        U32 fixedAxisOffset;
        if ((i % 2) == 0)
        {
            fixedAxisOffset = 0;
        }
        else
        {
            fixedAxisOffset = fixedAxis;
        }
        
        /* The vertex set for each face is determined by fixing one value
            * x,y,z or w at -scale or +scale. Sets for w=-scale are
            * xy,z=-scale 0,1,3,2
            * xz,y=-scale 0,1,5,4
            * yz,x=-scale 0,2,6,4
            * xy,z=+scale 4,5,7,6
            * xz,y=+scale 2,3,7,6
            * yz,x=+scale 1,3,7,5
            * Face normal will be defined by 0, 1, 3, 4, i.e. the two vertices
            * on either side of 0, and the replacment for 0 in the next facet
            */
        
        U32 planeAxis = 8;
        
        // Facets
        for (U32 j=0; j<6; ++j)
        {
            if (planeAxis == fixedAxis)
            {
                MUSHCOREASSERT(fixedAxis > 0 && planeAxis > 0);
                planeAxis /= 2;
            }
            
            U32 planeAxisOffset;
            if ((j % 2) == 0)
            {
                planeAxisOffset = 0;
            }
            else
            {
                planeAxisOffset = planeAxis;
            }
            
            U32 lowAxis = 1;
            while (lowAxis == fixedAxis || lowAxis == planeAxis)
            {
                lowAxis *= 2;
            }
            
            U32 highAxis = lowAxis * 2;
            while (highAxis == fixedAxis || highAxis == planeAxis)
            {
                highAxis *= 2;
            }
            
            U32 baseOffset = fixedAxisOffset + planeAxisOffset;
            
            pVertexList->push_back(baseOffset);
            pVertexList->push_back(baseOffset + lowAxis);
            pVertexList->push_back(baseOffset + lowAxis + highAxis);
            pVertexList->push_back(baseOffset + highAxis);
            
            pVertexGroupSize->push_back(4);
            
            if ((j % 2) == 1)
            {
                planeAxis /= 2;
            }
        }
        if ((i % 2) == 1)
        {
            fixedAxis /= 2;
        }
    }
}

void
MushMeshLibraryBase::PolygonPrismVerticesCreate(MushMesh4Mesh& ioMesh, const Mushware::t4Val& inScale, Mushware::U32 inOrder) const
{
    MushMesh4Mesh::tVertices& verticesRef = ioMesh.VerticesWRef();

    U32 numVertices = inOrder * 4;
    
    if (verticesRef.size() < numVertices)
    {
        verticesRef.resize(numVertices);
    }
    
    tVal angularStep = M_PI * 2.0 / inOrder;
    U32 vertexNum = 0;
    
    t4Val scale = inScale / 2;
    
    // Vertices.  Face 2 should be in the x=k hyperplane for convenient extrusion
    for (U32 i=0; i<4; ++i)
    {
        for (U32 j=0; j<inOrder; ++j)
        {
            MushMesh4Mesh::tVertex& vertex = verticesRef[vertexNum];
            
            vertex.XSet(scale.X() * cos(angularStep * (j-0.5)));
            vertex.YSet(scale.Y() * sin(angularStep * (j-0.5)));
            vertex.ZSet(((i & 1) == 0)?-scale.Z():scale.Z());
            vertex.WSet(((i & 2) == 0)?-scale.W():scale.W());
            
            ++vertexNum;
        }
    }
    MUSHCOREASSERT(vertexNum == numVertices);
    ioMesh.VertexCounterSet(numVertices);
}

void
MushMeshLibraryBase::PolygonPrismCreate(MushMesh4Mesh& ioMesh, const Mushware::t4Val& inScale, Mushware::U32 inOrder) const
{
    ioMesh.FaceCounterSet(0);

    MushMesh4Mesh::tFaces& facesRef = ioMesh.FacesWRef();
    facesRef.resize(0);
    
    MushMesh4Face *pFace = NULL;
    MushMesh4Face::tVertexList *pVertexList = NULL;
    MushMesh4Face::tVertexGroupSize *pVertexGroupSize = NULL;
    
    // Chunk.  All faces are placed in one chunk
    MushMesh4Util::NewChunkCreate(ioMesh);
    
    // Vertices
    PolygonPrismVerticesCreate(ioMesh, inScale, inOrder);
    
    U32 zStep = inOrder;
    U32 wStep = 2*inOrder;
    
    // w-fixed faces
    
    for (U32 w=0; w<2; ++w)
    {
        // Polygon end facets (the ends of the prism)
        // Creating new faces invalidates references to other faces and their components
        MushMesh4Util::NewFaceCreate(ioMesh, pFace, pVertexList, pVertexGroupSize);
        U32 vBase = w * wStep;   
        for (U32 z=0; z<2; ++z)
        {
            // zw-fixed facets
            for (U32 n=0; n<inOrder; ++n)
            {
                pVertexList->push_back(vBase + z*zStep + n);
            }
            pVertexGroupSize->push_back(inOrder);
        }
        
        // radial facets
        for (U32 n=0; n<inOrder; ++n)
        {
            U32 nPlusOneModOrder = (n + 1) % inOrder;
            pVertexList->push_back(vBase + n);
            pVertexList->push_back(vBase + nPlusOneModOrder);
            pVertexList->push_back(vBase + zStep + nPlusOneModOrder);
            pVertexList->push_back(vBase + zStep + n);
            pVertexGroupSize->push_back(4);
        }
    }
    CongruentFacesJoin(ioMesh, ioMesh.FaceCounter() - 1, ioMesh.FaceCounter() - 2);
}

void
MushMeshLibraryBase::CongruentFacesJoin(MushMesh4Mesh& ioMesh, Mushware::U32 inFaceNum1, Mushware::U32 inFaceNum2) const
{
    // Loop through the vertex groups (i.e. each facet) in the source face
    U32 srcVertNum = 0;
    for (U32 i=0; i< ioMesh.Face(inFaceNum1).VertexGroupSize().size(); ++i)
    {        
        MushMesh4Face *pFace = NULL;
        MushMesh4Face::tVertexList *pVertexList = NULL;
        MushMesh4Face::tVertexGroupSize *pVertexGroupSize = NULL;
        
        // Create a new (joining) face for each facet in the source face
        // Creating new faces invalidates references to other faces and their components
        MushMesh4Util::NewFaceCreate(ioMesh, pFace, pVertexList, pVertexGroupSize);
        
        const MushMesh4Face& face1Ref = ioMesh.Face(inFaceNum1);
        const MushMesh4Face::tVertexList& vertexList1Ref = face1Ref.VertexList();
        const MushMesh4Face& face2Ref = ioMesh.Face(inFaceNum2);
        const MushMesh4Face::tVertexList& vertexList2Ref = face2Ref.VertexList();
        
        U32 groupSize = ioMesh.Face(inFaceNum1).VertexGroupSize()[i];
        
        // Copy the facets from the two input faces to this new face
        std::copy(vertexList1Ref.begin()+srcVertNum, vertexList1Ref.begin()+srcVertNum+groupSize, back_inserter(*pVertexList));
        pVertexGroupSize->push_back(groupSize);
        std::copy(vertexList2Ref.begin()+srcVertNum, vertexList2Ref.begin()+srcVertNum+groupSize, back_inserter(*pVertexList));
        pVertexGroupSize->push_back(groupSize);
        
        for (U32 n=0; n<groupSize; ++n)
        {
            U32 nPlusOneModOrder = (n + 1) % groupSize;
            pVertexList->push_back(vertexList1Ref[srcVertNum + n]);
            pVertexList->push_back(vertexList1Ref[srcVertNum + nPlusOneModOrder]);
            pVertexList->push_back(vertexList2Ref[srcVertNum + nPlusOneModOrder]);
            pVertexList->push_back(vertexList2Ref[srcVertNum + n]);
            pVertexGroupSize->push_back(4);
        }
        srcVertNum += groupSize;
    }
}

void
MushMeshLibraryBase::SingleFacetCreate(MushMesh4Mesh& ioMesh,
                                       Mushware::U32 inOrder,
                                       const MushMeshDisplacement& inDisp) const
{        
    // Chunk.  All faces are placed in one chunk
    if (ioMesh.NumChunks() == 0)
    {
        MushMesh4Util::NewChunkCreate(ioMesh);
    }
    
    MushMesh4Mesh::tVertices& verticesRef = ioMesh.VerticesWRef();
    U32 vertexCounterBase = ioMesh.VertexCounter();
    
    tVal angularStep = M_PI * 2.0 / inOrder;
    tVal scale = std::sqrt(2.0); // Scale for unit square
    
    for (U32 i=0; i < inOrder; ++i)
    {
        MushMesh4Mesh::tVertex vertex;
        
        vertex.XSet(scale * cos(angularStep * (i-0.5)));
        vertex.YSet(scale * sin(angularStep * (i-0.5)));
        vertex.ZSet(0);
        vertex.WSet(0);
        
        inDisp.Displace(vertex);
        
        verticesRef.push_back(vertex);
    }

    ioMesh.VertexCounterSet(vertexCounterBase + inOrder);
    
    MushMesh4Face *pFace = NULL;
    MushMesh4Face::tVertexList *pVertexList = NULL;
    MushMesh4Face::tVertexGroupSize *pVertexGroupSize = NULL;
    
    MushMesh4Util::NewFaceCreate(ioMesh, pFace, pVertexList, pVertexGroupSize);

    for (U32 i=0; i<inOrder; ++i)
    {
        pVertexList->push_back(vertexCounterBase + i);
    }
    pVertexGroupSize->push_back(inOrder);
}

void
MushMeshLibraryBase::SingleFacetCreate(MushMesh4Mesh& ioMesh, Mushware::U32 inOrder) const
{
    MushMeshDisplacement disp = MushMeshDisplacement::Identity();
    SingleFacetCreate(ioMesh, inOrder, disp);
}



//%outOfLineFunctions {

const char *MushMeshLibraryBase::AutoName(void) const
{
    return "MushMeshLibraryBase";
}

MushcoreVirtualObject *MushMeshLibraryBase::AutoClone(void) const
{
    return new MushMeshLibraryBase(*this);
}

MushcoreVirtualObject *MushMeshLibraryBase::AutoCreate(void) const
{
    return new MushMeshLibraryBase;
}

MushcoreVirtualObject *MushMeshLibraryBase::AutoVirtualFactory(void)
{
    return new MushMeshLibraryBase;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshLibraryBase", MushMeshLibraryBase::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshLibraryBase::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMeshLibraryBase::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMeshLibraryBase::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } wQufol4cC3FpkNSmg5AJzw
