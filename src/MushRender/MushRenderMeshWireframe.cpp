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
 * $Id: MushRenderMeshWireframe.cpp,v 1.2 2005/07/04 15:59:00 southa Exp $
 * $Log: MushRenderMeshWireframe.cpp,v $
 * Revision 1.2  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushRenderMeshWireframe.h"

#include "MushRenderUtil.h"

#include "API/mushMushMesh.h"
#include "API/mushMushGL.h"

using namespace Mushware;
using namespace std;

MushRenderMeshWireframe::MushRenderMeshWireframe() :
    m_colourZMiddle(t4Val(1.0,1.0,1.0,1.0)),
    m_colourZLeft(t4Val(1.0,0.0,0.0,0.0)),
    m_colourZRight(t4Val(0.0,1.0,0.0,0.0))
{
}

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

inline void
MushRenderMeshWireframe::DerivedColourSet(Mushware::t4Val& outColour, const Mushware::t4Val& inEyeVertex)
{
    if (inEyeVertex.W() >= 0)
    {
        // Behind viewer
        if (inEyeVertex.Z() < 0)
        {
            outColour = m_colourZLeft;
        }
        else
        {
            outColour = m_colourZRight;
        }
    }
    else
    {
        tVal discrim = inEyeVertex.Z() / inEyeVertex.W();
        if (discrim < -1.0)
        {
            outColour = m_colourZLeft;
        }
        else if (discrim < 0.0)
        {
            outColour = -discrim * m_colourZLeft + (1+discrim) * m_colourZMiddle;
        }
        else if (discrim < 1.0)
        {
            outColour = discrim * m_colourZRight + (1-discrim) * m_colourZMiddle;
        }
        else
        {
            outColour = m_colourZRight;
        }
    }
}

bool
MushRenderMeshWireframe::OutputBufferGenerate(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh)
{
    // Gather data
    MushGLBuffers& glDestBuffersRef = inSpec.BuffersRef().WRef(); // GL Buffer set for output
    MushGLClaimer<MushGLBuffers> claimer(glDestBuffersRef); // Claim the buffers
    MushGLBuffers::tVertexBuffer& destVertices = glDestBuffersRef.VertexBufferWRef(); // Vertex buffer for output
    MushGLBuffers::tColourBuffer& destColours = glDestBuffersRef.ColourBufferWRef(); // Colour buffer for output
    
    const MushMesh4Mesh *p4Mesh = dynamic_cast<const MushMesh4Mesh *>(&inMesh); // Pointer to the input mesh
    if (p4Mesh == NULL)
    {
        throw MushcoreRequestFail(std::string("Cannot render mesh type '")+inMesh.AutoName()+"'");
    }
    
    const MushMesh4Mesh::tVertices& srcVertices = p4Mesh->Vertices(); // Input vertices
    // U32 srcVerticesSize = srcVertices.size(); // Number of input vertices
    const MushMesh4Mesh::tConnectivity& srcConnect = p4Mesh->Connectivity(); // Input connectivity (vector of vectors)
    U32 srcConnectSize = srcConnect.size(); // Size of connectivity's outer vector
    
    MushGLWorkspace<MushGLBuffers::tVertex>& projectedWorkspace =
        glDestBuffersRef.ProjectedVerticesWRef(); // Projected vertex workspace
    MushMesh4Mesh::tVertices& projectedVertices = projectedWorkspace.DataWRef();
    // Create the projected vertices
    MushRenderUtil::Transform(projectedVertices, srcVertices, inSpec.ModelToClipMattress());
    U32 projectedVerticesSize = projectedVertices.size(); // Size of projected vertex vector array

    MushGLWorkspace<MushGLBuffers::tVertex>& eyeWorkspace =
        glDestBuffersRef.EyeVerticesWRef(); // Projected vertex workspace
    MushMesh4Mesh::tVertices& eyeVertices = eyeWorkspace.DataWRef();
    // Create the projected vertices
    MushRenderUtil::Transform(eyeVertices, srcVertices, inSpec.ModelToEyeMattress());
    // U32 eyeVerticesSize = eyeVertices.size(); // Size of projected vertex vector array
    
    U32 numLines = p4Mesh->NumConnections(); // Number of connections => number of lines
    U32 numVertices = numLines * 2; // Number of output vertices, i.e. space to reserve in the output buffer
    
    // Reserve output space
    if (destVertices.Size() < numVertices)
    {
        destVertices.ClearAndResize(numVertices);
    }
    
    if (destColours.Size() < numVertices)
    {
        destColours.ClearAndResize(numVertices);
    }
    
    // Make output area writable
    destVertices.MapReadWrite();
    destColours.MapReadWrite();
    
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
                if (i >= projectedVerticesSize || vertexNum > projectedVerticesSize)
                {
                    throw MushcoreDataFail("Out of range in connectivity data");
                }
                
                destVertices.Set(projectedVertices[i], destVertexIndex);
                DerivedColourSet(destColours.Ref(destVertexIndex), eyeVertices[i]);
                destVertexIndex++;
                destVertices.Set(projectedVertices[vertexNum], destVertexIndex);
                DerivedColourSet(destColours.Ref(destVertexIndex), eyeVertices[vertexNum]);
                destVertexIndex++;            
            }
            else if (vertexNum == i)
            {
                throw MushcoreDataFail("Self-connection fault in connectivity data");
            }
        }
    }
    
    static U32 ctr=0;
    if (++ctr < 3)
    {
        for (U32 i=0; i<destVertexIndex; ++i)
        {
            cout << destVertices.Ref(i) << endl;
        }
    }
    
    bool unmapSuccess = destVertices.AttemptUnmap() && destColours.AttemptUnmap();
    return unmapSuccess;
}
//%outOfLineFunctions {

const char *MushRenderMeshWireframe::AutoName(void) const
{
    return "MushRenderMeshWireframe";
}

MushcoreVirtualObject *MushRenderMeshWireframe::AutoClone(void) const
{
    return new MushRenderMeshWireframe(*this);
}

MushcoreVirtualObject *MushRenderMeshWireframe::AutoCreate(void) const
{
    return new MushRenderMeshWireframe;
}

MushcoreVirtualObject *MushRenderMeshWireframe::AutoVirtualFactory(void)
{
    return new MushRenderMeshWireframe;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushRenderMeshWireframe", MushRenderMeshWireframe::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushRenderMeshWireframe::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushRenderMesh::AutoPrint(ioOut);
    ioOut << "colourZMiddle=" << m_colourZMiddle << ", ";
    ioOut << "colourZLeft=" << m_colourZLeft << ", ";
    ioOut << "colourZRight=" << m_colourZRight;
    ioOut << "]";
}
bool
MushRenderMeshWireframe::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "colourZMiddle")
    {
        ioIn >> m_colourZMiddle;
    }
    else if (inTagStr == "colourZLeft")
    {
        ioIn >> m_colourZLeft;
    }
    else if (inTagStr == "colourZRight")
    {
        ioIn >> m_colourZRight;
    }
    else if (MushRenderMesh::AutoXMLDataProcess(ioIn, inTagStr))
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
MushRenderMeshWireframe::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushRenderMesh::AutoXMLPrint(ioOut);
    ioOut.TagSet("colourZMiddle");
    ioOut << m_colourZMiddle;
    ioOut.TagSet("colourZLeft");
    ioOut << m_colourZLeft;
    ioOut.TagSet("colourZRight");
    ioOut << m_colourZRight;
}
//%outOfLineFunctions } biU/zaYKrgb0yw0EoKWggg
