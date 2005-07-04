//%includeGuardStart {
#ifndef MUSHMESH4MESH_H
#define MUSHMESH4MESH_H
//%includeGuardStart } ul3NY7e8xglZhwH7kPv8yQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Mesh.h
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
//%Header } pM9lKxUBsV8LUNEqYXbulg
/*
 * $Id: MushMesh4Mesh.h,v 1.4 2005/07/04 11:10:43 southa Exp $
 * $Log: MushMesh4Mesh.h,v $
 * Revision 1.4  2005/07/04 11:10:43  southa
 * Rendering pipeline
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

#include "MushMeshStandard.h"

#include "MushMeshMesh.h"
#include "MushMesh4Face.h"
#include "MushMeshVector.h"

//:xml1base MushMeshMesh
//:generate virtual standard ostream xml1
class MushMesh4Mesh : public MushMeshMesh
{
public:
    typedef Mushware::t4Val tVertex;
    typedef std::vector<tVertex> tVertices;
    typedef Mushware::t4Val tTexCoord;
    typedef std::vector<tTexCoord> tTexCoords;
    typedef MushMesh4Face tFace;
    typedef std::vector<tFace> tFaces;
    typedef Mushware::t4Val tNormal;
    typedef std::vector<tNormal> tNormals;
    typedef std::vector<Mushware::U32> tConnection;
    typedef std::vector<tConnection> tConnectivity;
    typedef Mushware::t4Val tCentroid;
    typedef Mushware::tVal tBoundingRadius;
        
    MushMesh4Mesh();
    virtual ~MushMesh4Mesh() {}
    
    const tNormals& Normals(void) const { if (!m_normalsValid) NormalsBuild(); return m_normals; }
    const tConnectivity& Connectivity(void) const { if (!m_connectivityValid) ConnectivityBuild(); return m_connectivity; }
    const Mushware::U32 NumConnections(void) const { if (!m_connectivityValid) ConnectivityBuild(); return m_numConnections; }
    const tCentroid& Centroid(Mushware::U32 inFaceNum) const { if (!m_centroidValid) CentroidBuild(); return m_centroid; }
    const tBoundingRadius BoundingRadius(Mushware::U32 inFaceNum) const { if (!m_boundingRadiusValid) BoundingRadiusBuild(); return m_boundingRadius; }
    const tCentroid& FaceCentroid(Mushware::U32 inFaceNum) const;
    const tBoundingRadius& FaceBoundingRadius(Mushware::U32 inFaceNum) const;
    
    void NormalsBuild(void) const;
    void ConnectivityBuild(void) const;    
    void CentroidBuild(void) const;
    void BoundingRadiusBuild(void) const;
    void FaceCentroidsBuild(void) const;
    void FaceBoundingRadiiBuild(void) const;

    void TouchAll(void);
    void TouchVertices(void);
    void Prebuild(void);
    
private:
    // Minimal representation
    tVertices m_vertices; //:readwrite :wref
    tTexCoords m_texCoords; //:readwrite :wref
    tFaces m_faces; //:readwrite :wref
    
    // Derived representation
    mutable tNormals m_normals;
    mutable tConnectivity m_connectivity;
    mutable tCentroid m_centroid;
    mutable tBoundingRadius m_boundingRadius;
    mutable std::vector<tCentroid> m_faceCentroids;
    mutable std::vector<tBoundingRadius> m_faceBoundingRadii;
    mutable Mushware::U32 m_numConnections;
    
    mutable bool m_normalsValid;
    mutable bool m_connectivityValid;
    mutable bool m_centroidValid;
    mutable bool m_boundingRadiusValid;
    mutable bool m_faceCentroidsValid;
    mutable bool m_faceBoundingRadiiValid;

//%classPrototypes {
public:
    const tVertices& Vertices(void) const { return m_vertices; }
    void VerticesSet(const tVertices& inValue) { m_vertices=inValue; }
    // Writable reference for m_vertices
    tVertices& VerticesWRef(void) { return m_vertices; }
    const tTexCoords& TexCoords(void) const { return m_texCoords; }
    void TexCoordsSet(const tTexCoords& inValue) { m_texCoords=inValue; }
    // Writable reference for m_texCoords
    tTexCoords& TexCoordsWRef(void) { return m_texCoords; }
    const tFaces& Faces(void) const { return m_faces; }
    void FacesSet(const tFaces& inValue) { m_faces=inValue; }
    // Writable reference for m_faces
    tFaces& FacesWRef(void) { return m_faces; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } /FVhjQ5mJ568RN6f+goISQ
};

inline const MushMesh4Mesh::tCentroid&
MushMesh4Mesh::FaceCentroid(Mushware::U32 inFaceNum) const
{
    if (!m_faceCentroidsValid)
    {
        FaceCentroidsBuild();
    }
    MushcoreUtil::BoundsCheck(inFaceNum, m_faceCentroids.size());
    return m_faceCentroids[inFaceNum]; 
}

inline const MushMesh4Mesh::tBoundingRadius&
MushMesh4Mesh::FaceBoundingRadius(Mushware::U32 inFaceNum) const
{
    if (!m_faceBoundingRadiiValid)
    {
        FaceBoundingRadiiBuild();
    }
    MushcoreUtil::BoundsCheck(inFaceNum, m_faceBoundingRadii.size());
    return m_faceBoundingRadii[inFaceNum]; 
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMesh4Mesh& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } fACZKG6NkAx8/ELzs0ocQw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
