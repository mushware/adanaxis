//%includeGuardStart {
#ifndef MUSHRENDERSPEC_H
#define MUSHRENDERSPEC_H
//%includeGuardStart } MUbKk7V90INvJGmjmfoblQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderSpec.h
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
//%Header } 9GhtgaU/qjg2U0oi+++gmw
/*
 * $Id: MushRenderSpec.h,v 1.17 2006/11/14 14:02:17 southa Exp $
 * $Log: MushRenderSpec.h,v $
 * Revision 1.17  2006/11/14 14:02:17  southa
 * Ball projectiles
 *
 * Revision 1.16  2006/10/06 14:48:19  southa
 * Material animation
 *
 * Revision 1.15  2006/10/06 11:54:58  southa
 * Scaled rendering
 *
 * Revision 1.14  2006/09/09 11:16:42  southa
 * One-time vertex buffer generation
 *
 * Revision 1.13  2006/09/07 16:38:52  southa
 * Vertex shader
 *
 * Revision 1.12  2006/07/18 16:58:39  southa
 * Texture fixes
 *
 * Revision 1.11  2006/07/17 14:43:42  southa
 * Billboarded deco objects
 *
 * Revision 1.10  2006/06/01 15:39:38  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/09/05 12:54:30  southa
 * Solid rendering work
 *
 * Revision 1.8  2005/07/19 10:06:49  southa
 * Adanaxis work
 *
 * Revision 1.7  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/07/04 15:59:01  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.3  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.1  2005/07/01 10:36:46  southa
 * MushRender work
 *
 */

#include "MushRenderStandard.h"

#include "MushRenderSpec.h"

#include "API/mushMushGL.h"

//:generate standard ostream xml1
class MushRenderSpec : public MushcoreVirtualObject
{
public:
    typedef Mushware::t4x4o4Val tMattress;
    
    MushRenderSpec() : m_scale(Mushware::t4Val(1.0, 1.0, 1.0, 1.0)), m_useSharedVertices(true) {}
    virtual ~MushRenderSpec() {}
    
    const tMattress ModelToEyeMattress(void) const { return m_view * ScaledModelMattress(); }
    const tMattress ModelToEyeBillboardMattress(void) const { return m_view * ScaledModelBillboardMattress(); }
    const tMattress ModelToEyeBillboardRandomMattress(void) const { return m_view * ScaledModelBillboardRandomMattress(); }
    const tMattress ModelToClipMattress(void) const { return m_projection.Mattress() * ModelToEyeMattress(); }
    const tMattress ModelToClipBillboardMattress(void) const;
    const tMattress ModelToClipBillboardRandomMattress(void) const;
    const tMattress ScaledModelMattress(void) const { return tMattress(ScaleMatrix() * m_model.Matrix(), m_model.Offset()); }
    const tMattress ScaledModelBillboardMattress(void) const;
    const tMattress ScaledModelBillboardRandomMattress(void) const;
    const tMattress::tMatrix ScaleMatrix(void) const;
    
private:
    MushGLProjection m_projection; //:readwrite :wref
    tMattress m_view; //:readwrite :wref
    tMattress m_model; //:readwrite :wref
    Mushware::t4Val m_scale; //:readwrite :wref
    
    MushGLBuffers::tDataRef m_buffersRef; //:readwrite
    MushGLBuffers::tSharedDataRef m_sharedBuffersRef; //:readwrite
    bool m_useSharedVertices; //:readwrite
    Mushware::tVal m_materialAnimator; //:readwrite
        
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
    const Mushware::t4Val& Scale(void) const { return m_scale; }
    void ScaleSet(const Mushware::t4Val& inValue) { m_scale=inValue; }
    // Writable reference for m_scale
    Mushware::t4Val& ScaleWRef(void) { return m_scale; }
    const MushGLBuffers::tDataRef& BuffersRef(void) const { return m_buffersRef; }
    void BuffersRefSet(const MushGLBuffers::tDataRef& inValue) { m_buffersRef=inValue; }
    const MushGLBuffers::tSharedDataRef& SharedBuffersRef(void) const { return m_sharedBuffersRef; }
    void SharedBuffersRefSet(const MushGLBuffers::tSharedDataRef& inValue) { m_sharedBuffersRef=inValue; }
    const bool& UseSharedVertices(void) const { return m_useSharedVertices; }
    void UseSharedVerticesSet(const bool& inValue) { m_useSharedVertices=inValue; }
    const Mushware::tVal& MaterialAnimator(void) const { return m_materialAnimator; }
    void MaterialAnimatorSet(const Mushware::tVal& inValue) { m_materialAnimator=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } HXp/kWlFzxcW/shbqot3lg
};

inline const MushRenderSpec::tMattress
MushRenderSpec::ModelToClipBillboardMattress(void) const
{
    tMattress billModel = ModelToEyeMattress();
    
    billModel.MatrixSet(ScaleMatrix());
    
    return m_projection.Mattress() * billModel;
}

inline const MushRenderSpec::tMattress
MushRenderSpec::ScaledModelBillboardMattress(void) const
{
    tMattress billModel = Model();
    
    billModel.MatrixSet(ScaleMatrix());
    
    return billModel;
}

inline const MushRenderSpec::tMattress
MushRenderSpec::ModelToClipBillboardRandomMattress(void) const
{
    tMattress billModel = ModelToEyeMattress();
    
    billModel.MatrixSet(ScaleMatrix() * MushMeshTools::MatrixRotateInAxis(MushMeshTools::kAxisXY, MushcoreUtil::RandomVal(0,2*M_PI)));
    
    return m_projection.Mattress() * billModel;
}

inline const MushRenderSpec::tMattress
MushRenderSpec::ScaledModelBillboardRandomMattress(void) const
{
    tMattress billModel = Model();
    
    billModel.MatrixSet(ScaleMatrix() * MushMeshTools::MatrixRotateInAxis(MushMeshTools::kAxisXY, MushcoreUtil::RandomVal(0,2*M_PI)));
    
    return billModel;
}

inline const MushRenderSpec::tMattress::tMatrix
MushRenderSpec::ScaleMatrix(void) const
{
    return tMattress::tMatrix(
                              Mushware::t4Val(m_scale.X(), 0, 0, 0),
                              Mushware::t4Val(0, m_scale.Y(), 0, 0),
                              Mushware::t4Val(0, 0, m_scale.Z(), 0),
                              Mushware::t4Val(0, 0, 0, m_scale.W()));
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushRenderSpec& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } AwM/RwQovTTCL3UpRXcpCg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
