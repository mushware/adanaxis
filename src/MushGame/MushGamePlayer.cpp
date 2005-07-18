//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePlayer.cpp
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
//%Header } nBtAQHbpc8XKKxgcOfRPVA
/*
 * $Id: MushGamePlayer.cpp,v 1.11 2005/07/12 12:18:18 southa Exp $
 * $Log: MushGamePlayer.cpp,v $
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

#include "MushGamePlayer.h"

#include "MushGameLogic.h"
#include "MushGameMessageFire.h"
#include "MushGameMessageUplinkPlayer.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGamePlayer);

MushGamePlayer::MushGamePlayer(std::string inID) :
    m_id(inID),
    m_fireState(0),
    m_fireLastMsec(0),
    m_fireCount(0),
    m_useControlMailbox(false)
{
    PostWRef().ToIdentitySet();
}

void
MushGamePlayer::UplinkSend(MushGameLogic& ioLogic)
{
    MushGameMessageUplinkPlayer uplinkPlayer(Id());
    
    uplinkPlayer.PostSet(Post());
    uplinkPlayer.FireStateSet(FireState());
    
    ioLogic.CopyAndSendToServer(uplinkPlayer);
}

void
MushGamePlayer::ControlMailboxNameSet(const std::string& inName)
{
    m_controlMailboxRef.NameSet(inName);
    m_useControlMailbox = true;
}

void
MushGamePlayer::ControlInfoConsume(MushGameLogic& ioLogic, const MushGameMessageControlInfo& inMessage)
{
    static U8 errCtr=0;
    if (errCtr == 0)
    {
        ++errCtr;
        throw MushcoreDataFail(std::string("Discarding messages of type '")+inMessage.AutoName()+"' in MushGamePlayer");
    }
}

void
MushGamePlayer::FireConsume(MushGameLogic& ioLogic, const MushGameMessageFire& inMessage)
{
    static U8 errCtr=0;
    if (errCtr == 0)
    {
        ++errCtr;
        throw MushcoreDataFail(std::string("Discarding messages of type '")+inMessage.AutoName()+"' in MushGamePlayer");
    }
}

Mushware::tMsec
MushGamePlayer::FirePeriodMsec(void)
{
    return 250;   
}

void
MushGamePlayer::ServerSideFire(MushGameLogic& ioLogic)
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
MushGamePlayer::UplinkPlayerConsume(MushGameLogic& ioLogic, const MushGameMessageUplinkPlayer& inMessage)
{
    // cout << inMessage << endl;
    PostSet(inMessage.Post());
    if (inMessage.FireState() && !FireState())
    {
        // Start of firing
        FireStartMsecSet(ioLogic.FrameMsec());
    }
    FireStateSet(inMessage.FireState());
}

void
MushGamePlayer::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
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
MushGamePlayer::ControlMailboxProcess(MushGameLogic& ioLogic)
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
MushGamePlayer::TickerProcess(MushGameLogic& ioLogic)
{
    if (FireState() &&
        ioLogic.FrameMsec() >= FireLastMsec() + FirePeriodMsec())
    {
        ServerSideFire(ioLogic);
    }
}

//%outOfLineFunctions {

const char *MushGamePlayer::AutoName(void) const
{
    return "MushGamePlayer";
}

MushcoreVirtualObject *MushGamePlayer::AutoClone(void) const
{
    return new MushGamePlayer(*this);
}

MushcoreVirtualObject *MushGamePlayer::AutoCreate(void) const
{
    return new MushGamePlayer;
}

MushcoreVirtualObject *MushGamePlayer::AutoVirtualFactory(void)
{
    return new MushGamePlayer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGamePlayer", MushGamePlayer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGamePlayer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "id=" << m_id << ", ";
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
MushGamePlayer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "id")
    {
        ioIn >> m_id;
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
MushGamePlayer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("id");
    ioOut << m_id;
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
//%outOfLineFunctions } nwZ9MgjnFJjRzEsHlYu4eQ
