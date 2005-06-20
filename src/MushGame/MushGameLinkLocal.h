//%includeGuardStart {
#ifndef MUSHGAMELINKLOCAL_H
#define MUSHGAMELINKLOCAL_H
//%includeGuardStart } 0/YY5aWWhNBrwLukR235Qw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLinkLocal.h
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
//%Header } 3aRv+tX8/7XZNh7xGrmOrA
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

#include "MushGameClient.h"
#include "MushGameDigest.h"
#include "MushGameLink.h"
#include "MushGameServer.h"

//:xml1base MushGameLink
//:generate virtual standard ostream xml1
class MushGameLinkLocal : public MushGameLink
{
public:
    virtual ~MushGameLinkLocal() {}
    virtual void MessagesPump(void);
    
private:
    MushcoreDataRef<MushGameClient> m_clientRef; //:readwrite
    MushcoreDataRef<MushGameServer> m_serverRef; //:readwrite
    MushcorePipe<MushGameMailbox> m_clientToServer; //:ignore
    MushcorePipe<MushGameMailbox> m_serverToClient; //:ignore
    
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameClient>& ClientRef(void) const { return m_clientRef; }
    void ClientRefSet(const MushcoreDataRef<MushGameClient>& inValue) { m_clientRef=inValue; }
    const MushcoreDataRef<MushGameServer>& ServerRef(void) const { return m_serverRef; }
    void ServerRefSet(const MushcoreDataRef<MushGameServer>& inValue) { m_serverRef=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } +W8szZZ0/vfABfyInM4o1g
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameLinkLocal& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } GJAmucyBlwTyaWsSpOPcGw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
