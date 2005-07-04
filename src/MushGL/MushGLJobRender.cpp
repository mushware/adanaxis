//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLJobRender.cpp
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
//%Header } X47iPT+8iMD/6mUj/Cr/qg
/*
 * $Id$
 * $Log$
 */


#include "MushGLJobRender.h"

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
    U32 workSpecSize = m_workSpecs.size();
    MushGLBuffers& buffersRef = m_buffersRef.WRef();
    
    for (U32 i=0; i<workSpecSize; ++i)
    {
        if (m_workSpecs[i] == NULL)
        {
            throw MushcoreLogicFail(std::string("Corrupt ")+AutoName()+" job");
        }
        m_workSpecs[i]->Execute(buffersRef);
    }    
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
    ioOut << "buffersRef=" << m_buffersRef;
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
}
//%outOfLineFunctions } MHMwse8jUppzhUcsiyrRdg
