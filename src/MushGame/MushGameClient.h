//%includeGuardStart {
#ifndef MUSHGAMECLIENT_H
#define MUSHGAMECLIENT_H
//%includeGuardStart } Zb4Xh6cwZEEwiwitVkMl3g
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameClient.h
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
//%Header } tEYrYr0gF9dIdGmExJumYA
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

#include "MushGameMailbox.h"
#include "MushGameMessage.h"

//:generate virtual standard ostream xml1
class MushGameClient : public MushcoreVirtualObject
{
public:
    MushGameClient();
    virtual ~MushGameClient() {}
    virtual void MessageConsume(MushGameMailbox& outReplyBox, const MushGameMessage& inMessage);

//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } FwEN8XJox/Ejr30NeyHzCg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameClient& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } mCMJYXr8K3IjM5atdYET9w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
