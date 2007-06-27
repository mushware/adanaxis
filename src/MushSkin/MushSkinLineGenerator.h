//%includeGuardStart {
#ifndef MUSHSKINLINEGENERATOR_H
#define MUSHSKINLINEGENERATOR_H
//%includeGuardStart } 1GadzkzRSgK/YV1YF+Nb6Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinLineGenerator.h
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
//%Header } JDYn2RavD/biuRK3X4NrEw
/*
 * $Id: MushSkinLineGenerator.h,v 1.10 2007/04/18 09:23:04 southa Exp $
 * $Log: MushSkinLineGenerator.h,v $
 * Revision 1.10  2007/04/18 09:23:04  southa
 * Header and level fixes
 *
 * Revision 1.9  2006/08/01 17:21:38  southa
 * River demo
 *
 * Revision 1.8  2006/07/28 16:52:24  southa
 * Options work
 *
 * Revision 1.7  2006/07/18 16:58:39  southa
 * Texture fixes
 *
 * Revision 1.6  2006/07/17 14:43:42  southa
 * Billboarded deco objects
 *
 * Revision 1.5  2006/06/09 21:07:14  southa
 * Tiled skin generation
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
 * Revision 1.1  2006/06/05 11:48:26  southa
 * Noise textures
 *
 */

#include "MushSkinStandard.h"

//:generate nonvirtual standard ostream xml1
class MushSkinLineGenerator : public MushcoreVirtualObject
{
public:
	enum
	{
		kHashSize = 256,
		kHashMask = kHashSize - 1
	};
	
	void CellNoiseInitialise(Mushware::U32 inSeed);
	void CellNoiseLineGenerate(std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
							   const Mushware::t4Val& inStartPos, const Mushware::t4Val& inEndPos);
	void OctavedCellNoiseLineGenerate(std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
									  const Mushware::t4Val& inStartPos, const Mushware::t4Val& inEndPos,
									  Mushware::U32 inNumOctaves, Mushware::tVal inOctaveRatio);
	void GridLineGenerate(std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
						  const Mushware::t4Val& inStartPos, const Mushware::t4Val& inEndPos);
	void TileShowLineGenerate(std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
							  const std::vector<Mushware::t4Val>& inTexCoords,
							  const Mushware::t4Val& inStartUV, const Mushware::t4Val& inEndUV);
	void RadialInitialise(void) {}
	void OctavedRadialLineGenerate(std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
                                   const Mushware::t4Val& inStartPos, const Mushware::t4Val& inEndPos,
                                   Mushware::U32 inNumOctaves, Mushware::tVal inOctaveRatio);
	void RadialLineGenerate(std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
							   const Mushware::t4Val& inStartPos, const Mushware::t4Val& inEndPos);
private:
	Mushware::t4U32 HashValues(const Mushware::t4Val& inVec);
	Mushware::t4Val FadeValues(const Mushware::t4Val& inVec);
	Mushware::tVal HashScale(Mushware::U8 inValue);
	Mushware::tVal Lerp(Mushware::tVal inProp, Mushware::tVal inA, Mushware::tVal inB);
	
	Mushware::tVal CellNoiseGenerate(const Mushware::t4Val& inPos);
	Mushware::tVal GridGenerate(const Mushware::t4Val& inPos);
	inline Mushware::tVal TileShowGenerate(const Mushware::t4Val& inPos,
										   const std::vector<Mushware::t2Val>& inStartPoints,
										   const std::vector<Mushware::t2Val>& inEdges);
	Mushware::tVal RadialGenerate(const Mushware::t4Val& inPos);

	std::vector<Mushware::U8> m_cellNoiseHash;
	Mushware::t4Val m_gridRatioOver2; //:readwrite;
	Mushware::t4Val m_gridSharpness; //:readwrite;
	
//%classPrototypes {
public:
    const Mushware::t4Val& GridRatioOver2(void) const { return m_gridRatioOver2; }
    void GridRatioOver2Set(const Mushware::t4Val& inValue) { m_gridRatioOver2=inValue; }
    const Mushware::t4Val& GridSharpness(void) const { return m_gridSharpness; }
    void GridSharpnessSet(const Mushware::t4Val& inValue) { m_gridSharpness=inValue; }
    const char *AutoName(void) const;
    MushcoreVirtualObject *AutoClone(void) const;
    MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 9t15v7S3CkK1VrM/RZxJUA
};

inline Mushware::t4U32
MushSkinLineGenerator::HashValues(const Mushware::t4Val& inVec)
{
	Mushware::t4U32 retVal;
	for (Mushware::U32 i=0; i<4; ++i)
	{
		retVal.Set(static_cast<Mushware::U32>(inVec.Get(i)) & kHashMask, i);
	}
	return retVal;
}

inline Mushware::t4Val 
MushSkinLineGenerator::FadeValues(const Mushware::t4Val& inVec)
{
	/* Each element x becomes x*x*(3-x*2)
	 * Vector-at-a-time to take advantage of SIMD instructions
	*/
	Mushware::t4Val retVal;

	retVal = inVec * -2 + 3;
	retVal *= inVec;
	retVal *= inVec;
	return retVal;
}

inline Mushware::tVal
MushSkinLineGenerator::HashScale(Mushware::U8 inValue)
{
	return static_cast<Mushware::tVal>(inValue) / (kHashSize-1);
}

inline Mushware::tVal
MushSkinLineGenerator::Lerp(Mushware::tVal inProp, Mushware::tVal inA, Mushware::tVal inB)
{
	return inB * inProp + inA * (1-inProp);
}

inline Mushware::tVal
MushSkinLineGenerator::CellNoiseGenerate(const Mushware::t4Val& inPos)
{
	MUSHCOREASSERT(m_cellNoiseHash.size() >= kHashSize*2); // m_cellNoiseHash not initialised
	
	Mushware::t4Val floorVec = inPos.Floor();       // Floor oof input position
	Mushware::t4U32 hashVec = HashValues(floorVec); // Hash coordinates for this cube
	Mushware::t4Val cubeVec = inPos - floorVec;     // Fractional offsets into this cube
	Mushware::t4Val fadeVec = FadeValues(cubeVec);  // Interpolation coefficient corresponding to to cubeVec
	
	const std::vector<Mushware::U8>& p = m_cellNoiseHash;
	const Mushware::t4U32& h = hashVec;
	
#define MUSH_HASH_SCALE(x,y,z,w) HashScale(p[p[p[p[h.X()+(x)] + h.Y()+(y)] + h.Z()+(z)] + h.W()+(w)])
	
	Mushware::tVal p0000 = MUSH_HASH_SCALE(0,0,0,0);
	Mushware::tVal p1000 = MUSH_HASH_SCALE(1,0,0,0);
	Mushware::tVal p0100 = MUSH_HASH_SCALE(0,1,0,0);
	Mushware::tVal p1100 = MUSH_HASH_SCALE(1,1,0,0);
	Mushware::tVal p0010 = MUSH_HASH_SCALE(0,0,1,0);
	Mushware::tVal p1010 = MUSH_HASH_SCALE(1,0,1,0);
	Mushware::tVal p0110 = MUSH_HASH_SCALE(0,1,1,0);
	Mushware::tVal p1110 = MUSH_HASH_SCALE(1,1,1,0);
	Mushware::tVal p0001 = MUSH_HASH_SCALE(0,0,0,1);
	Mushware::tVal p1001 = MUSH_HASH_SCALE(1,0,0,1);
	Mushware::tVal p0101 = MUSH_HASH_SCALE(0,1,0,1);
	Mushware::tVal p1101 = MUSH_HASH_SCALE(1,1,0,1);
	Mushware::tVal p0011 = MUSH_HASH_SCALE(0,0,1,1);
	Mushware::tVal p1011 = MUSH_HASH_SCALE(1,0,1,1);
	Mushware::tVal p0111 = MUSH_HASH_SCALE(0,1,1,1);
	Mushware::tVal p1111 = MUSH_HASH_SCALE(1,1,1,1);

#undef MUSH_HASH_SCALE
	
	// Quadrilinear interpolation of hash values
	
	Mushware::tVal retVal = 
		Lerp(fadeVec.W(),
			 Lerp(fadeVec.Z(), 
				  Lerp(fadeVec.Y(), 
					   Lerp(fadeVec.X(), p0000, p1000), Lerp(fadeVec.X(), p0100, p1100)
					   ),
				  Lerp(fadeVec.Y(), 
					   Lerp(fadeVec.X(), p0010, p1010), Lerp(fadeVec.X(), p0110, p1110)
					   )
				  ),
			 Lerp(fadeVec.Z(), 
				  Lerp(fadeVec.Y(), 
					   Lerp(fadeVec.X(), p0001, p1001), Lerp(fadeVec.X(), p0101, p1101)
					   ),
				  Lerp(fadeVec.Y(), 
					   Lerp(fadeVec.X(), p0011, p1011), Lerp(fadeVec.X(), p0111, p1111)
					   )
				  )
			 );
	return retVal;
}

inline void
MushSkinLineGenerator::CellNoiseLineGenerate(std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
											 const Mushware::t4Val& inStartPos, const Mushware::t4Val& inEndPos)
{
	MUSHCOREASSERT(outData.size() >= inNumPixels);;
	
    Mushware::t4Val objectPos = inStartPos;
    Mushware::t4Val objectPosStep = (inEndPos - inStartPos) / inNumPixels;
	
	for (Mushware::U32 i=0; i<inNumPixels; ++i)
	{
		outData[i] = CellNoiseGenerate(objectPos);
		objectPos += objectPosStep;
	}
}

inline Mushware::tVal
MushSkinLineGenerator::GridGenerate(const Mushware::t4Val& inPos)
{
	Mushware::tVal lowestMultiplier = 1;

	for (Mushware::U32 i=0; i<4; ++i)
	{
		Mushware::tVal multiplier = 1;
		
		// Get fractional part of coordinate
		double dummy;
		Mushware::tVal x = std::modf(inPos[i], &dummy);
		
		// If greater than half way, reflect into the first half
		if (x < 0) x = -x;
		if (x > 0.5) x = 1-x;
		
		MUSHCOREASSERT(x >= 0);
		MUSHCOREASSERT(x <= 0.5);
		
		if (m_gridSharpness[i] > 0.999999)
		{
			multiplier = (x >= m_gridRatioOver2[i])?1:0;
		}
		else
		{
			
			Mushware::tVal sharpness = m_gridSharpness[i];
			
			sharpness = std::tan((M_PI/2)*sharpness);
            
			Mushware::tVal t = (x - m_gridRatioOver2[i]) * sharpness + 0.5;
			
			if (t <= 0)
			{
				multiplier = 0;	
			}
			else if (t >= 1)
			{
				multiplier = 1;
			}
			else
			{
				multiplier = t*t*(3-2*t);
			}
		}
			
		if (lowestMultiplier > multiplier)
		{
			lowestMultiplier = multiplier;
		}
	}
	
	return 1-lowestMultiplier;
}

inline void
MushSkinLineGenerator::GridLineGenerate(std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
										const Mushware::t4Val& inStartPos, const Mushware::t4Val& inEndPos)
{
	MUSHCOREASSERT(outData.size() >= inNumPixels);;
	
    Mushware::t4Val objectPos = inStartPos;
    Mushware::t4Val objectPosStep = (inEndPos - inStartPos) / inNumPixels;
	
	for (Mushware::U32 i=0; i<inNumPixels; ++i)
	{
		outData[i] = GridGenerate(objectPos);
		objectPos += objectPosStep;
	}
}

inline Mushware::tVal
MushSkinLineGenerator::TileShowGenerate(const Mushware::t4Val& inPos,
										const std::vector<Mushware::t2Val>& inStartPoints,
										const std::vector<Mushware::t2Val>& inEdges)
{
	Mushware::U32 numEdges = inEdges.size();
	
	bool positive = false;
	bool negative = false;
	
	for (Mushware::U32 i=0; i<numEdges; ++i)
	{
		Mushware::t2Val startToPos = Mushware::t2Val(inPos.X(), inPos.Y()) - inStartPoints[i];
		Mushware::tVal sign = startToPos.X() * inEdges[i].Y() - startToPos.Y() * inEdges[i].X();
		if (sign >= 0)
		{
			positive = true;
		}
		else
		{
			negative = true;
		}	
	}
	Mushware::tVal retVal;
	if (positive && negative)
	{
		retVal = 0; // Outside of tile	
	}
	else
	{
		retVal = 1;	
	}
	return retVal;
}	

inline void
MushSkinLineGenerator::TileShowLineGenerate(std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
											const std::vector<Mushware::t4Val>& inTexCoords,
											const Mushware::t4Val& inStartUV, const Mushware::t4Val& inEndUV)
{
	MUSHCOREASSERT(outData.size() >= inNumPixels);;
	
    Mushware::t4Val uvPos = inStartUV;
    Mushware::t4Val uvPosStep = (inEndUV - inStartUV) / inNumPixels;
		
	Mushware::U32 texCoordsSize = inTexCoords.size();
	
	std::vector<Mushware::t2Val> startVectors(texCoordsSize);
	std::vector<Mushware::t2Val> edgeVectors(texCoordsSize);
	
	for (Mushware::U32 i=0; i<texCoordsSize; ++i)
	{
		startVectors[i] = Mushware::t2Val(inTexCoords[i].X(), inTexCoords[i].Y());
		Mushware::t4Val edge = inTexCoords[ (i+1) % texCoordsSize ] - inTexCoords[i];
		edgeVectors[i] = Mushware::t2Val(edge.X(), edge.Y());
	}
	
	for (Mushware::U32 i=0; i<inNumPixels; ++i)
	{
		outData[i] = TileShowGenerate(uvPos, startVectors, edgeVectors);
		uvPos += uvPosStep;
	}
}

inline Mushware::tVal
MushSkinLineGenerator::RadialGenerate(const Mushware::t4Val& inPos)
{		
    Mushware::tVal dist = std::sqrt(inPos.X()*inPos.X() + inPos.Y()*inPos.Y());
    Mushware::tVal clampedDist = dist;
    MushcoreUtil::Constrain<Mushware::tVal>(clampedDist, 0, 1);
    Mushware::tVal clampedInvDist = 1.0 - clampedDist;
    
    Mushware::tVal retVal = clampedInvDist;
    MushcoreUtil::Constrain<Mushware::tVal>(retVal, 0, 1);
    
	return retVal;
}

inline void
MushSkinLineGenerator::RadialLineGenerate(std::vector<Mushware::tVal>& outData, Mushware::U32 inNumPixels,
											 const Mushware::t4Val& inStartPos, const Mushware::t4Val& inEndPos)
{
	MUSHCOREASSERT(outData.size() >= inNumPixels);;
    Mushware::t4Val objectPos = inStartPos;

    Mushware::t4Val objectPosStep = (inEndPos - inStartPos) / inNumPixels;
    
    for (Mushware::U32 i=0; i<inNumPixels; ++i)
    {
        outData[i] = RadialGenerate(objectPos);
        objectPos += objectPosStep;
    }
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushSkinLineGenerator& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
inline MushcoreXMLIStream&
operator>>(MushcoreXMLIStream& ioIn, MushSkinLineGenerator& outObj)
{
    throw MushcoreDataFail("Cannot read XML object type 'MushSkinLineGenerator'");
    return ioIn;
}
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushSkinLineGenerator& inObj)
{
    inObj.AutoXMLPrint(ioOut);
    return ioOut;
}
//%inlineHeader } c/25EfbvScu7pJKtlq9g8A

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
