//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLWorkSpec.cpp
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
//%Header } B/Uhyb8oyTGYwsbcQe79PQ
/*
 * $Id: MushGLWorkSpec.cpp,v 1.10 2006/06/20 19:06:52 southa Exp $
 * $Log: MushGLWorkSpec.cpp,v $
 * Revision 1.10  2006/06/20 19:06:52  southa
 * Object creation
 *
 * Revision 1.9  2006/06/19 15:57:17  southa
 * Materials
 *
 * Revision 1.8  2006/06/01 15:39:19  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2006/04/11 23:30:08  southa
 * Created MushRuby from ruby-1.8.4
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
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLWorkSpec.h"

#include "MushGLClaimer.h"
#include "MushGLState.h"
#include "MushGLTexture.h"

using namespace Mushware;
using namespace std;

void
MushGLWorkSpec::Execute(MushGLBuffers::tDataRef& ioDataRef, MushGLBuffers::tSharedDataRef& ioSharedDataRef)
{
    if (ioDataRef.Name() == 0)
    {
        throw MushcoreDataFail("MushGLWorkSpec data name not set");
    }
    if (ioSharedDataRef.Name() == "")
    {
        throw MushcoreDataFail("MushGLWorkSpec shared data name not set");
    }

    MushGLState& stateRef = MushGLState::Sgl();

    MushGLBuffers *pVertexBuffers = m_useSharedVertices ? &ioSharedDataRef.WRef() : &ioDataRef.WRef();
    MushGLBuffers *pColourBuffers = &ioDataRef.WRef();
    MushGLBuffers *pTexCoordBuffers = &ioSharedDataRef.WRef();

    tSize vertexSize = pVertexBuffers->VertexBuffer().Size();
    if (vertexSize > 0)
    {
        stateRef.VertexArraySetTrue(pVertexBuffers->VertexBufferWRef());
    }
    
    tSize colourSize = pColourBuffers->ColourBuffer().Size();
    if (colourSize > 0)
    {
        if (vertexSize != colourSize)
        {
            throw MushcoreDataFail("Sizes of vertex and colour buffers do not match");
        }
        stateRef.ColourArraySetTrue(pColourBuffers->ColourBufferWRef());
    }

    for (U32 i=0; i < pTexCoordBuffers->NumTexCoordBuffers(); ++i)
    {
        tSize texCoordSize = pTexCoordBuffers->TexCoordBuffer(i).Size();

        if (texCoordSize > 0)
        {
            if (vertexSize != texCoordSize)
            {
                ostringstream message;
                message << "Sizes of vertex (" << vertexSize << ") and texture (" << texCoordSize << ") coordinate buffers do not match";
                throw MushcoreDataFail(message.str());
            }
            if (IsValidTexture(i))
            {
                stateRef.ActiveTextureZeroBased(i);
                Texture(i).Bind();
                stateRef.TexCoordArraySetTrue(pTexCoordBuffers->TexCoordBufferWRef(i), i);
                stateRef.TextureEnable2D(i);
            }
        }
    }

    switch (m_renderType)
    {
        case GL_POINTS:
        case GL_LINE_STRIP:
        case GL_LINE_LOOP:
        case GL_LINES:
        case GL_TRIANGLES:
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:
        case GL_QUAD_STRIP:
        case GL_QUADS:
        case GL_POLYGON:
            break;
            
        default:
        {
            ostringstream message;
            message << "Unknown render type '" << m_renderType << "'";
            throw MushcoreDataFail(message.str());
        }
        break;
    }

    MushGLV::Sgl().DrawArrays(m_renderType, 0, vertexSize);
    
    stateRef.TexturesDisable();
    stateRef.ArraysDisable();
}

//%outOfLineFunctions {

const char *MushGLWorkSpec::AutoName(void) const
{
    return "MushGLWorkSpec";
}

MushcoreVirtualObject *MushGLWorkSpec::AutoClone(void) const
{
    return new MushGLWorkSpec(*this);
}

MushcoreVirtualObject *MushGLWorkSpec::AutoCreate(void) const
{
    return new MushGLWorkSpec;
}

MushcoreVirtualObject *MushGLWorkSpec::AutoVirtualFactory(void)
{
    return new MushGLWorkSpec;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLWorkSpec", MushGLWorkSpec::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLWorkSpec::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "renderType=" << m_renderType << ", ";
    ioOut << "textures=" << m_textures << ", ";
    ioOut << "useSharedVertices=" << m_useSharedVertices;
    ioOut << "]";
}
bool
MushGLWorkSpec::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "renderType")
    {
        ioIn >> m_renderType;
    }
    else if (inTagStr == "textures")
    {
        ioIn >> m_textures;
    }
    else if (inTagStr == "useSharedVertices")
    {
        ioIn >> m_useSharedVertices;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLWorkSpec::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("renderType");
    ioOut << m_renderType;
    ioOut.TagSet("textures");
    ioOut << m_textures;
    ioOut.TagSet("useSharedVertices");
    ioOut << m_useSharedVertices;
}
//%outOfLineFunctions } sgvqsERl60B2FOCU24bqWQ
