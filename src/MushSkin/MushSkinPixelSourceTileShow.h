//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCETILESHOW_H
#define MUSHSKINPIXELSOURCETILESHOW_H
//%includeGuardStart } eUJQoAykO9ARdk6mWyAhDw
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceTileShow.h
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
//%Header } ak8kIDJs8BoNF69uIKJ8Lw
/*
 * $Id: MushSkinPixelSourceTileShow.h,v 1.3 2007/04/18 09:23:05 southa Exp $
 * $Log: MushSkinPixelSourceTileShow.h,v $
 * Revision 1.3  2007/04/18 09:23:05  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/08/01 17:21:40  southa
 * River demo
 *
 * Revision 1.1  2006/06/09 21:07:14  southa
 * Tiled skin generation
 *
 */

#include "MushSkinLineGenerator.h"
#include "MushSkinPixelSourceProc.h"
#include "MushSkinUtil.h"

//:xml1base MushSkinPixelSourceProc
//:generate virtual standard ostream xml1
class MushSkinPixelSourceTileShow : public MushSkinPixelSourceProc
{
public:
    MushSkinPixelSourceTileShow();
    virtual void ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue);
    virtual void ToTextureCreate(MushGLTexture& outTexture);
    virtual void ToTextureBind(MushGLTexture& outTexture);
	virtual void TileShowLineGenerate(Mushware::U8 *outpTileData,
									  Mushware::U32 inNumPixels, const std::vector<Mushware::t4Val>& texCoords,
									  const Mushware::t4Val& inStartUV, const Mushware::t4Val& inEndUV);
	
protected:
		
private:
	MushSkinLineGenerator m_lineGenerator;
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
operator<<(std::ostream& ioOut, const MushSkinPixelSourceTileShow& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } fNt+LMtJ3yA7duDJ7wAmKg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
