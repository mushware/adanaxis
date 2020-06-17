//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMeshWireframe.cpp
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
//%Header } fvAIlDbRcdSITFlC+axAzw
/*
 * $Id: MushRenderMeshWireframe.cpp,v 1.9 2006/11/14 14:02:17 southa Exp $
 * $Log: MushRenderMeshWireframe.cpp,v $
 * Revision 1.9  2006/11/14 14:02:17  southa
 * Ball projectiles
 *
 * Revision 1.8  2006/07/24 18:46:51  southa
 * Depth sorting
 *
 * Revision 1.7  2006/06/27 11:58:10  southa
 * Warning fixes
 *
 * Revision 1.6  2006/06/01 15:39:38  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.4  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
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
    const MushMesh4Mesh *p4Mesh = dynamic_cast<const MushMesh4Mesh *>(&inMesh); // Pointer to the input mesh
    if (p4Mesh == NULL)
    {
        throw MushcoreRequestFail(std::string("Cannot render mesh type '")+inMesh.AutoName()+"'");
    }
    
    if (!ShouldMeshCull(inSpec, *p4Mesh))
    {    
    
        if (!OutputBufferGenerate(inSpec, *p4Mesh))
        {
            if (!OutputBufferGenerate(inSpec, *p4Mesh))
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
}

inline void
MushRenderMeshWireframe::DerivedColourSet(Mushware::t4Val& outColour, const Mushware::t4Val& inEyeVertex, const MushRenderSpec& inSpec)
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
        tVal discrim = (inEyeVertex.Z() * inSpec.Projection().FValue()) / inEyeVertex.W();
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
MushRenderMeshWireframe::OutputBufferGenerate(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh)
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
    switch (inMesh.TransformType())
    {
        case MushMesh4Mesh::kTransformTypeBillboard:
            MushRenderUtil::Transform(projectedVertices, srcVertices, inSpec.ModelToClipBillboardMattress());
            break;
            
        case MushMesh4Mesh::kTransformTypeBillboardRandom:
            MushRenderUtil::Transform(projectedVertices, srcVertices, inSpec.ModelToClipBillboardRandomMattress());
        break;
        
        default:
            MushRenderUtil::Transform(projectedVertices, srcVertices, inSpec.ModelToClipMattress());
            break;
    }
    
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
                DerivedColourSet(destColours.Ref(destVertexIndex), eyeVertices[i], inSpec);
                destVertexIndex++;
                destVertices.Set(projectedVertices[vertexNum], destVertexIndex);
                DerivedColourSet(destColours.Ref(destVertexIndex), eyeVertices[vertexNum], inSpec);
                destVertexIndex++;            
            }
            else if (vertexNum == i)
            {
                throw MushcoreDataFail("Self-connection fault in connectivity data");
            }
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
