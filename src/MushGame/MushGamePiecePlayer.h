//%includeGuardStart {
#ifndef MUSHGAMEPIECEPLAYER_H
#define MUSHGAMEPIECEPLAYER_H
//%includeGuardStart } BJ2Xc/64bglJcr5KX7jmdw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePiecePlayer.h
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
//%Header } zJmB83zXo+ISd6J+KIp1Ng
/*
 * $Id: MushGamePiecePlayer.h,v 1.3 2006/11/02 09:47:33 southa Exp $
 * $Log: MushGamePiecePlayer.h,v $
 * Revision 1.3  2006/11/02 09:47:33  southa
 * Player weapon control
 *
 * Revision 1.2  2006/10/17 15:28:02  southa
 * Player collisions
 *
 * Revision 1.1  2006/10/02 17:25:06  southa
 * Object lookup and target selection
 *
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
class MushGamePiecePlayer : public MushGamePiece, public MushCollisionPiece
{
public:
    explicit MushGamePiecePlayer(std::string inID = "");
    virtual ~MushGamePiecePlayer() {}
    
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
    
    virtual const MushMesh4Mesh& CollisionMesh(void) const { return Mesh(); }
    virtual const MushMeshPosticity& CollisionPost(void) const { return Post(); }

private:
    std::string m_playerName; //:readwrite
    Mushware::U32 m_fireState; //:readwrite
    Mushware::tMsec m_fireStartMsec; //:readwrite
    Mushware::tMsec m_fireLastMsec; //:readwrite
    Mushware::tMsec m_fireCount; //:readwrite
    MushcoreDataRef<MushGameMailbox> m_controlMailboxRef;
    bool m_useControlMailbox;
    
//%classPrototypes {
public:
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
//%classPrototypes } KdGOnGzWp+H3MRemKkY57A
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGamePiecePlayer& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } aS5rddSGsGKn47wTJ9xeBA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
