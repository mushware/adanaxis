//%includeGuardStart {
#ifndef MUSHGLMATERIAL_H
#define MUSHGLMATERIAL_H
//%includeGuardStart } 3FmB3AiqkU1/EChg95jSNg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLMaterial.h
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
//%Header } P2ESZRWT+d893C0av4rQpQ
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
