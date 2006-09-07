//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLJobRender.cpp
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
//%Header } FhldoK+rPKGab09yIIQtMw
/*
 * $Id: MushGLJobRender.cpp,v 1.4 2006/07/24 18:46:49 southa Exp $
 * $Log: MushGLJobRender.cpp,v $
 * Revision 1.4  2006/07/24 18:46:49  southa
 * Depth sorting
 *
 * Revision 1.3  2006/06/01 15:39:17  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/09/05 17:14:22  southa
 * Solid rendering
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */


#include "MushGLJobRender.h"

#include "MushGLState.h"

using namespace Mushware;
using namespace std;

MushGLJobRender::~MushGLJobRender()
{
    U32 workSpecSize = m_workSpecs.size();
    for (U32 i=0; i<workSpecSize; ++i)
    {
        delete m_workSpecs[i];
    }
}

void
MushGLJobRender::Execute(void)
{
    if (m_shaderRef.Name() == "")
    {
        MushGLState::Sgl().ShaderDisable();
    }
    else
    {
        MushGLShader& shaderRef = m_shaderRef.WRef();
        shaderRef.Bind();
        shaderRef.AttribsApply(m_attribs);
    }
    
    U32 workSpecSize = m_workSpecs.size();
    
    for (U32 i=0; i<workSpecSize; ++i)
    {
        if (m_workSpecs[i] == NULL)
        {
            throw MushcoreLogicFail(std::string("Corrupt ")+AutoName()+" job");
        }
        m_workSpecs[i]->Execute(m_buffersRef, m_texCoordBuffersRef);
    }    
    MushGLState::Sgl().ShaderDisable();
}

//%outOfLineFunctions {

const char *MushGLJobRender::AutoName(void) const
{
    return "MushGLJobRender";
}

MushcoreVirtualObject *MushGLJobRender::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'MushGLJobRender'");;
}

MushcoreVirtualObject *MushGLJobRender::AutoCreate(void) const
{
    return new MushGLJobRender;
}

MushcoreVirtualObject *MushGLJobRender::AutoVirtualFactory(void)
{
    return new MushGLJobRender;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLJobRender", MushGLJobRender::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLJobRender::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGLJob::AutoPrint(ioOut);
    ioOut << "workSpecs=" << m_workSpecs << ", ";
    ioOut << "buffersRef=" << m_buffersRef << ", ";
    ioOut << "texCoordBuffersRef=" << m_texCoordBuffersRef << ", ";
    ioOut << "sortValue=" << m_sortValue << ", ";
    ioOut << "shaderRef=" << m_shaderRef << ", ";
    ioOut << "attribs=" << m_attribs;
    ioOut << "]";
}
bool
MushGLJobRender::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "workSpecs")
    {
        ioIn >> m_workSpecs;
    }
    else if (inTagStr == "buffersRef")
    {
        ioIn >> m_buffersRef;
    }
    else if (inTagStr == "texCoordBuffersRef")
    {
        ioIn >> m_texCoordBuffersRef;
    }
    else if (inTagStr == "sortValue")
    {
        ioIn >> m_sortValue;
    }
    else if (inTagStr == "shaderRef")
    {
        ioIn >> m_shaderRef;
    }
    else if (inTagStr == "attribs")
    {
        ioIn >> m_attribs;
    }
    else if (MushGLJob::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGLJobRender::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGLJob::AutoXMLPrint(ioOut);
    ioOut.TagSet("workSpecs");
    ioOut << m_workSpecs;
    ioOut.TagSet("buffersRef");
    ioOut << m_buffersRef;
    ioOut.TagSet("texCoordBuffersRef");
    ioOut << m_texCoordBuffersRef;
    ioOut.TagSet("sortValue");
    ioOut << m_sortValue;
    ioOut.TagSet("shaderRef");
    ioOut << m_shaderRef;
    ioOut.TagSet("attribs");
    ioOut << m_attribs;
}
//%outOfLineFunctions } KwC/mpbdgBhLykiAy+YbSg
