//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceRadial.cpp
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
//%Header } nfStv5u9QiqgSGuO+Qw4cQ
/*
 * $Id: MushSkinPixelSourceRadial.cpp,v 1.3 2007/04/18 09:23:04 southa Exp $
 * $Log: MushSkinPixelSourceRadial.cpp,v $
 * Revision 1.3  2007/04/18 09:23:04  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/08/01 17:21:39  southa
 * River demo
 *
 * Revision 1.1  2006/07/17 14:43:43  southa
 * Billboarded deco objects
 *
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
