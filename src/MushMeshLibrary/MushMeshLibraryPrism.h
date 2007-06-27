//%includeGuardStart {
#ifndef MUSHMESHLIBRARYPRISM_H
#define MUSHMESHLIBRARYPRISM_H
//%includeGuardStart } ymO6abrq9vtxQdg683ciiw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryPrism.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } sePcDLYy4n4dPCbfMsmiKQ
/*
 * $Id: MushMeshLibraryPrism.h,v 1.4 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryPrism.h,v $
 * Revision 1.4  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/08/01 17:21:35  southa
 * River demo
 *
 * Revision 1.2  2006/06/16 12:11:04  southa
 * Ruby subclasses
 *
 * Revision 1.1  2006/06/16 01:02:32  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshLibraryStandard.h"

//:xml1base MushMesh4Base
//:generate virtual standard ostream xml1
class MushMeshLibraryPrism : public MushMesh4Base
{
public:
	MushMeshLibraryPrism() : m_order(0) {}
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
operator<<(std::ostream& ioOut, const MushMeshLibraryPrism& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Q1CuKx8cj185hgpPU6ytGg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
