//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLogic.cpp
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
//%Header } G0/dfauKPLZ8TwNbwBtU8A
/*
 * $Id: MushGameLogic.cpp,v 1.4 2005/06/23 11:58:28 southa Exp $
 * $Log: MushGameLogic.cpp,v $
 * Revision 1.4  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameLogic.h"

#include "MushGameAddress.h"
#include "MushGameJob.h"
#include "MushGameLink.h"
#include "MushGameMessageWake.h"
#include "MushGameUtil.h"

#include "API/mushGame.h"

MUSHCORE_DATA_INSTANCE(MushGameLogic);

using namespace Mushware;
using namespace std;

Mushware::U32
MushGameLogic::GameMsec(void) const
{
    GameAppHandler *pGameAppHandler=dynamic_cast<GameAppHandler *>(&MushcoreAppHandler::Sgl());
    if (pGameAppHandler == NULL)
    {
        return 0;
    }
    else
    {
        return pGameAppHandler->MillisecondsGet();
    }
}

void
MushGameLogic::JobListProcess(tJobList& ioList)
{
    U32 msecNow = GameMsec();
    
    for (tJobList::tIterator p = ioList.Begin(); p != ioList.End(); )
    {
        MushGameJob *pJob = p->second;
        MUSHCOREASSERT(pJob != NULL);
        if (pJob->ShouldWake())
        {
            if (pJob->WakeTime() <= msecNow)
            {
                MushGameMessageWake wakeMessage("wakeup");
                try
                {
                    pJob->MessageConsume(*this, wakeMessage);
                }
                catch (MushcoreNonFatalFail& e)
                {
                    MushcoreLog::Sgl().ErrorLog() << "Job wake consumption failure: " << e.what() << endl
                        << "Job was '" << p->first << "': " << *pJob << endl;
                    pJob->CompleteSet(true);
                }
            }
        }
        
        tJobList::tIterator oldP = p;
        ++p;

        if (pJob->Complete())
        {
            ioList.Delete(oldP);
        }
    }
}

void
MushGameLogic::PerFrameProcessing(void)
{
    JobListProcess(SaveData().JobListWRef());
    JobListProcess(HostSaveData().JobListWRef());
}

void
MushGameLogic::DefaultMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("Discarding message of type '")+inMessage.AutoName()+"' with no ID");
}

void
MushGameLogic::JobMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("Discarding message of type '")+inMessage.AutoName()+"' with Job ID");
}

void
MushGameLogic::PieceMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("Discarding message of type '")+inMessage.AutoName()+"' with Piece ID");
}

void
MushGameLogic::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const std::string& msgID = inMessage.Id();
    
    if (msgID == "")
    {
        DefaultMessageConsume(ioLogic, inMessage);
    }
    else
    {
        switch (msgID[0])
        {
            case 'j':
                JobMessageConsume(ioLogic, inMessage);
                break;
                
            case 'p':
                PieceMessageConsume(ioLogic, inMessage);
                break;
                
            default:
                throw MushcoreDataFail(std::string("Discarding message of type '")+inMessage.AutoName()+"' with unknown ID prefix");
                break;
        }
    }
}

void
MushGameLogic::ServerAddressSet(const std::string& inName)
{
    SaveData().ServerAddrRefWRef().NameSet(inName);    
}

void
MushGameLogic::ClientAddressAdd(const std::string& inName)
{
    MushcoreDataRef<MushGameAddress> clientAddressRef(inName);
    HostSaveData().ClientAddrRefsWRef().push_back(clientAddressRef);    
}

void
MushGameLogic::CopyAndSendToServer(const MushGameMessage& inMessage)
{
    try
    {
        // Find the link
        SaveData().ServerAddrRef().Ref().LinkRef().WRef().ToOutboxCopy(inMessage);
    }
    catch (MushcoreNonFatalFail& e)
    {
        MushcoreLog::Sgl().WarningLog() << e.what() << endl;
    }
}

void
MushGameLogic::AsReplyCopyAndSend(MushGameMessage& ioMessage, const MushGameMessage& inSrcMessage)
{
    try
    {
        ioMessage.IdSet(MushGameUtil::ReplyIDFromMessage(inSrcMessage));
        inSrcMessage.SrcAddrRef().Ref().LinkRef().WRef().ToOutboxCopy(ioMessage);
    }
    catch (MushcoreNonFatalFail& e)
    {
        MushcoreLog::Sgl().WarningLog() << e.what() << endl;
    }
}

void
MushGameLogic::ClientMailboxConsume(MushGameMailbox& inMailbox)
{
    std::auto_ptr<MushGameMessage> aMessage;
    while (inMailbox.TakeIfAvailable(aMessage))
    {
        MUSHCOREASSERT(&*aMessage != NULL);
        aMessage->SrcAddrRefSet(inMailbox.SrcAddrRef());
        try
        {
            MessageConsume(*this, *aMessage);
        }
        catch (MushcoreNonFatalFail& e)
        {
            MushcoreLog::Sgl().WarningLog() << e.what() << ": " << *aMessage << endl;
        }
    }
}

void
MushGameLogic::ServerMailboxConsume(MushGameMailbox& inMailbox)
{
    std::auto_ptr<MushGameMessage> aMessage;
    while (inMailbox.TakeIfAvailable(aMessage))
    {
        MUSHCOREASSERT(&*aMessage != NULL);
        aMessage->SrcAddrRefSet(inMailbox.SrcAddrRef());
        try
        {
            MessageConsume(*this, *aMessage);
        }
        catch (MushcoreNonFatalFail& e)
        {
            MushcoreLog::Sgl().WarningLog() << e.what() << ": " << *aMessage << endl;
        }
    }
}

void
MushGameLogic::ClientReceiveSequence(void)
{
    // I am a client picking up messages from my server
    MushGameMailbox mailbox;
    const MushcoreDataRef<MushGameAddress>& addrDataRef = SaveData().ServerAddrRef();
    if (addrDataRef.Ref().LinkRef().WRef().InboxGetUnlessEmpty(mailbox))
    {
        MushcoreLog::Sgl().InfoLog() << "Receiving from address " << addrDataRef.Ref() << endl;
        mailbox.SrcAddrRefSet(addrDataRef);
        ClientMailboxConsume(mailbox);
    }
}

void
MushGameLogic::ServerReceiveSequence(void)
{
    // I am the server picking up my messages from clients
    typedef MushGameHostSaveData::tClientAddrRefs tClientAddrRefs;
    
    tClientAddrRefs& clientAddrRefs = HostSaveData().ClientAddrRefsWRef();
        
    for (tClientAddrRefs::iterator p = clientAddrRefs.begin(); p != clientAddrRefs.end(); ++p)
    {
        MushGameMailbox mailbox;
        if (p->Ref().LinkRef().WRef().InboxGetUnlessEmpty(mailbox))
        {
            MushcoreLog::Sgl().InfoLog() << "Receiving from address " << p->Ref() << endl;
            mailbox.SrcAddrRefSet(*p);
            ServerMailboxConsume(mailbox);
        }
    }
}

void
MushGameLogic::ClientSendSequence(void)
{
    SaveData().ServerAddrRef().Ref().LinkRef().WRef().OutboxSendUnlessEmpty();
}

void
MushGameLogic::ServerSendSequence(void)
{
    // I am the server sending my outboxes
    typedef MushGameHostSaveData::tClientAddrRefs tClientAddrRefs;
    
    tClientAddrRefs& clientAddrRefs = HostSaveData().ClientAddrRefsWRef();
    
    for (tClientAddrRefs::iterator p = clientAddrRefs.begin(); p != clientAddrRefs.end(); ++p)
    {
        p->Ref().LinkRef().WRef().OutboxSendUnlessEmpty();
    }
}

void
MushGameLogic::ReceiveSequence(void)
{
    ServerReceiveSequence();
    ClientReceiveSequence();
}

void
MushGameLogic::SendSequence(void)
{
    ServerSendSequence();
    ClientSendSequence();
}

void
MushGameLogic::MainSequence(void)
{
    ReceiveSequence();
    SendSequence();
}

//%outOfLineFunctions {

const char *MushGameLogic::AutoName(void) const
{
    return "MushGameLogic";
}

MushcoreVirtualObject *MushGameLogic::AutoClone(void) const
{
    return new MushGameLogic(*this);
}

MushcoreVirtualObject *MushGameLogic::AutoCreate(void) const
{
    return new MushGameLogic;
}

MushcoreVirtualObject *MushGameLogic::AutoVirtualFactory(void)
{
    return new MushGameLogic;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameLogic", MushGameLogic::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameLogic::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "dataRef=" << m_dataRef << ", ";
    ioOut << "hostDataRef=" << m_hostDataRef;
    ioOut << "]";
}
bool
MushGameLogic::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "dataRef")
    {
        ioIn >> m_dataRef;
    }
    else if (inTagStr == "hostDataRef")
    {
        ioIn >> m_hostDataRef;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGameLogic::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("dataRef");
    ioOut << m_dataRef;
    ioOut.TagSet("hostDataRef");
    ioOut << m_hostDataRef;
}
//%outOfLineFunctions } DVO9yyMiWy5cK9z0gQKXvQ
