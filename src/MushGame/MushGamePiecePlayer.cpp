//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePiecePlayer.cpp
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
//%Header } We4/BYPfUEB17lZnFrtfqQ
/*
 * $Id: MushGamePiecePlayer.cpp,v 1.4 2006/12/14 00:33:49 southa Exp $
 * $Log: MushGamePiecePlayer.cpp,v $
 * Revision 1.4  2006/12/14 00:33:49  southa
 * Control fix and audio pacing
 *
 * Revision 1.3  2006/11/02 09:47:33  southa
 * Player weapon control
 *
 * Revision 1.2  2006/10/09 16:00:17  southa
 * Intern generation
 *
 * Revision 1.1  2006/10/02 17:25:05  southa
 * Object lookup and target selection
 *
 * Revision 1.13  2006/06/01 15:39:25  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.11  2005/07/12 12:18:18  southa
 * Projectile work
 *
 * Revision 1.10  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.9  2005/07/11 14:48:46  southa
 * Uplink work
 *
 * Revision 1.8  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.7  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.6  2005/07/01 10:03:30  southa
 * Projection work
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

#include "MushGamePiecePlayer.h"

#include "MushGameLogic.h"
#include "MushGameMessageFire.h"
#include "MushGameMessageUplinkPlayer.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGamePiecePlayer);

MushGamePiecePlayer::MushGamePiecePlayer(std::string inID) :
    MushGamePiece(inID),
    m_fireState(0),
    m_fireLastMsec(0),
    m_fireCount(0),
    m_useControlMailbox(false)
{
    PostWRef().ToIdentitySet();
}

void
MushGamePiecePlayer::UplinkSend(MushGameLogic& ioLogic)
{
    MushGameMessageUplinkPlayer uplinkPlayer(Id());
    
    uplinkPlayer.PostSet(Post());
    uplinkPlayer.FireStateSet(FireState());
    
    ioLogic.CopyAndSendToServer(uplinkPlayer);
}

void
MushGamePiecePlayer::ControlMailboxNameSet(const std::string& inName)
{
    m_controlMailboxRef.NameSet(inName);
    m_controlMailboxRef.WRef().DiscardAll(); // Purge mailbox
    m_useControlMailbox = true;
}

void
MushGamePiecePlayer::ControlInfoConsume(MushGameLogic& ioLogic, const MushGameMessageControlInfo& inMessage)
{
    static U8 errCtr=0;
    if (errCtr == 0)
    {
        ++errCtr;
        throw MushcoreDataFail(std::string("Discarding messages of type '")+inMessage.AutoName()+"' in MushGamePiecePlayer");
    }
}

void
MushGamePiecePlayer::FireConsume(MushGameLogic& ioLogic, const MushGameMessageFire& inMessage)
{
    static U8 errCtr=0;
    if (errCtr == 0)
    {
        ++errCtr;
        throw MushcoreDataFail(std::string("Discarding messages of type '")+inMessage.AutoName()+"' in MushGamePiecePlayer");
    }
}

Mushware::tMsec
MushGamePiecePlayer::FirePeriodMsec(void)
{
    return 100;   
}

void
MushGamePiecePlayer::ServerSideFire(MushGameLogic& ioLogic)
{
    FireLastMsecSet(ioLogic.FrameMsec());
    MushGameMessageFire fireMessage(Id());
    fireMessage.PostSet(Post());
    fireMessage.CountSet(m_fireCount);
    fireMessage.TypeSet(0);
    fireMessage.OwnerSet(Id());
    ioLogic.CopyAndBroadcast(fireMessage);
    ++m_fireCount;
}
                                    
void
MushGamePiecePlayer::UplinkPlayerConsume(MushGameLogic& ioLogic, const MushGameMessageUplinkPlayer& inMessage)
{
    PostSet(inMessage.Post());
    if (inMessage.FireState() && !FireState())
    {
        // Start of firing
        FireStartMsecSet(ioLogic.FrameMsec());
    }
    FireStateSet(inMessage.FireState());
}

void
MushGamePiecePlayer::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const MushGameMessageControlInfo *pControlInfo;
    const MushGameMessageUplinkPlayer *pUplinkPlayer;
    const MushGameMessageFire *pFire;
    
    if ((pControlInfo = dynamic_cast<const MushGameMessageControlInfo *>(&inMessage)) != NULL)
    {
        ControlInfoConsume(ioLogic, *pControlInfo);
    }
    else if ((pUplinkPlayer = dynamic_cast<const MushGameMessageUplinkPlayer *>(&inMessage)) != NULL)
    {
        UplinkPlayerConsume(ioLogic, *pUplinkPlayer);
    }
    else if ((pFire = dynamic_cast<const MushGameMessageFire *>(&inMessage)) != NULL)
    {
        FireConsume(ioLogic, *pFire);
    }
    else
    {
        // Pass to base class
        MushGamePiece::MessageConsume(ioLogic, inMessage);
    }
}

void
MushGamePiecePlayer::ControlMailboxProcess(MushGameLogic& ioLogic)
{
    if (m_useControlMailbox)
    {
        MushGameMailbox& mailboxRef = m_controlMailboxRef.WRef();
        
        std::auto_ptr<MushGameMessage> aMessage;
        
        while (mailboxRef.TakeIfAvailable(aMessage))
        {
            MUSHCOREASSERT(aMessage.get() != NULL);
            MessageConsume(ioLogic, *aMessage);
        }
    }
}

void
MushGamePiecePlayer::TickerProcess(MushGameLogic& ioLogic)
{
    if (FireState() &&
        ioLogic.FrameMsec() >= FireLastMsec() + FirePeriodMsec())
    {
        ServerSideFire(ioLogic);
    }
}

//%outOfLineFunctions {

const char *MushGamePiecePlayer::AutoName(void) const
{
    return "MushGamePiecePlayer";
}

MushcoreVirtualObject *MushGamePiecePlayer::AutoClone(void) const
{
    return new MushGamePiecePlayer(*this);
}

MushcoreVirtualObject *MushGamePiecePlayer::AutoCreate(void) const
{
    return new MushGamePiecePlayer;
}

MushcoreVirtualObject *MushGamePiecePlayer::AutoVirtualFactory(void)
{
    return new MushGamePiecePlayer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGamePiecePlayer", MushGamePiecePlayer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGamePiecePlayer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "playerName=" << m_playerName << ", ";
    ioOut << "fireState=" << m_fireState << ", ";
    ioOut << "fireStartMsec=" << m_fireStartMsec << ", ";
    ioOut << "fireLastMsec=" << m_fireLastMsec << ", ";
    ioOut << "fireCount=" << m_fireCount << ", ";
    ioOut << "controlMailboxRef=" << m_controlMailboxRef << ", ";
    ioOut << "useControlMailbox=" << m_useControlMailbox;
    ioOut << "]";
}
bool
MushGamePiecePlayer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "playerName")
    {
        ioIn >> m_playerName;
    }
    else if (inTagStr == "fireState")
    {
        ioIn >> m_fireState;
    }
    else if (inTagStr == "fireStartMsec")
    {
        ioIn >> m_fireStartMsec;
    }
    else if (inTagStr == "fireLastMsec")
    {
        ioIn >> m_fireLastMsec;
    }
    else if (inTagStr == "fireCount")
    {
        ioIn >> m_fireCount;
    }
    else if (inTagStr == "controlMailboxRef")
    {
        ioIn >> m_controlMailboxRef;
    }
    else if (inTagStr == "useControlMailbox")
    {
        ioIn >> m_useControlMailbox;
    }
    else if (MushGamePiece::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGamePiecePlayer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("playerName");
    ioOut << m_playerName;
    ioOut.TagSet("fireState");
    ioOut << m_fireState;
    ioOut.TagSet("fireStartMsec");
    ioOut << m_fireStartMsec;
    ioOut.TagSet("fireLastMsec");
    ioOut << m_fireLastMsec;
    ioOut.TagSet("fireCount");
    ioOut << m_fireCount;
    ioOut.TagSet("controlMailboxRef");
    ioOut << m_controlMailboxRef;
    ioOut.TagSet("useControlMailbox");
    ioOut << m_useControlMailbox;
}
//%outOfLineFunctions } 8mfMLcT+rZjJWZ7+0uzuOw
