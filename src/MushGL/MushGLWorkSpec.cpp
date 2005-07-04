//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLWorkSpec.cpp
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
//%Header } Wpgv8RTp/irSWsiiI5S6xA
/*
 * $Id$
 * $Log$
 */

#include "MushGLWorkSpec.h"

#include "MushGLClaimer.h"
#include "MushGLState.h"

using namespace Mushware;
using namespace std;

void
MushGLWorkSpec::Execute(MushGLBuffers& ioBuffers)
{
    MushGLClaimer<MushGLBuffers> claimBuffer(ioBuffers);
    MushGLState& stateRef = MushGLState::Sgl();
    

    tSize vertexSize = ioBuffers.VertexBuffer().Size();
    tSize colourSize = ioBuffers.ColourBuffer().Size();
    if (vertexSize > 0)
    {
        stateRef.VertexArraySetTrue(ioBuffers.VertexBufferWRef());
    }
    if (colourSize > 0)
    {
        if (vertexSize != colourSize)
        {
            throw MushcoreDataFail("Sizes of vertex and colour buffers do not match");
        }
        stateRef.ColourArraySetTrue(ioBuffers.ColourBufferWRef());
    }
    
    switch (m_renderType)
    {
        case GL_POINTS:
        case GL_LINE_STRIP:
        case GL_LINE_LOOP:
        case GL_LINES:
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
    ioOut << "renderType=" << m_renderType;
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
}
//%outOfLineFunctions } SluKYptWzn2XpYyCJv1AwQ
