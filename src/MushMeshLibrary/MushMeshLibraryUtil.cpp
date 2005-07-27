//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryUtil.cpp
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
//%Header } ic4notP94YKlJO17pfZjfA
/*
 * $Id: MushMeshLibraryUtil.cpp,v 1.1 2005/07/19 13:44:26 southa Exp $
 * $Log: MushMeshLibraryUtil.cpp,v $
 * Revision 1.1  2005/07/19 13:44:26  southa
 * MushMesh4Chunk work
 *
 */

#include "MushMeshLibraryUtil.h"

void
MushMeshLibraryUtil::NewFaceCreate(MushMesh4Mesh& ioMesh,
                                   MushMesh4Face *& outpFace,
                                   MushMesh4Face::tVertexList *& outpVertexList,
                                   MushMesh4Face::tVertexGroupSize *& outpVertexGroupSize)
{

    ioMesh.FacesWRef().push_back(MushMesh4Mesh::tFace());
    
    outpFace = &ioMesh.FacesWRef().back();
    outpVertexList = &outpFace->VertexListWRef();
    outpVertexGroupSize = &outpFace->VertexGroupSizeWRef();

    // Add this face to the current chunk
    if (ioMesh.Chunks().size() == 0)
    {
        throw MushcoreLogicFail("Attempt to add face without creating a chunk");
    }
    ioMesh.ChunksWRef().back().FaceListWRef().push_back(ioMesh.FaceCounter());

    ++ioMesh.FaceCounterWRef();
}

void
MushMeshLibraryUtil::NewChunkCreate(MushMesh4Mesh& ioMesh)
{
    ioMesh.ChunksWRef().push_back(MushMesh4Mesh::tChunk());
}
