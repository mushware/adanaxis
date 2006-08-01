//%includeGuardStart {
#ifndef MUSHMESHLIBRARYSINGLEFACET_H
#define MUSHMESHLIBRARYSINGLEFACET_H
//%includeGuardStart } 1xrY4qzG9DP6f9oteHdXAA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibrarySingleFacet.h
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } rzTMv1++NG1XvEjjPwfgnw
/*
 * $Id: MushMeshLibrarySingleFacet.h,v 1.1 2006/07/17 14:43:41 southa Exp $
 * $Log: MushMeshLibrarySingleFacet.h,v $
 * Revision 1.1  2006/07/17 14:43:41  southa
 * Billboarded deco objects
 *
 */

#include "MushMeshLibraryStandard.h"

//:xml1base MushMesh4Base
//:generate virtual standard ostream xml1
class MushMeshLibrarySingleFacet : public MushMesh4Base
{
public:
	MushMeshLibrarySingleFacet() : m_order(0) {}
	virtual void Make(MushMesh4Mesh& ioMesh) const;
	
private:
	Mushware::U32 m_order; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& Order(void) const { return m_order; }
    void OrderSet(const Mushware::U32& inValue) { m_order=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } hDw3+Tv1KM2d61dLsWDqNg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshLibrarySingleFacet& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } yz4Hm5TprueHez589yRipg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
