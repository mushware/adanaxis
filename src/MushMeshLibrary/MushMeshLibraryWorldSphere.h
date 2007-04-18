//%includeGuardStart {
#ifndef MUSHMESHLIBRARYWORLDSPHERE_H
#define MUSHMESHLIBRARYWORLDSPHERE_H
//%includeGuardStart } ICihSiFZ14lya5GMsZGyxg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryWorldSphere.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } uYB2/3aeTJhDnDfpBBjy6w
/*
 * $Id: MushMeshLibraryWorldSphere.h,v 1.1 2006/09/12 15:28:50 southa Exp $
 * $Log: MushMeshLibraryWorldSphere.h,v $
 * Revision 1.1  2006/09/12 15:28:50  southa
 * World sphere
 *
 */

#include "MushMeshLibraryStandard.h"

//:xml1base MushMesh4Base
//:generate virtual standard ostream xml1
class MushMeshLibraryWorldSphere : public MushMesh4Base
{
public:
	MushMeshLibraryWorldSphere() : m_numFacets(0), m_tilesPerTexture(1) {}
	virtual void Make(MushMesh4Mesh& ioMesh) const;
	
private:
	Mushware::U32 m_numFacets; //:readwrite
	Mushware::U32 m_tilesPerTexture; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& NumFacets(void) const { return m_numFacets; }
    void NumFacetsSet(const Mushware::U32& inValue) { m_numFacets=inValue; }
    const Mushware::U32& TilesPerTexture(void) const { return m_tilesPerTexture; }
    void TilesPerTextureSet(const Mushware::U32& inValue) { m_tilesPerTexture=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } zTjihiUaDCblKubwyXd/gw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshLibraryWorldSphere& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } wNXHclssm7jHDg8Ke7c0oQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
