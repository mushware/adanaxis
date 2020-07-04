//%includeGuardStart {
#ifndef MUSHMESH4FACE_H
#define MUSHMESH4FACE_H
//%includeGuardStart } 514KzcB1qGtIcv3av3g+kw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Face.h
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
//%Header } ieO1vboD2t6A8cnZRTBfbQ
/*
 * $Id: MushMesh4Face.h,v 1.10 2006/12/18 15:39:35 southa Exp $
 * $Log: MushMesh4Face.h,v $
 * Revision 1.10  2006/12/18 15:39:35  southa
 * Palette changes
 *
 * Revision 1.9  2006/06/19 15:57:17  southa
 * Materials
 *
 * Revision 1.8  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 * Revision 1.6  2005/07/27 18:09:10  southa
 * Collision checking
 *
 * Revision 1.5  2005/07/13 20:35:48  southa
 * Extrusion work
 *
 * Revision 1.4  2005/07/13 16:45:05  southa
 * Extrusion work
 *
 * Revision 1.3  2005/07/12 20:39:04  southa
 * Mesh library work
 *
 * Revision 1.2  2005/06/30 12:34:59  southa
 * Mesh and source conditioner work
 *
 * Revision 1.1  2005/06/30 12:04:55  southa
 * Mesh work
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshFace.h"
#include "MushMesh4LinkFaceFace.h"
#include "MushMeshVector.h"

//:xml1base MushMeshFace
//:generate virtual standard ostream xml1
class MushMesh4Face : public MushMeshFace
{
public:
    typedef std::vector<Mushware::U32> tVertexList;
    typedef std::vector<Mushware::U32> tVertexGroupSize;
    typedef std::vector<Mushware::U32> tTexCoordList;
    typedef MushMesh4LinkFaceFace tFaceConnection;
    typedef std::vector<tFaceConnection> tFaceConnectivity;
    typedef std::vector<Mushware::U32> tVertexConnection;
    typedef std::map<Mushware::U32, tVertexConnection> tVertexConnectivity;
    typedef std::map<Mushware::U32, Mushware::U32> tExtrusionMap;
    typedef std::pair<Mushware::U32, Mushware::U32> tTransform;
    typedef std::vector<tTransform> tTransformList;
    
    enum
    {
        kFaceTypeInvalid,
        kFaceTypeNone,
        kFaceTypeCubic
    };
    
    MushMesh4Face();
    virtual ~MushMesh4Face();
    
    void VerticesTouch(void); // Called from constructor
    void AllTouch(void); // Called from constructor
    void Purge(void);
    
    void FacetLimitsGet(Mushware::U32& outStart, Mushware::U32& outEnd, Mushware::U32 inFacetNum) const;
    bool ConnectedVertexInFacetFind(Mushware::U32& outNum, Mushware::U32 inFacetNum, Mushware::U32 inVertNum) const;
    Mushware::U32 NumFacets(void) const { return m_vertexGroupSize.size(); }

    // Read access for mutable elements
    const tVertexList& UniqueVertexList(void) const;
    const Mushware::t4Val& FaceCentroid(void) const;
    const tFaceConnectivity& FaceConnectivity(void) const;
    const tVertexConnectivity& VertexConnectivity(void) const;
    
    // Write access for mutable elements
    void FaceCentroidSet(const Mushware::t4Val& inValue) const { m_faceCentroid=inValue; m_faceCentroidValid = true; }
    void BoundingRadiusSet(const Mushware::tVal& inValue) const { m_boundingRadius=inValue; }
    void BoundingRadiusValidSet(const bool inValue) const { m_boundingRadiusValid=inValue; }
    void FaceConnectivityValidSet(const bool inValue) const { m_faceConnectivityValid=inValue; }
    tFaceConnectivity& FaceConnectivityWRef(void) const { return m_faceConnectivity; }
    tVertexConnectivity& VertexConnectivityWRef(void) const { return m_vertexConnectivity; }

protected:
    void UniqueVertexListBuild(void) const;
    void VertexConnectivityBuild(void) const;
    
private:
    // Minimal representation
    Mushware::U32 m_faceType; //:readwrite
    tVertexList m_vertexList; //:readwrite :wref
    tVertexGroupSize m_vertexGroupSize; //:readwrite :wref
    tTexCoordList m_texCoordList; //:readwrite :wref
	Mushware::U32 m_materialNum; //:readwrite
    std::vector<Mushware::U8> m_edgeSmoothness; //:readwrite
    bool m_internal; //:readwrite
    
    // Derived representation
    tExtrusionMap m_extrusionMap; //:read :wref
    std::vector<Mushware::U32> m_extrudedFaces; //:read :wref
    tTransformList m_extrusionTransformList; //:read :wref
    
    mutable tVertexList m_uniqueVertexList;
    mutable Mushware::t4Val m_faceCentroid;
    mutable Mushware::tVal m_boundingRadius; //:read
    mutable tFaceConnectivity m_faceConnectivity;
    mutable tVertexConnectivity m_vertexConnectivity; 
    mutable bool m_uniqueVertexListValid; //:read
    mutable bool m_faceCentroidValid; //:read
    mutable bool m_boundingRadiusValid; //:read
    mutable bool m_faceConnectivityValid; //:read
    mutable bool m_vertexConnectivityValid; //:read
    mutable Mushware::U32 m_numVertexConnections; //:read
    
//%classPrototypes {
public:
    const Mushware::U32& FaceType(void) const { return m_faceType; }
    void FaceTypeSet(const Mushware::U32& inValue) { m_faceType=inValue; }
    const tVertexList& VertexList(void) const { return m_vertexList; }
    void VertexListSet(const tVertexList& inValue) { m_vertexList=inValue; }
    // Writable reference for m_vertexList
    tVertexList& VertexListWRef(void) { return m_vertexList; }
    const tVertexGroupSize& VertexGroupSize(void) const { return m_vertexGroupSize; }
    void VertexGroupSizeSet(const tVertexGroupSize& inValue) { m_vertexGroupSize=inValue; }
    // Writable reference for m_vertexGroupSize
    tVertexGroupSize& VertexGroupSizeWRef(void) { return m_vertexGroupSize; }
    const tTexCoordList& TexCoordList(void) const { return m_texCoordList; }
    void TexCoordListSet(const tTexCoordList& inValue) { m_texCoordList=inValue; }
    // Writable reference for m_texCoordList
    tTexCoordList& TexCoordListWRef(void) { return m_texCoordList; }
    const Mushware::U32& MaterialNum(void) const { return m_materialNum; }
    void MaterialNumSet(const Mushware::U32& inValue) { m_materialNum=inValue; }
    const std::vector<Mushware::U8>& EdgeSmoothness(void) const { return m_edgeSmoothness; }
    void EdgeSmoothnessSet(const std::vector<Mushware::U8>& inValue) { m_edgeSmoothness=inValue; }
    const bool& Internal(void) const { return m_internal; }
    void InternalSet(const bool& inValue) { m_internal=inValue; }
    const tExtrusionMap& ExtrusionMap(void) const { return m_extrusionMap; }
    // Writable reference for m_extrusionMap
    tExtrusionMap& ExtrusionMapWRef(void) { return m_extrusionMap; }
    const std::vector<Mushware::U32>& ExtrudedFaces(void) const { return m_extrudedFaces; }
    // Writable reference for m_extrudedFaces
    std::vector<Mushware::U32>& ExtrudedFacesWRef(void) { return m_extrudedFaces; }
    const tTransformList& ExtrusionTransformList(void) const { return m_extrusionTransformList; }
    // Writable reference for m_extrusionTransformList
    tTransformList& ExtrusionTransformListWRef(void) { return m_extrusionTransformList; }
    const Mushware::tVal& BoundingRadius(void) const { return m_boundingRadius; }
    const bool& UniqueVertexListValid(void) const { return m_uniqueVertexListValid; }
    const bool& FaceCentroidValid(void) const { return m_faceCentroidValid; }
    const bool& BoundingRadiusValid(void) const { return m_boundingRadiusValid; }
    const bool& FaceConnectivityValid(void) const { return m_faceConnectivityValid; }
    const bool& VertexConnectivityValid(void) const { return m_vertexConnectivityValid; }
    const Mushware::U32& NumVertexConnections(void) const { return m_numVertexConnections; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } oBd8y8M4v4t77bAPV/mKxA
};

inline const MushMesh4Face::tVertexList&
MushMesh4Face::UniqueVertexList(void) const
{
    if (!m_uniqueVertexListValid)
    {
        UniqueVertexListBuild();
    }
    MUSHCOREASSERT(m_uniqueVertexListValid);
    return m_uniqueVertexList;
}

inline const MushMesh4Face::tVertexConnectivity&
MushMesh4Face::VertexConnectivity(void) const
{
    if (!m_vertexConnectivityValid)
    {
        VertexConnectivityBuild();
    }
    MUSHCOREASSERT(m_vertexConnectivityValid);
    return m_vertexConnectivity;
}


inline const Mushware::t4Val&
MushMesh4Face::FaceCentroid(void) const
{
    if (!m_faceCentroidValid)
    {
        throw MushcoreRequestFail("Face centroid not valid (FaceCentroid() must be called on mesh object)");
    }
    return m_faceCentroid;
}

inline const MushMesh4Face::tFaceConnectivity&
MushMesh4Face::FaceConnectivity(void) const
{
    if (!m_faceConnectivityValid)
    {
        throw MushcoreRequestFail("Face connectivity not valid (FaceConnectivity() must be called on mesh object)");
    }
    return m_faceConnectivity;
}


//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMesh4Face& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } CyIr8dEwXRn2j4Z+XVMmgQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
