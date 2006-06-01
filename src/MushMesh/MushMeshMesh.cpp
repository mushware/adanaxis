//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshMesh.cpp
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
//%Header } F+vVCutfXCZOYBmPmuwLKA
/*
 * $Id: MushMeshMesh.cpp,v 1.2 2005/07/02 00:42:38 southa Exp $
 * $Log: MushMeshMesh.cpp,v $
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/30 12:04:56  southa
 * Mesh work
 *
 */

#include "MushMeshMesh.h"

MushMeshMesh::MushMeshMesh()
{
}

MushMeshMesh::~MushMeshMesh()
{
}

//%outOfLineFunctions {

const char *MushMeshMesh::AutoName(void) const
{
    return "MushMeshMesh";
}

MushcoreVirtualObject *MushMeshMesh::AutoClone(void) const
{
    return new MushMeshMesh(*this);
}

MushcoreVirtualObject *MushMeshMesh::AutoCreate(void) const
{
    return new MushMeshMesh;
}

MushcoreVirtualObject *MushMeshMesh::AutoVirtualFactory(void)
{
    return new MushMeshMesh;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshMesh", MushMeshMesh::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshMesh::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "materialRef=" << m_materialRef;
    ioOut << "]";
}
bool
MushMeshMesh::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "materialRef")
    {
        ioIn >> m_materialRef;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMeshMesh::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("materialRef");
    ioOut << m_materialRef;
}
//%outOfLineFunctions } RiAIJv1YEYjRk9D44S7YrQ
