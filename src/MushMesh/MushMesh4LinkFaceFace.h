//%includeGuardStart {
#ifndef MUSHMESH4LINKFACEFACE_H
#define MUSHMESH4LINKFACEFACE_H
//%includeGuardStart } Ts/6esfbQFVxvfonUaZAUw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4LinkFaceFace.h
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
//%Header } QFgCZykW9WhJywJmAKekIA
/*
 * $Id: MushMesh4LinkFaceFace.h,v 1.2 2006/06/01 15:39:28 southa Exp $
 * $Log: MushMesh4LinkFaceFace.h,v $
 * Revision 1.2  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/13 16:45:05  southa
 * Extrusion work
 *
 */

#include "MushMeshStandard.h"

//:generate virtual standard ostream xml1
class MushMesh4LinkFaceFace : public MushcoreVirtualObject
{
public:
    MushMesh4LinkFaceFace() {}
    virtual ~MushMesh4LinkFaceFace() {}
    
private:
    Mushware::U32 m_faceNum; //:readwrite
    Mushware::U32 m_localFacetNum; //:readwrite
    Mushware::U32 m_remoteFacetNum; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& FaceNum(void) const { return m_faceNum; }
    void FaceNumSet(const Mushware::U32& inValue) { m_faceNum=inValue; }
    const Mushware::U32& LocalFacetNum(void) const { return m_localFacetNum; }
    void LocalFacetNumSet(const Mushware::U32& inValue) { m_localFacetNum=inValue; }
    const Mushware::U32& RemoteFacetNum(void) const { return m_remoteFacetNum; }
    void RemoteFacetNumSet(const Mushware::U32& inValue) { m_remoteFacetNum=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } RWHYhncadx94i1MjlIis1w
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMesh4LinkFaceFace& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } JT7LgmuuM0WYbTWrdpqzdQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
