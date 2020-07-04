//%includeGuardStart {
#ifndef MUSHGLJOBRENDER_H
#define MUSHGLJOBRENDER_H
//%includeGuardStart } 7yyXQ8mlHYTGywQ4zBKQag
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLJobRender.h
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
//%Header } R2tHuSZ89uRrbOjM/LViJQ
/*
 * $Id: MushGLJobRender.h,v 1.7 2006/09/09 11:16:40 southa Exp $
 * $Log: MushGLJobRender.h,v $
 * Revision 1.7  2006/09/09 11:16:40  southa
 * One-time vertex buffer generation
 *
 * Revision 1.6  2006/09/07 16:38:50  southa
 * Vertex shader
 *
 * Revision 1.5  2006/07/24 18:46:49  southa
 * Depth sorting
 *
 * Revision 1.4  2006/06/27 11:58:08  southa
 * Warning fixes
 *
 * Revision 1.3  2006/06/01 15:39:17  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/09/05 17:14:22  southa
 * Solid rendering
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLStandard.h"

#include "MushGLAttribs.h"
#include "MushGLBuffers.h"
#include "MushGLJob.h"
#include "MushGLShader.h"
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
    MushGLJobRender(const MushGLJobRender&) : MushGLJob() {}
    
    std::vector<MushGLWorkSpec *> m_workSpecs; //:read
    
    MushGLBuffers::tDataRef m_buffersRef; //:readwrite
    MushGLBuffers::tSharedDataRef m_sharedBuffersRef; //:readwrite
    
    Mushware::tVal m_sortValue; //:readwrite
    MushGLShader::tDataRef m_shaderRef; //:readwrite :wref
    MushGLAttribs m_attribs; //:readwrite :wref

//%classPrototypes {
public:
    const std::vector<MushGLWorkSpec *>& WorkSpecs(void) const { return m_workSpecs; }
    const MushGLBuffers::tDataRef& BuffersRef(void) const { return m_buffersRef; }
    void BuffersRefSet(const MushGLBuffers::tDataRef& inValue) { m_buffersRef=inValue; }
    const MushGLBuffers::tSharedDataRef& SharedBuffersRef(void) const { return m_sharedBuffersRef; }
    void SharedBuffersRefSet(const MushGLBuffers::tSharedDataRef& inValue) { m_sharedBuffersRef=inValue; }
    const Mushware::tVal& SortValue(void) const { return m_sortValue; }
    void SortValueSet(const Mushware::tVal& inValue) { m_sortValue=inValue; }
    const MushGLShader::tDataRef& ShaderRef(void) const { return m_shaderRef; }
    void ShaderRefSet(const MushGLShader::tDataRef& inValue) { m_shaderRef=inValue; }
    // Writable reference for m_shaderRef
    MushGLShader::tDataRef& ShaderRefWRef(void) { return m_shaderRef; }
    const MushGLAttribs& Attribs(void) const { return m_attribs; }
    void AttribsSet(const MushGLAttribs& inValue) { m_attribs=inValue; }
    // Writable reference for m_attribs
    MushGLAttribs& AttribsWRef(void) { return m_attribs; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } vxGl1AE4xHphsIvbROTS+w
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
