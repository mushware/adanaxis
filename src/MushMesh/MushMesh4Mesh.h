//%includeGuardStart {
#ifndef MUSHMESH4MESH_H
#define MUSHMESH4MESH_H
//%includeGuardStart } ul3NY7e8xglZhwH7kPv8yQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Mesh.h
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
//%Header } YrK9KiG4XjKqbWo1rVGU4w
/*
 * $Id: MushMesh4Mesh.h,v 1.19 2006/07/17 14:43:40 southa Exp $
 * $Log: MushMesh4Mesh.h,v $
 * Revision 1.19  2006/07/17 14:43:40  southa
 * Billboarded deco objects
 *
 * Revision 1.18  2006/06/19 15:57:18  southa
 * Materials
 *
 * Revision 1.17  2006/06/16 01:02:32  southa
 * Ruby mesh generation
 *
 * Revision 1.16  2006/06/14 18:45:47  southa
 * Ruby mesh generation
 *
 * Revision 1.15  2006/06/14 11:20:07  southa
 * Ruby mesh generation
 *
 * Revision 1.14  2006/05/01 17:39:00  southa
 * Texture generation
 *
 * Revision 1.13  2005/09/05 12:54:30  southa
 * Solid rendering work
 *
 * Revision 1.12  2005/09/03 17:05:36  southa
 * Material work
 *
 * Revision 1.11  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 * Revision 1.10  2005/08/01 17:58:25  southa
 * Object explosion
 *
 * Revision 1.9  2005/07/27 18:09:10  southa
 * Collision checking
 *
 * Revision 1.8  2005/07/19 13:44:26  southa
 * MushMesh4Chunk work
 *
 * Revision 1.7  2005/07/13 16:45:05  southa
 * Extrusion work
 *
 * Revision 1.6  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 * Revision 1.5  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
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

#include "MushMesh4Base.h"
#include "MushMesh4Chunk.h"
#include "MushMesh4Extruder.h"
#include "MushMesh4Face.h"
#include "MushMesh4FaceGenerator.h"
#include "MushMesh4Material.h"
#include "MushMesh4TextureTile.h"
#include "MushMesh4VertexGenerator.h"
#include "MushMeshDisplacement.h"
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
    typedef MushMesh4Chunk tChunk;
    typedef std::vector<tChunk> tChunks;
    typedef MushcoreDataRef<MushMesh4Mesh> tDataRef;
    typedef MushMesh4TextureTile tTextureTile;
    typedef std::vector<tTextureTile> tTextureTiles;
    typedef std::vector< MushcoreAutoClonePtr<MushMesh4Extruder> > tExtruders;
	typedef MushcoreDataRef<MushMesh4Material> tMaterialRef;
	typedef std::vector<tMaterialRef> tMaterials;
	
    enum
    {
        kTransformTypeInvalid = 0,
        kTransformTypeNormal,
        kTransformTypeBillboard
    } tTransformType;
    
    MushMesh4Mesh();
    virtual ~MushMesh4Mesh() {}

    const tVertex& QuickVertex(Mushware::U32 inNum) const { MushcoreUtil::DebugBoundsCheck(inNum, m_vertices.size()); return m_vertices[inNum]; }
    const tVertex& Vertex(Mushware::U32 inNum) const { MushcoreUtil::BoundsCheck(inNum, m_vertices.size()); return m_vertices[inNum]; }
    tVertex& VertexWRef(Mushware::U32 inNum) { MushcoreUtil::BoundsCheck(inNum, m_vertices.size()); return m_vertices[inNum]; }
    const tFace& Face(Mushware::U32 inNum) const { MushcoreUtil::BoundsCheck(inNum, m_faces.size()); return m_faces[inNum]; }
    tFace& FaceWRef(Mushware::U32 inNum) { MushcoreUtil::BoundsCheck(inNum, m_faces.size()); return m_faces[inNum]; }
    const tChunk& Chunk(Mushware::U32 inNum) const { MushcoreUtil::BoundsCheck(inNum, m_chunks.size()); return m_chunks[inNum]; }
    tChunk& ChunkWRef(Mushware::U32 inNum) { MushcoreUtil::BoundsCheck(inNum, m_chunks.size()); return m_chunks[inNum]; }
    
    const tNormals& Normals(void) const { if (!m_normalsValid) NormalsBuild(); return m_normals; }
    const tConnectivity& Connectivity(void) const { if (!m_connectivityValid) ConnectivityBuild(); return m_connectivity; }
    const Mushware::U32 NumConnections(void) const { if (!m_connectivityValid) ConnectivityBuild(); return m_numConnections; }
    const Mushware::U32 NumFacets(void) const { if (!m_numFacetsValid) NumFacetsBuild(); return m_numFacets; }
    const tCentroid& Centroid(void) const { if (!m_centroidValid) CentroidBuild(); return m_centroid; }
    const tBoundingRadius BoundingRadius(void) const { if (!m_boundingRadiusValid) BoundingRadiusBuild(); return m_boundingRadius; }
    const tCentroid& FaceCentroid(Mushware::U32 inFaceNum) const;
    const MushMesh4Face::tFaceConnectivity& FaceConnectivity(Mushware::U32 inFaceNum) const;
    const tChunk::tVertexList& ChunkUniqueVertexList(Mushware::U32 inChunkNum) const;
    const tCentroid& ChunkCentroid(Mushware::U32 inChunkNum) const;
    const Mushware::tVal ChunkBoundingRadius(Mushware::U32 inChunkNum) const;
    
    void NormalsBuild(void) const;
    void ConnectivityBuild(void) const;    
    void NumFacetsBuild(void) const;    
    void CentroidBuild(void) const;
    void BoundingRadiusBuild(void) const;
    void FaceCentroidBuild(Mushware::U32 inFaceNum) const;
    void FaceConnectivityBuild(Mushware::U32 inFaceNum) const;    
    void FaceBoundingRadiiBuild(void) const;
    void ChunkUniqueVertexListBuild(Mushware::U32 inChunkNum) const;
    void ChunkBoundingRadiusBuild(Mushware::U32 inChunkNum) const;
    void ChunkCentroidBuild(Mushware::U32 inChunkNum) const;

    void AllTouch(void); // Called from constructor
    void VerticesTouch(void); // Called from constructor
    void Prebuild(void);
	
	void BaseGive(MushMesh4Base *pBase); // Takes ownership of the base generator
	const MushMesh4Base *BaseGet(void) const;
	MushMesh4Base *BaseWGet(void);
	
	void ExtruderGive(MushMesh4Extruder *pExtruder); // Takes ownership of the extruder
	const MushMesh4Extruder *ExtruderGet(Mushware::U32 inNum) const;
	MushMesh4Extruder *ExtruderWGet(Mushware::U32 inNum);
	Mushware::U32 NumExtruders(void) const;
	
	void MaterialNameSet(const std::string& inName, Mushware::U32 inIndex);
	const MushMesh4Material& MaterialRef(Mushware::U32 inIndex) const
	{
		MushcoreUtil::DebugBoundsCheck(inIndex, m_materials.size());
		return m_materials[inIndex].Ref();
	}
	Mushware::U32 NumMaterials(void) const { return m_materials.size(); }
	
	void Apply(const MushMeshDisplacement& inDisp);
    void ApplyScale(const Mushware::t4Val inScale);
            void Make(void);
	
private:
    // Minimal representation
    tVertices m_vertices; //:readwrite :wref
    tTexCoords m_texCoords; //:readwrite :wref
    tFaces m_faces; //:readwrite :wref
	tMaterials m_materials; //:readwrite :wref;
	Mushware::U32 m_levelOfDetail; //:readwrite
    Mushware::U32  m_transformType; //:readwrite
    
    // Delegates
    tDataRef m_texCoordDelegate; //:readwrite :wref
    
    // Generation and animation
    Mushware::U32 m_vertexCounter; //:readwrite :wref
    Mushware::U32 m_faceCounter; //:readwrite :wref
    Mushware::U32 m_texCoordCounter; //:readwrite :wref
    MushcoreAutoClonePtr<MushMesh4FaceGenerator> m_faceGenerator; //:readwrite :wref
    MushcoreAutoClonePtr<MushMesh4VertexGenerator> m_vertexGenerator; //:readwrite :wref
    MushcoreAutoClonePtr<MushMesh4Base> m_base; //:readwrite :wref
	MushMeshDisplacement m_baseDisplacement; //:readwrite :wref
    tExtruders m_extruders; //:read :wref
    tTextureTiles m_textureTiles; //:readwrite :wref
    
    // Collision
    tChunks m_chunks; //:readwrite :wref
    
    // Derived representation
    mutable tNormals m_normals;
    mutable tConnectivity m_connectivity;
    mutable tCentroid m_centroid;
    mutable tBoundingRadius m_boundingRadius;
    mutable std::vector<tCentroid> m_faceCentroids;
    mutable std::vector<tBoundingRadius> m_faceBoundingRadii;
    mutable Mushware::U32 m_numConnections;
    mutable Mushware::U32 m_numFacets;
    
    mutable bool m_normalsValid;
    mutable bool m_connectivityValid;
    mutable bool m_centroidValid;
    mutable bool m_boundingRadiusValid;
    mutable bool m_numFacetsValid;

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
    const tMaterials& Materials(void) const { return m_materials; }
    void MaterialsSet(const tMaterials& inValue) { m_materials=inValue; }
    // Writable reference for m_materials
    tMaterials& MaterialsWRef(void) { return m_materials; }
    const Mushware::U32& LevelOfDetail(void) const { return m_levelOfDetail; }
    void LevelOfDetailSet(const Mushware::U32& inValue) { m_levelOfDetail=inValue; }
    const Mushware::U32& TransformType(void) const { return m_transformType; }
    void TransformTypeSet(const Mushware::U32& inValue) { m_transformType=inValue; }
    const tDataRef& TexCoordDelegate(void) const { return m_texCoordDelegate; }
    void TexCoordDelegateSet(const tDataRef& inValue) { m_texCoordDelegate=inValue; }
    // Writable reference for m_texCoordDelegate
    tDataRef& TexCoordDelegateWRef(void) { return m_texCoordDelegate; }
    const Mushware::U32& VertexCounter(void) const { return m_vertexCounter; }
    void VertexCounterSet(const Mushware::U32& inValue) { m_vertexCounter=inValue; }
    // Writable reference for m_vertexCounter
    Mushware::U32& VertexCounterWRef(void) { return m_vertexCounter; }
    const Mushware::U32& FaceCounter(void) const { return m_faceCounter; }
    void FaceCounterSet(const Mushware::U32& inValue) { m_faceCounter=inValue; }
    // Writable reference for m_faceCounter
    Mushware::U32& FaceCounterWRef(void) { return m_faceCounter; }
    const Mushware::U32& TexCoordCounter(void) const { return m_texCoordCounter; }
    void TexCoordCounterSet(const Mushware::U32& inValue) { m_texCoordCounter=inValue; }
    // Writable reference for m_texCoordCounter
    Mushware::U32& TexCoordCounterWRef(void) { return m_texCoordCounter; }
    const MushcoreAutoClonePtr<MushMesh4FaceGenerator>& FaceGenerator(void) const { return m_faceGenerator; }
    void FaceGeneratorSet(const MushcoreAutoClonePtr<MushMesh4FaceGenerator>& inValue) { m_faceGenerator=inValue; }
    // Writable reference for m_faceGenerator
    MushcoreAutoClonePtr<MushMesh4FaceGenerator>& FaceGeneratorWRef(void) { return m_faceGenerator; }
    const MushcoreAutoClonePtr<MushMesh4VertexGenerator>& VertexGenerator(void) const { return m_vertexGenerator; }
    void VertexGeneratorSet(const MushcoreAutoClonePtr<MushMesh4VertexGenerator>& inValue) { m_vertexGenerator=inValue; }
    // Writable reference for m_vertexGenerator
    MushcoreAutoClonePtr<MushMesh4VertexGenerator>& VertexGeneratorWRef(void) { return m_vertexGenerator; }
    const MushcoreAutoClonePtr<MushMesh4Base>& Base(void) const { return m_base; }
    void BaseSet(const MushcoreAutoClonePtr<MushMesh4Base>& inValue) { m_base=inValue; }
    // Writable reference for m_base
    MushcoreAutoClonePtr<MushMesh4Base>& BaseWRef(void) { return m_base; }
    const MushMeshDisplacement& BaseDisplacement(void) const { return m_baseDisplacement; }
    void BaseDisplacementSet(const MushMeshDisplacement& inValue) { m_baseDisplacement=inValue; }
    // Writable reference for m_baseDisplacement
    MushMeshDisplacement& BaseDisplacementWRef(void) { return m_baseDisplacement; }
    const tExtruders& Extruders(void) const { return m_extruders; }
    // Writable reference for m_extruders
    tExtruders& ExtrudersWRef(void) { return m_extruders; }
    const tTextureTiles& TextureTiles(void) const { return m_textureTiles; }
    void TextureTilesSet(const tTextureTiles& inValue) { m_textureTiles=inValue; }
    // Writable reference for m_textureTiles
    tTextureTiles& TextureTilesWRef(void) { return m_textureTiles; }
    const tChunks& Chunks(void) const { return m_chunks; }
    void ChunksSet(const tChunks& inValue) { m_chunks=inValue; }
    // Writable reference for m_chunks
    tChunks& ChunksWRef(void) { return m_chunks; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } wiHO6BcqooUc9xVXHpfZBw
};

inline const MushMesh4Mesh::tCentroid&
MushMesh4Mesh::FaceCentroid(Mushware::U32 inFaceNum) const
{
    const tFace& faceRef = Face(inFaceNum);
    if (!faceRef.FaceCentroidValid())
    {
        FaceCentroidBuild(inFaceNum);
    }
    MUSHCOREASSERT(faceRef.FaceCentroidValid());
    return faceRef.FaceCentroid(); 
}

inline const MushMesh4Face::tFaceConnectivity&
MushMesh4Mesh::FaceConnectivity(Mushware::U32 inFaceNum) const
{
    const tFace& faceRef = Face(inFaceNum);
    if (!faceRef.FaceConnectivityValid())
    {
        FaceConnectivityBuild(inFaceNum);
    }
    MUSHCOREASSERT(faceRef.FaceConnectivityValid());
    return faceRef.FaceConnectivity(); 
}

inline const MushMesh4Chunk::tVertexList&
MushMesh4Mesh::ChunkUniqueVertexList(Mushware::U32 inChunkNum) const
{
    const tChunk& chunkRef = Chunk(inChunkNum);
    
    if (!chunkRef.UniqueVertexListValid())
    {
        ChunkUniqueVertexListBuild(inChunkNum);
    }
    MUSHCOREASSERT(chunkRef.UniqueVertexListValid());
    return chunkRef.UniqueVertexList(); 
}

inline const Mushware::tVal
MushMesh4Mesh::ChunkBoundingRadius(Mushware::U32 inChunkNum) const
{
    const tChunk& chunkRef = Chunk(inChunkNum);
    
    if (!chunkRef.BoundingRadiusValid())
    {
        ChunkBoundingRadiusBuild(inChunkNum);
    }
    MUSHCOREASSERT(chunkRef.BoundingRadiusValid());
    return chunkRef.BoundingRadius(); 
}

inline const MushMesh4Mesh::tCentroid&
MushMesh4Mesh::ChunkCentroid(Mushware::U32 inChunkNum) const
{
    const tChunk& chunkRef = Chunk(inChunkNum);
    
    if (!chunkRef.CentroidValid())
    {
        ChunkCentroidBuild(inChunkNum);
    }
    MUSHCOREASSERT(chunkRef.CentroidValid());
    return chunkRef.Centroid(); 
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
