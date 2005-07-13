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
 * $Id: MushMeshLibraryVGenExtrude.cpp,v 1.1 2005/07/12 20:39:05 southa Exp $
 * $Log: MushMeshLibraryVGenExtrude.cpp,v $
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshLibraryVGenExtrude.h"

using namespace Mushware;
using namespace std;

void
MushMeshLibraryVGenExtrude::FaceExtrudeOne(MushMesh4Mesh& ioMesh, const MushMeshDisplacement& inDisp, Mushware::U32 inFaceNum)
{
    const MushMesh4Face& srcFaceRef = ioMesh.Face(inFaceNum);

    const std::vector<U32>& extrudedFacesRef = srcFaceRef.ExtrudedFaces();
    
    for (U32 i=0; i < extrudedFacesRef.size(); ++i)
    {
        const MushMesh4Face& extrudedFaceRef = ioMesh.Face(extrudedFacesRef[i]);
        const MushMesh4Face::tTransformList& extrusionTransformListRef = extrudedFaceRef.ExtrusionTransformList();
        Mushware::U32 extrusionTransformListSize = extrusionTransformListRef.size();
        
        t4Val centroid = ioMesh.FaceCentroid(inFaceNum);
        
        MushMesh4Mesh::tVertices& verticesRef = ioMesh.VerticesWRef();
        U32 verticesSize = verticesRef.size();
        
        for (U32 i=0; i<extrusionTransformListSize; ++i)
        {
            const MushMesh4Face::tTransform& transformRef = extrusionTransformListRef[i];
            U32 oldVertexNum = transformRef.first;
            U32 newVertexNum = transformRef.second;
            
            if (oldVertexNum >= verticesSize || newVertexNum >= verticesSize)
            {
                throw MushcoreDataFail("Index overrun in extrusion transform map");
            }
            
            t4Val newVertex = verticesRef[oldVertexNum];
            
            newVertex = inDisp.Scale() * (newVertex - centroid);
            inDisp.Rotation().InPlaceRotate(newVertex);
            newVertex += inDisp.Offset();
            newVertex += centroid;
            
            verticesRef[newVertexNum] = newVertex;
        }
        
        // Looping through these wouldn't work as each extrusion needs it's own ioDisp
        break;
    }
}    

void
MushMeshLibraryVGenExtrude::FaceExtrude(MushMesh4Mesh& ioMesh, MushMeshDisplacement& ioDisp, Mushware::U32 inFaceNum, Mushware::U32 inNum)
{
    MushMesh4Mesh::tVertices& verticesRef = ioMesh.VerticesWRef();
    if (ioMesh.VertexCounter() > verticesRef.size())
    {
        verticesRef.resize(ioMesh.VertexCounter());
    }
    
    for (U32 i=0; i<inNum; ++i)
    {
        FaceExtrudeOne(ioMesh, ioDisp, inFaceNum);
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
