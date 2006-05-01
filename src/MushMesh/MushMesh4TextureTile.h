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
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

#include "MushMeshBox.h"
#include "MushMeshVector.h"

//:generate virtual standard ostream xml1
class MushMesh4TextureTile : public MushcoreVirtualObject
{
public:
    typedef Mushware::t4Val tVertex;
    void Transform(Mushware::t4Val& outVec, const Mushware::t2Val& inVec) const;
    void Make(void);
    
private:
    Mushware::t2BoxVal m_tileBox; //:readwrite
    Mushware::t2Val m_tileP0; //:readwrite
    Mushware::t2Val m_tileV0; //:readwrite
    Mushware::t2Val m_tileV1; //:readwrite
    Mushware::t4Val m_objectP0; //:readwrite
    Mushware::t4Val m_objectV0; //:readwrite
    Mushware::t4Val m_objectV1; //:readwrite
    
    Mushware::t4Val m_constant; //:readwrite
    Mushware::t4Val m_uFactor; //:readwrite
    Mushware::t4Val m_vFactor; //:readwrite
//%classPrototypes {
public:
    const Mushware::t2BoxVal& TileBox(void) const { return m_tileBox; }
    void TileBoxSet(const Mushware::t2BoxVal& inValue) { m_tileBox=inValue; }
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } OvMWGt5Ms+1X9uhA4Db41A
};

inline void
MushMesh4TextureTile::Transform(Mushware::t4Val& outVec, const Mushware::t2Val& inVec) const
{
    outVec = m_constant + inVec.X() * m_uFactor + inVec.Y() * m_vFactor;
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
