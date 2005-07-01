//%includeGuardStart {
#ifndef MUSHRENDERMESH_H
#define MUSHRENDERMESH_H
//%includeGuardStart } ABdf7JA7T3b7y0E3Z3dHBg
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMesh.h
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
//%Header } 5NT3TUzeT9fSzmpfPY/lmQ
/*
 * $Id$
 * $Log$
 */

#include "MushRenderStandard.h"

#include "MushRenderSpec.h"

//:generate standard ostream xml1
class MushRenderMesh : MushcoreVirtualObject
{
public:
    virtual ~MushRenderMesh() {}
    
    virtual void MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh);
    
private:
//%classPrototypes {
public:
    const char *AutoName(void) const;
    MushcoreVirtualObject *AutoClone(void) const;
    MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } oLR0tLUUWStTX02QfMX/OA
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
