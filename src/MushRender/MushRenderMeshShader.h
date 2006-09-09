//%includeGuardStart {
#ifndef MUSHRENDERMESHSHADER_H
#define MUSHRENDERMESHSHADER_H
//%includeGuardStart } 7SHmgrHFdosaTjKLWxNt8Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMeshShader.h
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
//%Header } 0Whuh3knBqfc8NyHXGX6rg
/*
 * $Id: MushRenderMeshShader.h,v 1.1 2006/09/07 16:38:52 southa Exp $
 * $Log: MushRenderMeshShader.h,v $
 * Revision 1.1  2006/09/07 16:38:52  southa
 * Vertex shader
 *
 */

#include "MushRenderStandard.h"

#include "MushRenderMesh.h"

//:xml1base MushRenderMesh
//:generate standard ostream xml1
class MushRenderMeshShader : public MushRenderMesh
{
public:
    typedef std::vector<Mushware::t4x4Val> tVertices;
    
    MushRenderMeshShader();
    virtual ~MushRenderMeshShader() {}
    
    virtual void MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh);
    virtual bool RenderJobCreate(MushGLJobRender& outRender,
                                 const MushRenderSpec& inSpec,
                                 const MushMeshMesh& inMesh);
protected:    
    
private:
    bool OutputBufferGenerate(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh);
    
    MushGLShader::tDataRef m_project4DRef;
    
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushRenderMeshShader& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } AoyiJ/+odDKDUkyrVd9U7g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
