//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCETILESHOW_H
#define MUSHSKINPIXELSOURCETILESHOW_H
//%includeGuardStart } eUJQoAykO9ARdk6mWyAhDw
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceTileShow.h
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
//%Header } o4xdBmUNAgvzefP3ug2cYw
/*
 * $Id: MushSkinPixelSourceTileShow.h,v 1.2 2006/08/01 17:21:40 southa Exp $
 * $Log: MushSkinPixelSourceTileShow.h,v $
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
