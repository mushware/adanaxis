/*
 * $Id: GameNetUtils.cpp,v 1.4 2002/12/05 23:52:51 southa Exp $
 * $Log: GameNetUtils.cpp,v $
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
    CoreData<MediaNetLink>::tMapIterator endValue=CoreData<MediaNetLink>::Instance().End();

    for (CoreData<MediaNetLink>::tMapIterator p=CoreData<MediaNetLink>::Instance().Begin(); p != endValue; ++p)
    {
        p->second->Disconnect(MediaNetProtocol::kReasonCodeUserDisconnect);
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
GameNetUtils::MaintainLinks(vector< CoreDataRef<MediaNetLink> >& inLinks, const string& inClientName, const MediaNetAddress& inAddress, U32 inLinkNum)
{
    bool linkGood=false;
    U32 size = inLinks.size();
    COREASSERT(inLinkNum <= size);
    
    for (U32 i=0; i<inLinkNum; ++i)
    {
        MediaNetLink *linkPtr = NULL;
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
GameNetUtils::CreateLink(CoreDataRef<MediaNetLink>& outLink, const string& inClientName, const MediaNetAddress& inAddress)
{
    try
    {
        string linkName=MediaNetLink::NextLinkNameTake();
        CoreData<MediaNetLink>::Instance().Give(linkName, new MediaNetLink(MediaNetIDString(inClientName), inAddress));
        outLink.NameSet(linkName);
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "Link creation failed: " << e.what() << endl;
    }
}

void
GameNetUtils::ReliableSend(U32& ioLinkNum, vector< CoreDataRef<MediaNetLink> >& inLinks, U32 inLinkNum, MediaNetData& ioData)
{
    COREASSERT(inLinkNum <= inLinks.size());
    for (U32 i=0; i<inLinkNum; ++i)
    {
        ++ioLinkNum;
        if (ioLinkNum >= inLinkNum) ioLinkNum = 0;
        MediaNetLink *linkPtr = NULL;
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
GameNetUtils::FastSend(U32& ioLinkNum, vector< CoreDataRef<MediaNetLink> >& inLinks, U32 inLinkNum, MediaNetData& ioData)
{
    COREASSERT(inLinkNum <= inLinks.size());
    for (U32 i=0; i<inLinkNum; ++i)
    {
        ++ioLinkNum;
        if (ioLinkNum >= inLinkNum) ioLinkNum = 0;
        MediaNetLink *linkPtr = NULL;
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
        if (!MediaNetServer::Instance().IsServing())
        {
            U32 portNum=GameConfig::Instance().ParameterGet("multiport").U32Get();
    
            try
            {
                MediaNetServer::Instance().Connect(portNum);
            }
            catch (NetworkFail& e)
            {
                static U32 failedPortNum=65536;
                if (portNum != failedPortNum)
                {
                    MediaNetLog::Instance().NetLog() << "Server creation exception: " << e.what() << endl;
                    PlatformMiscUtils::MinorErrorBox(e.what());
                    failedPortNum=portNum;
                }
            }
        }
    }
    else
    {
        if (MediaNetServer::Instance().IsServing())
        {
            MediaNetServer::Instance().Disconnect();
        }
    }
}

void
GameNetUtils::WebReceive(void)
{
    try
    {
        MediaNetWebServer::Instance().Accept();
        MediaNetWebRouter::Instance().ReceiveAll();
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().WebLog() << "Network exception: " << e.what() << endl;
    }
}

void
GameNetUtils::NetReceive(void)
{
    try
    {
        MediaNetServer::Instance().Accept();
        MediaNetRouter::Instance().ReceiveAll(GameRouter::Instance());
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "Network exception: " << e.what() << endl;
    }
}

bool
GameNetUtils::FindClientDefForLink(string& outName, const MediaNetLink *inLink)
{
    CoreData<GameDefClient>::tMapIterator endValue=CoreData<GameDefClient>::Instance().End();

    for (CoreData<GameDefClient>::tMapIterator p=CoreData<GameDefClient>::Instance().Begin();
         p != endValue; ++p)
    {
        if (p->second->ImageIs())
        {
            if (p->second->LinkMatch(inLink))
            {
                outName = p->first;
                return true;
            }
        }
    }
    return false;    
}
