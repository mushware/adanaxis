//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceTest.cpp
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
//%Header } yUgvO5z2fyuWgWEITvu7nA
/*
 * $Id: MushSkinPixelSourceTest.cpp,v 1.5 2007/04/18 09:23:05 southa Exp $
 * $Log: MushSkinPixelSourceTest.cpp,v $
 * Revision 1.5  2007/04/18 09:23:05  southa
 * Header and level fixes
 *
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
MushSkinPixelSourceTest::ToTextureCreate(MushGLTexture& outTexture, volatile bool *pKillSwitch)
{
    t4U32 currentSize = FinalSize() / ReductionFactor();
    U32 pixelDataSize = 4 * currentSize.X()*currentSize.Y();
    m_u8Data.resize(pixelDataSize, 0);

    t4Val objectPos, objectEndPos;

    t2Val startPoint = t2Val(0.0, 0.0);
    t2Val endPoint = t2Val(1.0, 1.0);
    U32 startX = static_cast<U32>(startPoint.X() * currentSize.X());
    U32 startY = static_cast<U32>(startPoint.Y() * currentSize.Y());
    U32 endX = static_cast<U32>(endPoint.X() * currentSize.X());
    U32 endY = static_cast<U32>(endPoint.Y() * currentSize.Y());
    MUSHCOREASSERT(endX >= startX);
    MUSHCOREASSERT(endY >= startY);

    for (U32 y = startY; y < endY; ++y)
    {
        U32 pixelOffset = 4 * (startX + y * currentSize.Y());
        if (pixelOffset + 4 * (endX - startX) > pixelDataSize)
        {
            throw MushcoreDataFail("Pixel data overrun");
        }
        U8 *pTileData = &m_u8Data[pixelOffset];

        objectPos = t4Val(static_cast<tVal>(startX) / currentSize.X(), static_cast<tVal>(y) / currentSize.Y(), 0, 0);
        objectEndPos = t4Val(static_cast<tVal>(endX) / currentSize.X(), static_cast<tVal>(y) / currentSize.Y(), 0, 0);

        if (endX > startX)
        {
            PixelSource().LineGenerate(pTileData, endX - startX, objectPos, objectEndPos);
        }
    }

    outTexture.SizeSet(t4U32(currentSize.X(), currentSize.Y(), 1, 1));
    outTexture.PixelTypeRGBASet();
    outTexture.StorageTypeGLSet();

    PaletteTextureInvalidate();
}


void
MushSkinPixelSourceTest::ToTextureBind(MushGLTexture& outTexture)
{
    // Bind the texture
    outTexture.PixelDataUse(&m_u8Data[0]);
    m_u8Data.resize(0);
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
