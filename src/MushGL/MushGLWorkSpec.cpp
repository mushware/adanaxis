//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLWorkSpec.cpp
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
//%Header } b7qUd52qZqu3DZi6+5Fjnw
/*
 * $Id: MushGLWorkSpec.cpp,v 1.11 2006/09/09 11:16:40 southa Exp $
 * $Log: MushGLWorkSpec.cpp,v $
 * Revision 1.11  2006/09/09 11:16:40  southa
 * One-time vertex buffer generation
 *
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

#include "API/mushGL.h"

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
                bool bound = Texture(i).Bind();
                stateRef.TexCoordArraySetTrue(pTexCoordBuffers->TexCoordBufferWRef(i), i);
                if (bound) {
                    stateRef.TextureEnable2D(i);
                }
                else {
                    stateRef.TextureDisable2D(i);
                }
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
