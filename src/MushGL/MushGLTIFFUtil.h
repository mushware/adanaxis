//%includeGuardStart {
#ifndef MUSHGLTIFFUTIL_H
#define MUSHGLTIFFUTIL_H
//%includeGuardStart } 2qBPfecKA56vdDUfoBJAcg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLTIFFUtil.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } FUSjt7oP2HjWF6m1BxppWw
/*
 * $Id: MushGLTIFFUtil.h,v 1.1 2006/06/05 11:48:25 southa Exp $
 * $Log: MushGLTIFFUtil.h,v $
 * Revision 1.1  2006/06/05 11:48:25  southa
 * Noise textures
 *
 */

#include "MushGLStandard.h"

class MushGLTIFFUtil
{
public:
	static void RGBASave(const std::string& inFilename, const std::string& inDesc,
						 const Mushware::t2U32& inSize, const Mushware::U8 *pData);
	static void ValSave(const std::string& inFilename, const std::string& inDesc,
						const Mushware::t2U32& inSize, const Mushware::tVal *inpData);
	static void TextureSave(const std::string& inFilename, const std::string& inDesc);
    static std::string CreatorGet(const std::string& inFilename);
    
private:
	static void FieldsSet(void *inpTIFF, const std::string& inDesc, const Mushware::t2U32& inSize,
						  Mushware::U32 inRowsPerStrip);
	
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
