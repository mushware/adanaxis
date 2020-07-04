//%includeGuardStart {
#ifndef MUSHMESH4LINKFACEFACE_H
#define MUSHMESH4LINKFACEFACE_H
//%includeGuardStart } Ts/6esfbQFVxvfonUaZAUw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4LinkFaceFace.h
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
//%Header } DCMEGoAoDjxVw3zpbSRgsQ
/*
 * $Id: MushMesh4LinkFaceFace.h,v 1.2 2006/06/01 15:39:28 southa Exp $
 * $Log: MushMesh4LinkFaceFace.h,v $
 * Revision 1.2  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/13 16:45:05  southa
 * Extrusion work
 *
 */

#include "MushMeshStandard.h"

//:generate virtual standard ostream xml1
class MushMesh4LinkFaceFace : public MushcoreVirtualObject
{
public:
    MushMesh4LinkFaceFace() {}
    virtual ~MushMesh4LinkFaceFace() {}
    
private:
    Mushware::U32 m_faceNum; //:readwrite
    Mushware::U32 m_localFacetNum; //:readwrite
    Mushware::U32 m_remoteFacetNum; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& FaceNum(void) const { return m_faceNum; }
    void FaceNumSet(const Mushware::U32& inValue) { m_faceNum=inValue; }
    const Mushware::U32& LocalFacetNum(void) const { return m_localFacetNum; }
    void LocalFacetNumSet(const Mushware::U32& inValue) { m_localFacetNum=inValue; }
    const Mushware::U32& RemoteFacetNum(void) const { return m_remoteFacetNum; }
    void RemoteFacetNumSet(const Mushware::U32& inValue) { m_remoteFacetNum=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } RWHYhncadx94i1MjlIis1w
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMesh4LinkFaceFace& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } JT7LgmuuM0WYbTWrdpqzdQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
