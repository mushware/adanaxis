//%includeGuardStart {
#ifndef MUSHGLWORKSPEC_H
#define MUSHGLWORKSPEC_H
//%includeGuardStart } 4IYGzsr2PcjyQ9a0eYSvXA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLWorkSpec.h
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
//%Header } d0PLtMuUJJgR2LEeb5ey+g
/*
 * $Id: MushGLWorkSpec.h,v 1.3 2005/09/05 17:14:23 southa Exp $
 * $Log: MushGLWorkSpec.h,v $
 * Revision 1.3  2005/09/05 17:14:23  southa
 * Solid rendering
 *
 * Revision 1.2  2005/08/31 23:57:27  southa
 * Texture coordinate work
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLStandard.h"

#include "MushGLBuffers.h"

//:generate virtual standard ostream xml1
class MushGLWorkSpec : public MushcoreVirtualObject
{
public:
    enum
    {
        kRenderTypeLines = GL_LINES,
        kRenderTypeTriangles = GL_TRIANGLES,
    };
    
    MushGLWorkSpec() : m_renderType(0) {}
    virtual ~MushGLWorkSpec() {}

    void Execute(MushGLBuffers::tDataRef& ioDataRef, MushGLBuffers::tSharedDataRef& ioSharedDataRef);
    
private:
    Mushware::U32 m_renderType; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::U32& RenderType(void) const { return m_renderType; }
    void RenderTypeSet(const Mushware::U32& inValue) { m_renderType=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } PSOTfAbS2nVFuLJMprN9Yg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLWorkSpec& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Pml5Trl+jExBeyd0Uu8qJg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
