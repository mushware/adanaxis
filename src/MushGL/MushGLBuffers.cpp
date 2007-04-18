//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLBuffers.cpp
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
//%Header } 7hGg8TwEMYNU9YV1DqmvRA
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
