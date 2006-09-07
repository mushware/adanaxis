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
 * $Id$
 * $Log$
 */

#include "MushRenderMeshShader.h"

#include "MushRenderUtil.h"

#include "API/mushMushMesh.h"
#include "API/mushMushGL.h"

using namespace Mushware;
using namespace std;

MushRenderMeshShader::MushRenderMeshShader() :
    m_colourZMiddle(t4Val(1.0,1.0,1.0,0.1)),
    m_colourZLeft(t4Val(1.0,0.8,0.8,0.0)),
    m_colourZRight(t4Val(0.8,1.0,0.8,0.0)),
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
        outRender.TexCoordBuffersRefSet(inSpec.TexCoordBuffersRef());
        workSpecRef.RenderTypeSet(MushGLWorkSpec::kRenderTypeTriangles);
        
        for (U32 i=0; i < p4Mesh->NumMaterials(); ++i)
        {
            const MushGLMaterial& materialRef = dynamic_cast<const MushGLMaterial&>(p4Mesh->MaterialRef(i));
            MushGLTexture *pTexture = &materialRef.TexRef(i);
            workSpecRef.TextureSet(pTexture, i);
        }
        outRender.SortValueSet(SortDepth(inSpec, *p4Mesh));
        outRender.ShaderRefSet(m_project4DRef);
        MushGLAttribs& attribsRef = outRender.AttribsWRef();
        attribsRef.ProjectionSet(inSpec.Projection());
        attribsRef.ViewSet(inSpec.View());
        attribsRef.ModelSet(inSpec.Model());
        jobCreated = true;
    }
    return jobCreated;
}

inline void
MushRenderMeshShader::DerivedColourSet(Mushware::t4Val& outColour, const Mushware::t4Val& inEyeVertex, const MushRenderSpec& inSpec)
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

void
MushRenderMeshShader::TriangleListBuild(MushGLBuffers::tTriangleList& ioList, const MushMesh4Mesh& inMesh,
                                       tSourceType inSourceType)
{
    ioList.resize(0);
    U32 numFaces = inMesh.Faces().size();
    U32 entryLimit = 0;
    for (U32 faceNum=0; faceNum<numFaces; ++faceNum)
    {
        if (!inMesh.Face(faceNum).Internal())
        { 
            const MushMesh4Face::tVertexList *pSrcList = NULL;
            switch (inSourceType)
            {
                case kSourceTypeVertex:
                    pSrcList = &inMesh.Face(faceNum).VertexList();
                    entryLimit = inMesh.Vertices().size();
                    break;
                    
                case kSourceTypeTexCoord:
                    pSrcList = &inMesh.Face(faceNum).TexCoordList();
                    entryLimit = inMesh.TexCoords().size();
                    break;
                    
                default:
                    throw MushcoreLogicFail("Bad source type selector");
            }
            
            const MushMesh4Face::tVertexList& srcListRef = *pSrcList;
            
            U32 srcListSize = srcListRef.size();
            
            const MushMesh4Face::tVertexGroupSize& srcGroupSizeRef = inMesh.Face(faceNum).VertexGroupSize();
            U32 numFacets = srcGroupSizeRef.size();
            
            U32 srcFaceIndex = 0;
            for (U32 facetNum=0; facetNum<numFacets; ++facetNum)
            {
                // listNum0 is srcFaceIndex
                if (srcFaceIndex >= srcListSize)
                {
                    throw MushcoreDataFail(std::string("Vertex list overrun in ")+AutoName());
                }            
                U32 entryValue0 = srcListRef[srcFaceIndex]; 
                if (entryValue0 >= entryLimit)
                {
                    throw MushcoreDataFail(std::string("Entry index list overrun in ")+AutoName());
                }
                // Add triangles for this facet
                U32 groupSize = srcGroupSizeRef[facetNum];
                
                for (U32 i=1; i+1 < groupSize; ++i)
                {
                    U32 listNum1 = srcFaceIndex + i;
                    U32 listNum2 = srcFaceIndex + i + 1;
                    
                    if (listNum1 >= srcListSize || listNum2 >= srcListSize)
                    {
                        throw MushcoreDataFail(std::string("Vertex list overrun in ")+AutoName());
                    }
                    U32 entryValue1 = srcListRef[listNum1];
                    U32 entryValue2 = srcListRef[listNum2];
                    if (entryValue1 >= entryLimit || entryValue2 >= entryLimit)
                    {
                        throw MushcoreDataFail(std::string("Entry index list overrun in ")+AutoName());
                    }
                    ioList.push_back(entryValue0);
                    ioList.push_back(entryValue1);
                    ioList.push_back(entryValue2);
                }
                srcFaceIndex += groupSize;
            }
        }
    }
}

bool
MushRenderMeshShader::OutputBufferGenerate(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh)
{
    // Gather data
    const MushMesh4Mesh *pTexCoordMesh = NULL;
    
    if (inMesh.TexCoordDelegate().Name().size() == 0)
    {
        // Name not set, use same mesh
        pTexCoordMesh = &inMesh;
    }
    else
    {
        pTexCoordMesh = &inMesh.TexCoordDelegate().Ref();
    }
    
    const MushMesh4Mesh::tVertices& srcVertices = inMesh.Vertices(); // Source vertices
    // const U32 srcVerticesSize = srcVertices.size(); // Number of source vertices
    const MushMesh4Mesh::tTexCoords& srcTexCoords = pTexCoordMesh->TexCoords(); // Source texture coordinates
    const U32 srcTexCoordsSize = srcTexCoords.size(); // Number of source texture coordinates
    
    U32 texCoordsPerVertex = 0;
    if (srcTexCoordsSize != 0)
    {
        texCoordsPerVertex = 1;
    }
    
    MushGLBuffers& glDestBuffersRef = inSpec.BuffersRef().WRef(); // GL Buffer set for output
    
    // Get the delegated buffer if there is one, otherwise use the main buffer
    MushGLBuffers *pglDestTexCoordBuffers;
    if (inSpec.TexCoordBuffersRef().Name().size() != 0)
    {
        pglDestTexCoordBuffers = &inSpec.TexCoordBuffersRef().WRef();
    }
    else
    {
        pglDestTexCoordBuffers = &glDestBuffersRef;
    }
    
    MushGLBuffers& glDestTexCoordBuffersRef = *pglDestTexCoordBuffers; // GL Buffer set for output

    MushGLClaimer<MushGLBuffers> claimer(glDestBuffersRef); // Claim the buffers
    MushGLBuffers::tVertexBuffer& destVertices = glDestBuffersRef.VertexBufferWRef(); // Vertex buffer for output
    MushGLBuffers::tColourBuffer& destColours = glDestBuffersRef.ColourBufferWRef(); // Colour buffer for output
    MushGLBuffers::tTexCoordBuffers& destTexCoords =
        glDestTexCoordBuffersRef.TexCoordBuffersWRef(); // Texture coordinate buffers for output
    
    if (texCoordsPerVertex > glDestTexCoordBuffersRef.NumTexCoordBuffers())
    {
        glDestTexCoordBuffersRef.NumTexCoordBuffersSet(texCoordsPerVertex);
    }

    // Build the triangle lists if necessary
    if (glDestBuffersRef.TriangleListContextNum() == 0)
    {
        TriangleListBuild(glDestBuffersRef.VertexTriangleListWRef(), inMesh, kSourceTypeVertex);
        glDestBuffersRef.TriangleListContextNumSet(1);
    }
    
    if (glDestTexCoordBuffersRef.TriangleListContextNum() < 2)
    {
        for (U32 i=0; i<texCoordsPerVertex; ++i)
        {
            TriangleListBuild(glDestTexCoordBuffersRef.TexCoordTriangleListWRef(), *pTexCoordMesh, kSourceTypeTexCoord);
            glDestTexCoordBuffersRef.TriangleListContextNumSet(2);
        }
    }
    
    MushGLWorkspace<MushGLBuffers::tVertex>& projectedWorkspace =
        glDestBuffersRef.ProjectedVerticesWRef(); // Projected vertex workspace
    MushMesh4Mesh::tVertices& projectedVertices = projectedWorkspace.DataWRef();
    // Create the projected vertices
    switch (inMesh.TransformType())
    {
        case MushMesh4Mesh::kTransformTypeBillboard:
            MushRenderUtil::Transform(projectedVertices, srcVertices, t4x4o4Val::Identity());
            break;
            
        default:
            MushRenderUtil::Transform(projectedVertices, srcVertices, t4x4o4Val::Identity());
            break;
    }
    
    MushGLWorkspace<MushGLBuffers::tVertex>& eyeWorkspace =
        glDestBuffersRef.EyeVerticesWRef(); // Projected vertex workspace
    MushMesh4Mesh::tVertices& eyeVertices = eyeWorkspace.DataWRef();
    // Create the projected vertices
    MushRenderUtil::Transform(eyeVertices, srcVertices, inSpec.ModelToEyeMattress());
    // U32 eyeVerticesSize = eyeVertices.size(); // Size of projected vertex vector array
    
    
    
    const MushGLBuffers::tTriangleList& vertexTriangleList = glDestBuffersRef.VertexTriangleList();
    Mushware::U32 vertexTriangleListSize = vertexTriangleList.size();
    const MushGLBuffers::tTriangleList& texCoordTriangleList = glDestTexCoordBuffersRef.TexCoordTriangleList();
    Mushware::U32 texCoordTriangleListSize = texCoordTriangleList.size();
    
    // Build the output buffers
    bool unmapSuccess = true;
    
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
        destVertices.Set(projectedVertices[vertexTriangleList[i]], i);
    }
    
    unmapSuccess = destVertices.AttemptUnmap();
    
    // Build the colour buffer
    if (destColours.Size() < vertexTriangleListSize)
    {
        destColours.ClearAndResize(vertexTriangleListSize);
    }
    destColours.MapReadWrite();
    for (U32 i=0; i<vertexTriangleListSize; ++i)
    {
        DerivedColourSet(destColours.Ref(i), eyeVertices[vertexTriangleList[i]], inSpec);
    }

    unmapSuccess = destColours.AttemptUnmap() && unmapSuccess;
    
    if (glDestTexCoordBuffersRef.TexCoordContextNum() < 2)
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
        glDestTexCoordBuffersRef.TexCoordContextNumSet(2);
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
    ioOut << "colourZMiddle=" << m_colourZMiddle << ", ";
    ioOut << "colourZLeft=" << m_colourZLeft << ", ";
    ioOut << "colourZRight=" << m_colourZRight << ", ";
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
    ioOut.TagSet("colourZMiddle");
    ioOut << m_colourZMiddle;
    ioOut.TagSet("colourZLeft");
    ioOut << m_colourZLeft;
    ioOut.TagSet("colourZRight");
    ioOut << m_colourZRight;
    ioOut.TagSet("project4DRef");
    ioOut << m_project4DRef;
}
//%outOfLineFunctions } gieUr5KYo9Oil9pU4giYew
