//%includeGuardStart {
#ifndef MUSHGLFONT_H
#define MUSHGLFONT_H
//%includeGuardStart } t3ghUhPwnkLwSMZ+RJKnCA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLFont.h
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
//%Header } 3R7hb2n1HMKPJ1NA8/z93w
/*
 * $Id: MushGLFont.h,v 1.9 2006/12/11 13:28:24 southa Exp $
 * $Log: MushGLFont.h,v $
 * Revision 1.9  2006/12/11 13:28:24  southa
 * Snapshot
 *
 * Revision 1.8  2006/10/17 20:43:01  southa
 * Dashboard work
 *
 * Revision 1.7  2006/10/09 16:00:16  southa
 * Intern generation
 *
 * Revision 1.6  2006/07/25 20:31:03  southa
 * Scanner work
 *
 * Revision 1.5  2006/07/25 13:30:58  southa
 * Initial scanner work
 *
 * Revision 1.4  2006/07/08 16:05:58  southa
 * Ruby menus and key handling
 *
 * Revision 1.3  2006/07/02 21:08:54  southa
 * Ruby menu work
 *
 * Revision 1.2  2006/07/02 09:43:27  southa
 * MushGLFont work
 *
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
    enum
    {
        kAlignLeft = 0,
        kAlignRight,
        kAlignTop,
        kAlignBottom,
        kAlignTopLeft,
        kAlignTopRight,
        kAlignBottomLeft,
        kAlignBottomRight,
        kAlignNumValues
    };
    
    typedef MushcoreData<MushGLFont> tData;
    typedef MushcoreDataRef<MushGLFont> tDataRef;
    
    MushGLFont();
    
    void RenderSymbolAtSize(const Mushware::U32 inValue, const Mushware::t4Val& inCoords,
                            const Mushware::t2Val& inSize) const;
    void RenderSymbolAtSizeProportion(const Mushware::U32 inValue, const Mushware::t4Val& inCoords,
                            const Mushware::t2Val& inSize, const Mushware::t2Val& inProp) const;
    void RenderSymbolAtSizeAngle(const Mushware::U32 inValue, const Mushware::t4Val& inCoords,
                                 const Mushware::t2Val& inSize, Mushware::tVal inAngle) const;
    
    void TextureNameSet(const std::string& inName) { m_textureRef.NameSet(inName); }
    void Render(const std::string& inStr) const;
    void RenderAt(const std::string& inStr, const Mushware::t2Val& inCoords) const;
    void RenderAtSize(const std::string& inStr, const Mushware::t2Val& inCoords, const Mushware::t2Val& inSize) const;
    
private:
    MushGLTexture::tDataRef m_textureRef; //:read
    Mushware::t2U32 m_divide; //:readwrite
    Mushware::t2Val m_extent; //:readwrite
    Mushware::t2Val m_size; //:readwrite
    Mushware::t4Val m_colour; //:readwrite
    
//%classPrototypes {
public:
    const MushGLTexture::tDataRef& TextureRef(void) const { return m_textureRef; }
    const Mushware::t2U32& Divide(void) const { return m_divide; }
    void DivideSet(const Mushware::t2U32& inValue) { m_divide=inValue; }
    const Mushware::t2Val& Extent(void) const { return m_extent; }
    void ExtentSet(const Mushware::t2Val& inValue) { m_extent=inValue; }
    const Mushware::t2Val& Size(void) const { return m_size; }
    void SizeSet(const Mushware::t2Val& inValue) { m_size=inValue; }
    const Mushware::t4Val& Colour(void) const { return m_colour; }
    void ColourSet(const Mushware::t4Val& inValue) { m_colour=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } xyixIJzuvxii+EvJypurYA
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
