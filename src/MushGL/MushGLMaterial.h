//%includeGuardStart {
#ifndef MUSHGLMATERIAL_H
#define MUSHGLMATERIAL_H
//%includeGuardStart } 3FmB3AiqkU1/EChg95jSNg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLMaterial.h
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
//%Header } pVNnocdRpPu4/VVhDtWttw
/*
 * $Id: MushGLMaterial.h,v 1.3 2006/06/01 15:39:18 southa Exp $
 * $Log: MushGLMaterial.h,v $
 * Revision 1.3  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/09/05 12:54:30  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/09/03 17:05:36  southa
 * Material work
 *
 */

#include "MushGLStandard.h"

#include "MushGLTexture.h"

//:generate virtual standard ostream xml1
class MushGLMaterial : public MushMesh4Material
{
public:
	typedef MushcoreDataRef<MushGLMaterial> tDataRef;

	virtual void TexNameSet(const std::string& inName, Mushware::U32 inIndex = 0);
	virtual MushGLTexture& TexRef(Mushware::U32 inIndex);
	virtual MushGLTexture& MushGLMaterial::TexWRef(Mushware::U32 inIndex);

	static Mushware::tRubyValue RubyDefine(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue Rubyto_xml(Mushware::tRubyValue inSelf);
	static void RubyInstall(void);
	
private:
    std::vector<MushGLTexture::tDataRef> m_texRefs; //:wref

//%classPrototypes {
public:
    // Writable reference for m_texRefs
    std::vector<MushGLTexture::tDataRef>& TexRefsWRef(void) { return m_texRefs; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 9kBrHf8P6AogaqTG+AvtuQ
};

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLMaterial& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } BHxDYVi+bKh2kGCE0vYN3g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
