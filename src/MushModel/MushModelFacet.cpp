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
 * $Id$
 * $Log$
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
void Install(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushModelFacet", MushModelFacet::AutoVirtualFactory);
}
MushcoreInstaller Installer(Install);
} // end anonymous namespace
void
MushModelFacet::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "type=" << m_type << ", ";
    ioOut << "material=" << m_material << ", ";
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
    else if (inTagStr == "type")
    {
        ioIn >> m_type;
    }
    else if (inTagStr == "material")
    {
        ioIn >> m_material;
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
    ioOut.TagSet("type");
    ioOut << m_type;
    ioOut.TagSet("material");
    ioOut << m_material;
    ioOut.TagSet("vertices");
    ioOut << m_vertices;
    ioOut.TagSet("texCoords");
    ioOut << m_texCoords;
    ioOut.TagSet("normals");
    ioOut << m_normals;
}
//%outOfLineFunctions } PL9vaTOajY4RipihL7/KsQ
