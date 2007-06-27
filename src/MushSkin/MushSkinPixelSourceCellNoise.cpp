//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceCellNoise.cpp
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
//%Header } LjSqbellznD69woXdmeJfQ
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
