//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceRadial.cpp
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
//%Header } nBqySfDGrWsyYOYUgmu9dQ
/*
 * $Id$
 * $Log$
 */

#include "MushSkinPixelSourceRadial.h"

#include "MushSkinUtil.h"

using namespace Mushware;
using namespace std;

MushSkinPixelSourceRadial::MushSkinPixelSourceRadial()
{
	m_lineGenerator.RadialInitialise();
}

void
MushSkinPixelSourceRadial::LineGenerate(Mushware::U8 *outpTileData,
                                           Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos)
{
    if (PaletteTextureValid())
    {
		std::vector<tVal> colourValues(inNumPixels);
		
		m_lineGenerator.OctavedRadialLineGenerate(colourValues, inNumPixels,
													 PositionTransform(inStartPos), PositionTransform(inEndPos),
													 NumOctaves(), OctaveRatio());
        
		MushSkinUtil::PalettedToRGBA(outpTileData, &colourValues[0], inNumPixels,
									 PaletteTexture(), PaletteStart(), PaletteVector1());																					
	}
}
//%outOfLineFunctions {

const char *MushSkinPixelSourceRadial::AutoName(void) const
{
    return "MushSkinPixelSourceRadial";
}

MushcoreVirtualObject *MushSkinPixelSourceRadial::AutoClone(void) const
{
    return new MushSkinPixelSourceRadial(*this);
}

MushcoreVirtualObject *MushSkinPixelSourceRadial::AutoCreate(void) const
{
    return new MushSkinPixelSourceRadial;
}

MushcoreVirtualObject *MushSkinPixelSourceRadial::AutoVirtualFactory(void)
{
    return new MushSkinPixelSourceRadial;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinPixelSourceRadial", MushSkinPixelSourceRadial::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinPixelSourceRadial::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushSkinPixelSourceProc::AutoPrint(ioOut);
    ioOut << "lineGenerator=" << m_lineGenerator;
    ioOut << "]";
}
bool
MushSkinPixelSourceRadial::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushSkinPixelSourceRadial::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushSkinPixelSourceProc::AutoXMLPrint(ioOut);
    ioOut.TagSet("lineGenerator");
    ioOut << m_lineGenerator;
}
//%outOfLineFunctions } qiYNk1qlDM8hXP6s1rU+NA
