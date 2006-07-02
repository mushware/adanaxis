//%includeGuardStart {
#ifndef MUSHGLFONT_H
#define MUSHGLFONT_H
//%includeGuardStart } t3ghUhPwnkLwSMZ+RJKnCA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLFont.h
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
//%Header } GszAZNIc4XTjBhyVnPxI7g
/*
 * $Id: MushGLFont.h,v 1.1 2006/04/21 00:10:43 southa Exp $
 * $Log: MushGLFont.h,v $
 * Revision 1.1  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 */

#include "MushGLStandard.h"

#include "MushGLTexture.h"

#include "API/mushMushRuby.h"

//:generate virtual standard ostream xml1
class MushGLFont : public MushcoreVirtualObject
{
public:
    void TextureNameSet(const std::string& inName) { m_textureRef.NameSet(inName); }
    
private:
    MushGLTexture::tDataRef m_textureRef; //:read
    Mushware::t2U32 m_divide; //:readwrite
    Mushware::t2Val m_extent; //:readwrite
    
//%classPrototypes {
public:
    const MushGLTexture::tDataRef& TextureRef(void) const { return m_textureRef; }
    const Mushware::t2U32& Divide(void) const { return m_divide; }
    void DivideSet(const Mushware::t2U32& inValue) { m_divide=inValue; }
    const Mushware::t2Val& Extent(void) const { return m_extent; }
    void ExtentSet(const Mushware::t2Val& inValue) { m_extent=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } C3s0M+p5fcmi8zpAft3Njw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLFont& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 1ZY58rqxwhcVg7rCFTydtA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
