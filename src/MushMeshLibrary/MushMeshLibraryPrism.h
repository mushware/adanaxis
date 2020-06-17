//%includeGuardStart {
#ifndef MUSHMESHLIBRARYPRISM_H
#define MUSHMESHLIBRARYPRISM_H
//%includeGuardStart } ymO6abrq9vtxQdg683ciiw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryPrism.h
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
//%Header } IcafpxWISY6l75qLRDOkOQ
/*
 * $Id: MushMeshLibraryPrism.h,v 1.4 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryPrism.h,v $
 * Revision 1.4  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/08/01 17:21:35  southa
 * River demo
 *
 * Revision 1.2  2006/06/16 12:11:04  southa
 * Ruby subclasses
 *
 * Revision 1.1  2006/06/16 01:02:32  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshLibraryStandard.h"

//:xml1base MushMesh4Base
//:generate virtual standard ostream xml1
class MushMeshLibraryPrism : public MushMesh4Base
{
public:
	MushMeshLibraryPrism() : m_order(0) {}
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
operator<<(std::ostream& ioOut, const MushMeshLibraryPrism& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Q1CuKx8cj185hgpPU6ytGg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
