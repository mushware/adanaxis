//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinUtil.cpp
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
//%Header } 6YaronELxKsMoIhQKqR4AA
/*
 * $Id: MushSkinUtil.cpp,v 1.1 2006/06/05 11:48:26 southa Exp $
 * $Log: MushSkinUtil.cpp,v $
 * Revision 1.1  2006/06/05 11:48:26  southa
 * Noise textures
 *
 */

#include "MushSkinUtil.h"

using namespace Mushware;
using namespace std;

void
MushSkinUtil::PalettedToRGBA(Mushware::U8 *outpData, const Mushware::tVal *inpData,
							 Mushware::U32 inNumPixels, const MushGLTexture& ioTexture,
							 const Mushware::t2Val& inStartPos, const Mushware::t2Val& inVec)
{
	Mushware::U8 *pData = outpData;
   	for (U32 i=0; i<inNumPixels; ++i)	
	{
		t4Val pixelCol = ioTexture.U8RGBALookup(inStartPos + inpData[i] * inVec);
		
		*pData++ = static_cast<U8>(pixelCol.X()); // Red
		*pData++ = static_cast<U8>(pixelCol.Y()); // Green
		*pData++ = static_cast<U8>(pixelCol.Z()); // Blue
		*pData++ = static_cast<U8>(pixelCol.W()); // Alpha
	}
}
