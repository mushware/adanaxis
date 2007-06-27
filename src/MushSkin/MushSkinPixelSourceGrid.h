//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCEGRID_H
#define MUSHSKINPIXELSOURCEGRID_H
//%includeGuardStart } k6UFlIjPy676Mn0sG2CiBg
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceGrid.h
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
//%Header } XfTw74lpY4ML6m2gWhlW1w
/*
 * $Id: MushSkinPixelSourceGrid.h,v 1.3 2007/04/18 09:23:04 southa Exp $
 * $Log: MushSkinPixelSourceGrid.h,v $
 * Revision 1.3  2007/04/18 09:23:04  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/08/01 17:21:39  southa
 * River demo
 *
 * Revision 1.1  2006/06/07 12:15:21  southa
 * Grid and test textures
 *
 */

#include "MushSkinStandard.h"

#include "MushSkinLineGenerator.h"
#include "MushSkinPixelSourceProc.h"
#include "MushSkinUtil.h"

//:xml1base MushSkinPixelSourceProc
//:generate virtual standard ostream xml1
class MushSkinPixelSourceGrid : public MushSkinPixelSourceProc
{
public:
    MushSkinPixelSourceGrid();
    virtual void ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue);
	virtual void LineGenerate(Mushware::U8 *inpTileData, Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos);
	
protected:
	
private:
	MushSkinLineGenerator m_lineGenerator;
	Mushware::t4Val m_gridRatio; //:read
	Mushware::t4Val m_gridSharpness; //:read
	
//%classPrototypes {
public:
    const Mushware::t4Val& GridRatio(void) const { return m_gridRatio; }
    const Mushware::t4Val& GridSharpness(void) const { return m_gridSharpness; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Cf0wz5bRerLg8GJgsZInDg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushSkinPixelSourceGrid& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } b2odhGqixUXBRE0br53koQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
