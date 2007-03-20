//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMeshSolid.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } gfNsThCmT0hAhMS/2HkW2w
/*
 * $Id: MushRenderMeshSolid.cpp,v 1.14 2006/11/14 14:02:17 southa Exp $
 * $Log: MushRenderMeshSolid.cpp,v $
 * Revision 1.14  2006/11/14 14:02:17  southa
 * Ball projectiles
 *
 * Revision 1.13  2006/09/09 11:16:42  southa
 * One-time vertex buffer generation
 *
 * Revision 1.12  2006/07/28 19:24:34  southa
 * Pre-release work
 *
 * Revision 1.11  2006/07/24 18:46:50  southa
 * Depth sorting
 *
 * Revision 1.10  2006/07/17 14:43:42  southa
 * Billboarded deco objects
 *
 * Revision 1.9  2006/06/20 19:06:54  southa
 * Object creation
 *
 * Revision 1.8  2006/06/19 15:57:19  southa
 * Materials
 *
 * Revision 1.7  2006/06/01 15:39:38  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 * Revision 1.5  2005/09/05 17:14:23  southa
 * Solid rendering
 *
 * Revision 1.4  2005/09/05 12:54:30  southa
 * Solid rendering work
 *
 * Revision 1.3  2005/09/03 17:05:36  southa
 * Material work
 *
 * Revision 1.2  2005/08/31 23:57:27  southa
 * Texture coordinate work
 *
 * Revision 1.1  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 */

#include "MushRenderMeshSolid.h"

#include "MushRenderUtil.h"

#include "API/mushMushMesh.h"
#include "API/mushMushGL.h"

using namespace Mushware;
using namespace std;

MushRenderMeshSolid::MushRenderMeshSolid()
{
}

void
MushRenderMeshSolid::MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh)
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
MushRenderMeshSolid::RenderJobCreate(MushGLJobRender& outRender,
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
        throw MushcoreDataFail("MushRenderMeshSolid::RenderJobCreate data name not set");
    }
    if (inSpec.SharedBuffersRef().Name() == "")
    {
        throw MushcoreDataFail("MushRenderMeshSolid::RenderJobCreate shared data name not set");
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
        workSpecRef.UseSharedVerticesSet(false);
        
        for (U32 i=0; i < p4Mesh->NumMaterials(); ++i)
        {
            const MushGLMaterial& materialRef = dynamic_cast<const MushGLMaterial&>(p4Mesh->MaterialRef(i));
            MushGLTexture *pTexture = &materialRef.AnimatedTexRef(inSpec.MaterialAnimator());
            workSpecRef.TextureSet(pTexture, i);
        }

        outRender.SortValueSet(SortDepth(inSpec, *p4Mesh));
        jobCreated = true;
    }
    return jobCreated;
}

inline void
MushRenderMeshSolid::DerivedColourSet(Mushware::t4Val& outColour, const Mushware::t4Val& inEyeVertex, const MushRenderSpec& inSpec)
{
    if (inEyeVertex.W() >= 0)
    {
        // Behind viewer
        if (inEyeVertex.Z() < 0)
        {
            outColour = ColourZLeft();
        }
        else
        {
            outColour = ColourZRight();
        }
    }
    else
    {
        tVal discrim = (inEyeVertex.Z() * inSpec.Projection().FValue()) / inEyeVertex.W();
        if (discrim < -1.0)
        {
            outColour = ColourZLeft();
        }
        else if (discrim < 0.0)
        {
            outColour = -discrim * ColourZLeft() + (1+discrim) * ColourZMiddle();
        }
        else if (discrim < 1.0)
        {
            outColour = discrim * ColourZRight() + (1-discrim) * ColourZMiddle();
        }
        else
        {
            outColour = ColourZRight();
        }
    }
}

bool
MushRenderMeshSolid::OutputBufferGenerate(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh)
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
    if (inSpec.SharedBuffersRef().Name().size() != 0)
    {
        pglDestTexCoordBuffers = &inSpec.SharedBuffersRef().WRef();
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
            MushRenderUtil::Transform(projectedVertices, srcVertices, inSpec.ModelToClipBillboardMattress());
            break;
            
        case MushMesh4Mesh::kTransformTypeBillboardRandom:
            MushRenderUtil::Transform(projectedVertices, srcVertices, inSpec.ModelToClipBillboardRandomMattress());
            break;
            
        default:
            MushRenderUtil::Transform(projectedVertices, srcVertices, inSpec.ModelToClipMattress());
            break;
    }
    
    MushGLWorkspace<MushGLBuffers::tVertex>& eyeWorkspace =
        glDestBuffersRef.EyeVerticesWRef(); // Projected vertex workspace
    MushMesh4Mesh::tVertices& eyeVertices = eyeWorkspace.DataWRef();
    // Create the projected vertices
    switch (inMesh.TransformType())
    {
        case MushMesh4Mesh::kTransformTypeBillboard:
            MushRenderUtil::Transform(eyeVertices, srcVertices, inSpec.ModelToEyeBillboardMattress());
            break;
            
        case MushMesh4Mesh::kTransformTypeBillboardRandom:
            // This gives a different random orientation, so a bit wrong
            MushRenderUtil::Transform(eyeVertices, srcVertices, inSpec.ModelToEyeBillboardRandomMattress());
            break;
       
        default:
            MushRenderUtil::Transform(eyeVertices, srcVertices, inSpec.ModelToEyeMattress());
            break;
    }
    
            
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

const char *MushRenderMeshSolid::AutoName(void) const
{
    return "MushRenderMeshSolid";
}

MushcoreVirtualObject *MushRenderMeshSolid::AutoClone(void) const
{
    return new MushRenderMeshSolid(*this);
}

MushcoreVirtualObject *MushRenderMeshSolid::AutoCreate(void) const
{
    return new MushRenderMeshSolid;
}

MushcoreVirtualObject *MushRenderMeshSolid::AutoVirtualFactory(void)
{
    return new MushRenderMeshSolid;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushRenderMeshSolid", MushRenderMeshSolid::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushRenderMeshSolid::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushRenderMesh::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushRenderMeshSolid::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
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
MushRenderMeshSolid::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushRenderMesh::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } oOdIRNnS3nfYXC4doS1+lQ
