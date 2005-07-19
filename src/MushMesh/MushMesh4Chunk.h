//%includeGuardStart {
#ifndef MUSHMESH4CHUNK_H
#define MUSHMESH4CHUNK_H
//%includeGuardStart } uXkWMjM5i2YbVh8KZWQ5VQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Chunk.h
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
//%Header } YGouJviALgm2Aa1vRXc28Q
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

#include "MushMeshVector.h"

//:generate virtual standard ostream xml1
class MushMesh4Chunk : public MushcoreVirtualObject
{
public:
    typedef std::vector<Mushware::U32> tVertexList;
    typedef std::vector<Mushware::U32> tFaceList;
    
    MushMesh4Chunk();
    virtual ~MushMesh4Chunk() {}
    
    virtual void AllTouch(void); 
    virtual void VerticesTouch(void); 
    
    // Read access to mutable elements
    const tVertexList& UniqueVertexList(void) const;    
    Mushware::tVal BoundingRadius(void) const;
    const Mushware::t4Val& Centroid(void) const;
        
    // Write access to mutable elements
    void UniqueVertexListSet(const tVertexList& inValue) const { m_uniqueVertexList=inValue; m_uniqueVertexListValid=true; }
    // Writable reference for m_uniqueVertexList
    tVertexList& UniqueVertexListWRef(void) const { return m_uniqueVertexList; }    
    void BoundingRadiusSet(const Mushware::tVal& inValue) const { m_boundingRadius=inValue; m_boundingRadiusValid=true; }
    void CentroidSet(const Mushware::t4Val& inValue) const { m_centroid=inValue; m_centroidValid=true; }
    void UniqueVertexListValidSet(bool inValue) const { m_uniqueVertexListValid=inValue; }
    
private:
    // Minimal data
    Mushware::U32 m_boundingType;
    tFaceList m_faceList; //:readwrite :wref
    
    // Dynamic data
    mutable tVertexList m_uniqueVertexList;
    mutable Mushware::tVal m_boundingRadius;
    mutable Mushware::t4Val m_centroid;
    
    mutable bool m_uniqueVertexListValid; //:read
    mutable bool m_boundingRadiusValid; //:read
    mutable bool m_centroidValid; //:read
    
//%classPrototypes {
public:
    const tFaceList& FaceList(void) const { return m_faceList; }
    void FaceListSet(const tFaceList& inValue) { m_faceList=inValue; }
    // Writable reference for m_faceList
    tFaceList& FaceListWRef(void) { return m_faceList; }
    const bool& UniqueVertexListValid(void) const { return m_uniqueVertexListValid; }
    const bool& BoundingRadiusValid(void) const { return m_boundingRadiusValid; }
    const bool& CentroidValid(void) const { return m_centroidValid; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } xOJQ1QLDMomDghplW5AJWg
};


inline const MushMesh4Chunk::tVertexList&
MushMesh4Chunk::UniqueVertexList(void) const
{
    if (!m_uniqueVertexListValid)
    {
        throw MushcoreRequestFail("Unique vertex list not valid (ChunkUniqueVertexList() must be called on mesh object)");
    }
    return m_uniqueVertexList;
}

inline Mushware::tVal
MushMesh4Chunk::BoundingRadius(void) const
{
    if (!m_boundingRadiusValid)
    {
        throw MushcoreRequestFail("Bounding radius not valid (ChunkBoundingRadius() must be called on mesh object)");
    }
    return m_boundingRadius;
}

inline const Mushware::t4Val&
MushMesh4Chunk::Centroid(void) const
{
    if (!m_centroidValid)
    {
        throw MushcoreRequestFail("Chunk centroid not valid (ChunkCentroid() must be called on mesh object)");
    }
    return m_centroid;
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMesh4Chunk& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } c9WqEWmOVe5lUyFPrbKHVw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
