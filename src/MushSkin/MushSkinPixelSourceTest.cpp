//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceTest.cpp
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
//%Header } Z+ok8bbipY/nXmUyKA7m7A
/*
 * $Id: MushSkinPixelSourceTest.cpp,v 1.4 2006/08/01 17:21:40 southa Exp $
 * $Log: MushSkinPixelSourceTest.cpp,v $
 * Revision 1.4  2006/08/01 17:21:40  southa
 * River demo
 *
 * Revision 1.3  2006/07/21 10:52:08  southa
 * win32 build fixes
 *
 * Revision 1.2  2006/06/07 12:15:21  southa
 * Grid and test textures
 *
 * Revision 1.1  2006/06/05 14:37:52  southa
 * Texture generation
 *
 */

#include "MushSkinPixelSourceTest.h"

#include "MushSkinPixelSourceGrid.h"

using namespace Mushware;
using namespace std;

MushSkinPixelSourceTest::MushSkinPixelSourceTest()
{
    m_pPixelSource = new MushSkinPixelSourceGrid;
}

MushSkinPixelSourceTest::~MushSkinPixelSourceTest()
{
    delete m_pPixelSource;
}
void
MushSkinPixelSourceTest::ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue)
{
	PixelSource().ParamDecode(inName, inValue);

	try
	{
		MushSkinPixelSourceProc::ParamDecode(inName, inValue);
	}
	catch (MushcoreNonFatalFail &e)
	{
		// Discard non-fatal errors about unrecognised parameters	
	}
}

MushSkinPixelSourceProc&
MushSkinPixelSourceTest::PixelSource(void) const
{
	MushSkinPixelSourceProc *pPixelSource = dynamic_cast<MushSkinPixelSourceProc *>(m_pPixelSource);
	if (m_pPixelSource == NULL)	
	{
		throw MushcoreLogicFail("Invalid pixel source");
	}
	return *pPixelSource;
}

void
MushSkinPixelSourceTest::ToTextureCreate(MushGLTexture& outTexture)
{
    U32 pixelDataSize = 4*Size().X()*Size().Y();
    std::vector<U8> pixelData(pixelDataSize, 0);
    
    t4Val objectPos, objectEndPos;

	t2Val startPoint = t2Val(0.0, 0.0);
	t2Val endPoint = t2Val(1.0, 1.0);
	U32 startX = static_cast<U32>(startPoint.X() * Size().X());
	U32 startY = static_cast<U32>(startPoint.Y() * Size().Y());
	U32 endX = static_cast<U32>(endPoint.X() * Size().X());
	U32 endY = static_cast<U32>(endPoint.Y() * Size().Y());
	MUSHCOREASSERT(endX >= startX);
	MUSHCOREASSERT(endY >= startY);
	
	for (U32 y=startY; y<endY; ++y)
	{
		U32 pixelOffset = 4*(startX+y*Size().Y());
		if (pixelOffset + 4*(endX - startX) > pixelDataSize)
		{
			throw MushcoreDataFail("Pixel data overrun");
		}
		U8 *pTileData = &pixelData[pixelOffset];
		
		objectPos = t4Val(static_cast<tVal>(startX) / Size().X(), static_cast<tVal>(y) / Size().Y(), 0, 0);
		objectEndPos = t4Val(static_cast<tVal>(endX) / Size().X(), static_cast<tVal>(y) / Size().Y(), 0, 0);
		
		if (endX > startX)
		{
			PixelSource().LineGenerate(pTileData, endX - startX, objectPos, objectEndPos);
		}
	}
	
    PaletteTextureInvalidate();
    
    // Bind the texture
    outTexture.SizeSet(t4U32(Size().X(), Size().Y(), 1, 1));
    outTexture.PixelTypeRGBASet();
    outTexture.StorageTypeGLSet();
    outTexture.PixelDataUse(&pixelData[0]);
	
	MushGLTIFFUtil::TextureSave(MushGLCacheControl::Sgl().
								TextureCachePlainFilenameMake("test-"+outTexture.Name()+".tiff"), outTexture.UniqueIdentifier());
}

//%outOfLineFunctions {

const char *MushSkinPixelSourceTest::AutoName(void) const
{
    return "MushSkinPixelSourceTest";
}

MushcoreVirtualObject *MushSkinPixelSourceTest::AutoClone(void) const
{
    return new MushSkinPixelSourceTest(*this);
}

MushcoreVirtualObject *MushSkinPixelSourceTest::AutoCreate(void) const
{
    return new MushSkinPixelSourceTest;
}

MushcoreVirtualObject *MushSkinPixelSourceTest::AutoVirtualFactory(void)
{
    return new MushSkinPixelSourceTest;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinPixelSourceTest", MushSkinPixelSourceTest::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinPixelSourceTest::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushSkinPixelSourceProc::AutoPrint(ioOut);
    if (m_pPixelSource == NULL)
    {
        ioOut << "pPixelSource=NULL" ;
    }
    else
    {
        ioOut << "pPixelSource=" << *m_pPixelSource;
    }
    ioOut << "]";
}
bool
MushSkinPixelSourceTest::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "pPixelSource")
    {
        ioIn >> m_pPixelSource;
    }
    else if (MushSkinPixelSourceProc::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushSkinPixelSourceTest::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushSkinPixelSourceProc::AutoXMLPrint(ioOut);
    ioOut.TagSet("pPixelSource");
    ioOut << m_pPixelSource;
}
//%outOfLineFunctions } T5d1J/csilnsW9Qc7d7IrA
