//%includeGuardStart {
#ifndef MUSHSKINTILEDMETHOD1_H
#define MUSHSKINTILEDMETHOD1_H
//%includeGuardStart } cTc3qAvpCZwye3sv8x+3Hw
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinTiledMethod1.h
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
//%Header } V01ZwEC4RWz6nM4nDhdUGA
/*
 * $Id: MushSkinTiledMethod1.h,v 1.3 2007/04/18 09:23:06 southa Exp $
 * $Log: MushSkinTiledMethod1.h,v $
 * Revision 1.3  2007/04/18 09:23:06  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/08/01 17:21:41  southa
 * River demo
 *
 * Revision 1.1  2006/06/09 21:07:15  southa
 * Tiled skin generation
 *
 */

#include "MushSkinStandard.h"

//:generate virtual standard ostream xml1
class MushSkinTiledMethod1 : public MushcoreVirtualObject
{
public:
    MushSkinTiledMethod1();
    
    virtual void DivideSize(Mushware::t2U32& outSizes, Mushware::U32 inNumFacets);
    virtual void TexCoordsGenerate(MushMesh4Mesh& ioMesh);
	
protected:
	Mushware::tVal MultiplierForTile(Mushware::U32 inNumVertices);
	
private:
	Mushware::tVal m_pullInRatio;
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
operator<<(std::ostream& ioOut, const MushSkinTiledMethod1& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } nMbCcXUqKAWlVwtq0NV/vw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
