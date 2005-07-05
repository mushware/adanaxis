//%includeGuardStart {
#ifndef MUSHRENDERMESHWIREFRAME_H
#define MUSHRENDERMESHWIREFRAME_H
//%includeGuardStart } yWUi9oXnokdSM/hurSycsQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMeshWireframe.h
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
//%Header } tS7SXrOHlPA5Gu5Vj1LZkg
/*
 * $Id: MushRenderMeshWireframe.h,v 1.2 2005/07/04 15:59:00 southa Exp $
 * $Log: MushRenderMeshWireframe.h,v $
 * Revision 1.2  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushRenderStandard.h"

#include "MushRenderMesh.h"

//:xml1base MushRenderMesh
//:generate standard ostream xml1
class MushRenderMeshWireframe : public MushRenderMesh
{
public:
    typedef std::vector<Mushware::t4x4Val> tVertices;

    MushRenderMeshWireframe();
    virtual ~MushRenderMeshWireframe() {}

    virtual void MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh);
    
protected:
    void DerivedColourSet(Mushware::t4Val& outColour, const Mushware::t4Val& inEyeVertex);
    
private:
    bool OutputBufferGenerate(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh);
    
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
operator<<(std::ostream& ioOut, const MushRenderMeshWireframe& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } k0keisck+DyO5hne+i3wJg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
