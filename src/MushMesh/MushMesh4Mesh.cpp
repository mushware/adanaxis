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
 * $Id: MushMesh4Mesh.cpp,v 1.4 2005/07/02 00:42:38 southa Exp $
 * $Log: MushMesh4Mesh.cpp,v $
 * Revision 1.4  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/06/30 14:26:36  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/30 12:34:59  southa
 * Mesh and source conditioner work
 *
 * Revision 1.1  2005/06/30 12:04:55  southa
 * Mesh work
 *
 */

#include "MushMesh4Mesh.h"

#include "MushMeshMushcoreIO.h"
#include "MushMeshSTL.h"

using namespace Mushware;
using namespace std;

MushMesh4Mesh::MushMesh4Mesh()
{
    TouchAll();
}

void
MushMesh4Mesh::TouchVertices(void)
{
    m_normalsValid = false;
    m_centroidValid = false;
    m_boundingRadiusValid = false;
    m_faceCentroidsValid = false;
    m_faceBoundingRadiiValid = false; 
}

void
MushMesh4Mesh::TouchAll(void)
{
    TouchVertices();
    m_connectivityValid = false;
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
    m_numConnections = 0;
    m_connectivity.resize(m_vertices.size());
    for (U32 i=0; i<m_connectivity.size(); ++i)
    {
        m_connectivity[i].resize(0);
    }    
    
    for (U32 i=0; i<m_faces.size(); ++i)
    {
        const MushMesh4Face& faceRef = m_faces[i];
        const MushMesh4Face::tVertexList& vertexListRef = faceRef.VertexList();
        const MushMesh4Face::tVertexGroupSize& vertexGroupSizeRef = faceRef.VertexGroupSize();
        
        U32 listIndex = 0;
        for (U32 j=0; j<vertexGroupSizeRef.size(); ++j)
        {
            U32 vertexGroupSize = vertexGroupSizeRef[j];
            if (vertexGroupSize > 1)
            {
                for (U32 k=0; k<vertexGroupSize; ++k)
                {
                    U32 vertIndex = listIndex+k;
                    U32 otherVertIndex;
                    if (k+1 < vertexGroupSize)
                    {
                        otherVertIndex = listIndex+k+1;
                    }
                    else
                    {
                        otherVertIndex = listIndex;
                    }
                    
                    MUSHCOREASSERT(vertIndex < vertexListRef.size());
                    MUSHCOREASSERT(otherVertIndex < vertexListRef.size());

                    U32 vertNum = vertexListRef[vertIndex];
                    U32 otherVertNum = vertexListRef[otherVertIndex];
                    
                    MUSHCOREASSERT(vertNum < m_connectivity.size());
                    MUSHCOREASSERT(otherVertNum < m_connectivity.size());
                    
                    if (std::find(m_connectivity[vertNum].begin(),
                             m_connectivity[vertNum].end(),
                             otherVertNum) == m_connectivity[vertNum].end())
                    {
                        m_connectivity[vertNum].push_back(otherVertNum);
                        ++m_numConnections;
                    }
                    if (std::find(m_connectivity[otherVertNum].begin(),
                             m_connectivity[otherVertNum].end(),
                             vertNum) == m_connectivity[otherVertNum].end())
                    {
                        m_connectivity[otherVertNum].push_back(vertNum);
                        ++m_numConnections;
                    }
                }
            }
            listIndex += vertexGroupSize;
        }
    }
    
    for (U32 i=0; i<m_connectivity.size(); ++i)
    {
        std::sort(m_connectivity[i].begin(), m_connectivity[i].end());
    }  
    
    // Each connection counted twice (once from each end), so divide
    m_numConnections /= 2;
    
    m_connectivityValid = true;
}

void
MushMesh4Mesh::CentroidBuild(void) const
{
    m_centroid = t4Val(0,0,0,0);
    U32 verticesSize = m_vertices.size();
    for (U32 i=0; i<verticesSize; ++i)
    {
        m_centroid += m_vertices[i];
    }
    m_centroid /= verticesSize;
    
    m_centroidValid = true;
}

void
MushMesh4Mesh::BoundingRadiusBuild(void) const
{
    if (!m_centroidValid)
    {
        CentroidBuild();
    }
    
    tVal maxRadiusSquared = 0;
    
    U32 verticesSize = m_vertices.size();
    for (U32 i=0; i<verticesSize; ++i)
    {
        tVal radiusSquared = (m_centroid - m_vertices[i]).MagnitudeSquared();
        if (radiusSquared >  maxRadiusSquared)
        {
             maxRadiusSquared = radiusSquared;
        }
    }
    
    m_boundingRadius = std::sqrt(maxRadiusSquared);
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
    ioOut << "numConnections=" << m_numConnections << ", ";
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
    else if (inTagStr == "numConnections")
    {
        ioIn >> m_numConnections;
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
    ioOut.TagSet("numConnections");
    ioOut << m_numConnections;
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
//%outOfLineFunctions } jO+f+zBR25Zb2usY/uQnPg
