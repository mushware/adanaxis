//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryVGenExtrude.cpp
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
//%Header } cpuHvOGMjHTRln6lMEXwpw
/*
 * $Id: MushMeshLibraryVGenExtrude.cpp,v 1.8 2007/04/18 09:22:54 southa Exp $
 * $Log: MushMeshLibraryVGenExtrude.cpp,v $
 * Revision 1.8  2007/04/18 09:22:54  southa
 * Header and level fixes
 *
 * Revision 1.7  2006/08/01 17:21:36  southa
 * River demo
 *
 * Revision 1.6  2006/06/14 18:45:49  southa
 * Ruby mesh generation
 *
 * Revision 1.5  2006/06/01 15:39:34  southa
 * DrawArray verification and fixes
 *
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
            
            newVertex = inDisp.Scale().ElementwiseProduct((newVertex - centroid));
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
