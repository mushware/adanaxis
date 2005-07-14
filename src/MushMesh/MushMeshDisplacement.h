//%includeGuardStart {
#ifndef MUSHMESHDISPLACEMENT_H
#define MUSHMESHDISPLACEMENT_H
//%includeGuardStart } v0vcp/ttab4sGjtSWLtmZQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshDisplacement.h
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
//%Header } NsK1vgnlKsr599coHkcjRA
/*
 * $Id: MushMeshDisplacement.h,v 1.1 2005/07/12 20:39:05 southa Exp $
 * $Log: MushMeshDisplacement.h,v $
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshQuaternionPair.h"
#include "MushMeshVector.h"

//:generate virtual standard ostream xml1
class MushMeshDisplacement : public MushcoreVirtualObject
{
public:
    MushMeshDisplacement() {}
    MushMeshDisplacement(const Mushware::t4Val& inOffset, const Mushware::tQValPair& inRotation, Mushware::tVal inScale) :
        m_offset(inOffset), m_rotation(inRotation), m_scale(inScale) {}
    
    void ToIdentitySet(void) { m_rotation.ToRotationIdentitySet(); m_offset.ToAdditiveIdentitySet(); m_scale = 1;}
    
private:
    Mushware::t4Val m_offset; //:readwrite :wref
    Mushware::tQValPair m_rotation; //:readwrite :wref
    Mushware::tVal m_scale; //:readwrite :wref
    
//%classPrototypes {
public:
    const Mushware::t4Val& Offset(void) const { return m_offset; }
    void OffsetSet(const Mushware::t4Val& inValue) { m_offset=inValue; }
    // Writable reference for m_offset
    Mushware::t4Val& OffsetWRef(void) { return m_offset; }
    const Mushware::tQValPair& Rotation(void) const { return m_rotation; }
    void RotationSet(const Mushware::tQValPair& inValue) { m_rotation=inValue; }
    // Writable reference for m_rotation
    Mushware::tQValPair& RotationWRef(void) { return m_rotation; }
    const Mushware::tVal& Scale(void) const { return m_scale; }
    void ScaleSet(const Mushware::tVal& inValue) { m_scale=inValue; }
    // Writable reference for m_scale
    Mushware::tVal& ScaleWRef(void) { return m_scale; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } YsnPi/1DwXAZh1VRc8P5KA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshDisplacement& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 2e6DCxwmnaulAhEB2fj4Zg

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
