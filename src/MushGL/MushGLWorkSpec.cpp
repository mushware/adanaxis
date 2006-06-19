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
 * $Id: MushGLWorkSpec.cpp,v 1.8 2006/06/01 15:39:19 southa Exp $
 * $Log: MushGLWorkSpec.cpp,v $
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
    MushGLState& stateRef = MushGLState::Sgl();

    MushGLBuffers& buffersRef = ioDataRef.WRef();
    MushGLClaimer<MushGLBuffers> claimBuffer(buffersRef);

    tSize vertexSize = buffersRef.VertexBuffer().Size();
    tSize colourSize = buffersRef.ColourBuffer().Size();
    if (vertexSize > 0)
    {
        stateRef.VertexArraySetTrue(buffersRef.VertexBufferWRef());
    }
    if (colourSize > 0)
    {
        if (vertexSize != colourSize)
        {
            throw MushcoreDataFail("Sizes of vertex and colour buffers do not match");
        }
        stateRef.ColourArraySetTrue(buffersRef.ColourBufferWRef());
    }

    if (ioSharedDataRef.Name() != "")
    {
        MushGLBuffers& texCoordBuffersRef = ioSharedDataRef.WRef();
        MushGLClaimer<MushGLBuffers> texCoordClaimBuffer(texCoordBuffersRef);

        for (U32 i=0; i<texCoordBuffersRef.NumTexCoordBuffers(); ++i)
        {
            tSize texCoordSize = texCoordBuffersRef.TexCoordBuffer(i).Size();

            if (texCoordSize > 0)
            {
                if (vertexSize != texCoordSize)
                {
                    throw MushcoreDataFail("Sizes of vertex and texture coordinate buffers do not match");
                }
                MUSHCOREASSERT(m_pTexture != NULL);
				
                m_pTexture->Bind();
                stateRef.TexCoordArraySetTrue(texCoordBuffersRef.TexCoordBufferWRef(i), i);
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
    if (m_pTexture == NULL)
    {
        ioOut << "pTexture=NULL" ;
    }
    else
    {
        ioOut << "pTexture=" << *m_pTexture;
    }
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
    else if (inTagStr == "pTexture")
    {
        ioIn >> m_pTexture;
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
    ioOut.TagSet("pTexture");
    ioOut << m_pTexture;
}
//%outOfLineFunctions } eiSvgnrdvGSdGmKniSgq4A
