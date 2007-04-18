//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCETEST_H
#define MUSHSKINPIXELSOURCETEST_H
//%includeGuardStart } f0Svt4agKJBECQvN71XmnQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceTest.h
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
//%Header } EVim9EPFLUzfY5JugnrHQw
/*
 * $Id: MushSkinPixelSourceTest.h,v 1.3 2006/08/01 17:21:40 southa Exp $
 * $Log: MushSkinPixelSourceTest.h,v $
 * Revision 1.3  2006/08/01 17:21:40  southa
 * River demo
 *
 * Revision 1.2  2006/06/07 12:15:21  southa
 * Grid and test textures
 *
 * Revision 1.1  2006/06/05 14:37:52  southa
 * Texture generation
 *
 */

#include "MushSkinStandard.h"

#include "MushSkinLineGenerator.h"
#include "MushSkinPixelSourceProc.h"
#include "MushSkinUtil.h"

//:xml1base MushSkinPixelSourceProc
//:generate virtual standard ostream xml1
class MushSkinPixelSourceTest : public MushSkinPixelSourceProc
{
public:
    MushSkinPixelSourceTest();
	virtual ~MushSkinPixelSourceTest();
	
	virtual void ToTextureCreate(MushGLTexture& outTexture);

	// Delegate everything else
	virtual void ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue);
	virtual void LineGenerate(Mushware::U8 *inpTileData, Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos)
	{
		PixelSource().LineGenerate(inpTileData, inNumPixels, inStartPos, inEndPos);
	}
	virtual void PaletteResolve(void) const
	{
		PixelSource().PaletteResolve();
	}
	
private:
	MushSkinPixelSourceProc& PixelSource(void) const;

	MushGLPixelSource *m_pPixelSource;
	
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
operator<<(std::ostream& ioOut, const MushSkinPixelSourceTest& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } FcjVs5dyLxHsUAkyB2zX0w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
