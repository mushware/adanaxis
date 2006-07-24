//%includeGuardStart {
#ifndef MUSHGLPROJECTION_H
#define MUSHGLPROJECTION_H
//%includeGuardStart } T38RsetZbekqaRFJwoUBnw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLProjection.h
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
//%Header } i38koAQPddGZTaMyB0d/+w
/*
 * $Id: MushGLProjection.h,v 1.4 2006/06/01 15:39:18 southa Exp $
 * $Log: MushGLProjection.h,v $
 * Revision 1.4  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.1  2005/07/01 10:03:30  southa
 * Projection work
 *
 */

#include "MushGLStandard.h"

//:generate virtual standard ostream xml1
class MushGLProjection : public MushcoreVirtualObject
{
public:
    MushGLProjection() : m_viewHalfRadians(0) {}
    virtual ~MushGLProjection() {}
    
    virtual void FromAspectNearFarMake(Mushware::tVal inAspect, Mushware::tVal inNear, Mushware::tVal inFar);
    virtual Mushware::tVal FValue(void) const { return FValueFromViewHalfRadians(m_viewHalfRadians); }

    void TransformVector(Mushware::t4Val& ioVec) const;
    Mushware::t4Val TransformedVector(const Mushware::t4Val& ioVec) const;

protected:
    virtual Mushware::tVal FValueFromViewHalfRadians(Mushware::tVal inRadians) const;

private:
    Mushware::tVal m_viewHalfRadians; //:readwrite
    Mushware::t4x4o4Val m_mattress; //:readwrite :wref
    Mushware::t4Val m_clipMin; //:read
    Mushware::t4Val m_clipMax; //:read
    Mushware::t4Val m_boundingRadiusFactor; //:read
    
//%classPrototypes {
public:
    const Mushware::tVal& ViewHalfRadians(void) const { return m_viewHalfRadians; }
    void ViewHalfRadiansSet(const Mushware::tVal& inValue) { m_viewHalfRadians=inValue; }
    const Mushware::t4x4o4Val& Mattress(void) const { return m_mattress; }
    void MattressSet(const Mushware::t4x4o4Val& inValue) { m_mattress=inValue; }
    // Writable reference for m_mattress
    Mushware::t4x4o4Val& MattressWRef(void) { return m_mattress; }
    const Mushware::t4Val& ClipMin(void) const { return m_clipMin; }
    const Mushware::t4Val& ClipMax(void) const { return m_clipMax; }
    const Mushware::t4Val& BoundingRadiusFactor(void) const { return m_boundingRadiusFactor; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } jNBLCPpor/KH0xzJp5iHWA
};

inline void
MushGLProjection::TransformVector(Mushware::t4Val& ioVec) const
{
    ioVec = m_mattress * ioVec;
}

inline Mushware::t4Val
MushGLProjection::TransformedVector(const Mushware::t4Val& ioVec) const
{
    Mushware::t4Val retVal(ioVec);
    TransformVector(retVal);
    return retVal;
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLProjection& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } sH3eACuAhXVY7WwCWEwifg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
