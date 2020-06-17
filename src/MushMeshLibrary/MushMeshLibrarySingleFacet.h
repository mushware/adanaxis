//%includeGuardStart {
#ifndef MUSHMESHLIBRARYSINGLEFACET_H
#define MUSHMESHLIBRARYSINGLEFACET_H
//%includeGuardStart } 1xrY4qzG9DP6f9oteHdXAA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibrarySingleFacet.h
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
//%Header } U53bpxescLjZQu9pN4gZjw
/*
 * $Id: MushMeshLibrarySingleFacet.h,v 1.3 2007/04/18 09:22:54 southa Exp $
 * $Log: MushMeshLibrarySingleFacet.h,v $
 * Revision 1.3  2007/04/18 09:22:54  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/08/01 17:21:35  southa
 * River demo
 *
 * Revision 1.1  2006/07/17 14:43:41  southa
 * Billboarded deco objects
 *
 */

#include "MushMeshLibraryStandard.h"

//:xml1base MushMesh4Base
//:generate virtual standard ostream xml1
class MushMeshLibrarySingleFacet : public MushMesh4Base
{
public:
	MushMeshLibrarySingleFacet() : m_order(0) {}
	virtual void Make(MushMesh4Mesh& ioMesh) const;
	
private:
	Mushware::U32 m_order; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& Order(void) const { return m_order; }
    void OrderSet(const Mushware::U32& inValue) { m_order=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } hDw3+Tv1KM2d61dLsWDqNg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshLibrarySingleFacet& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } yz4Hm5TprueHez589yRipg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
