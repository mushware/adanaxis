//%includeGuardStart {
#ifndef MUSHMESHLIBRARYWORLDSPHERE_H
#define MUSHMESHLIBRARYWORLDSPHERE_H
//%includeGuardStart } ICihSiFZ14lya5GMsZGyxg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryWorldSphere.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } I25e23XmGMT2aM1wOOhsSQ
/*
 * $Id: MushMeshLibraryWorldSphere.h,v 1.2 2007/04/18 09:22:54 southa Exp $
 * $Log: MushMeshLibraryWorldSphere.h,v $
 * Revision 1.2  2007/04/18 09:22:54  southa
 * Header and level fixes
 *
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
