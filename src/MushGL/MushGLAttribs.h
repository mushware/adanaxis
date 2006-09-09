//%includeGuardStart {
#ifndef MUSHGLATTRIBS_H
#define MUSHGLATTRIBS_H
//%includeGuardStart } XdRMlV8XPEzwrMbnmgkNeA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLAttribs.h
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
//%Header } ajCMNJ9+nE9yqrSF4kKMGQ
/*
 * $Id: MushGLAttribs.h,v 1.1 2006/09/07 16:38:50 southa Exp $
 * $Log: MushGLAttribs.h,v $
 * Revision 1.1  2006/09/07 16:38:50  southa
 * Vertex shader
 *
 */

#include "MushGLStandard.h"

#include "MushGLProjection.h"

class MushGLShader;

//:generate standard ostream xml1
class MushGLAttribs : public MushcoreVirtualObject
{
public:
    typedef Mushware::t4x4o4Val tMattress;
    typedef std::vector<Mushware::t4GLVal> tColours;

private:
    MushGLProjection m_projection; //:readwrite :wref
    tMattress m_view; //:readwrite :wref
    tMattress m_model; //:readwrite :wref
    tColours m_colours; //:readwrite :wref
    
//%classPrototypes {
public:
    const MushGLProjection& Projection(void) const { return m_projection; }
    void ProjectionSet(const MushGLProjection& inValue) { m_projection=inValue; }
    // Writable reference for m_projection
    MushGLProjection& ProjectionWRef(void) { return m_projection; }
    const tMattress& View(void) const { return m_view; }
    void ViewSet(const tMattress& inValue) { m_view=inValue; }
    // Writable reference for m_view
    tMattress& ViewWRef(void) { return m_view; }
    const tMattress& Model(void) const { return m_model; }
    void ModelSet(const tMattress& inValue) { m_model=inValue; }
    // Writable reference for m_model
    tMattress& ModelWRef(void) { return m_model; }
    const tColours& Colours(void) const { return m_colours; }
    void ColoursSet(const tColours& inValue) { m_colours=inValue; }
    // Writable reference for m_colours
    tColours& ColoursWRef(void) { return m_colours; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } oiazj5eBax7f0V6xGqVo6g
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLAttribs& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } KCi2RnXZ9DkdpyiukxlACg

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
