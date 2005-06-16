//%includeGuardStart {
#ifndef MUSHGAMEPLAYER_H
#define MUSHGAMEPLAYER_H
//%includeGuardStart } foHvGbTEB8G6XgqJu9SuYA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePlayer.h
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
//%Header } oGbXkYO013mPUX90XE1YJg
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

#include "MushGameMailbox.h"
#include "MushGameMessage.h"

//:generate virtual standard ostream xml1
class MushGamePlayer : public MushcoreVirtualObject
{
public:
    explicit MushGamePlayer(Mushware::U32 inPlayerID = 0);
    virtual ~MushGamePlayer() {}
    virtual void MessageConsume(MushGameMailbox& outReplyBox, const MushGameMessage& inMessage);
    
private:
    Mushware::U32 m_playerID; //:read
    
//%classPrototypes {
public:
    const Mushware::U32& PlayerID(void) const { return m_playerID; }
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } gnAZuCvapICQ1MjyCHbleg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGamePlayer& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } qNoomoiXq6eGt3pwxj2Fmw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
