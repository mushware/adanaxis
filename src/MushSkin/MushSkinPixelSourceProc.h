//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCEPROC_H
#define MUSHSKINPIXELSOURCEPROC_H
//%includeGuardStart } PS0y8NlNwuuXJo5y1w7GRA
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceProc.h
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
//%Header } +kUGpDFYk7ZjU2sY++utkg
/*
 * $Id$
 * $Log$
 */

#include "MushSkinStandard.h"

//:xml1base MushGLPixelSource
//:generate virtual standard ostream xml1
class MushSkinPixelSourceProc : public MushGLPixelSource
{
public:
    MushSkinPixelSourceProc();
    virtual void ToTextureCreate(MushGLTexture& outTexture);
    virtual void ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue);
	
	bool PaletteTextureValid(void) const
	{
		if (m_pPaletteTexture == NULL)
	    {
			PaletteResolve();
		}
		return m_pPaletteTexture != NULL;
	}
    const MushGLTexture& PaletteTexture(void) const;
	void PaletteTextureInvalidate(void) const { m_pPaletteTexture = NULL; }
	virtual void LineGenerate(Mushware::U8 *inpTileData, Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos);
	virtual void PaletteResolve(void) const;
	Mushware::t4Val PositionTransform(const Mushware::t4Val& inPos) { return inPos.ElementwiseProduct(m_scale) + m_offset; }
	
protected:
	
private:
	std::string m_meshName; //:read
    std::string m_paletteName; //:read
	Mushware::t2Val m_paletteStart;   //:read 
    Mushware::t2Val m_paletteVector1; //:read
    Mushware::t2Val m_paletteVector2; //:read
	Mushware::t4Val m_scale; //:read
	Mushware::t4Val m_offset; //:read
	Mushware::U32 m_numOctaves; //:read
	Mushware::tVal m_octaveRatio; //:read
	
    mutable MushGLTexture *m_pPaletteTexture; //Not owned by this object
	
//%classPrototypes {
public:
    const std::string& MeshName(void) const { return m_meshName; }
    const std::string& PaletteName(void) const { return m_paletteName; }
    const Mushware::t2Val& PaletteStart(void) const { return m_paletteStart; }
    const Mushware::t2Val& PaletteVector1(void) const { return m_paletteVector1; }
    const Mushware::t2Val& PaletteVector2(void) const { return m_paletteVector2; }
    const Mushware::t4Val& Scale(void) const { return m_scale; }
    const Mushware::t4Val& Offset(void) const { return m_offset; }
    const Mushware::U32& NumOctaves(void) const { return m_numOctaves; }
    const Mushware::tVal& OctaveRatio(void) const { return m_octaveRatio; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } su++rvSm8fROLzldsIHyNw
};

inline const MushGLTexture&
MushSkinPixelSourceProc::PaletteTexture(void) const
{
	if (m_pPaletteTexture == NULL)
	{
		PaletteResolve();
		if (m_pPaletteTexture == NULL)
		{		
			throw MushcoreLogicFail("Access to NULL palette texture");
		}
	}
	return *m_pPaletteTexture;
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushSkinPixelSourceProc& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } kKM7y6TbRGlZfkO+xPlJiA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
