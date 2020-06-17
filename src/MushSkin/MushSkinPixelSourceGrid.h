//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCEGRID_H
#define MUSHSKINPIXELSOURCEGRID_H
//%includeGuardStart } k6UFlIjPy676Mn0sG2CiBg
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceGrid.h
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
//%Header } rCHo8Mip0QAZZ2MqhvdOvA
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
