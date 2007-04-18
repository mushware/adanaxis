//%includeGuardStart {
#ifndef MUSHGAMEPLAYER_H
#define MUSHGAMEPLAYER_H
//%includeGuardStart } foHvGbTEB8G6XgqJu9SuYA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePlayer.h
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
//%Header } EXEEmDNBxsC8v9S7Eh//Ug
/*
 * $Id: MushGamePlayer.h,v 1.11 2006/06/01 15:39:26 southa Exp $
 * $Log: MushGamePlayer.h,v $
 * Revision 1.11  2006/06/01 15:39:26  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.9  2005/07/12 12:18:18  southa
 * Projectile work
 *
 * Revision 1.8  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.7  2005/07/11 14:48:46  southa
 * Uplink work
 *
 * Revision 1.6  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.5  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.4  2005/06/24 10:30:13  southa
 * MushGame camera work
 *
 * Revision 1.3  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 17:25:39  southa
 * Client/server work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMailbox.h"
#include "MushGameMessage.h"
#include "MushGameMessageControlInfo.h"
#include "MushGameMessageFire.h"
#include "MushGameMessageUplinkPlayer.h"
#include "MushGamePiece.h"

#include "API/mushMushMesh.h"

//:xml1base MushGamePiece
//:generate virtual standard ostream xml1
class MushGamePlayer : public MushGamePiece
{
public:
    explicit MushGamePlayer(std::string inID = "");
    virtual ~MushGamePlayer() {}
    
    virtual void ControlMailboxNameSet(const std::string& inName);
    virtual void ControlInfoConsume(MushGameLogic& ioLogic, const MushGameMessageControlInfo& inMessage);
    virtual void UplinkPlayerConsume(MushGameLogic& ioLogic, const MushGameMessageUplinkPlayer& inMessage);
    virtual void FireConsume(MushGameLogic& ioLogic, const MushGameMessageFire& inMessage);
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void ControlMailboxProcess(MushGameLogic& ioLogic);
    virtual void TickerProcess(MushGameLogic& ioLogic);
    virtual void UplinkSend(MushGameLogic& ioLogic);
    virtual Mushware::tMsec FirePeriodMsec(void);
    virtual void ServerSideFire(MushGameLogic& ioLogic);
    
private:
    std::string m_id; //:readwrite
    std::string m_playerName; //:readwrite
    Mushware::U32 m_fireState; //:readwrite
    Mushware::tMsec m_fireStartMsec; //:readwrite
    Mushware::tMsec m_fireLastMsec; //:readwrite
    Mushware::tMsec m_fireCount; //:readwrite
    MushcoreDataRef<MushGameMailbox> m_controlMailboxRef;
    bool m_useControlMailbox;
    
//%classPrototypes {
public:
    const std::string& Id(void) const { return m_id; }
    void IdSet(const std::string& inValue) { m_id=inValue; }
    const std::string& PlayerName(void) const { return m_playerName; }
    void PlayerNameSet(const std::string& inValue) { m_playerName=inValue; }
    const Mushware::U32& FireState(void) const { return m_fireState; }
    void FireStateSet(const Mushware::U32& inValue) { m_fireState=inValue; }
    const Mushware::tMsec& FireStartMsec(void) const { return m_fireStartMsec; }
    void FireStartMsecSet(const Mushware::tMsec& inValue) { m_fireStartMsec=inValue; }
    const Mushware::tMsec& FireLastMsec(void) const { return m_fireLastMsec; }
    void FireLastMsecSet(const Mushware::tMsec& inValue) { m_fireLastMsec=inValue; }
    const Mushware::tMsec& FireCount(void) const { return m_fireCount; }
    void FireCountSet(const Mushware::tMsec& inValue) { m_fireCount=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } WqGZjuwdPoprQ0AAD3fETQ
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
