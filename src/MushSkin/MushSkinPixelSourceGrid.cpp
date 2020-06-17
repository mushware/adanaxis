//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceGrid.cpp
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
//%Header } ddA1TQPrKeTyUGE8CLWZfQ
/*
 * $Id: MushSkinPixelSourceGrid.cpp,v 1.5 2007/04/18 09:23:04 southa Exp $
 * $Log: MushSkinPixelSourceGrid.cpp,v $
 * Revision 1.5  2007/04/18 09:23:04  southa
 * Header and level fixes
 *
 * Revision 1.4  2006/08/01 17:21:38  southa
 * River demo
 *
 * Revision 1.3  2006/06/09 21:07:14  southa
 * Tiled skin generation
 *
 * Revision 1.2  2006/06/07 14:25:56  southa
 * Grid texture fixes
 *
 * Revision 1.1  2006/06/07 12:15:21  southa
 * Grid and test textures
 *
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
	m_lineGenerator.GridRatioOver2Set(GridRatio() / 2);
	m_lineGenerator.GridSharpnessSet(GridSharpness());
	
    if (PaletteTextureValid())
    {
		std::vector<tVal> colourValues(inNumPixels);
		
		m_lineGenerator.GridLineGenerate(colourValues, inNumPixels,
										 PositionTransform(inStartPos), PositionTransform(inEndPos));
		
		MushSkinUtil::PalettedToRGBA(outpTileData, &colourValues[0], inNumPixels,
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
