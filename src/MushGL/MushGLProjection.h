//%includeGuardStart {
#ifndef MUSHGLPROJECTION_H
#define MUSHGLPROJECTION_H
//%includeGuardStart } T38RsetZbekqaRFJwoUBnw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLProjection.h
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
//%Header } A82t3KCFKhG+wPnlmwzf2Q
/*
 * $Id$
 * $Log$
 */

#include "MushGLStandard.h"

//:generate virtual standard ostream xml1
class MushGLProjection : public MushcoreVirtualObject
{
public:
    virtual ~MushGLProjection() {}
    
    virtual Mushware::tVal FValueFromViewHalfRadians(Mushware::tVal inRadians);
    virtual void FromFAspectNearFarMake(Mushware::tVal inF, Mushware::tVal inAspect, Mushware::tVal inNear, Mushware::tVal inFar);
    
    void TransformVector(Mushware::t4Val& ioVec) const;
    Mushware::t4Val TransformedVector(const Mushware::t4Val& ioVec) const;
    
private:
    Mushware::t4x4Val m_matrix; //:readwrite :wref
    Mushware::t4Val m_offset; //:readwrite :wref
//%classPrototypes {
public:
    const Mushware::t4x4Val& Matrix(void) const { return m_matrix; }
    void MatrixSet(const Mushware::t4x4Val& inValue) { m_matrix=inValue; }
    // Writable reference for m_matrix
    Mushware::t4x4Val& MatrixWRef(void) { return m_matrix; }
    const Mushware::t4Val& Offset(void) const { return m_offset; }
    void OffsetSet(const Mushware::t4Val& inValue) { m_offset=inValue; }
    // Writable reference for m_offset
    Mushware::t4Val& OffsetWRef(void) { return m_offset; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } ivFZlHEwUvzALC3RHQLQzg
};

inline void
MushGLProjection::TransformVector(Mushware::t4Val& ioVec) const
{
    ioVec = m_matrix * ioVec + m_offset;
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
