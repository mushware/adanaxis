//%includeGuardStart {
#ifndef MUSHMESHMESH_H
#define MUSHMESHMESH_H
//%includeGuardStart } i5h+IBpPu0u2mYXIzMJChg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshMesh.h
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
//%Header } zu4vnvFL3Sw0qRayn8Pdlw

/*
 * $Id: MushMeshMesh.h,v 1.1 2005/06/30 12:04:56 southa Exp $
 * $Log: MushMeshMesh.h,v $
 * Revision 1.1  2005/06/30 12:04:56  southa
 * Mesh work
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshMaterialRef.h"

//:generate virtual standard ostream xml1
class MushMeshMesh : public MushcoreVirtualObject
{
public:
    MushMeshMesh();
    virtual ~MushMeshMesh();
    
private:
    MushMeshMaterialRef m_materialRef; //:readwrite
//%classPrototypes {
public:
    const MushMeshMaterialRef& MaterialRef(void) const { return m_materialRef; }
    void MaterialRefSet(const MushMeshMaterialRef& inValue) { m_materialRef=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 9Q2BNrtEErDEZYN7fMrSiQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshMesh& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } N94eae81SQnIESQ3JfAsmg

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
