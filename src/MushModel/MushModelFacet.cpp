//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelFacet.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } TFlui4Tvtcpr+T5oISSwRA
/*
 * $Id: MushModelFacet.cpp,v 1.1 2004/01/07 18:01:18 southa Exp $
 * $Log: MushModelFacet.cpp,v $
 * Revision 1.1  2004/01/07 18:01:18  southa
 * MushModel and Infernal work
 *
 */

#include "MushModelFacet.h"

#include "MushModelIO.h"

//%outOfLineFunctions {
const char *MushModelFacet::AutoNameGet(void) const
{
    return "MushModelFacet";
}
MushModelFacet *MushModelFacet::AutoClone(void) const
{
    return new MushModelFacet(*this);
}
MushModelFacet *MushModelFacet::AutoCreate(void) const
{
    return new MushModelFacet;
}
MushcoreVirtualObject *MushModelFacet::AutoVirtualFactory(void)
{
    return new MushModelFacet;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushModelFacet", MushModelFacet::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushModelFacet::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "renderType=" << m_renderType << ", ";
    ioOut << "materialRef=" << m_materialRef << ", ";
    ioOut << "vertices=" << m_vertices << ", ";
    ioOut << "texCoords=" << m_texCoords << ", ";
    ioOut << "normals=" << m_normals;
    ioOut << "]";
}
bool
MushModelFacet::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "renderType")
    {
        ioIn >> m_renderType;
    }
    else if (inTagStr == "materialRef")
    {
        ioIn >> m_materialRef;
    }
    else if (inTagStr == "vertices")
    {
        ioIn >> m_vertices;
    }
    else if (inTagStr == "texCoords")
    {
        ioIn >> m_texCoords;
    }
    else if (inTagStr == "normals")
    {
        ioIn >> m_normals;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushModelFacet::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("renderType");
    ioOut << m_renderType;
    ioOut.TagSet("materialRef");
    ioOut << m_materialRef;
    ioOut.TagSet("vertices");
    ioOut << m_vertices;
    ioOut.TagSet("texCoords");
    ioOut << m_texCoords;
    ioOut.TagSet("normals");
    ioOut << m_normals;
}
//%outOfLineFunctions } FjBUA6XZAlFzinQacIRISw
