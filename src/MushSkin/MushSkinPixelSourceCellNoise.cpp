//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceCellNoise.cpp
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
//%Header } UT/HgyeTr2gY4BhAEUOtbQ
/*
 * $Id: MushSkinPixelSourceCellNoise.cpp,v 1.5 2007/04/18 09:23:04 southa Exp $
 * $Log: MushSkinPixelSourceCellNoise.cpp,v $
 * Revision 1.5  2007/04/18 09:23:04  southa
 * Header and level fixes
 *
 * Revision 1.4  2006/08/01 17:21:38  southa
 * River demo
 *
 * Revision 1.3  2006/06/26 17:03:15  southa
 * win32 installer tweaks
 *
 * Revision 1.2  2006/06/09 21:07:14  southa
 * Tiled skin generation
 *
 * Revision 1.1  2006/06/07 12:15:20  southa
 * Grid and test textures
 *
 * Revision 1.1  2006/06/05 14:37:52  southa
 * Texture generation
 *
 */

#include "MushSkinPixelSourceCellNoise.h"

#include "MushSkinUtil.h"

using namespace Mushware;
using namespace std;

MushSkinPixelSourceCellNoise::MushSkinPixelSourceCellNoise()
{
	m_lineGenerator.CellNoiseInitialise(0);
}

void
MushSkinPixelSourceCellNoise::LineGenerate(Mushware::U8 *outpTileData,
	Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos)
{
    if (PaletteTextureValid())
    {
		std::vector<tVal> colourValues(inNumPixels);
		
		m_lineGenerator.OctavedCellNoiseLineGenerate(colourValues, inNumPixels,
													 PositionTransform(inStartPos), PositionTransform(inEndPos),
													 NumOctaves(), OctaveRatio());

		MushSkinUtil::PalettedToRGBA(outpTileData, &colourValues[0], inNumPixels,
									 PaletteTexture(), PaletteStart(), PaletteVector1());																					
	}
}

//%outOfLineFunctions {

const char *MushSkinPixelSourceCellNoise::AutoName(void) const
{
    return "MushSkinPixelSourceCellNoise";
}

MushcoreVirtualObject *MushSkinPixelSourceCellNoise::AutoClone(void) const
{
    return new MushSkinPixelSourceCellNoise(*this);
}

MushcoreVirtualObject *MushSkinPixelSourceCellNoise::AutoCreate(void) const
{
    return new MushSkinPixelSourceCellNoise;
}

MushcoreVirtualObject *MushSkinPixelSourceCellNoise::AutoVirtualFactory(void)
{
    return new MushSkinPixelSourceCellNoise;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinPixelSourceCellNoise", MushSkinPixelSourceCellNoise::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinPixelSourceCellNoise::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushSkinPixelSourceProc::AutoPrint(ioOut);
    ioOut << "lineGenerator=" << m_lineGenerator;
    ioOut << "]";
}
bool
MushSkinPixelSourceCellNoise::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "lineGenerator")
    {
        ioIn >> m_lineGenerator;
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
MushSkinPixelSourceCellNoise::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushSkinPixelSourceProc::AutoXMLPrint(ioOut);
    ioOut.TagSet("lineGenerator");
    ioOut << m_lineGenerator;
}
//%outOfLineFunctions } HoFX78ezU6IrW0Fxjm2wJQ
