//%includeGuardStart {
#ifndef MUSHSKINTILED_H
#define MUSHSKINTILED_H
//%includeGuardStart } kZD0CEqivw3yeKDiSUrmlA
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinTiled.h
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
//%Header } /a36SukeyI0aIBpjcBJphg
/*
 * $Id: MushSkinTiled.h,v 1.4 2007/04/18 09:23:05 southa Exp $
 * $Log: MushSkinTiled.h,v $
 * Revision 1.4  2007/04/18 09:23:05  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/08/01 17:21:41  southa
 * River demo
 *
 * Revision 1.2  2006/06/09 21:07:15  southa
 * Tiled skin generation
 *
 * Revision 1.1  2006/06/07 12:15:22  southa
 * Grid and test textures
 *
 * Revision 1.2  2006/06/01 15:39:40  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 */

#include "MushSkinStandard.h"

//:generate virtual standard ostream xml1
class MushSkinTiled : public MushcoreVirtualObject
{
public:
    MushSkinTiled();
    
    virtual void DivideSize(Mushware::t2U32& outSizes, Mushware::U32 inNumFacets);
    virtual void TexCoordsGenerate(MushMesh4Mesh& ioMesh);
 
protected:

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
operator<<(std::ostream& ioOut, const MushSkinTiled& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } G5CINZQknhQNvC3mkG1rWg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
