/*
 * $Id$
 * $Log$
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
GameNetUtils::KillServersByType(bool inIsImage)
{
    CoreData<GameDefServer>::tMapIterator endValue=CoreData<GameDefServer>::Instance().End();

    for (CoreData<GameDefServer>::tMapIterator p=CoreData<GameDefServer>::Instance().Begin(); p != endValue; ++p)
    {
        if (p->second->IsImage() == inIsImage)
        {
            p->second->Kill();
        }
    }
}

void
GameNetUtils::KillClientsByType(bool inIsImage)
{
    CoreData<GameDefClient>::tMapIterator endValue=CoreData<GameDefClient>::Instance().End();

    for (CoreData<GameDefClient>::tMapIterator p=CoreData<GameDefClient>::Instance().Begin(); p != endValue; ++p)
    {
        if (p->second->IsImage() == inIsImage)
        {
            p->second->Kill();
        }
    }
}
