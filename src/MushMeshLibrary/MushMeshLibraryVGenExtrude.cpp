//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryVGenExtrude.cpp
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
//%Header } 1XpIVIgiHvKJLMjMoray6A
/*
 * $Id: MushMeshLibraryVGenExtrude.cpp,v 1.4 2005/07/14 16:55:09 southa Exp $
 * $Log: MushMeshLibraryVGenExtrude.cpp,v $
 * Revision 1.4  2005/07/14 16:55:09  southa
 * Mesh library work
 *
 * Revision 1.3  2005/07/14 12:50:31  southa
 * Extrusion work
 *
 * Revision 1.2  2005/07/13 20:35:48  southa
 * Extrusion work
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshLibraryVGenExtrude.h"

using namespace Mushware;
using namespace std;

void
MushMeshLibraryVGenExtrude::FaceExtrudeOne(MushMesh4Mesh& ioMesh, const MushMeshDisplacement& inDisp, Mushware::U32& ioFaceNum)
{
    const MushMesh4Face& srcFaceRef = ioMesh.Face(ioFaceNum);

    const std::vector<U32>& extrudedFacesRef = srcFaceRef.ExtrudedFaces();
    U32 keyFaceNum = 0;
    
    for (U32 i=0; i < extrudedFacesRef.size(); ++i)
    {
        keyFaceNum = extrudedFacesRef[i];
        const MushMesh4Face& extrudedFaceRef = ioMesh.Face(extrudedFacesRef[i]);
        const MushMesh4Face::tTransformList& extrusionTransformListRef = extrudedFaceRef.ExtrusionTransformList();
        Mushware::U32 extrusionTransformListSize = extrusionTransformListRef.size();
        
        t4Val centroid = ioMesh.FaceCentroid(ioFaceNum);
        
        MushMesh4Mesh::tVertices& verticesRef = ioMesh.VerticesWRef();
        U32 verticesSize = verticesRef.size();
        
        for (U32 j=0; j<extrusionTransformListSize; ++j)
        {
            const MushMesh4Face::tTransform& transformRef = extrusionTransformListRef[j];
            U32 oldVertexNum = transformRef.first;
            U32 newVertexNum = transformRef.second;
            
            if (oldVertexNum >= verticesSize || newVertexNum >= verticesSize)
            {
                throw MushcoreDataFail("Index overrun in extrusion transform map");
            }
            
            t4Val newVertex = verticesRef[oldVertexNum];
            
            newVertex = inDisp.Scale() * (newVertex - centroid);
            inDisp.Rotation().VectorRotate(newVertex);
            newVertex += inDisp.Offset();
            newVertex += centroid;
            
            verticesRef[newVertexNum] = newVertex;
        }
        
        // Looping through these wouldn't work as each extrusion needs it's own ioDisp
        break;
    }
    
    ioFaceNum = keyFaceNum;
}    

void
MushMeshLibraryVGenExtrude::FaceExtrude(MushMesh4Mesh& ioMesh, MushMeshLibraryExtrusionContext& ioContext, Mushware::U32 inNum)
{
    MushMesh4Mesh::tVertices& verticesRef = ioMesh.VerticesWRef();
    if (ioMesh.VertexCounter() > verticesRef.size())
    {
        verticesRef.resize(ioMesh.VertexCounter());
    }
    
    for (U32 i=0; i<inNum; ++i)
    {
        FaceExtrudeOne(ioMesh, ioContext.RollingDispWRef(), ioContext.RollingFaceNumWRef());
        ioContext.VelocityAdd();
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
