//%includeGuardStart {
#ifndef MUSHGAMEPLAYER_H
#define MUSHGAMEPLAYER_H
//%includeGuardStart } foHvGbTEB8G6XgqJu9SuYA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePlayer.h
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
//%Header } H1oljR44QK5XqInq0yNUtA
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
