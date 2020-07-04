//%includeGuardStart {
#ifndef MUSHCOLLISIONRESOLVER_H
#define MUSHCOLLISIONRESOLVER_H
//%includeGuardStart } jGGnAirmq717WeH6BtDTlw
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionResolver.h
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
//%Header } vfgpZYNfLPM84hT+fAaaCg
/*
 * $Id: MushCollisionResolver.h,v 1.6 2006/11/14 20:28:37 southa Exp $
 * $Log: MushCollisionResolver.h,v $
 * Revision 1.6  2006/11/14 20:28:37  southa
 * Added rail gun
 *
 * Revision 1.5  2006/06/01 15:39:16  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 * Revision 1.3  2005/07/30 19:06:14  southa
 * Collision checking
 *
 * Revision 1.2  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.1  2005/07/27 18:09:59  southa
 * Collision checking
 *
 */

#include "MushCollisionStandard.h"

#include "MushCollisionInfo.h"
#include "MushCollisionPiece.h"

//:generate standard ostream xml1
class MushCollisionResolver : public MushcoreVirtualObject, public MushcoreSingleton<MushCollisionResolver>
{
public:
    void Resolve(MushCollisionInfo& outCollInfo, const MushCollisionPiece& inPiece1, const MushCollisionPiece& inPiece2) const;

protected:
    void ChunkResolve(MushCollisionInfo& outCollInfo, const MushCollisionPiece& inPiece1, const MushCollisionPiece& inPiece2) const;
    void WCylinderResolve(MushCollisionInfo& outCollInfo, const MushCollisionPiece& inPiece1, const MushCollisionPiece& inPiece2) const;
    
private:
    Mushware::tMsec m_frameMsec; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::tMsec& FrameMsec(void) const { return m_frameMsec; }
    void FrameMsecSet(const Mushware::tMsec& inValue) { m_frameMsec=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } P6nDSQv2g7W3VXxd34GhhQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushCollisionResolver& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } HNNZFTynkudwCQk/JqIOBw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
