/*
 * $Id: GameNetUtils.cpp,v 1.2 2002/12/04 12:54:41 southa Exp $
 * $Log: GameNetUtils.cpp,v $
 * Revision 1.2  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.1  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 */

#include "GameNetUtils.h"

#include "GameDefClient.h"
#include "GameDefServer.h"

#include "mushMedia.h"

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
GameNetUtils::MaintainLinks(vector< CoreDataRef<MediaNetLink> >& inLinks, const MediaNetAddress& inAddress, U32 inLinkNum)
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
                CreateLink(inLinks[i], inAddress);
            }
            else
            {
                linkGood = true;
            }
        }
        else
        {
            CreateLink(inLinks[i], inAddress);
        }
    }
    return linkGood;
}

void
GameNetUtils::CreateLink(CoreDataRef<MediaNetLink>& outLink, const MediaNetAddress& inAddress)
{
    try
    {
        string linkName=MediaNetLink::NextLinkNameTake();
        CoreData<MediaNetLink>::Instance().Give(linkName, new MediaNetLink(inAddress));
        outLink.NameSet(linkName);
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "Link creation failed: " << e.what() << endl;
    }
}

void
GameNetUtils::ReliableSend(U32& ioLinkNum, vector< CoreDataRef<MediaNetLink> >& inLinks, MediaNetData& ioData)
{
    U32 size=inLinks.size();
    for (U32 i=0; i<size; ++i)
    {
        ++ioLinkNum;
        if (ioLinkNum >= size) ioLinkNum = 0;
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
    
    
