//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMeshShader.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } XKDM1ZJgQpb3nz4x0n57Og
/*
 * $Id: MushRenderMeshShader.cpp,v 1.6 2006/10/06 14:48:19 southa Exp $
 * $Log: MushRenderMeshShader.cpp,v $
 * Revision 1.6  2006/10/06 14:48:19  southa
 * Material animation
 *
 * Revision 1.5  2006/10/06 11:54:58  southa
 * Scaled rendering
 *
 * Revision 1.4  2006/09/10 10:30:53  southa
 * Shader billboarding
 *
 * Revision 1.3  2006/09/09 15:59:28  southa
 * Shader colour calculations
 *
 * Revision 1.2  2006/09/09 11:16:41  southa
 * One-time vertex buffer generation
 *
 * Revision 1.1  2006/09/07 16:38:52  southa
 * Vertex shader
 *
 */

#include "MushRenderMeshShader.h"

#include "MushRenderUtil.h"

#include "API/mushMushMesh.h"
#include "API/mushMushGL.h"

using namespace Mushware;
using namespace std;

MushRenderMeshShader::MushRenderMeshShader() :
    m_project4DRef("project4d")
{
}

void
MushRenderMeshShader::MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh)
{
    MushGLJobRender renderJob;
    
    try
    {
        if (RenderJobCreate(renderJob, inSpec, inMesh))
        {
            renderJob.Execute();
        }
    }
    catch (std::exception& e)
    {
        static U32 ctr = 0;
        if (++ctr < 100)
        {
            throw MushcoreDataFail(std::string("Cannot render mesh: ")+e.what());
        }
    }
}

bool
MushRenderMeshShader::RenderJobCreate(MushGLJobRender& outRender,
                                      const MushRenderSpec& inSpec,
                                      const MushMeshMesh& inMesh)
{
    bool jobCreated = false;
    
    const MushMesh4Mesh *p4Mesh = dynamic_cast<const MushMesh4Mesh *>(&inMesh); // Pointer to the input mesh
    if (p4Mesh == NULL)
    {
        throw MushcoreRequestFail(std::string("Cannot render mesh type '")+inMesh.AutoName()+"'");
    }
    
    if (inSpec.BuffersRef().Name() == 0)
    {
        throw MushcoreDataFail("MushRenderMeshShader::RenderJobCreate data name not set");
    }
    if (inSpec.SharedBuffersRef().Name() == "")
    {
        throw MushcoreDataFail("MushRenderMeshShader::RenderJobCreate shared data name not set");
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
        
        MushGLWorkSpec& workSpecRef = outRender.WorkSpecNew();
        
        outRender.BuffersRefSet(inSpec.BuffersRef());
        outRender.SharedBuffersRefSet(inSpec.SharedBuffersRef());
        workSpecRef.RenderTypeSet(MushGLWorkSpec::kRenderTypeTriangles);
        workSpecRef.UseSharedVerticesSet(true);

        for (U32 i=0; i < p4Mesh->NumMaterials(); ++i)
        {
            const MushGLMaterial& materialRef = dynamic_cast<const MushGLMaterial&>(p4Mesh->MaterialRef(i));
            MushGLTexture *pTexture = &materialRef.AnimatedTexRef(inSpec.MaterialAnimator());
            workSpecRef.TextureSet(pTexture, i);
        }
        
        outRender.SortValueSet(SortDepth(inSpec, *p4Mesh));
        outRender.ShaderRefSet(m_project4DRef);
        MushGLAttribs& attribsRef = outRender.AttribsWRef();
        attribsRef.ProjectionSet(inSpec.Projection());
        attribsRef.ViewSet(inSpec.View());
        if (p4Mesh->TransformType() == MushMesh4Mesh::kTransformTypeBillboard)
        {
            attribsRef.ModelSet(inSpec.ScaledModelBillboardMattress());
        }
        else if (p4Mesh->TransformType() == MushMesh4Mesh::kTransformTypeBillboardRandom)
        {
            attribsRef.ModelSet(inSpec.ScaledModelBillboardRandomMattress());
        }
        else
        {
            attribsRef.ModelSet(inSpec.ScaledModelMattress());
        }
        attribsRef.ColoursWRef().resize(0);
        attribsRef.ColoursWRef().push_back(t4GLVal(ColourZLeft()));
        attribsRef.ColoursWRef().push_back(t4GLVal(ColourZMiddle()));
        attribsRef.ColoursWRef().push_back(t4GLVal(ColourZRight()));
        attribsRef.TransformTypeSet(p4Mesh->TransformType());
        jobCreated = true;
    }
    return jobCreated;
}

bool
MushRenderMeshShader::OutputBufferGenerate(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh)
{
    // Gather data
    const MushMesh4Mesh *pVertexMesh = NULL;
    const MushMesh4Mesh *pColourMesh = NULL;
    const MushMesh4Mesh *pTexCoordMesh = NULL;
    
    MeshDelegatesGet(pVertexMesh, pColourMesh, pTexCoordMesh, inMesh);
    
    const MushMesh4Mesh::tVertices& srcVertices = pVertexMesh->Vertices(); // Source vertices
    const MushMesh4Mesh::tTexCoords& srcTexCoords = pTexCoordMesh->TexCoords(); // Source texture coordinates
    const U32 srcTexCoordsSize = srcTexCoords.size(); // Number of source texture coordinates
    
    U32 texCoordsPerVertex = 0;
    if (srcTexCoordsSize != 0)
    {
        texCoordsPerVertex = 1;
    }
    
    MushGLBuffers *pDestVertex = NULL;
    MushGLBuffers *pDestColour = NULL;
    MushGLBuffers *pDestTexCoord = NULL;
    
    DestDelegatesGet(pDestVertex, pDestColour, pDestTexCoord, inSpec);

    MushGLBuffers::tVertexBuffer& destVertices = pDestVertex->VertexBufferWRef(); // Vertex buffer for output
    MushGLBuffers::tColourBuffer& destColours = pDestColour->ColourBufferWRef(); // Colour buffer for output
    MushGLBuffers::tTexCoordBuffers& destTexCoords = pDestTexCoord->TexCoordBuffersWRef(); // Texture coordinate buffers for output
    
    if (texCoordsPerVertex > pDestTexCoord->NumTexCoordBuffers())
    {
        pDestTexCoord->NumTexCoordBuffersSet(texCoordsPerVertex);
    }

    // Build the triangle lists if necessary
    if (pDestVertex->TriangleListContextNum() == 0 || pDestVertex->VertexTriangleList().size() == 0)
    {
        TriangleListBuild(pDestVertex->VertexTriangleListWRef(), inMesh, kSourceTypeVertex);
        pDestVertex->TriangleListContextNumSet(1);
    }

    if (pDestTexCoord->TriangleListContextNum() < 2 || pDestTexCoord->TexCoordTriangleList().size() == 0)
    {
        for (U32 i=0; i<texCoordsPerVertex; ++i)
        {
            TriangleListBuild(pDestTexCoord->TexCoordTriangleListWRef(), *pTexCoordMesh, kSourceTypeTexCoord);
            pDestTexCoord->TriangleListContextNumSet(2);
        }
    }

    const MushGLBuffers::tTriangleList& vertexTriangleList = pDestVertex->VertexTriangleList();
    Mushware::U32 vertexTriangleListSize = vertexTriangleList.size();
    const MushGLBuffers::tTriangleList& texCoordTriangleList = pDestTexCoord->TexCoordTriangleList();
    Mushware::U32 texCoordTriangleListSize = texCoordTriangleList.size();
    
    if (vertexTriangleListSize == 0)
    {
        MushcoreLog::Sgl().XMLInfoLog() << inMesh;
        abort();   
    }
    
    // Build the output buffers
    bool unmapSuccess = true;
    
    if (pDestVertex->VertexContextNum() == 0 || destVertices.Size() == 0)
    {
        // Build the vertex buffer
        // Reserve output space
        if (destVertices.Size() < vertexTriangleListSize)
        {
            destVertices.ClearAndResize(vertexTriangleListSize);
        }
        
        // Make output area writable
        destVertices.MapReadWrite();

        for (U32 i=0; i<vertexTriangleListSize; ++i)
        {
            destVertices.Set(srcVertices[vertexTriangleList[i]], i);
        }
        
        unmapSuccess = destVertices.AttemptUnmap();
        
        pDestVertex->VertexContextNumSet(1);
    }
    
    // Clear the colour buffer if another renderer has filled it
    if (destColours.Size() > 0)
    {
        destColours.ClearAndResize(0);
    }

    if (pDestTexCoord->TexCoordContextNum() < 2)
    {
        for (U32 texCoordNum=0; texCoordNum<texCoordsPerVertex; ++texCoordNum)
        {
            MushGLBuffers::tTexCoordBuffer& destTexCoord = destTexCoords[texCoordNum];
            if (destTexCoord.Size() != texCoordTriangleListSize)
            {
                destTexCoord.ClearAndResize(texCoordTriangleListSize);
            }
            
            destTexCoord.MapReadWrite();
            for (U32 i=0; i<texCoordTriangleListSize; ++i)
            {
                const MushMesh4Mesh::tTexCoord& srcCoord = srcTexCoords[texCoordTriangleList[i]];
                destTexCoord.Set(tGLTexCoord(srcCoord.X(), srcCoord.Y()), i);
            }
            unmapSuccess = destTexCoord.AttemptUnmap() && unmapSuccess;
        }
        pDestTexCoord->TexCoordContextNumSet(2);
    }

    return unmapSuccess;
}
//%outOfLineFunctions {

const char *MushRenderMeshShader::AutoName(void) const
{
    return "MushRenderMeshShader";
}

MushcoreVirtualObject *MushRenderMeshShader::AutoClone(void) const
{
    return new MushRenderMeshShader(*this);
}

MushcoreVirtualObject *MushRenderMeshShader::AutoCreate(void) const
{
    return new MushRenderMeshShader;
}

MushcoreVirtualObject *MushRenderMeshShader::AutoVirtualFactory(void)
{
    return new MushRenderMeshShader;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushRenderMeshShader", MushRenderMeshShader::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushRenderMeshShader::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushRenderMesh::AutoPrint(ioOut);
    ioOut << "project4DRef=" << m_project4DRef;
    ioOut << "]";
}
bool
MushRenderMeshShader::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "project4DRef")
    {
        ioIn >> m_project4DRef;
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
MushRenderMeshShader::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushRenderMesh::AutoXMLPrint(ioOut);
    ioOut.TagSet("project4DRef");
    ioOut << m_project4DRef;
}
//%outOfLineFunctions } rW4uh5jn9PHHeH/+lHDYlg
