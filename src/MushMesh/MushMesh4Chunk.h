//%includeGuardStart {
#ifndef MUSHMESH4CHUNK_H
#define MUSHMESH4CHUNK_H
//%includeGuardStart } uXkWMjM5i2YbVh8KZWQ5VQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Chunk.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } wOnKTilEizgjG7dtAe6sjA
/*
 * $Id: MushMesh4Chunk.h,v 1.3 2006/06/01 15:39:28 southa Exp $
 * $Log: MushMesh4Chunk.h,v $
 * Revision 1.3  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/27 18:09:10  southa
 * Collision checking
 *
 * Revision 1.1  2005/07/19 13:44:26  southa
 * MushMesh4Chunk work
 *
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
    
    void AllTouch(void); // Called from constructor
    void VerticesTouch(void); // Called from constructor
    
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
