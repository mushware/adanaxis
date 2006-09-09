//%includeGuardStart {
#ifndef MUSHRENDERMESHSOLID_H
#define MUSHRENDERMESHSOLID_H
//%includeGuardStart } NAkbcNGYXEVoHub0YFbq9g
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMeshSolid.h
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
//%Header } FObiLM884v89SsLhON7VJQ
/*
 * $Id: MushRenderMeshSolid.h,v 1.5 2006/07/24 18:46:51 southa Exp $
 * $Log: MushRenderMeshSolid.h,v $
 * Revision 1.5  2006/07/24 18:46:51  southa
 * Depth sorting
 *
 * Revision 1.4  2006/06/01 15:39:38  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 * Revision 1.2  2005/09/05 12:54:30  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 */

#include "MushRenderStandard.h"

#include "MushRenderMesh.h"

//:xml1base MushRenderMesh
//:generate standard ostream xml1
class MushRenderMeshSolid : public MushRenderMesh
{
public:
    typedef std::vector<Mushware::t4x4Val> tVertices;
    
    MushRenderMeshSolid();
    virtual ~MushRenderMeshSolid() {}
    
    virtual void MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh);
    virtual bool RenderJobCreate(MushGLJobRender& outRender,
                                 const MushRenderSpec& inSpec,
                                 const MushMeshMesh& inMesh);
protected:
    void DerivedColourSet(Mushware::t4Val& outColour, const Mushware::t4Val& inEyeVertex, const MushRenderSpec& inSpec);
    
private:
    bool OutputBufferGenerate(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh);
    
    
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
operator<<(std::ostream& ioOut, const MushRenderMeshSolid& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } LSuz9qpqZGNGsW62WSfCjQ

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
