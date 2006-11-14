//%includeGuardStart {
#ifndef MUSHCOLLISIONRESOLVER_H
#define MUSHCOLLISIONRESOLVER_H
//%includeGuardStart } jGGnAirmq717WeH6BtDTlw
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionResolver.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } W+ZPeiSLOk9REJMC2q6iwg
/*
 * $Id: MushCollisionResolver.h,v 1.5 2006/06/01 15:39:16 southa Exp $
 * $Log: MushCollisionResolver.h,v $
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
