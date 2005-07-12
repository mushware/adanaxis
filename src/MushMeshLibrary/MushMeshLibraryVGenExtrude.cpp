//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryVGenExtrude.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 2KTLnycOd02KKD1ahGuagQ
/*
 * $Id$
 * $Log$
 */

#include "MushMeshLibraryVGenExtrude.h"

using namespace Mushware;
using namespace std;

void
MushMeshLibraryVGenExtrude::FaceExtrudeOne(MushMesh4Mesh& ioMesh, const MushMeshDisplacement& inDisp, Mushware::U32 inFace)
{
    const MushMesh4Face& faceRef = ioMesh.Face(inFace);
    
    const MushMesh4Face::tVertexList& uniqueVertexListRef = faceRef.UniqueVertexList();
    tSize uniqueVertexListSize = uniqueVertexListRef.size();
    
    U32 vertexBase = ioMesh.VertexCounter();
    tSize newSize = vertexBase + uniqueVertexListSize;
    
    MushMesh4Mesh::tVertices& verticesRef = ioMesh.VerticesWRef();
    U32 verticesSize = verticesRef.size();

    if (verticesRef.size() < newSize)
    {
        verticesRef.resize(newSize);
        verticesSize = verticesRef.size();
    }
    
    t4Val centroid = ioMesh.FaceCentroid(inFace);
    
    for (U32 i=0; i<uniqueVertexListSize; ++i)
    {
        MUSHCOREASSERT(i < uniqueVertexListRef.size());
        U32 newVertexNum = uniqueVertexListRef[i];
        MUSHCOREASSERT(newVertexNum < verticesSize);
        t4Val newVertex = verticesRef[newVertexNum];
        
        newVertex = inDisp.Scale() * (newVertex - centroid);
        inDisp.Rotation().InPlaceRotate(newVertex);
        newVertex += inDisp.Offset();
        newVertex += centroid;
        
        verticesRef[vertexBase + i] = newVertex;
    }
    ioMesh.VertexCounterSet(newSize); 
}    

void
MushMeshLibraryVGenExtrude::FaceExtrude(MushMesh4Mesh& ioMesh, MushMeshDisplacement& ioDisp, Mushware::U32 inFace, Mushware::U32 inNum)
{
    for (U32 i=0; i<inNum; ++i)
    {
        FaceExtrudeOne(ioMesh, ioDisp, inFace);
    }
}


//%outOfLineFunctions {

const char *MushMeshLibraryVGenExtrude::AutoName(void) const
{
    return "MushMeshLibraryVGenExtrude";
}

MushcoreVirtualObject *MushMeshLibraryVGenExtrude::AutoClone(void) const
{
    return new MushMeshLibraryVGenExtrude(*this);
}

MushcoreVirtualObject *MushMeshLibraryVGenExtrude::AutoCreate(void) const
{
    return new MushMeshLibraryVGenExtrude;
}

MushcoreVirtualObject *MushMeshLibraryVGenExtrude::AutoVirtualFactory(void)
{
    return new MushMeshLibraryVGenExtrude;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshLibraryVGenExtrude", MushMeshLibraryVGenExtrude::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshLibraryVGenExtrude::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMesh4VertexGenerator::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushMeshLibraryVGenExtrude::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushMesh4VertexGenerator::AutoXMLDataProcess(ioIn, inTagStr))
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
MushMeshLibraryVGenExtrude::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMesh4VertexGenerator::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } /HtH1CPoaff3QRA7MQ2mqg
