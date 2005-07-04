//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLBuffers.cpp
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
//%Header } iJqp18kDKyw/qVmGx/vsLQ
/*
 * $Id$
 * $Log$
 */

#include "MushGLBuffers.h"

MUSHCORE_KEYED_DATA_INSTANCE(MushGLBuffers, Mushware::U32);

Mushware::U32 MushGLBuffers::m_nextBufferNum = 1;

//%outOfLineFunctions {

const char *MushGLBuffers::AutoName(void) const
{
    return "MushGLBuffers";
}

MushcoreVirtualObject *MushGLBuffers::AutoClone(void) const
{
    return new MushGLBuffers(*this);
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
    ioOut << "texCoordBuffers=" << m_texCoordBuffers;
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
    else if (inTagStr == "texCoordBuffers")
    {
        ioIn >> m_texCoordBuffers;
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
    ioOut.TagSet("texCoordBuffers");
    ioOut << m_texCoordBuffers;
}
//%outOfLineFunctions } /2ZcKv5GYhw/y3hcxBYYtw
