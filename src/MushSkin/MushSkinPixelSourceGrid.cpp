//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceGrid.cpp
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
//%Header } 04zVh+OEPDlIVf3XywyElw
/*
 * $Id$
 * $Log$
 */

#include "MushSkinPixelSourceGrid.h"

using namespace Mushware;
using namespace std;

MushSkinPixelSourceGrid::MushSkinPixelSourceGrid() :
    m_gridRatio(0.5,0.5,0.5,0.5),
    m_gridSharpness(1,1,1,1)
{
}

void
MushSkinPixelSourceGrid::ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue)
{
	std::string nameStr = inName.String();
	
	if (nameStr == "gridratio")
	{
		m_gridRatio = t4Val(inValue.ValVector());
	}	
	else if (nameStr == "gridsharpness")
	{
		m_gridSharpness = t4Val(inValue.ValVector());
	}	
	else
	{
		MushSkinPixelSourceProc::ParamDecode(inName, inValue);
	}
}

void
MushSkinPixelSourceGrid::LineGenerate(Mushware::U8 *outpTileData, Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos)
{
	m_lineGenerator.GridRatioSet(GridRatio());
	m_lineGenerator.GridSharpnessSet(GridSharpness());
	
    if (PaletteTextureValid())
    {
		std::vector<tVal> noiseValues(inNumPixels);
		
		m_lineGenerator.GridLineGenerate(noiseValues, inNumPixels,
										 PositionTransform(inStartPos), PositionTransform(inEndPos));
		
		MushSkinUtil::PalettedToRGBA(outpTileData, &noiseValues[0], inNumPixels,
									 PaletteTexture(), PaletteStart(), PaletteVector1());																					
	}
}

//%outOfLineFunctions {

const char *MushSkinPixelSourceGrid::AutoName(void) const
{
    return "MushSkinPixelSourceGrid";
}

MushcoreVirtualObject *MushSkinPixelSourceGrid::AutoClone(void) const
{
    return new MushSkinPixelSourceGrid(*this);
}

MushcoreVirtualObject *MushSkinPixelSourceGrid::AutoCreate(void) const
{
    return new MushSkinPixelSourceGrid;
}

MushcoreVirtualObject *MushSkinPixelSourceGrid::AutoVirtualFactory(void)
{
    return new MushSkinPixelSourceGrid;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinPixelSourceGrid", MushSkinPixelSourceGrid::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinPixelSourceGrid::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushSkinPixelSourceProc::AutoPrint(ioOut);
    ioOut << "lineGenerator=" << m_lineGenerator << ", ";
    ioOut << "gridRatio=" << m_gridRatio << ", ";
    ioOut << "gridSharpness=" << m_gridSharpness;
    ioOut << "]";
}
bool
MushSkinPixelSourceGrid::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "gridRatio")
    {
        ioIn >> m_gridRatio;
    }
    else if (inTagStr == "gridSharpness")
    {
        ioIn >> m_gridSharpness;
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
MushSkinPixelSourceGrid::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushSkinPixelSourceProc::AutoXMLPrint(ioOut);
    ioOut.TagSet("lineGenerator");
    ioOut << m_lineGenerator;
    ioOut.TagSet("gridRatio");
    ioOut << m_gridRatio;
    ioOut.TagSet("gridSharpness");
    ioOut << m_gridSharpness;
}
//%outOfLineFunctions } r0klM0JrOxLzobwPTfk9zA
