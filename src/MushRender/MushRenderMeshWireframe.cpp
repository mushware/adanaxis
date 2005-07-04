//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMeshWireframe.cpp
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
//%Header } nnreRrgtAG1/ZKElYmX31w
/*
 * $Id$
 * $Log$
 */

#include "MushRenderMeshWireframe.h"

#include "API/mushMushMesh.h"
#include "API/mushMushGL.h"

using namespace Mushware;
using namespace std;

void
MushRenderMeshWireframe::MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh)
{
    if (!OutputBufferGenerate(inSpec, inMesh))
    {
        if (!OutputBufferGenerate(inSpec, inMesh))
        {
            throw MushcoreDeviceFail("Double fault when unmapping vertex buffer");
        }
    }
    
    MushGLJobRender jobRender;
    MushGLWorkSpec& workSpecRef = jobRender.WorkSpecNew();
    
    jobRender.BuffersRefSet(inSpec.BuffersRef());
    workSpecRef.RenderTypeSet(MushGLWorkSpec::kRenderTypeLines);
    
    jobRender.Execute();
}

bool
MushRenderMeshWireframe::OutputBufferGenerate(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh)
{
    // Gather data
    MushGLBuffers& glDestBuffersRef = inSpec.BuffersRef().WRef(); // GL Buffer set for output
    MushGLClaimer<MushGLBuffers> claimer(glDestBuffersRef); // Claim the buffers
    MushGLBuffers::tVertexBuffer& destVertices = glDestBuffersRef.VertexBufferWRef(); // Vertex buffer for output
    
    const MushMesh4Mesh *p4Mesh = dynamic_cast<const MushMesh4Mesh *>(&inMesh); // Pointer to the input mesh
    if (p4Mesh == NULL)
    {
        throw MushcoreRequestFail(std::string("Cannot render mesh type '")+inMesh.AutoName()+"'");
    }
    
    const MushMesh4Mesh::tVertices& srcVertices = p4Mesh->Vertices(); // Input vertices
    U32 srcVerticesSize = srcVertices.size(); // Number of input vertices
    const MushMesh4Mesh::tConnectivity& srcConnect = p4Mesh->Connectivity(); // Input connectivity (vector of vectors)
    U32 srcConnectSize = srcConnect.size(); // Size of connectivity's outer vector

    U32 numLines = p4Mesh->NumConnections(); // Number of connections => number of lines
    U32 numVertices = numLines * 2; // Number of output vertices, i.e. space to reserve in the output buffer
    
    // Reserve output space
    if (destVertices.Size() < numVertices)
    {
        destVertices.ClearAndResize(numVertices);
    }
    
    // Make output area writable
    destVertices.MapReadWrite();
    
    U32 destVertexIndex = 0; // Index into output buffer for next output vertex
    U32 destVerticesSize = destVertices.Size(); // Size (in elements) of the destVertices buffer
    
    // Loop through the connectivity array
    for (U32 i=0; i < srcConnectSize; ++i)
    {
        /* Get data for this vertex.  The entry is a vector of vertex numbers
         * that this vertex is connected to
         */
        const MushMesh4Mesh::tConnection& connectEntryRef = srcConnect[i];
        U32 connectEntryRefSize = connectEntryRef.size();
        
        for (U32 j=0; j < connectEntryRefSize; ++j)
        {
            U32 vertexNum = connectEntryRef[j];
            
            // Only draw those where vertexNum > i, so we don't draw every line twice
            
            if (vertexNum > i)
            {
                if (destVertexIndex + 1 >= destVerticesSize)
                {
                    throw MushcoreDataFail("Overflow in connectivity data");
                }
                if (i >= srcVerticesSize || vertexNum > srcVerticesSize)
                {
                    throw MushcoreDataFail("Out of range in connectivity data");
                }
                
                destVertices.Set(srcVertices[i], destVertexIndex);
                destVertexIndex++;
                destVertices.Set(srcVertices[vertexNum], destVertexIndex);
                destVertexIndex++;            
            }
            else if (vertexNum == i)
            {
                throw MushcoreDataFail("Self-connection fault in connectivity data");
            }
        }
    }
    
    bool unmapSuccess = destVertices.AttemptUnmap();
    return unmapSuccess;
}
