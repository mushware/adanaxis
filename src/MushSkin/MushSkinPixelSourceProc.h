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
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Dh/c1j83L0T2aLqfoYBajw
/*
 * $Id: MushSkinPixelSourceProc.h,v 1.2 2006/06/09 21:07:14 southa Exp $
 * $Log: MushSkinPixelSourceProc.h,v $
 * Revision 1.2  2006/06/09 21:07:14  southa
 * Tiled skin generation
 *
 * Revision 1.1  2006/06/07 12:15:21  southa
 * Grid and test textures
 *
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
	virtual void PaletteResolve(void) const;

	bool MeshValid(void) const
	{
		if (m_pMesh == NULL)
		{
			MeshResolve();	
		}
		return m_pMesh != NULL;
	}
	const MushMesh4Mesh& Mesh(void) const;
	void MeshInvalidate(void) { m_pMesh = NULL; }
	virtual void MeshResolve(void) const;

	virtual void LineGenerate(Mushware::U8 *inpTileData, Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos);
	Mushware::t4Val PositionTransform(const Mushware::t4Val& inPos) { return inPos.ElementwiseProduct(m_scale) + m_offset; }
	
protected:
	
private:
	std::string m_meshName; //:readwrite
    std::string m_paletteName; //:read
	Mushware::t2Val m_paletteStart;   //:read 
    Mushware::t2Val m_paletteVector1; //:read
    Mushware::t2Val m_paletteVector2; //:read
	Mushware::t4Val m_scale; //:read
	Mushware::t4Val m_offset; //:read
	Mushware::U32 m_numOctaves; //:read
	Mushware::tVal m_octaveRatio; //:read
	
    mutable MushGLTexture *m_pPaletteTexture; //Not owned by this object
	mutable MushMesh4Mesh *m_pMesh; //:read
	
//%classPrototypes {
public:
    const std::string& MeshName(void) const { return m_meshName; }
    void MeshNameSet(const std::string& inValue) { m_meshName=inValue; }
    const std::string& PaletteName(void) const { return m_paletteName; }
    const Mushware::t2Val& PaletteStart(void) const { return m_paletteStart; }
    const Mushware::t2Val& PaletteVector1(void) const { return m_paletteVector1; }
    const Mushware::t2Val& PaletteVector2(void) const { return m_paletteVector2; }
    const Mushware::t4Val& Scale(void) const { return m_scale; }
    const Mushware::t4Val& Offset(void) const { return m_offset; }
    const Mushware::U32& NumOctaves(void) const { return m_numOctaves; }
    const Mushware::tVal& OctaveRatio(void) const { return m_octaveRatio; }
    const MushMesh4Mesh& PMesh(void) const { return *m_pMesh; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } zCIEMLUMgqNAtQZIC6vhGQ
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

inline const MushMesh4Mesh&
MushSkinPixelSourceProc::Mesh(void) const
{
	if (m_pMesh == NULL)
	{
		MeshResolve();
		if (m_pMesh == NULL)
		{		
			throw MushcoreLogicFail("Access to NULL mesh");
		}
	}
	return *m_pMesh;
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
