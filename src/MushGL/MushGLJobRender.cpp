//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLJobRender.cpp
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
//%Header } 6IyRiw/GPkSiBF+Ip2sr7Q
/*
 * $Id: MushGLJobRender.cpp,v 1.6 2006/09/09 11:16:40 southa Exp $
 * $Log: MushGLJobRender.cpp,v $
 * Revision 1.6  2006/09/09 11:16:40  southa
 * One-time vertex buffer generation
 *
 * Revision 1.5  2006/09/07 16:38:50  southa
 * Vertex shader
 *
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
        m_workSpecs[i]->Execute(m_buffersRef, m_sharedBuffersRef);
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
    ioOut << "sharedBuffersRef=" << m_sharedBuffersRef << ", ";
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
    else if (inTagStr == "sharedBuffersRef")
    {
        ioIn >> m_sharedBuffersRef;
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
    ioOut.TagSet("sharedBuffersRef");
    ioOut << m_sharedBuffersRef;
    ioOut.TagSet("sortValue");
    ioOut << m_sortValue;
    ioOut.TagSet("shaderRef");
    ioOut << m_shaderRef;
    ioOut.TagSet("attribs");
    ioOut << m_attribs;
}
//%outOfLineFunctions } hRuMIWSbuYqSHoYodI0q0A
