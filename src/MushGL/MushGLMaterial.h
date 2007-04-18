//%includeGuardStart {
#ifndef MUSHGLMATERIAL_H
#define MUSHGLMATERIAL_H
//%includeGuardStart } 3FmB3AiqkU1/EChg95jSNg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLMaterial.h
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
//%Header } nWa5C/BGY6w6sbIvFKgwOA
/*
 * $Id: MushGLMaterial.h,v 1.6 2006/10/06 14:48:19 southa Exp $
 * $Log: MushGLMaterial.h,v $
 * Revision 1.6  2006/10/06 14:48:19  southa
 * Material animation
 *
 * Revision 1.5  2006/06/20 19:06:52  southa
 * Object creation
 *
 * Revision 1.4  2006/06/19 15:57:17  southa
 * Materials
 *
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
    typedef MushGLTexture::tDataRef tTextureRef;
    typedef std::vector<tTextureRef> tMultiTextureRef;
    
    const tMultiTextureRef& MultiTextureRef(Mushware::U32 inFrame) const;
    
	virtual void TexNameSet(const std::string& inName, Mushware::U32 inFrame = 0, Mushware::U32 inTexNum = 0);
	virtual MushGLTexture& TexRef(Mushware::U32 inFrame = 0, Mushware::U32 inTexNum = 0) const;
    virtual Mushware::U32 AnimatorToFrame(Mushware::tVal inAnimator) const;
    virtual MushGLTexture& AnimatedTexRef(Mushware::tVal inAnimator, Mushware::U32 inTexNum = 0) const;

    
	static Mushware::tRubyValue RubyDefine(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue Rubyto_xml(Mushware::tRubyValue inSelf);
	static void RubyInstall(void);
	
private:
    std::vector<tMultiTextureRef> m_multiTexRefs; //:wref

//%classPrototypes {
public:
    // Writable reference for m_multiTexRefs
    std::vector<tMultiTextureRef>& MultiTexRefsWRef(void) { return m_multiTexRefs; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 43ZKccyqLuP1MDe9Oa6SpQ
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
