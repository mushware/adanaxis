//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLState.cpp
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
//%Header } tWGKT6xf6h2OQMzlKKglYA
/*
 * $Id: MushGLState.cpp,v 1.1 2005/07/04 11:10:43 southa Exp $
 * $Log: MushGLState.cpp,v $
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLState.h"

MUSHCORE_SINGLETON_INSTANCE(MushGLState);

//%outOfLineFunctions {

const char *MushGLState::AutoName(void) const
{
    return "MushGLState";
}

MushcoreVirtualObject *MushGLState::AutoClone(void) const
{
    return new MushGLState(*this);
}

MushcoreVirtualObject *MushGLState::AutoCreate(void) const
{
    return new MushGLState;
}

MushcoreVirtualObject *MushGLState::AutoVirtualFactory(void)
{
    return new MushGLState;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLState", MushGLState::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLState::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "colourArray=" << m_colourArray << ", ";
    ioOut << "edgeFlagArray=" << m_edgeFlagArray << ", ";
    ioOut << "indexArray=" << m_indexArray << ", ";
    ioOut << "normalArray=" << m_normalArray << ", ";
    ioOut << "vertexArray=" << m_vertexArray << ", ";
    ioOut << "texCoordArrays=" << m_texCoordArrays << ", ";
    ioOut << "textureStates=" << m_textureStates << ", ";
    ioOut << "activeTexNum=" << m_activeTexNum;
    ioOut << "]";
}
bool
MushGLState::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "colourArray")
    {
        ioIn >> m_colourArray;
    }
    else if (inTagStr == "edgeFlagArray")
    {
        ioIn >> m_edgeFlagArray;
    }
    else if (inTagStr == "indexArray")
    {
        ioIn >> m_indexArray;
    }
    else if (inTagStr == "normalArray")
    {
        ioIn >> m_normalArray;
    }
    else if (inTagStr == "vertexArray")
    {
        ioIn >> m_vertexArray;
    }
    else if (inTagStr == "texCoordArrays")
    {
        ioIn >> m_texCoordArrays;
    }
    else if (inTagStr == "textureStates")
    {
        ioIn >> m_textureStates;
    }
    else if (inTagStr == "activeTexNum")
    {
        ioIn >> m_activeTexNum;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLState::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("colourArray");
    ioOut << m_colourArray;
    ioOut.TagSet("edgeFlagArray");
    ioOut << m_edgeFlagArray;
    ioOut.TagSet("indexArray");
    ioOut << m_indexArray;
    ioOut.TagSet("normalArray");
    ioOut << m_normalArray;
    ioOut.TagSet("vertexArray");
    ioOut << m_vertexArray;
    ioOut.TagSet("texCoordArrays");
    ioOut << m_texCoordArrays;
    ioOut.TagSet("textureStates");
    ioOut << m_textureStates;
    ioOut.TagSet("activeTexNum");
    ioOut << m_activeTexNum;
}
//%outOfLineFunctions } wffnwScjrhX7HJurtizrmw
