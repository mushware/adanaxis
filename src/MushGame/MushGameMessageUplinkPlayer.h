//%includeGuardStart {
#ifndef MUSHGAMEMESSAGEUPLINKPLAYER_H
#define MUSHGAMEMESSAGEUPLINKPLAYER_H
//%includeGuardStart } gpSVa44PKQe3LJxVX6ucOg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageUplinkPlayer.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } a58iCltWnU+QdI5tX2u1JA
/*
 * $Id: MushGameMessageUplinkPlayer.h,v 1.2 2006/06/01 15:39:25 southa Exp $
 * $Log: MushGameMessageUplinkPlayer.h,v $
 * Revision 1.2  2006/06/01 15:39:25  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/11 14:48:46  southa
 * Uplink work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMessageUplinkPiece.h"

//:xml1base MushGameMessageUplinkPiece
//:generate standard ostream xml1
class MushGameMessageUplinkPlayer : public MushGameMessageUplinkPiece
{
public:
    explicit MushGameMessageUplinkPlayer(const std::string& inID = "") : MushGameMessageUplinkPiece(inID) {}
    virtual ~MushGameMessageUplinkPlayer() {}
    
private:
    Mushware::U32 m_fireState; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::U32& FireState(void) const { return m_fireState; }
    void FireStateSet(const Mushware::U32& inValue) { m_fireState=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } KE2kHyYLhb/CBm54Vq5kGw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageUplinkPlayer& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } mmZHxVbk3GrZzT1fusSLDQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
