//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLBuffers.cpp
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
//%Header } zkhgmcWBV/TK5XEAFOa7SA
/*
 * $Id: MushGLBuffers.cpp,v 1.7 2006/06/30 15:05:33 southa Exp $
 * $Log: MushGLBuffers.cpp,v $
 * Revision 1.7  2006/06/30 15:05:33  southa
 * Texture and buffer purge
 *
 * Revision 1.6  2006/06/01 15:39:17  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/09/05 12:54:30  southa
 * Solid rendering work
 *
 * Revision 1.4  2005/09/03 17:05:36  southa
 * Material work
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

#include "MushGLBuffers.h"

// Keyed data for per-object buffers
MUSHCORE_KEYED_DATA_INSTANCE(MushGLBuffers, Mushware::U32);

// Named data for shared buffers
MUSHCORE_DATA_INSTANCE(MushGLBuffers);

using namespace Mushware;
using namespace std;

Mushware::U32 MushGLBuffers::m_nextBufferNum = 1;

void
MushGLBuffers::Purge(void)
{
    m_vertexContextNum = 0;
    m_colourContextNum = 0;
    m_texCoordContextNum = 0;
    m_triangleListContextNum = 0;    
    m_vertexBuffer.Purge();
    m_colourBuffer.Purge();
    
    MUSHCOREASSERT(m_numTexCoordBuffers < kNumTexCoordBuffers);
    
    for (U32 i=0; i<m_numTexCoordBuffers; ++i)
    {
        m_texCoordBuffers[i].Purge();
    }
}

//%outOfLineFunctions {

const char *MushGLBuffers::AutoName(void) const
{
    return "MushGLBuffers";
}

MushcoreVirtualObject *MushGLBuffers::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'MushGLBuffers'");;
}

MushcoreVirtualObject *MushGLBuffers::AutoCreate(void) const
{
    return new MushGLBuffers;
}

MushcoreVirtualObject *MushGLBuffers::AutoVirtualFactory(void)
{
    return new MushGLBuffers;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLBuffers", MushGLBuffers::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLBuffers::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "owner=" << static_cast<Mushware::U32>(m_owner) << ", ";
    ioOut << "vertexBuffer=" << m_vertexBuffer << ", ";
    ioOut << "colourBuffer=" << m_colourBuffer << ", ";
    ioOut << "texCoordBuffers=" << m_texCoordBuffers << ", ";
    ioOut << "numTexCoordBuffers=" << m_numTexCoordBuffers << ", ";
    ioOut << "vertexTriangleList=" << m_vertexTriangleList << ", ";
    ioOut << "texCoordTriangleList=" << m_texCoordTriangleList << ", ";
    ioOut << "vertexContextNum=" << m_vertexContextNum << ", ";
    ioOut << "colourContextNum=" << m_colourContextNum << ", ";
    ioOut << "texCoordContextNum=" << m_texCoordContextNum << ", ";
    ioOut << "triangleListContextNum=" << m_triangleListContextNum << ", ";
    ioOut << "worldVertices=" << m_worldVertices << ", ";
    ioOut << "eyeVertices=" << m_eyeVertices << ", ";
    ioOut << "projectedVertices=" << m_projectedVertices;
    ioOut << "]";
}
bool
MushGLBuffers::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "owner")
    {
        ioIn >> m_owner;
    }
    else if (inTagStr == "vertexBuffer")
    {
        ioIn >> m_vertexBuffer;
    }
    else if (inTagStr == "colourBuffer")
    {
        ioIn >> m_colourBuffer;
    }
    else if (inTagStr == "numTexCoordBuffers")
    {
        ioIn >> m_numTexCoordBuffers;
    }
    else if (inTagStr == "vertexTriangleList")
    {
        ioIn >> m_vertexTriangleList;
    }
    else if (inTagStr == "texCoordTriangleList")
    {
        ioIn >> m_texCoordTriangleList;
    }
    else if (inTagStr == "vertexContextNum")
    {
        ioIn >> m_vertexContextNum;
    }
    else if (inTagStr == "colourContextNum")
    {
        ioIn >> m_colourContextNum;
    }
    else if (inTagStr == "texCoordContextNum")
    {
        ioIn >> m_texCoordContextNum;
    }
    else if (inTagStr == "triangleListContextNum")
    {
        ioIn >> m_triangleListContextNum;
    }
    else if (inTagStr == "worldVertices")
    {
        ioIn >> m_worldVertices;
    }
    else if (inTagStr == "eyeVertices")
    {
        ioIn >> m_eyeVertices;
    }
    else if (inTagStr == "projectedVertices")
    {
        ioIn >> m_projectedVertices;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLBuffers::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("owner");
    ioOut << m_owner;
    ioOut.TagSet("vertexBuffer");
    ioOut << m_vertexBuffer;
    ioOut.TagSet("colourBuffer");
    ioOut << m_colourBuffer;
    ioOut.TagSet("numTexCoordBuffers");
    ioOut << m_numTexCoordBuffers;
    ioOut.TagSet("vertexTriangleList");
    ioOut << m_vertexTriangleList;
    ioOut.TagSet("texCoordTriangleList");
    ioOut << m_texCoordTriangleList;
    ioOut.TagSet("vertexContextNum");
    ioOut << m_vertexContextNum;
    ioOut.TagSet("colourContextNum");
    ioOut << m_colourContextNum;
    ioOut.TagSet("texCoordContextNum");
    ioOut << m_texCoordContextNum;
    ioOut.TagSet("triangleListContextNum");
    ioOut << m_triangleListContextNum;
    ioOut.TagSet("worldVertices");
    ioOut << m_worldVertices;
    ioOut.TagSet("eyeVertices");
    ioOut << m_eyeVertices;
    ioOut.TagSet("projectedVertices");
    ioOut << m_projectedVertices;
}
//%outOfLineFunctions } ASFwYJD7v+VNjlqdWpgnyw
