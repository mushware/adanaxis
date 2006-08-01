//%includeGuardStart {
#ifndef MUSHSKINUTIL_H
#define MUSHSKINUTIL_H
//%includeGuardStart } P1MS7xj1VbWj+jgxypUXJw
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinUtil.h
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } x+iG0OCuJvniS7V3C8ByMw
/*
 * $Id: MushSkinUtil.h,v 1.2 2006/06/07 12:15:22 southa Exp $
 * $Log: MushSkinUtil.h,v $
 * Revision 1.2  2006/06/07 12:15:22  southa
 * Grid and test textures
 *
 * Revision 1.1  2006/06/05 11:48:26  southa
 * Noise textures
 *
 */

#include "MushSkinStandard.h"

class MushSkinUtil
{
public:
	static void PalettedToRGBA(Mushware::U8 *outpData, const Mushware::tVal *inpData,
							   Mushware::U32 inNumPixels, const MushGLTexture& ioTexture,
							   const Mushware::t2Val& inStartPos, const Mushware::t2Val& inVec);
	
private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
