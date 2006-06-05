//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCENOISECELL_H
#define MUSHSKINPIXELSOURCENOISECELL_H
//%includeGuardStart } LdLFBZfUUCEjMB4lhPcBdg
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceNoiseCell.h
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
//%Header } Sn+2MvNExA8jrcnESoqtgw
/*
 * $Id$
 * $Log$
 */

#include "MushSkinStandard.h"

#include "MushSkinPixelSourceNoise.h"

#include "MushSkinLineGenerator.h"

//:xml1base MushSkinPixelSourceNoise
//:generate virtual standard ostream xml1
class MushSkinPixelSourceNoiseCell : public MushSkinPixelSourceNoise
{
public:
	MushSkinPixelSourceNoiseCell();
	
protected:
	virtual void TileLineGenerate(Mushware::U8 *inpTileData, const MushMesh4Mesh::tTextureTile& inTileRef,
    							  Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos);
	
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
operator<<(std::ostream& ioOut, const MushSkinPixelSourceNoiseCell& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 6xoQJWzYokddAJOpBAfOEg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
