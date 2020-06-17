//%includeGuardStart {
#ifndef MUSHSKINSINGULAR_H
#define MUSHSKINSINGULAR_H
//%includeGuardStart } Bi+Sl554bG8sYG45Xne7BQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinSingular.h
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
//%Header } A6jesHorU2vhZ6LcEy/ZAg
/*
 * $Id: MushSkinSingular.h,v 1.2 2007/04/18 09:23:05 southa Exp $
 * $Log: MushSkinSingular.h,v $
 * Revision 1.2  2007/04/18 09:23:05  southa
 * Header and level fixes
 *
 * Revision 1.1  2006/10/19 15:41:37  southa
 * Item handling
 *
 */

#include "MushSkinStandard.h"

//:generate virtual standard ostream xml1
class MushSkinSingular : public MushcoreVirtualObject
{
public:
    MushSkinSingular();
    
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
operator<<(std::ostream& ioOut, const MushSkinSingular& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } WEe+I3W8dV7HSp3jc6XGEw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
