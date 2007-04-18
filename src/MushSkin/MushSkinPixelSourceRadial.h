//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCERADIAL_H
#define MUSHSKINPIXELSOURCERADIAL_H
//%includeGuardStart } 6r/+wHsBUjIgsuAo9gCR4Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceRadial.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } YPJTJu3QQFPS1g3ETVWpug
/*
 * $Id: MushSkinPixelSourceRadial.h,v 1.2 2006/08/01 17:21:39 southa Exp $
 * $Log: MushSkinPixelSourceRadial.h,v $
 * Revision 1.2  2006/08/01 17:21:39  southa
 * River demo
 *
 * Revision 1.1  2006/07/17 14:43:43  southa
 * Billboarded deco objects
 *
 */

#include "MushSkinPixelSourceProc.h"

#include "MushSkinLineGenerator.h"

//:xml1base MushSkinPixelSourceProc
//:generate virtual standard ostream xml1
class MushSkinPixelSourceRadial : public MushSkinPixelSourceProc
{
public:
	MushSkinPixelSourceRadial();
	
protected:
	virtual void LineGenerate(Mushware::U8 *inpTileData, Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos);
	
private:
	MushSkinLineGenerator m_lineGenerator;
	
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushSkinPixelSourceRadial& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } XjhJ5Kaj2XhnswRRclkapw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
