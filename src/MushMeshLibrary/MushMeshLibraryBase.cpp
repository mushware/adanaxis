//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryBase.cpp
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
//%Header } lKuxq2tc2FqBaZd4TQuE+A
/*
 * $Id: MushMeshLibraryBase.cpp,v 1.5 2005/08/01 17:58:44 southa Exp $
 * $Log: MushMeshLibraryBase.cpp,v $
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
    
    // Vertices
    for (U32 i=0; i<4; ++i)
    {
        for (U32 j=0; j<inOrder; ++j)
        {
            MushMesh4Mesh::tVertex& vertex = verticesRef[vertexNum];
            
            vertex.XSet(scale.X() * cos(angularStep * j));
            vertex.YSet(scale.Y() * sin(angularStep * j));
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
