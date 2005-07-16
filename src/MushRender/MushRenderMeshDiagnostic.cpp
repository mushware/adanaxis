//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMeshDiagnostic.cpp
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
//%Header } J0UI+16d74Ka/SXeExniNg
/*
 * $Id$
 * $Log$
 */

#include "MushRenderMeshDiagnostic.h"

#include "MushRenderUtil.h"

#include "API/mushMushMesh.h"
#include "API/mushMushGL.h"

using namespace Mushware;
using namespace std;

Mushware::U32 MushRenderMeshDiagnostic::m_highlightedFace = 0;
Mushware::U32 MushRenderMeshDiagnostic::m_highlightedFacet = 0;

MushRenderMeshDiagnostic::MushRenderMeshDiagnostic() :
    m_colourZMiddle(t4Val(1.0,1.0,1.0,0.5)),
    m_colourZLeft(t4Val(1.0,0.0,0.0,0.0)),
    m_colourZRight(t4Val(0.0,1.0,0.0,0.0))
{
}

void
MushRenderMeshDiagnostic::MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh)
{
    if (MushGLUtil::AppHandler().LatchedKeyStateTake(GLKeys::kKeyF1))
    {
        m_highlightedFace = 0;
    }
    if (MushGLUtil::AppHandler().LatchedKeyStateTake(GLKeys::kKeyF2))
    {
        --m_highlightedFace;
    }
    if (MushGLUtil::AppHandler().LatchedKeyStateTake(GLKeys::kKeyF3))
    {
        ++m_highlightedFace;
    }
    
    if (MushGLUtil::AppHandler().LatchedKeyStateTake(GLKeys::kKeyF5))
    {
        m_highlightedFacet = 0;
    }
    if (MushGLUtil::AppHandler().LatchedKeyStateTake(GLKeys::kKeyF6))
    {
        --m_highlightedFacet;
    }
    if (MushGLUtil::AppHandler().LatchedKeyStateTake(GLKeys::kKeyF7))
    {
        ++m_highlightedFacet;
    }
    
    
    
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
MushRenderMeshDiagnostic::DerivedColourSet(Mushware::t4Val& outColour, const Mushware::t4Val& inEyeVertex, const MushRenderSpec& inSpec)
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
MushRenderMeshDiagnostic::OutputBufferGenerate(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh)
{
    tMsec msecNow = MushGLUtil::AppHandler().MillisecondsGet();
    tVal scale = 0.99+0.01*sin(msecNow * M_PI/2000);
    
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
    
    MushGLWorkspace<MushGLBuffers::tVertex>& projectedWorkspace =
        glDestBuffersRef.ProjectedVerticesWRef(); // Projected vertex workspace
    MushMesh4Mesh::tVertices& projectedVertices = projectedWorkspace.DataWRef();
    // Create the projected vertices
    MushRenderUtil::Transform(projectedVertices, srcVertices, inSpec.ModelToClipMattress());

    MushGLWorkspace<MushGLBuffers::tVertex>& eyeWorkspace =
        glDestBuffersRef.EyeVerticesWRef(); // Projected vertex workspace
    MushMesh4Mesh::tVertices& eyeVertices = eyeWorkspace.DataWRef();
    // Create the projected vertices
    MushRenderUtil::Transform(eyeVertices, srcVertices, inSpec.ModelToEyeMattress());
    // U32 eyeVerticesSize = eyeVertices.size(); // Size of projected vertex vector array
    
    U32 numLines = 0;
    for (U32 faceNum=0; faceNum<p4Mesh->Faces().size(); ++faceNum)
    {
        const MushMesh4Face::tVertexGroupSize& srcGroupSizeRef = p4Mesh->Face(faceNum).VertexGroupSize();

        for (U32 facetNum=0; facetNum<srcGroupSizeRef.size(); ++facetNum)
        {
            numLines += srcGroupSizeRef[facetNum];
        }
    }
    
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
        
    for (U32 faceNum=0; faceNum<p4Mesh->Faces().size(); ++faceNum)
    {
        const MushMesh4Face::tVertexList& srcVertexListRef = p4Mesh->Face(faceNum).VertexList();
        const MushMesh4Face::tVertexGroupSize& srcGroupSizeRef = p4Mesh->Face(faceNum).VertexGroupSize();
        U32 srcFaceVertexIndex = 0;
        
        for (U32 facetNum=0; facetNum<srcGroupSizeRef.size(); ++facetNum)
        {
            m_colourZMiddle = t4Val(1.0,1.0,1.0,0.3);   

            if (faceNum != m_highlightedFace)
            {
                m_colourZMiddle = t4Val(1.0,1.0,1.0,0.05);   
            }
            if (msecNow % 500 < 250 && faceNum == m_highlightedFace && facetNum == m_highlightedFacet)
            
            {
                m_colourZMiddle = t4Val(1.0,1.0,1.0,1.0);   
            }
        
            
            t4Val faceCentroid;
            faceCentroid.ToAdditiveIdentitySet();
            for (U32 i=0; i<srcGroupSizeRef[facetNum]; ++i)
            {
                U32 vertexListNum1 = srcFaceVertexIndex + i;
                
                if (vertexListNum1 >= srcVertexListRef.size())
                {
                    throw MushcoreDataFail(std::string("Vertex list overrun in ")+AutoName());
                }
                U32 vertexNum1 = srcVertexListRef[vertexListNum1];
                if (vertexNum1 >= projectedVertices.size())
                {
                    throw MushcoreDataFail(std::string("Vertex overrun in ")+AutoName());
                }
                faceCentroid += projectedVertices[vertexNum1];
            }
            
            for (U32 i=0; i<srcGroupSizeRef[facetNum]; ++i)
            {
                U32 vertexListNum1 = srcFaceVertexIndex + i;
                U32 vertexListNum2 = srcFaceVertexIndex + ((i + 1) % srcGroupSizeRef[facetNum]);
                
                if (vertexListNum1 >= srcVertexListRef.size() || vertexListNum2 >= srcVertexListRef.size())
                {
                    throw MushcoreDataFail(std::string("Vertex list overrun in ")+AutoName());
                }
                U32 vertexNum1 = srcVertexListRef[vertexListNum1];
                U32 vertexNum2 = srcVertexListRef[vertexListNum2];
                if (vertexNum1 >= projectedVertices.size() || vertexNum2 >= projectedVertices.size())
                {
                    throw MushcoreDataFail(std::string("Vertex overrun in ")+AutoName());
                }
                
                destVertices.Set(projectedVertices[vertexNum1] * scale + faceCentroid * (1-scale), destVertexIndex);
                DerivedColourSet(destColours.Ref(destVertexIndex), eyeVertices[vertexNum1], inSpec);
                destVertexIndex++;
                destVertices.Set(projectedVertices[vertexNum2] * scale + faceCentroid * (1-scale), destVertexIndex);
                DerivedColourSet(destColours.Ref(destVertexIndex), eyeVertices[vertexNum2], inSpec);
                destVertexIndex++;
                if (destVertexIndex > destVerticesSize)
                {
                    throw MushcoreDataFail(std::string("Destination vertex overrun in ")+AutoName());
                } 
            }
            srcFaceVertexIndex += srcGroupSizeRef[facetNum];
        }
    }
    
    static U32 ctr=0;
    if (++ctr < 0)
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

const char *MushRenderMeshDiagnostic::AutoName(void) const
{
    return "MushRenderMeshDiagnostic";
}

MushcoreVirtualObject *MushRenderMeshDiagnostic::AutoClone(void) const
{
    return new MushRenderMeshDiagnostic(*this);
}

MushcoreVirtualObject *MushRenderMeshDiagnostic::AutoCreate(void) const
{
    return new MushRenderMeshDiagnostic;
}

MushcoreVirtualObject *MushRenderMeshDiagnostic::AutoVirtualFactory(void)
{
    return new MushRenderMeshDiagnostic;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushRenderMeshDiagnostic", MushRenderMeshDiagnostic::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushRenderMeshDiagnostic::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushRenderMesh::AutoPrint(ioOut);
    ioOut << "colourZMiddle=" << m_colourZMiddle << ", ";
    ioOut << "colourZLeft=" << m_colourZLeft << ", ";
    ioOut << "colourZRight=" << m_colourZRight;
    ioOut << "]";
}
bool
MushRenderMeshDiagnostic::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushRenderMeshDiagnostic::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushRenderMesh::AutoXMLPrint(ioOut);
    ioOut.TagSet("colourZMiddle");
    ioOut << m_colourZMiddle;
    ioOut.TagSet("colourZLeft");
    ioOut << m_colourZLeft;
    ioOut.TagSet("colourZRight");
    ioOut << m_colourZRight;
}
//%outOfLineFunctions } b9olmizukJHjsrL60ssL5Q
