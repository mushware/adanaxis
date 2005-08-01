//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryFGenExtrude.cpp
 *
 * Copyright: Andy Southgate 2005
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
//%Header } 5mXJjsgE9FySBp3B30JsGw
/*
 * $Id: MushMeshLibraryFGenExtrude.cpp,v 1.6 2005/07/19 13:44:26 southa Exp $
 * $Log: MushMeshLibraryFGenExtrude.cpp,v $
 * Revision 1.6  2005/07/19 13:44:26  southa
 * MushMesh4Chunk work
 *
 * Revision 1.5  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.4  2005/07/14 12:50:31  southa
 * Extrusion work
 *
 * Revision 1.3  2005/07/13 20:35:48  southa
 * Extrusion work
 *
 * Revision 1.2  2005/07/13 16:45:05  southa
 * Extrusion work
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshLibraryFGenExtrude.h"

#include "MushMeshLibraryUtil.h"

using namespace Mushware;
using namespace std;

void
MushMeshLibraryFGenExtrude::FaceExtrudeOne(MushMesh4Mesh& ioMesh, Mushware::U32& ioFaceNum, bool inToPoint)
{
    MushMesh4Mesh::tFaces& facesRef = ioMesh.FacesWRef();
    U32 numNewFaces = 0;

    {
        const MushMesh4Mesh::tFace::tFaceConnectivity& connectivityRef =
            ioMesh.FaceConnectivity(ioFaceNum);
        // We need the number of faces in the connectivity of the source face, plus one
        numNewFaces = 1 + connectivityRef.size();
        U32 newFacesSize = ioMesh.FaceCounter() + numNewFaces;

        if (newFacesSize > facesRef.size())
        {
            facesRef.resize(newFacesSize);
        }
        // References to objects within faces invalid after resize, so discard
    }

    // New chunk.  All faces are placed in one chunk
    MushMesh4Util::NewChunkCreate(ioMesh);
    
    const MushMesh4Mesh::tFace& srcFaceRef = ioMesh.Face(ioFaceNum);
    const MushMesh4Mesh::tFace::tFaceConnectivity& srcConnectivityRef =
        ioMesh.FaceConnectivity(ioFaceNum);
    
    // Generate the key face, by copying the source face to it
    MushMesh4Mesh::tFace& keyFaceRef = ioMesh.FaceWRef(ioMesh.FaceCounter());
    U32 keyFaceNum = ioMesh.FaceCounter();
    
    keyFaceRef = srcFaceRef; // Partial copy would be better

    /* After this touch, we must be careful not to create any of the derived information
     * before the vertex renumbering is done.  No function with side effects should be
     * called on this face before then
     */
    keyFaceRef.AllTouch();
    
    /* Fill the extrusion map.  It maps vertex numbers in the source face to vertex numbers
     * in all of the newly generated faces
     */
    MushMesh4Face::tExtrusionMap& extrusionMapRef = keyFaceRef.ExtrusionMapWRef();
    extrusionMapRef.clear();
    
    MushMesh4Face::tTransformList& extrusionTransformListRef = keyFaceRef.ExtrusionTransformListWRef();
    extrusionTransformListRef.clear();
    
    // Add the new vertices used to generate the key face
    const MushMesh4Face::tVertexList& srcUniqueVertexListRef = srcFaceRef.UniqueVertexList();
    tSize srcUniqueVertexListSize = srcUniqueVertexListRef.size();

    U32 vertexBase = ioMesh.VertexCounter();

    for (U32 i=0; i<srcUniqueVertexListSize; ++i)
    {
        extrusionMapRef[srcUniqueVertexListRef[i]] = vertexBase;
        if (!inToPoint)
        {
            // Extruding to a point generates only one new vertex
            extrusionTransformListRef.push_back(MushMesh4Face::tTransform(srcUniqueVertexListRef[i], vertexBase));
            ++vertexBase;
        }
    }
    if (inToPoint)
    {
        extrusionTransformListRef.push_back(MushMesh4Face::tTransform(srcUniqueVertexListRef[0], vertexBase));
        ++vertexBase;
    }

    // Copy the other faces into position, and create the correspondance map
    for (U32 newFaceNum=0; newFaceNum < srcConnectivityRef.size(); ++newFaceNum)
    {
        const MushMesh4Face::tFaceConnection& vertConnection = srcConnectivityRef[newFaceNum];
        
        MushMesh4Mesh::tFace& newFaceRef = ioMesh.FaceWRef(ioMesh.FaceCounter() + 1 + newFaceNum);
        const MushMesh4Mesh::tFace& connectedFaceRef = ioMesh.Face(vertConnection.FaceNum());
        newFaceRef = connectedFaceRef;
        
        /* After this touch, we must be careful not to create any of the derived information
         * before the vertex renumbering is done.  No function should be called on this face
         * before then
         */
        newFaceRef.AllTouch();

        MushMesh4Face::tVertexList& newVertexListRef = newFaceRef.VertexListWRef();
        tSize newVertexListSize = newVertexListRef.size();

        for (U32 i=0; i<newVertexListSize; ++i)
        {
            U32 vertexNum = newVertexListRef[i];
            std::map<U32, U32>::iterator p = extrusionMapRef.find(vertexNum);
            if (p == extrusionMapRef.end())
            {
                U32 newVertexNum;
                if (connectedFaceRef.ConnectedVertexInFacetFind(newVertexNum, vertConnection.RemoteFacetNum(), vertexNum))
                {
                    extrusionMapRef[vertexNum] = newVertexNum;
                }
                else
                {
                    throw MushcoreDataFail(std::string(AutoName())+": Failed to create correspondance map");
                }
            }
        }
    }
    
    MushMesh4Chunk::tFaceList& chunkFaceListRef = ioMesh.ChunksWRef().back().FaceListWRef();
    
    // Apply the correspondance map, fill the chunk and tidy/remove facets
    for (U32 newFaceNum=0; newFaceNum < numNewFaces; ++newFaceNum)
    {
        U32 faceIndexNum = ioMesh.FaceCounter() + newFaceNum;
        MushMesh4Mesh::tFace& newFaceRef = ioMesh.FaceWRef(faceIndexNum);
        MushMesh4Face::tVertexList& newVertexListRef = newFaceRef.VertexListWRef();
        tSize newVertexListSize = newVertexListRef.size();
        
        for (U32 i=0; i<newVertexListSize; ++i)
        {
            U32 vertexNum = newVertexListRef[i];
            std::map<U32, U32>::iterator p = extrusionMapRef.find(vertexNum);
            if (p == extrusionMapRef.end())
            {
                throw MushcoreDataFail(std::string(AutoName())+": Invalid correspondance map");
            }
            else
            {
                newVertexListRef[i] = p->second;
            }
        }
        if (inToPoint)
        {
            MushMesh4Util::NullFacetsRemove(ioMesh, faceIndexNum);
        }
        chunkFaceListRef.push_back(faceIndexNum);
    }

    // Commit the new faces
    ioMesh.FaceWRef(ioFaceNum).ExtrudedFacesWRef().push_back(ioMesh.FaceCounter());
    ioMesh.FaceCounterWRef() += numNewFaces;
    ioMesh.VertexCounterSet(vertexBase);
    ioFaceNum = keyFaceNum; // Modifies parameter - keep last
}

void
MushMeshLibraryFGenExtrude::FaceExtrude(MushMesh4Mesh& ioMesh, MushMeshLibraryExtrusionContext& ioContext, Mushware::U32 inNum)
{
    for (U32 i=0; i<inNum; ++i)
    {
        bool toPoint;
        toPoint = (ioContext.RollingDisp().Scale() <= 0);

        FaceExtrudeOne(ioMesh, ioContext.RollingFaceNumWRef(), toPoint);
        
        if (ioContext.RollingDisp().Scale() <= 0)
        {
            break;
        }
        
        ioContext.VelocityAdd();
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
