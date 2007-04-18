//%includeGuardStart {
#ifndef MUSHGLCAMERA_H
#define MUSHGLCAMERA_H
//%includeGuardStart } FKjlErIhB4R6UWU6iP8Vxg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLCamera.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } lP7ipzxeQTl9DZ0bOIkg3Q
/*
 * $Id: MushGLCamera.h,v 1.1 2006/07/24 18:46:49 southa Exp $
 * $Log: MushGLCamera.h,v $
 * Revision 1.1  2006/07/24 18:46:49  southa
 * Depth sorting
 *
 */

#include "MushGLStandard.h"

#include "MushGLProjection.h"

//:generate virtual standard ostream xml1
class MushGLCamera : public MushcoreVirtualObject
{
public:
    virtual ~MushGLCamera();
    
private:
    MushMeshPosticity m_post; //:readwrite :wref
    MushGLProjection m_projection; //:readwrite :wref
//%classPrototypes {
public:
    const MushMeshPosticity& Post(void) const { return m_post; }
    void PostSet(const MushMeshPosticity& inValue) { m_post=inValue; }
    // Writable reference for m_post
    MushMeshPosticity& PostWRef(void) { return m_post; }
    const MushGLProjection& Projection(void) const { return m_projection; }
    void ProjectionSet(const MushGLProjection& inValue) { m_projection=inValue; }
    // Writable reference for m_projection
    MushGLProjection& ProjectionWRef(void) { return m_projection; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } b0TYGAO+rwIrQB2rMp5jQQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLCamera& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } t7NpPqMwrm6Qf7QTsZXiNg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
