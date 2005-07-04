//%includeGuardStart {
#ifndef MUSHGLJOBRENDER_H
#define MUSHGLJOBRENDER_H
//%includeGuardStart } 7yyXQ8mlHYTGywQ4zBKQag
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLJobRender.h
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
//%Header } +jbVM6qu2ll8Cr1eMnWiVw
/*
 * $Id$
 * $Log$
 */

#include "MushGLStandard.h"

#include "MushGLBuffers.h"
#include "MushGLJob.h"
#include "MushGLWorkSpec.h"

//:xml1base MushGLJob
//:generate virtual nocopy standard ostream xml1
class MushGLJobRender : public MushGLJob
{
public:
    MushGLJobRender() : MushGLJob() {}
    virtual ~MushGLJobRender();
    
    virtual void Execute(void);
    virtual MushGLWorkSpec& WorkSpecNew(void);
    
private:
    MushGLJobRender(const MushGLJobRender&) {}
    
    std::vector<MushGLWorkSpec *> m_workSpecs; //:read
    
    MushGLBuffers::tDataRef m_buffersRef; //:readwrite
    
//%classPrototypes {
public:
    const std::vector<MushGLWorkSpec *>& WorkSpecs(void) const { return m_workSpecs; }
    const MushGLBuffers::tDataRef& BuffersRef(void) const { return m_buffersRef; }
    void BuffersRefSet(const MushGLBuffers::tDataRef& inValue) { m_buffersRef=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 61cy2U7Ak1vG33247TP3Sw
};

inline MushGLWorkSpec&
MushGLJobRender::WorkSpecNew(void)
{
    MushGLWorkSpec *pWorkSpec = new MushGLWorkSpec;
    m_workSpecs.push_back(pWorkSpec);
    return *pWorkSpec;
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLJobRender& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } j3L9GPvFPslS/sWMeaIRIQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
