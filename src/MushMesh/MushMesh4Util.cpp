//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Util.cpp
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
//%Header } JaX7H34UxSrez6vzfkn8eA
/*
 * $Id: MushMesh4Util.cpp,v 1.4 2006/12/14 00:33:50 southa Exp $
 * $Log: MushMesh4Util.cpp,v $
 * Revision 1.4  2006/12/14 00:33:50  southa
 * Control fix and audio pacing
 *
 * Revision 1.3  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/08/01 17:58:25  southa
 * Object explosion
 *
 * Revision 1.1  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 */

#include "MushMesh4Util.h"

#include "MushMeshMushcoreIO.h"
#include "MushMeshSTL.h"

using namespace Mushware;
using namespace std;

void
MushMesh4Util::NewFaceCreate(MushMesh4Mesh& ioMesh,
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
MushMesh4Util::NewFaceClone(MushMesh4Mesh& ioMesh,
                            MushMesh4Face *& outpFace,
                            MushMesh4Face::tVertexList *& outpVertexList,
                            MushMesh4Face::tVertexGroupSize *& outpVertexGroupSize,
                            const MushMesh4Face& inFace)
{
    
    ioMesh.FacesWRef().push_back(inFace);
    
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
MushMesh4Util::NewChunkCreate(MushMesh4Mesh& ioMesh)
{
    ioMesh.ChunksWRef().push_back(MushMesh4Mesh::tChunk());
}


void 
MushMesh4Util::NullFacetsRemove(MushMesh4Mesh& ioMesh, Mushware::U32 inFaceNum)
{
    bool modified = false;
    MushMesh4Face& faceRef = ioMesh.FaceWRef(inFaceNum);
    
    MushMesh4Face::tVertexList& srcVertexListRef = faceRef.VertexListWRef();
    U32 srcVertexListSize = srcVertexListRef.size();
    MushMesh4Face::tVertexGroupSize& srcGroupSizeRef = faceRef.VertexGroupSizeWRef();
    MushMesh4Face::tVertexList newVertexList;
    MushMesh4Face::tVertexGroupSize newGroupSizeList;
    
    U32 srcVertexNum = 0;
    for (U32 i=0; i<srcGroupSizeRef.size(); ++i)
    {
        U32 srcGroupSize = srcGroupSizeRef[i];
        U32 newGroupSize = 0;
        for (U32 j=0; j < srcGroupSize; ++j)
        {
            U32 vertNum = srcVertexNum + j;
            U32 otherVertNum = srcVertexNum + ((j + 1) % srcGroupSize);
            
            if (vertNum >= srcVertexListSize || otherVertNum >= srcVertexListSize)
            {
                throw MushcoreDataFail("Vertex overrun in NullFacetsRemove");
            }
            
            if (srcVertexListRef[vertNum] == srcVertexListRef[otherVertNum])
            {
                modified = true;
            }
            else
            {
                newVertexList.push_back(srcVertexListRef[vertNum]);
                ++newGroupSize;
            }
        }
        if (newGroupSize > 2)
        {
#if 0
            if (newGroupSize == srcGroupSize)
            {
                MushcoreLog::Sgl().InfoLog() << "Keeping facet size " << srcGroupSize << endl;
            }
            else
            {
                MushcoreLog::Sgl().InfoLog() << "Reducing facet size " << srcGroupSize << " to " << newGroupSize << endl;
            }
#endif       
            newGroupSizeList.push_back(newGroupSize);
        }
        else if (newGroupSize == 2)
        {
            MushcoreLog::Sgl().WarningLog() << "Discarding two point facet" << endl;
            newVertexList.resize(newVertexList.size() - 2);
        }
        else if (newGroupSize == 1)
        {
            MushcoreLog::Sgl().ErrorLog() << "Discarding rogue single point facet" << endl;
            newVertexList.resize(newVertexList.size() - 1);
        }
        else
        {
            // Discard entire facet
            // MushcoreLog::Sgl().InfoLog() << "Discarding facet of size " << srcGroupSize << endl;
        }
        srcVertexNum += srcGroupSize;
    }
    
    if (modified)
    {
        
        srcVertexListRef = newVertexList;
        srcGroupSizeRef = newGroupSizeList;
        
        faceRef.AllTouch();
        // MushcoreLog::Sgl().InfoLog() << "Wrote modified face" << endl;

    }
}

void 
MushMesh4Util::ChunkCopy(MushMesh4Mesh& ioMesh, const MushMesh4Mesh& inMesh, Mushware::U32 inChunkNum)
{
    typedef MushMesh4Mesh::tChunk tChunk;
    const tChunk& chunkRef = inMesh.Chunk(inChunkNum);
    const tChunk::tVertexList& uniqueVertexListRef = chunkRef.UniqueVertexList();
    
    
    // Map lookup for old vertex numbers to new
    std::map<U32, U32> vertexOldToNew;
    
    // Create the set of vertices
    MushMesh4Mesh::tVertices& outVerticesRef = ioMesh.VerticesWRef();
    U32 numVertices = uniqueVertexListRef.size();
    U32 vertexBase = ioMesh.VertexCounter();
    U32 newNumVertices = vertexBase + numVertices;
    
    if (outVerticesRef.size() < newNumVertices)
    {
        outVerticesRef.resize(newNumVertices);
        ioMesh.VertexCounterSet(newNumVertices);
    }
    t4Val vertexOffset = -inMesh.ChunkCentroid(inChunkNum);
    
    for (U32 i=0; i<numVertices; ++i)
    {
        MUSHCOREASSERT(vertexBase + i < outVerticesRef.size());
        
        outVerticesRef[vertexBase + i] = inMesh.Vertex(uniqueVertexListRef[i]) + vertexOffset;
        vertexOldToNew[uniqueVertexListRef[i]] = vertexBase + i;
    }
    
    MushMesh4Face *pFace = NULL;
    MushMesh4Face::tVertexList *pVertexList = NULL;
    MushMesh4Face::tVertexGroupSize *pVertexGroupSize = NULL;
    MushMesh4Util::NewChunkCreate(ioMesh);
    
    const tChunk::tFaceList& faceListRef = chunkRef.FaceList();

    for (U32 i=0; i<faceListRef.size(); ++i)
    {
        U32 faceNum = faceListRef[i];
        
        MushMesh4Util::NewFaceClone(ioMesh, pFace, pVertexList, pVertexGroupSize, inMesh.Face(faceNum));
        
        U32 vertexListSize = pVertexList->size();
        for (U32 j=0; j<vertexListSize; ++j)
        {
            std::map<U32, U32>::const_iterator p = vertexOldToNew.find((*pVertexList)[j]);
            
            if (p == vertexOldToNew.end())
            {
                throw MushcoreDataFail("ChunkCopy vertex map failure");
            }
            
            (*pVertexList)[j] = p->second;
        }
        pFace->InternalSet(false);
    }
    ioMesh.AllTouch();
}
