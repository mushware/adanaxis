//%includeGuardStart {
#ifndef MUSHMESH4TEXTURETILE_H
#define MUSHMESH4TEXTURETILE_H
//%includeGuardStart } 4wz5X/AM+fLCctx4wJKPhA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4TextureTile.h
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
//%Header } El3vYxHWgyUa35uKJ9pxug
/*
 * $Id: MushMesh4TextureTile.h,v 1.5 2006/07/18 16:58:38 southa Exp $
 * $Log: MushMesh4TextureTile.h,v $
 * Revision 1.5  2006/07/18 16:58:38  southa
 * Texture fixes
 *
 * Revision 1.4  2006/06/09 21:07:13  southa
 * Tiled skin generation
 *
 * Revision 1.3  2006/06/09 11:43:03  southa
 * Facet to texture transformation
 *
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
	MushMesh4TextureTile();
    void Transform(Mushware::t4Val& outVec, const Mushware::t2Val& inVec) const; // Method 1
	void FacetToTexture(Mushware::t2Val& outVec, const Mushware::t4Val& inVec) const; // Method 2
	void TextureToFacet(Mushware::t4Val& outVec, const Mushware::t2Val& inVec) const; // Method 2
	
    void Make(void);

private:
    Mushware::t2BoxVal m_tileBox; //:readwrite	
    Mushware::U32 m_sourceFaceNum; //:readwrite
    Mushware::U32 m_sourceFacetNum; //:readwrite
	
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
    const Mushware::U32& SourceFaceNum(void) const { return m_sourceFaceNum; }
    void SourceFaceNumSet(const Mushware::U32& inValue) { m_sourceFaceNum=inValue; }
    const Mushware::U32& SourceFacetNum(void) const { return m_sourceFacetNum; }
    void SourceFacetNumSet(const Mushware::U32& inValue) { m_sourceFacetNum=inValue; }
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
//%classPrototypes } MIs3j/euzdiuzoKcWiDYMA
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
