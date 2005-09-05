//%includeGuardStart {
#ifndef MUSHGLMATERIAL_H
#define MUSHGLMATERIAL_H
//%includeGuardStart } 3FmB3AiqkU1/EChg95jSNg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLMaterial.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } o2aSbaPsq9RU5xpAX8xZpQ
/*
 * $Id: MushGLMaterial.h,v 1.1 2005/09/03 17:05:36 southa Exp $
 * $Log: MushGLMaterial.h,v $
 * Revision 1.1  2005/09/03 17:05:36  southa
 * Material work
 *
 */

#include "MushGLStandard.h"

#include "MushGLTexture.h"

//:generate virtual standard ostream xml1
class MushGLMaterial : public MushcoreVirtualObject
{
public:
    const MushGLTexture::tDataRef& TextureHandles(Mushware::U32 inIndex) const { MushcoreUtil::BoundsCheck(inIndex, m_textureHandles.size()); return m_textureHandles[inIndex]; }
    void TextureHandlesResizeAndSet(const MushGLTexture::tDataRef& inValue, Mushware::U32 inIndex) { if (inIndex >= m_textureHandles.size()) m_textureHandles.resize(inIndex + 1); m_textureHandles[inIndex]=inValue; }
    
private:
    std::vector<MushGLTexture::tDataRef> m_textureHandles; //:wref
    
//%classPrototypes {
public:
    // Writable reference for m_textureHandles
    std::vector<MushGLTexture::tDataRef>& TextureHandlesWRef(void) { return m_textureHandles; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } axqNSa5Fgcgko3ukg4CIXg
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
