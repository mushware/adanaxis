/*
 * $Id: GameNetUtils.cpp,v 1.8 2002/12/12 18:38:57 southa Exp $
 * $Log: GameNetUtils.cpp,v $
 * Revision 1.8  2002/12/12 18:38:57  southa
 * Mustl separation
 *
 * Revision 1.7  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.6  2002/12/09 23:59:58  southa
 * Network control
 *
 * Revision 1.5  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.4  2002/12/05 23:52:51  southa
 * Network management and status
 *
 * Revision 1.3  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.2  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.1  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 */

#include "GameNetUtils.h"

#include "GameConfig.h"
#include "GameDefClient.h"
#include "GameDefServer.h"
#include "GameException.h"
#include "GameNetID.h"
#include "GameRouter.h"

#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

void
GameNetUtils::KillServers(void)
{
    KillServersByType(false);
}

void
GameNetUtils::KillServerImages(void)
{
    KillServersByType(true);
}

void
GameNetUtils::KillClients(void)
{
    KillClientsByType(false);
}

void
GameNetUtils::KillClientImages(void)
{
    KillClientsByType(true);
}

void
GameNetUtils::KillLinks(void)
{
    CoreData<MustlLink>::tMapIterator endValue=CoreData<MustlLink>::Instance().End();

    for (CoreData<MustlLink>::tMapIterator p=CoreData<MustlLink>::Instance().Begin(); p != endValue; ++p)
    {
        p->second->Disconnect(MustlProtocol::kReasonCodeUserDisconnect);
    }
}

void
GameNetUtils::KillServersByType(bool inImageIs)
{
    CoreData<GameDefServer>::tMapIterator endValue=CoreData<GameDefServer>::Instance().End();

    for (CoreData<GameDefServer>::tMapIterator p=CoreData<GameDefServer>::Instance().Begin(); p != endValue; ++p)
    {
        if (p->second->ImageIs() == inImageIs)
        {
            p->second->Kill();
        }
    }
}

void
GameNetUtils::KillClientsByType(bool inImageIs)
{
    CoreData<GameDefClient>::tMapIterator endValue=CoreData<GameDefClient>::Instance().End();

    for (CoreData<GameDefClient>::tMapIterator p=CoreData<GameDefClient>::Instance().Begin(); p != endValue; ++p)
    {
        if (p->second->ImageIs() == inImageIs)
        {
            p->second->Kill();
        }
    }
}

bool
GameNetUtils::MaintainLinks(vector< CoreDataRef<MustlLink> >& inLinks, const string& inClientName, const MustlAddress& inAddress, U32 inLinkNum)
{
    bool linkGood=false;
    U32 size = inLinks.size();
    COREASSERT(inLinkNum <= size);
    
    for (U32 i=0; i<inLinkNum; ++i)
    {
        MustlLink *linkPtr = NULL;
        if (inLinks[i].GetIfExists(linkPtr))
        {
            COREASSERT(linkPtr != NULL);
            if (linkPtr->IsDead())
            {
                CreateLink(inLinks[i], inClientName, inAddress);
            }
            else
            {
                linkGood = true;
            }
        }
        else
        {
            CreateLink(inLinks[i], inClientName, inAddress);
        }
    }
    return linkGood;
}

void
GameNetUtils::CreateLink(CoreDataRef<MustlLink>& outLink, const string& inClientName, const MustlAddress& inAddress)
{
    try
    {
        string linkName=MustlLink::NextLinkNameTake();
        CoreData<MustlLink>::Instance().Give(linkName, new MustlLink(GameNetID(inClientName), inAddress));
        outLink.NameSet(linkName);
    }
    catch (MustlFail& e)
    {
        MustlLog::Instance().NetLog() << "Link creation failed: " << e.what() << endl;
    }
}

void
GameNetUtils::ReliableSend(U32& ioLinkNum, vector< CoreDataRef<MustlLink> >& inLinks, U32 inLinkNum, MustlData& ioData)
{
    COREASSERT(inLinkNum <= inLinks.size());
    for (U32 i=0; i<inLinkNum; ++i)
    {
        ++ioLinkNum;
        if (ioLinkNum >= inLinkNum) ioLinkNum = 0;
        MustlLink *linkPtr = NULL;
        if (inLinks[ioLinkNum].GetIfExists(linkPtr))
        {
            COREASSERT(linkPtr != NULL);
            if (linkPtr->ReadyIs())
            {
                linkPtr->ReliableSend(ioData);
                return;
            }
        }
    }
    throw(NetworkFail("Send failed because no links were available"));
}

void
GameNetUtils::FastSend(U32& ioLinkNum, vector< CoreDataRef<MustlLink> >& inLinks, U32 inLinkNum, MustlData& ioData)
{
    COREASSERT(inLinkNum <= inLinks.size());
    for (U32 i=0; i<inLinkNum; ++i)
    {
        ++ioLinkNum;
        if (ioLinkNum >= inLinkNum) ioLinkNum = 0;
        MustlLink *linkPtr = NULL;
        if (inLinks[ioLinkNum].GetIfExists(linkPtr))
        {
            COREASSERT(linkPtr != NULL);
            if (linkPtr->ReadyIs())
            {
                linkPtr->FastSend(ioData);
                return;
            }
        }
    }
    throw(NetworkFail("Send failed because no links were available"));
}

void
GameNetUtils::NetTicker(void)
{
    // Needs to be called at least once a second
    U32 currentMsec = dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance()).MillisecondsGet();
    {
        CoreData<GameDefClient>::tMapIterator endValue = CoreData<GameDefClient>::Instance().End();
        CoreData<GameDefClient>::tMapIterator killValue = CoreData<GameDefClient>::Instance().End();
    
        for (CoreData<GameDefClient>::tMapIterator p=CoreData<GameDefClient>::Instance().Begin(); p != endValue; ++p)
        {
            if (p->second->ImageIs())
            {
                // Expire images after a time limit
                if (currentMsec > p->second->CreationMsecGet() + kImageLifetimeMsec)
                {
                    p->second->Kill();
                }
            }
            else
            {
                p->second->Ticker(p->first);
            }
            if (p->second->IsDead())
            {
                killValue = p;
            }
        }
        if (killValue != CoreData<GameDefClient>::Instance().End())
        {
            CoreData<GameDefClient>::Instance().Delete(killValue);
        }
    }
    
    
    bool serverNeeded=false;
    {
        CoreData<GameDefServer>::tMapIterator endValue = CoreData<GameDefServer>::Instance().End();
        CoreData<GameDefServer>::tMapIterator killValue = CoreData<GameDefServer>::Instance().End();
    
        for (CoreData<GameDefServer>::tMapIterator p = CoreData<GameDefServer>::Instance().Begin(); p != endValue; ++p)
        {
            if (p->second->ImageIs())
            {
                // Expire images after a time limit
                if (currentMsec > p->second->CreationMsecGet() + kImageLifetimeMsec)
                {
                    p->second->Kill();
                }
            }
            else
            {
                p->second->Ticker(p->first);
                serverNeeded=true;
            }
            if (p->second->IsDead())
            {
                killValue = p;
            }
        }
        if (killValue != CoreData<GameDefServer>::Instance().End())
        {
            CoreData<GameDefServer>::Instance().Delete(killValue);
        }
    }
    
    if (serverNeeded)
    {
        if (!MustlServer::Instance().IsServing())
        {
            U32 portNum=GameConfig::Instance().ParameterGet("multiport").U32Get();
    
            try
            {
                MustlServer::Instance().Connect(portNum);
            }
            catch (MustlFail& e)
            {
                static U32 failedPortNum=65536;
                if (portNum != failedPortNum)
                {
                    MustlLog::Instance().NetLog() << "Server creation exception: " << e.what() << endl;
                    PlatformMiscUtils::MinorErrorBox(e.what());
                    failedPortNum=portNum;
                }
            }
        }
    }
    else
    {
        if (MustlServer::Instance().IsServing())
        {
            MustlServer::Instance().Disconnect();
        }
    }
}

void
GameNetUtils::WebReceive(void)
{
    try
    {
        MustlWebServer::Instance().Accept();
        MustlWebRouter::Instance().ReceiveAll();
    }
    catch (MustlFail& e)
    {
        MustlLog::Instance().WebLog() << "Network exception: " << e.what() << endl;
    }
}

void
GameNetUtils::NetReceive(void)
{
    try
    {
        MustlServer::Instance().Accept();
        MustlRouter::Instance().ReceiveAll(GameRouter::Instance());
    }
    catch (MustlFail& e)
    {
        MustlLog::Instance().NetLog() << "Network exception: " << e.what() << endl;
    }
}
