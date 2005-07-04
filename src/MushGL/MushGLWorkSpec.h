//%includeGuardStart {
#ifndef MUSHGLWORKSPEC_H
#define MUSHGLWORKSPEC_H
//%includeGuardStart } 4IYGzsr2PcjyQ9a0eYSvXA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLWorkSpec.h
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
//%Header } Tcvr8t/02ON4PA2mIz92sQ
/*
 * $Id$
 * $Log$
 */

#include "MushGLStandard.h"

#include "MushGLBuffers.h"

//:generate virtual standard ostream xml1
class MushGLWorkSpec : public MushcoreVirtualObject
{
public:
    enum
    {
        kRenderTypeLines = GL_LINES
    };
    
    MushGLWorkSpec() : m_renderType(0) {}
    virtual ~MushGLWorkSpec() {}

    void Execute(MushGLBuffers& ioBuffers);
    
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
