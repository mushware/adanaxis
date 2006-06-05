//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCETEST_H
#define MUSHSKINPIXELSOURCETEST_H
//%includeGuardStart } f0Svt4agKJBECQvN71XmnQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceTest.h
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } DCgOpQQAdiwGFko3kpjm3g
/*
 * $Id$
 * $Log$
 */

#include "MushSkinStandard.h"

#include "MushSkinLineGenerator.h"
#include "MushSkinUtil.h"

//:generate virtual standard ostream xml1
class MushSkinPixelSourceTest : public MushGLPixelSource
{
public:
    MushSkinPixelSourceTest();
    
    virtual void ValueParameterSet(const Mushware::U32 inNum, const Mushware::tLongVal inVal);
    virtual void StringParameterSet(const Mushware::U32 inNum, const std::string& inStr);
    virtual void ToTextureCreate(MushGLTexture& outTexture);
    
protected:
	virtual void LineGenerate(Mushware::U8 *inpTileData, Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos);
	
    Mushware::t2Val m_paletteStart;    
    Mushware::t2Val m_paletteVector1;
    Mushware::t2Val m_paletteVector2;
    MushGLTexture *m_pPaletteTexture; // Not owned by this object
    
private:
	Mushware::U32 m_xSize;
    Mushware::U32 m_ySize;
    std::string m_sourceName; //:read
    std::string m_paletteName; //:read
	MushSkinLineGenerator m_lineGenerator;

//%classPrototypes {
public:
    const std::string& SourceName(void) const { return m_sourceName; }
    const std::string& PaletteName(void) const { return m_paletteName; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } hNp9sR/1oLVBPc7uQnaDNw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushSkinPixelSourceTest& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } FcjVs5dyLxHsUAkyB2zX0w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
