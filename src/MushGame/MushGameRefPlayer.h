//%includeGuardStart {
#ifndef MUSHGAMEREFPLAYER_H
#define MUSHGAMEREFPLAYER_H
//%includeGuardStart } HF7zdGcRkfhImkNuyJGPWw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRefPlayer.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } SMj7RZxMAshsGD/gkM/X5g
/*
 * $Id: MushcoreDataRef.h,v 1.16 2005/06/21 13:10:52 southa Exp $
 * $Log: MushcoreDataRef.h,v $
 */

#include "MushGameStandard.h"

#include "MushGameRef.h"
#include "MushGameRefPiece.h"

#include "MushGamePiece.h"
#include "MushGamePlayer.h"

//:xml1base MushGameRef
//:generate virtual standard ostream xml1
class MushGameRefPlayer : public MushGameRef
{
public:
    MushGameRefPlayer() {}
    explicit MushGameRefPlayer(const std::string& inName, MushcoreData<MushGamePlayer> *inInstance);
    virtual MushcoreVirtualObject& Ref() { return m_playerRef.WRef(); }
    
private:
    MushcoreDataRef<MushGamePlayer> m_playerRef;
    
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
operator<<(std::ostream& ioOut, const MushGameRefPlayer& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 7Duhn8Ai9wx1lFcVH+6gDw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw