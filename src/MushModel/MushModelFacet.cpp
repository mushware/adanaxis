//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelFacet.cpp
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
//%Header } WTo3qhRr63RK1J47o9bcbQ
/*
 * $Id: MushModelFacet.cpp,v 1.3 2005/02/10 12:34:08 southa Exp $
 * $Log: MushModelFacet.cpp,v $
 * Revision 1.3  2005/02/10 12:34:08  southa
 * Template fixes
 *
 * Revision 1.2  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
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

MushcoreVirtualObject *MushModelFacet::AutoClone(void) const
{
    return new MushModelFacet(*this);
}

MushcoreVirtualObject *MushModelFacet::AutoCreate(void) const
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
//%outOfLineFunctions } 0dG/ACymQk84v7Mhm1UaVA
