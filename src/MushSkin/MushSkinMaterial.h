//%includeGuardStart {
#ifndef MUSHSKINMATERIAL_H
#define MUSHSKINMATERIAL_H
//%includeGuardStart } z6+Uj+WopuZ/5d2SvQ6t4A
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinMaterial.h
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
//%Header } K4isL40HJqwvsvQ3zMAxaQ
/*
 * $Id: MushSkinMaterial.h,v 1.1 2006/06/19 15:57:20 southa Exp $
 * $Log: MushSkinMaterial.h,v $
 * Revision 1.1  2006/06/19 15:57:20  southa
 * Materials
 *
 */

#include "MushSkinStandard.h"

//:xml1base MushMesh4Material
//:generate virtual standard ostream xml1
class MushSkinMaterial : public MushMesh4Material
{
public:
	void NameSet(const std::string& inName) { m_texRef.NameSet(inName); }
	
	const MushGLTexture& TexRef(void) { return m_texRef.Ref(); }
	MushGLTexture& TexWRef(void) { return m_texRef.WRef(); }
	
private:
	MushcoreDataRef<MushGLTexture> m_texRef;

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
operator<<(std::ostream& ioOut, const MushSkinMaterial& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } D6kGwvVXSh5+Jq9uOBxDog
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
