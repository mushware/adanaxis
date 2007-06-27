//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCECELLNOISE_H
#define MUSHSKINPIXELSOURCECELLNOISE_H
//%includeGuardStart } vyJb7C5ehMMoJGqEZEV9Vw
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceCellNoise.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } lG700CNR21Im3ZwIwD/Kug
/*
 * $Id: MushSkinPixelSourceCellNoise.h,v 1.4 2007/04/18 09:23:04 southa Exp $
 * $Log: MushSkinPixelSourceCellNoise.h,v $
 * Revision 1.4  2007/04/18 09:23:04  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/08/01 17:21:38  southa
 * River demo
 *
 * Revision 1.2  2006/06/26 17:03:15  southa
 * win32 installer tweaks
 *
 * Revision 1.1  2006/06/07 12:15:20  southa
 * Grid and test textures
 *
 * Revision 1.1  2006/06/05 14:37:52  southa
 * Texture generation
 *
 */

#include "MushSkinStandard.h"

#include "MushSkinPixelSourceProc.h"

#include "MushSkinLineGenerator.h"

//:xml1base MushSkinPixelSourceProc
//:generate virtual standard ostream xml1
class MushSkinPixelSourceCellNoise : public MushSkinPixelSourceProc
{
public:
	MushSkinPixelSourceCellNoise();
	
protected:
	virtual void LineGenerate(Mushware::U8 *inpTileData, Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos);
	
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
operator<<(std::ostream& ioOut, const MushSkinPixelSourceCellNoise& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } xnk8wOly3PaWcGzqM26juA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
