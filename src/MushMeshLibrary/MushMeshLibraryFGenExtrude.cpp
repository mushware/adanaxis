//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryFGenExtrude.cpp
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
//%Header } l0+UwpoHyOGqSBuOhWU1Vw
/*
 * $Id$
 * $Log$
 */

#include "MushMeshLibraryFGenExtrude.h"

using namespace Mushware;
using namespace std;

void
MushMeshLibraryFGenExtrude::FaceExtrudeOne(MushMesh4Mesh& ioMesh, Mushware::U32 inFace)
{
    /* Generated faces are:
     *   1.  An image of the face we're extruding from, containing all of the new vertices
     *   2.  Faces connecting each of the new facets on that face to the corresponding facet
     *       on the original face
     */

    // Faces are held in a vector, so creating new faces can invalidate references

    MushMesh4Mesh::tFaces& facesRef = ioMesh.FacesWRef();
    facesRef.push_back(MushMesh4Mesh::tFace(ioMesh.Face(inFace)));
    MushMesh4Mesh::tFace& newFaceRef = facesRef.back();

    const MushMesh4Mesh::tFace& oldFaceRef = ioMesh.Face(inFace);
    
    
    const MushMesh4Face::tVertexList& uniqueVertexListRef = oldFaceRef.UniqueVertexList();
    tSize uniqueVertexListSize = uniqueVertexListRef.size();






    // Build the correspondance list in this face
    U32 vertexBase = ioMesh.VertexCounter();

    /* Correspondance lists map a vertex number in the old face to the same
     * vertex in the extruded face
     */
    
    std::map<U32, U32> vertexOldToNew;
    std::map<U32, U32> vertexNewToOld;
    for (U32 i=0; i<uniqueVertexListSize; ++i)
    {
        vertexOldToNew[uniqueVertexListRef[i]] = vertexBase;
        vertexNewToOld[vertexBase] = uniqueVertexListRef[i];
        ++vertexBase;
    }
    
    MushMesh4Face::tVertexList& newVertexListRef = newFaceRef.VertexListWRef();
    tSize newVertexListSize = newVertexListRef.size();
    
    for (U32 i=0; i<newVertexListSize; ++i)
    {
        U32 vertexNum = newVertexListRef[i];
        std::map<U32, U32>::iterator p = vertexOldToNew.find(vertexNum);
        if (p == vertexOldToNew.end())
        {
            cout << "vertexOldToNew=" << vertexOldToNew << endl;
            cout << "vertexNum=" << vertexNum << endl;
            throw MushcoreLogicFail(std::string(AutoName())+": Invalid correspondance map");
        }
        else
        {
            newVertexListRef[i] = p->second;
        }
    }
}

void
MushMeshLibraryFGenExtrude::FaceExtrude(MushMesh4Mesh& ioMesh, Mushware::U32 inFace, Mushware::U32 inNum)
{
    for (U32 i=0; i<inNum; ++i)
    {
        FaceExtrudeOne(ioMesh, inFace);
    }
}

//%outOfLineFunctions {

const char *MushMeshLibraryFGenExtrude::AutoName(void) const
{
    return "MushMeshLibraryFGenExtrude";
}

MushcoreVirtualObject *MushMeshLibraryFGenExtrude::AutoClone(void) const
{
    return new MushMeshLibraryFGenExtrude(*this);
}

MushcoreVirtualObject *MushMeshLibraryFGenExtrude::AutoCreate(void) const
{
    return new MushMeshLibraryFGenExtrude;
}

MushcoreVirtualObject *MushMeshLibraryFGenExtrude::AutoVirtualFactory(void)
{
    return new MushMeshLibraryFGenExtrude;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshLibraryFGenExtrude", MushMeshLibraryFGenExtrude::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshLibraryFGenExtrude::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMesh4FaceGenerator::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushMeshLibraryFGenExtrude::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushMesh4FaceGenerator::AutoXMLDataProcess(ioIn, inTagStr))
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
MushMeshLibraryFGenExtrude::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMesh4FaceGenerator::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } o+mCXEu+AbRb/A0bBOaPUw
