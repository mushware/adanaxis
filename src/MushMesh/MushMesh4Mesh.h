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
 * $Id$
 * $Log$
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
    
    MushMesh4Mesh();
    virtual ~MushMesh4Mesh() {}
    
    const tNormals& Normals(void) const { if (!m_normalsValid) NormalsBuild(); return m_normals; }
    const tConnectivity& Connectivity(void) const { if (!m_connectivityValid) ConnectivityBuild(); return m_connectivity; }

    
    void NormalsBuild(void) const; // Also automatic
    void ConnectivityBuild(void) const; // Also automatic
    
private:
    // Minimal representation
    tVertices m_vertices; //:readwrite :wref
    tTexCoords m_texCoords; //:readwrite :wref
    tFaces m_faces; //:readwrite :wref
    
    // Derived representation
    mutable tNormals m_normals;
    mutable tConnectivity m_connectivity;
    
    mutable bool m_normalsValid;
    mutable bool m_connectivityValid;
    
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
