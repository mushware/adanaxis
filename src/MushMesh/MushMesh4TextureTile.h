//%includeGuardStart {
#ifndef MUSHMESH4TEXTURETILE_H
#define MUSHMESH4TEXTURETILE_H
//%includeGuardStart } 4wz5X/AM+fLCctx4wJKPhA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4TextureTile.h
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
//%Header } Gpt6onVQ6MJeAFRAfWsomw
/*
 * $Id: MushMesh4TextureTile.h,v 1.2 2006/05/02 17:32:13 southa Exp $
 * $Log: MushMesh4TextureTile.h,v $
 * Revision 1.2  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.1  2006/05/01 17:39:00  southa
 * Texture generation
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshBox.h"
#include "MushMeshQuaternionPair.h"
#include "MushMeshVector.h"

//:generate virtual standard ostream xml1
class MushMesh4TextureTile : public MushcoreVirtualObject
{
public:
    typedef Mushware::t4Val tVertex;
	MushMesh4TextureTile() : m_sK(1), m_facetTransformValid(false) {}
    void Transform(Mushware::t4Val& outVec, const Mushware::t2Val& inVec) const; // Method 1
	void FacetToTexture(Mushware::t2Val& outVec, const Mushware::t4Val& inVec) const; // Method 2
	void TextureToFacet(Mushware::t4Val& outVec, const Mushware::t2Val& inVec) const; // Method 2
	
    void Make(void);

private:
    Mushware::t2BoxVal m_tileBox; //:readwrite	
    Mushware::U32 m_sourceFace; //:readwrite
	
	// Method 1 values
    Mushware::t2Val m_tileP0; //:readwrite
    Mushware::t2Val m_tileV0; //:readwrite
    Mushware::t2Val m_tileV1; //:readwrite
    Mushware::t4Val m_objectP0; //:readwrite
    Mushware::t4Val m_objectV0; //:readwrite
    Mushware::t4Val m_objectV1; //:readwrite
    
    Mushware::t4Val m_constant; //:readwrite
    Mushware::t4Val m_uFactor; //:readwrite
    Mushware::t4Val m_vFactor; //:readwrite

	// Method 2 values
	Mushware::tVal m_sK; //:readwrite

	Mushware::tQValPair m_qR; //:readwrite
	Mushware::t4Val m_vS; //:readwrite
	Mushware::t4Val m_vT; //:readwrite
	
	Mushware::tQValPair m_qRInverse; //:readwrite
	Mushware::t4Val m_vSInverse; //:readwrite
    // m_vTInverse can be achieved by subtracting m_vT
	
	bool m_facetTransformValid; //:readwrite
	
//%classPrototypes {
public:
    const Mushware::t2BoxVal& TileBox(void) const { return m_tileBox; }
    void TileBoxSet(const Mushware::t2BoxVal& inValue) { m_tileBox=inValue; }
    const Mushware::U32& SourceFace(void) const { return m_sourceFace; }
    void SourceFaceSet(const Mushware::U32& inValue) { m_sourceFace=inValue; }
    const Mushware::t2Val& TileP0(void) const { return m_tileP0; }
    void TileP0Set(const Mushware::t2Val& inValue) { m_tileP0=inValue; }
    const Mushware::t2Val& TileV0(void) const { return m_tileV0; }
    void TileV0Set(const Mushware::t2Val& inValue) { m_tileV0=inValue; }
    const Mushware::t2Val& TileV1(void) const { return m_tileV1; }
    void TileV1Set(const Mushware::t2Val& inValue) { m_tileV1=inValue; }
    const Mushware::t4Val& ObjectP0(void) const { return m_objectP0; }
    void ObjectP0Set(const Mushware::t4Val& inValue) { m_objectP0=inValue; }
    const Mushware::t4Val& ObjectV0(void) const { return m_objectV0; }
    void ObjectV0Set(const Mushware::t4Val& inValue) { m_objectV0=inValue; }
    const Mushware::t4Val& ObjectV1(void) const { return m_objectV1; }
    void ObjectV1Set(const Mushware::t4Val& inValue) { m_objectV1=inValue; }
    const Mushware::t4Val& Constant(void) const { return m_constant; }
    void ConstantSet(const Mushware::t4Val& inValue) { m_constant=inValue; }
    const Mushware::t4Val& UFactor(void) const { return m_uFactor; }
    void UFactorSet(const Mushware::t4Val& inValue) { m_uFactor=inValue; }
    const Mushware::t4Val& VFactor(void) const { return m_vFactor; }
    void VFactorSet(const Mushware::t4Val& inValue) { m_vFactor=inValue; }
    const Mushware::tVal& SK(void) const { return m_sK; }
    void SKSet(const Mushware::tVal& inValue) { m_sK=inValue; }
    const Mushware::tQValPair& QR(void) const { return m_qR; }
    void QRSet(const Mushware::tQValPair& inValue) { m_qR=inValue; }
    const Mushware::t4Val& VS(void) const { return m_vS; }
    void VSSet(const Mushware::t4Val& inValue) { m_vS=inValue; }
    const Mushware::t4Val& VT(void) const { return m_vT; }
    void VTSet(const Mushware::t4Val& inValue) { m_vT=inValue; }
    const Mushware::tQValPair& QRInverse(void) const { return m_qRInverse; }
    void QRInverseSet(const Mushware::tQValPair& inValue) { m_qRInverse=inValue; }
    const Mushware::t4Val& VSInverse(void) const { return m_vSInverse; }
    void VSInverseSet(const Mushware::t4Val& inValue) { m_vSInverse=inValue; }
    const bool& FacetTransformValid(void) const { return m_facetTransformValid; }
    void FacetTransformValidSet(const bool& inValue) { m_facetTransformValid=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } M6CgAHrum31XdyHIhMx8ZA
};

inline void
MushMesh4TextureTile::Transform(Mushware::t4Val& outVec, const Mushware::t2Val& inVec) const
{
    outVec = m_constant + inVec.X() * m_uFactor + inVec.Y() * m_vFactor;
}

inline void
MushMesh4TextureTile::FacetToTexture(Mushware::t2Val& outVec, const Mushware::t4Val& inVec) const
{
	MUSHCOREASSERT(m_facetTransformValid);
	Mushware::t4Val rotVec = m_qR.RotatedVector(inVec);
	rotVec *= m_vS;
	rotVec += m_vT;
	outVec = Mushware::t2Val(rotVec.X(), rotVec.Y());
}

inline void
MushMesh4TextureTile::TextureToFacet(Mushware::t4Val& outVec, const Mushware::t2Val& inVec) const
{
	MUSHCOREASSERT(m_facetTransformValid);
	outVec = Mushware::t4Val(inVec.X(), inVec.Y(), 0, 0);
	outVec -= m_vT;
	outVec *= m_vSInverse;
	outVec = m_qRInverse.RotatedVector(outVec);	
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMesh4TextureTile& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } aVpAwrQ1WVaRKrZg9TxyVQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
