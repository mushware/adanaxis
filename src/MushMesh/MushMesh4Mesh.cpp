//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Mesh.cpp
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
//%Header } v136Oh1IVziX36Di81JIXQ
/*
 * $Id$
 * $Log$
 */

#include "MushMesh4Mesh.h"

#include "MushMeshMushcoreIO.h"

MushMesh4Mesh::MushMesh4Mesh() :
    m_normalsValid(false),
    m_connectivityValid(false)
{
}

void
MushMesh4Mesh::NormalsBuild(void) const
{
    m_normalsValid = true;
}

void
MushMesh4Mesh::ConnectivityBuild(void) const
{
    m_connectivityValid = true;
}

//%outOfLineFunctions {

const char *MushMesh4Mesh::AutoName(void) const
{
    return "MushMesh4Mesh";
}

MushcoreVirtualObject *MushMesh4Mesh::AutoClone(void) const
{
    return new MushMesh4Mesh(*this);
}

MushcoreVirtualObject *MushMesh4Mesh::AutoCreate(void) const
{
    return new MushMesh4Mesh;
}

MushcoreVirtualObject *MushMesh4Mesh::AutoVirtualFactory(void)
{
    return new MushMesh4Mesh;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4Mesh", MushMesh4Mesh::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4Mesh::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMeshMesh::AutoPrint(ioOut);
    ioOut << "vertices=" << m_vertices << ", ";
    ioOut << "texCoords=" << m_texCoords << ", ";
    ioOut << "faces=" << m_faces;
    ioOut << "]";
}
bool
MushMesh4Mesh::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "vertices")
    {
        ioIn >> m_vertices;
    }
    else if (inTagStr == "texCoords")
    {
        ioIn >> m_texCoords;
    }
    else if (inTagStr == "faces")
    {
        ioIn >> m_faces;
    }
    else if (MushMeshMesh::AutoXMLDataProcess(ioIn, inTagStr))
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
MushMesh4Mesh::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMeshMesh::AutoXMLPrint(ioOut);
    ioOut.TagSet("vertices");
    ioOut << m_vertices;
    ioOut.TagSet("texCoords");
    ioOut << m_texCoords;
    ioOut.TagSet("faces");
    ioOut << m_faces;
}
//%outOfLineFunctions } +FMAuAskXJGxIeC722NMew
