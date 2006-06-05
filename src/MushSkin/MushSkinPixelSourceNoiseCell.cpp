//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceNoiseCell.cpp
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
//%Header } zwFz0LnO2rpz/X7otVp1FA
/*
 * $Id$
 * $Log$
 */

#include "MushSkinPixelSourceNoiseCell.h"

#include "MushSkinUtil.h"

using namespace Mushware;
using namespace std;

MushSkinPixelSourceNoiseCell::MushSkinPixelSourceNoiseCell()
{
	m_lineGenerator.CellNoiseInitialise(0);
}

void
MushSkinPixelSourceNoiseCell::TileLineGenerate(Mushware::U8 *outpTileData, const MushMesh4Mesh::tTextureTile& inTileRef,
	Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos)
{
    if (m_pPaletteTexture != NULL)
    {
		std::vector<tVal> noiseValues(inNumPixels);
		
		m_lineGenerator.OctavedCellNoiseLineGenerate(noiseValues, inNumPixels, 2*inStartPos, 2*inEndPos, 8);
		

		MushSkinUtil::PalettedToRGBA(outpTileData, &noiseValues[0], inNumPixels,
									 *m_pPaletteTexture, m_paletteStart, m_paletteVector1);																					
	}
}

//%outOfLineFunctions {

const char *MushSkinPixelSourceNoiseCell::AutoName(void) const
{
    return "MushSkinPixelSourceNoiseCell";
}

MushcoreVirtualObject *MushSkinPixelSourceNoiseCell::AutoClone(void) const
{
    return new MushSkinPixelSourceNoiseCell(*this);
}

MushcoreVirtualObject *MushSkinPixelSourceNoiseCell::AutoCreate(void) const
{
    return new MushSkinPixelSourceNoiseCell;
}

MushcoreVirtualObject *MushSkinPixelSourceNoiseCell::AutoVirtualFactory(void)
{
    return new MushSkinPixelSourceNoiseCell;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinPixelSourceNoiseCell", MushSkinPixelSourceNoiseCell::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinPixelSourceNoiseCell::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushSkinPixelSourceNoise::AutoPrint(ioOut);
    ioOut << "lineGenerator=" << m_lineGenerator;
    ioOut << "]";
}
bool
MushSkinPixelSourceNoiseCell::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (MushSkinPixelSourceNoise::AutoXMLDataProcess(ioIn, inTagStr))
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
MushSkinPixelSourceNoiseCell::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushSkinPixelSourceNoise::AutoXMLPrint(ioOut);
    ioOut.TagSet("lineGenerator");
    ioOut << m_lineGenerator;
}
//%outOfLineFunctions } BIey1Jn101qy0Gnyrm5imw
