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
 * $Id: MushMesh4Mesh.cpp,v 1.1 2005/06/30 12:04:55 southa Exp $
 * $Log: MushMesh4Mesh.cpp,v $
 * Revision 1.1  2005/06/30 12:04:55  southa
 * Mesh work
 *
 */

#include "MushMesh4Mesh.h"

#include "MushMeshMushcoreIO.h"

MushMesh4Mesh::MushMesh4Mesh()
{
    Touch();
}

void
MushMesh4Mesh::Touch(void)
{
    m_normalsValid = false;
    m_connectivityValid = false;
    m_centroidValid = false;
    m_boundingRadiusValid = false;
    m_faceCentroidsValid = false;
    m_faceBoundingRadiiValid = false;
}

void
MushMesh4Mesh::Prebuild(void)
{
    NormalsBuild();
    ConnectivityBuild();
    CentroidBuild();
    BoundingRadiusBuild();
    FaceCentroidsBuild();
    FaceBoundingRadiiBuild();
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

void
MushMesh4Mesh::CentroidBuild(void) const
{
    m_centroidValid = true;
}

void
MushMesh4Mesh::BoundingRadiusBuild(void) const
{
    m_boundingRadiusValid = true;
}

void
MushMesh4Mesh::FaceCentroidsBuild(void) const
{
    m_faceCentroidsValid = true;
}

void
MushMesh4Mesh::FaceBoundingRadiiBuild(void) const
{
    m_faceBoundingRadiiValid = true;
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
    ioOut << "faces=" << m_faces << ", ";
    ioOut << "normals=" << m_normals << ", ";
    ioOut << "connectivity=" << m_connectivity << ", ";
    ioOut << "centroid=" << m_centroid << ", ";
    ioOut << "boundingRadius=" << m_boundingRadius << ", ";
    ioOut << "faceCentroids=" << m_faceCentroids << ", ";
    ioOut << "faceBoundingRadii=" << m_faceBoundingRadii << ", ";
    ioOut << "normalsValid=" << m_normalsValid << ", ";
    ioOut << "connectivityValid=" << m_connectivityValid << ", ";
    ioOut << "centroidValid=" << m_centroidValid << ", ";
    ioOut << "boundingRadiusValid=" << m_boundingRadiusValid << ", ";
    ioOut << "faceCentroidsValid=" << m_faceCentroidsValid << ", ";
    ioOut << "faceBoundingRadiiValid=" << m_faceBoundingRadiiValid;
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
    else if (inTagStr == "normals")
    {
        ioIn >> m_normals;
    }
    else if (inTagStr == "connectivity")
    {
        ioIn >> m_connectivity;
    }
    else if (inTagStr == "centroid")
    {
        ioIn >> m_centroid;
    }
    else if (inTagStr == "boundingRadius")
    {
        ioIn >> m_boundingRadius;
    }
    else if (inTagStr == "faceCentroids")
    {
        ioIn >> m_faceCentroids;
    }
    else if (inTagStr == "faceBoundingRadii")
    {
        ioIn >> m_faceBoundingRadii;
    }
    else if (inTagStr == "normalsValid")
    {
        ioIn >> m_normalsValid;
    }
    else if (inTagStr == "connectivityValid")
    {
        ioIn >> m_connectivityValid;
    }
    else if (inTagStr == "centroidValid")
    {
        ioIn >> m_centroidValid;
    }
    else if (inTagStr == "boundingRadiusValid")
    {
        ioIn >> m_boundingRadiusValid;
    }
    else if (inTagStr == "faceCentroidsValid")
    {
        ioIn >> m_faceCentroidsValid;
    }
    else if (inTagStr == "faceBoundingRadiiValid")
    {
        ioIn >> m_faceBoundingRadiiValid;
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
    ioOut.TagSet("normals");
    ioOut << m_normals;
    ioOut.TagSet("connectivity");
    ioOut << m_connectivity;
    ioOut.TagSet("centroid");
    ioOut << m_centroid;
    ioOut.TagSet("boundingRadius");
    ioOut << m_boundingRadius;
    ioOut.TagSet("faceCentroids");
    ioOut << m_faceCentroids;
    ioOut.TagSet("faceBoundingRadii");
    ioOut << m_faceBoundingRadii;
    ioOut.TagSet("normalsValid");
    ioOut << m_normalsValid;
    ioOut.TagSet("connectivityValid");
    ioOut << m_connectivityValid;
    ioOut.TagSet("centroidValid");
    ioOut << m_centroidValid;
    ioOut.TagSet("boundingRadiusValid");
    ioOut << m_boundingRadiusValid;
    ioOut.TagSet("faceCentroidsValid");
    ioOut << m_faceCentroidsValid;
    ioOut.TagSet("faceBoundingRadiiValid");
    ioOut << m_faceBoundingRadiiValid;
}
//%outOfLineFunctions } eH02ZinmCnCeZF0Gs42A3g
