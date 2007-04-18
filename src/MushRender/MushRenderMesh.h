//%includeGuardStart {
#ifndef MUSHRENDERMESH_H
#define MUSHRENDERMESH_H
//%includeGuardStart } ABdf7JA7T3b7y0E3Z3dHBg
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMesh.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } 2sAi+XKvm7zOclmHfDP+WA
/*
 * $Id: MushRenderMesh.h,v 1.7 2006/09/09 11:16:41 southa Exp $
 * $Log: MushRenderMesh.h,v $
 * Revision 1.7  2006/09/09 11:16:41  southa
 * One-time vertex buffer generation
 *
 * Revision 1.6  2006/07/25 13:30:58  southa
 * Initial scanner work
 *
 * Revision 1.5  2006/07/24 18:46:50  southa
 * Depth sorting
 *
 * Revision 1.4  2006/06/01 15:39:38  southa
 * DrawArray verification and fixes
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

//:generate standard ostream xml1
class MushRenderMesh : public MushcoreVirtualObject
{
public:
    MushRenderMesh();
    virtual ~MushRenderMesh() {}
    
    virtual void MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh);
    virtual bool RenderJobCreate(MushGLJobRender& outRender,
                                 const MushRenderSpec& inSpec,
                                 const MushMeshMesh& inMesh);
    
    virtual void MeshDelegatesGet(const MushMesh4Mesh *& outpVertexMesh,
                                  const MushMesh4Mesh *& outpColourMesh,
                                  const MushMesh4Mesh *& outpTexCoordMesh,
                                  const MushMesh4Mesh& inMesh);
    virtual void DestDelegatesGet(MushGLBuffers *& outpDestVertex,
                                  MushGLBuffers *& outpDestColour,
                                  MushGLBuffers *& outpDestTexCoord,
                                  const MushRenderSpec& inSpec);
    
    virtual Mushware::tVal SortDepth(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh);
    
    virtual bool ShouldMeshCull(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh);
    
    virtual void CentroidToClip(Mushware::t4Val outPos, 
                                const MushRenderSpec& inSpec,
                                const MushMesh4Mesh& inMesh);
protected:
    enum tSourceType
    {
        kSourceTypeVertex,
        kSourceTypeTexCoord
    };
    
    virtual void TriangleListBuild(MushGLBuffers::tTriangleList& ioList, const MushMesh4Mesh& inMesh, tSourceType inSourceType);
    
private:
    Mushware::t4Val m_colourZMiddle; //:readwrite
    Mushware::t4Val m_colourZLeft;   //:readwrite
    Mushware::t4Val m_colourZRight;  //:readwrite
    
//%classPrototypes {
public:
    const Mushware::t4Val& ColourZMiddle(void) const { return m_colourZMiddle; }
    void ColourZMiddleSet(const Mushware::t4Val& inValue) { m_colourZMiddle=inValue; }
    const Mushware::t4Val& ColourZLeft(void) const { return m_colourZLeft; }
    void ColourZLeftSet(const Mushware::t4Val& inValue) { m_colourZLeft=inValue; }
    const Mushware::t4Val& ColourZRight(void) const { return m_colourZRight; }
    void ColourZRightSet(const Mushware::t4Val& inValue) { m_colourZRight=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } +P6+SbQdCkMB4JhavYauEw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushRenderMesh& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Prj6108OeDef62/U9aQ3PA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
