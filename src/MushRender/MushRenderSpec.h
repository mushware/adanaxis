//%includeGuardStart {
#ifndef MUSHRENDERSPEC_H
#define MUSHRENDERSPEC_H
//%includeGuardStart } MUbKk7V90INvJGmjmfoblQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderSpec.h
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
//%Header } 6hLRNoZfeBvP570tKfB/gA
/*
 * $Id: MushRenderSpec.h,v 1.15 2006/10/06 11:54:58 southa Exp $
 * $Log: MushRenderSpec.h,v $
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
    const tMattress ModelToClipMattress(void) const { return m_projection.Mattress() * ModelToEyeMattress(); }
    const tMattress ModelToClipBillboardMattress(void) const;
    const tMattress ScaledModelMattress(void) const { return tMattress(ScaleMatrix() * m_model.Matrix(), m_model.Offset()); }
    const tMattress ScaledModelBillboardMattress(void) const;
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
    
    // billModel.MatrixSet(MushMeshTools::MatrixRotateInAxis(MushMeshTools::kAxisXY, MushcoreUtil::RandomVal(0,2*M_PI)));    
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
