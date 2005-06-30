//%includeGuardStart {
#ifndef MUSHMESH4FACE_H
#define MUSHMESH4FACE_H
//%includeGuardStart } 514KzcB1qGtIcv3av3g+kw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Face.h
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
//%Header } 5yE/wZtm0/nEX6N7oHMfOA
/*
 * $Id: MushMesh4Face.h,v 1.1 2005/06/30 12:04:55 southa Exp $
 * $Log: MushMesh4Face.h,v $
 * Revision 1.1  2005/06/30 12:04:55  southa
 * Mesh work
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshFace.h"
#include "MushMeshMaterialRef.h"
#include "MushMeshVector.h"

//:xml1base MushMeshFace
//:generate virtual standard ostream xml1
class MushMesh4Face : public MushMeshFace
{
public:
    typedef std::vector<Mushware::U32> tVertexList;
    typedef std::vector<Mushware::U32> tVertexGroupSize;
    typedef std::vector<Mushware::U32> tTexCoordList;
    
    enum
    {
        kFaceTypeInvalid,
        kFaceTypeNone,
        kFaceTypeCubic
    };
    
    MushMesh4Face();
    virtual ~MushMesh4Face();
    
private:
    // Minimal representation
    Mushware::U32 m_faceType; //:readwrite
    tVertexList m_vertexList; //:readwrite :wref
    tVertexGroupSize m_vertexGroupSize; //:readwrite :wref
    tTexCoordList m_texCoordList; //:readwrite :wref
    MushMeshMaterialRef m_faceMaterialRef; //:readwrite
    std::vector<Mushware::U8> m_edgeSmoothness; //:readwrite
    
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
    const MushMeshMaterialRef& FaceMaterialRef(void) const { return m_faceMaterialRef; }
    void FaceMaterialRefSet(const MushMeshMaterialRef& inValue) { m_faceMaterialRef=inValue; }
    const std::vector<Mushware::U8>& EdgeSmoothness(void) const { return m_edgeSmoothness; }
    void EdgeSmoothnessSet(const std::vector<Mushware::U8>& inValue) { m_edgeSmoothness=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } EJTo+TOmP2VcoOC4KEqFbQ
};
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
