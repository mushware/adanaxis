//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinLineGenerator.cpp
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
//%Header } 4g172sEJC8H7gwmHtc+LBg
/*
 * $Id: MushSkinLineGenerator.cpp,v 1.7 2007/04/18 09:23:04 southa Exp $
 * $Log: MushSkinLineGenerator.cpp,v $
 * Revision 1.7  2007/04/18 09:23:04  southa
 * Header and level fixes
 *
 * Revision 1.6  2006/08/01 17:21:37  southa
 * River demo
 *
 * Revision 1.5  2006/07/17 14:43:42  southa
 * Billboarded deco objects
 *
 * Revision 1.4  2006/06/07 14:25:56  southa
 * Grid texture fixes
 *
 * Revision 1.3  2006/06/07 12:15:20  southa
 * Grid and test textures
 *
 * Revision 1.2  2006/06/05 14:37:52  southa
 * Texture generation
 *
 * Revision 1.1  2006/06/05 11:48:25  southa
 * Noise textures
 *
 */

#include "MushSkinLineGenerator.h"

using namespace Mushware;
using namespace std;

void
MushSkinLineGenerator::CellNoiseInitialise(Mushware::U32 inSeed)
{
	m_cellNoiseHash.resize(2*kHashSize);

	U32 seed = inSeed;
	for (U32 i=0; i<kHashSize; ++i)
	{
		U32 lo = 16807 * ((seed+1) & 0xffff);
		U32 hi = 16807 * (seed >> 16);
		lo += (hi & 0x7fff) << 16;
		lo += hi >> 15;
		if (lo > 0x7fffffff) lo -= 0x7fffffff;
		seed = lo;
		m_cellNoiseHash[i] = seed & 0xff;
		m_cellNoiseHash[i+kHashSize] = seed & 0xff;
	}
}

void
MushSkinLineGenerator::OctavedCellNoiseLineGenerate(
	std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
	const Mushware::t4Val& inStartPos, const Mushware::t4Val& inEndPos,
	Mushware::U32 inNumOctaves, Mushware::tVal inOctaveRatio)
{
	MUSHCOREASSERT(outData.size() >= inNumPixels);
	
	for (U32 i=0; i<inNumPixels; ++i)
	{
		outData[i] = 0;
	}
	
	tVal spaceMultiplier = 1;
	tVal amplitude = 1;
	tVal cumulativeAmplitude = 0;
	
	for (U32 octave=0; octave < inNumOctaves; ++octave)
	{
		std::vector<tVal> octaveData(inNumPixels);
		CellNoiseLineGenerate(octaveData, inNumPixels, spaceMultiplier * inStartPos,
							  spaceMultiplier * inEndPos);
		
		for (U32 i=0; i<inNumPixels; ++i)
		{
			outData[i] += amplitude * octaveData[i];
		}
		cumulativeAmplitude += amplitude;
		amplitude *= inOctaveRatio;
		spaceMultiplier *= 2;
	}
	
	for (U32 i=0; i<inNumPixels; ++i)
	{
		outData[i] /= cumulativeAmplitude;
	}
}

void
MushSkinLineGenerator::OctavedRadialLineGenerate(std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
                                                 const Mushware::t4Val& inStartPos, const Mushware::t4Val& inEndPos,
                                                 Mushware::U32 inNumOctaves, Mushware::tVal inOctaveRatio)
{
	MUSHCOREASSERT(outData.size() >= inNumPixels);
	
	for (U32 i=0; i<inNumPixels; ++i)
	{
		outData[i] = 0;
	}
	
	tVal spaceMultiplier = 1;
	tVal amplitude = 1;
	tVal cumulativeAmplitude = 0;
	
	for (U32 octave=0; octave < inNumOctaves; ++octave)
	{
		std::vector<tVal> octaveData(inNumPixels);
		RadialLineGenerate(octaveData, inNumPixels, spaceMultiplier * inStartPos,
                           spaceMultiplier * inEndPos);
		
		for (U32 i=0; i<inNumPixels; ++i)
		{
			outData[i] += amplitude * octaveData[i];
		}
		cumulativeAmplitude += amplitude;
		amplitude *= inOctaveRatio;
		spaceMultiplier *= 2;
	}
	
	for (U32 i=0; i<inNumPixels; ++i)
	{
		outData[i] /= cumulativeAmplitude;
	}
}

//%outOfLineFunctions {

const char *MushSkinLineGenerator::AutoName(void) const
{
    return "MushSkinLineGenerator";
}

MushcoreVirtualObject *MushSkinLineGenerator::AutoClone(void) const
{
    return new MushSkinLineGenerator(*this);
}

MushcoreVirtualObject *MushSkinLineGenerator::AutoCreate(void) const
{
    return new MushSkinLineGenerator;
}

MushcoreVirtualObject *MushSkinLineGenerator::AutoVirtualFactory(void)
{
    return new MushSkinLineGenerator;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinLineGenerator", MushSkinLineGenerator::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinLineGenerator::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "cellNoiseHash=" << m_cellNoiseHash << ", ";
    ioOut << "gridRatioOver2=" << m_gridRatioOver2 << ", ";
    ioOut << "gridSharpness=" << m_gridSharpness;
    ioOut << "]";
}
bool
MushSkinLineGenerator::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "cellNoiseHash")
    {
        ioIn >> m_cellNoiseHash;
    }
    else if (inTagStr == "gridRatioOver2")
    {
        ioIn >> m_gridRatioOver2;
    }
    else if (inTagStr == "gridSharpness")
    {
        ioIn >> m_gridSharpness;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushSkinLineGenerator::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("cellNoiseHash");
    ioOut << m_cellNoiseHash;
    ioOut.TagSet("gridRatioOver2");
    ioOut << m_gridRatioOver2;
    ioOut.TagSet("gridSharpness");
    ioOut << m_gridSharpness;
}
//%outOfLineFunctions } +CUv04aNXKzlqn+1hLDi2A
