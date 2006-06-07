//%includeGuardStart {
#ifndef MUSHSKINLINEGENERATOR_H
#define MUSHSKINLINEGENERATOR_H
//%includeGuardStart } 1GadzkzRSgK/YV1YF+Nb6Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinLineGenerator.h
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
//%Header } tuTK6NcDPsNibg7CubVnHw
/*
 * $Id: MushSkinLineGenerator.h,v 1.2 2006/06/05 14:37:52 southa Exp $
 * $Log: MushSkinLineGenerator.h,v $
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

private:
	Mushware::t4U32 HashValues(const Mushware::t4Val& inVec);
	Mushware::t4Val FadeValues(const Mushware::t4Val& inVec);
	Mushware::tVal HashScale(Mushware::U8 inValue);
	Mushware::tVal Lerp(Mushware::tVal inProp, Mushware::tVal inA, Mushware::tVal inB);
	
	Mushware::tVal CellNoiseGenerate(const Mushware::t4Val& inPos);
	Mushware::tVal GridGenerate(const Mushware::t4Val& inPos);
	
	std::vector<Mushware::U8> m_cellNoiseHash;
	Mushware::t4Val m_gridRatio; //:readwrite;
	Mushware::t4Val m_gridSharpness; //:readwrite;
	
//%classPrototypes {
public:
    const Mushware::t4Val& GridRatio(void) const { return m_gridRatio; }
    void GridRatioSet(const Mushware::t4Val& inValue) { m_gridRatio=inValue; }
    const Mushware::t4Val& GridSharpness(void) const { return m_gridSharpness; }
    void GridSharpnessSet(const Mushware::t4Val& inValue) { m_gridSharpness=inValue; }
    const char *AutoName(void) const;
    MushcoreVirtualObject *AutoClone(void) const;
    MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Y0y376oIVqgz9UiKRsSLsw
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
	Mushware::t4Val floorVec = inPos.Floor();        // Floor of input position
	Mushware::t4Val cubeVec = inPos - floorVec;      // Fractional offsets into this cube
	Mushware::t4Val gridVec = cubeVec - m_gridRatio; // Offset from the grid boundary
	
	Mushware::tVal lowestMultiplier = 1;

	for (Mushware::U32 i=0; i<4; ++i)
	{
		if (gridVec[i] <= 0)
		{
		    // Point is within the grid boundary
			Mushware::tVal multiplier;
			if (m_gridSharpness[i] < 1.0)
			{
				multiplier = gridVec[i] / (1 - m_gridSharpness[i]);
				if (multiplier > 1)
				{
					multiplier = 1;	
				}
				else
				{
					multiplier = multiplier*multiplier*(3-2*multiplier);
				}
			}
			else
			{
				multiplier = 0;	
			}
			if (lowestMultiplier > multiplier)
			{
				lowestMultiplier = multiplier;
			}
		}
	}
	
	return lowestMultiplier;
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
