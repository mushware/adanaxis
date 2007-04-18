//%includeGuardStart {
#ifndef MUSHGAMEMESSAGEJOINCONFIRM_H
#define MUSHGAMEMESSAGEJOINCONFIRM_H
//%includeGuardStart } ncqNKv/Pw1HGEZ4QVCnOLA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageJoinConfirm.h
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
//%Header } cW2/a+cG41TcajWAmvYCKQ
/*
 * $Id: MushGameMessageJoinConfirm.h,v 1.4 2006/06/01 15:39:24 southa Exp $
 * $Log: MushGameMessageJoinConfirm.h,v $
 * Revision 1.4  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 */

#include "MushGameStandard.h"
#include "MushGameMessage.h"

//:xml1base MushGameMessage
//:generate virtual standard ostream xml1
class MushGameMessageJoinConfirm : public MushGameMessage
{
public:
    explicit MushGameMessageJoinConfirm(const std::string& inID = "") : MushGameMessage(inID) {}
    virtual ~MushGameMessageJoinConfirm() {}
    
private:
    std::string m_newPlayerID; //:readwrite
    std::string m_hostName; //:readwrite
    std::string m_playerName; //:readwrite
    std::string m_hostPackageID; //:readwrite
    
//%classPrototypes {
public:
    const std::string& NewPlayerID(void) const { return m_newPlayerID; }
    void NewPlayerIDSet(const std::string& inValue) { m_newPlayerID=inValue; }
    const std::string& HostName(void) const { return m_hostName; }
    void HostNameSet(const std::string& inValue) { m_hostName=inValue; }
    const std::string& PlayerName(void) const { return m_playerName; }
    void PlayerNameSet(const std::string& inValue) { m_playerName=inValue; }
    const std::string& HostPackageID(void) const { return m_hostPackageID; }
    void HostPackageIDSet(const std::string& inValue) { m_hostPackageID=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } ZROunlbn2p02d+AsWwVBBw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageJoinConfirm& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } viUsrq0dwybkoMu8vWWN6Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
