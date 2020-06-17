//%includeGuardStart {
#ifndef MUSHGLATTRIBS_H
#define MUSHGLATTRIBS_H
//%includeGuardStart } XdRMlV8XPEzwrMbnmgkNeA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLAttribs.h
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
//%Header } zCMYAfOM07s1uiBX1VtA1A
/*
 * $Id: MushGLAttribs.h,v 1.3 2006/09/10 10:30:52 southa Exp $
 * $Log: MushGLAttribs.h,v $
 * Revision 1.3  2006/09/10 10:30:52  southa
 * Shader billboarding
 *
 * Revision 1.2  2006/09/09 15:59:28  southa
 * Shader colour calculations
 *
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
    Mushware::U32 m_transformType; //:readwrite
    
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
    const Mushware::U32& TransformType(void) const { return m_transformType; }
    void TransformTypeSet(const Mushware::U32& inValue) { m_transformType=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } B84lntyDwJzpd+5fKzEpXg
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
