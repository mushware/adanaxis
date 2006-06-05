//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinLineGenerator.cpp
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
//%Header } /ogEinXWaS3ZU9x1JORYXA
/*
 * $Id: MushSkinLineGenerator.cpp,v 1.1 2006/06/05 11:48:25 southa Exp $
 * $Log: MushSkinLineGenerator.cpp,v $
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
	const Mushware::t4Val& inStartPos, const Mushware::t4Val& inEndPos, Mushware::U32 numOctaves)
{
	MUSHCOREASSERT(outData.size() >= inNumPixels);
	
	for (U32 i=0; i<inNumPixels; ++i)
	{
		outData[i] = 0;
	}
	
	tVal spaceMultiplier = 1;
	tVal amplitude = 1;
	tVal cumulativeAmplitude = 0;
	for (U32 octave=0; octave < numOctaves; ++octave)
	{
		std::vector<tVal> octaveData(inNumPixels);
		CellNoiseLineGenerate(octaveData, inNumPixels, spaceMultiplier * inStartPos,
							  spaceMultiplier * inEndPos);
		
		for (U32 i=0; i<inNumPixels; ++i)
		{
			outData[i] += amplitude * octaveData[i];
		}
		cumulativeAmplitude += amplitude;
		amplitude /= 2;
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
    ioOut << "cellNoiseHash=" << m_cellNoiseHash;
    ioOut << "]";
}
bool
MushSkinLineGenerator::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "cellNoiseHash")
    {
        ioIn >> m_cellNoiseHash;
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
}
//%outOfLineFunctions } 9v76OG1vOKDgtg1eBbFSEg
