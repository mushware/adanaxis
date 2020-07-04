//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCEPROC_H
#define MUSHSKINPIXELSOURCEPROC_H
//%includeGuardStart } PS0y8NlNwuuXJo5y1w7GRA
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceProc.h
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
//%Header } o2VJQ+Cz7JRHh2Irdfx02A
/*
 * $Id: MushSkinPixelSourceProc.h,v 1.5 2007/06/11 20:06:17 southa Exp $
 * $Log: MushSkinPixelSourceProc.h,v $
 * Revision 1.5  2007/06/11 20:06:17  southa
 * Compatibility fixes and level 27
 *
 * Revision 1.4  2007/04/18 09:23:04  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/08/01 17:21:39  southa
 * River demo
 *
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
    virtual void PrerequisitesCreate(MushGLTexture& outTexture);
    virtual void ToTextureCreate(MushGLTexture& outTexture);
    virtual void ToTextureBind(MushGLTexture& outTexture);
    virtual void DataCreate(void);
    virtual void DataRelease(void);
    virtual const std::vector<Mushware::U8>& DataRGBAU8Get(void) const;

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
    std::vector<Mushware::U8> m_u8Data;
	
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
