/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameNetUtils.cpp,v 1.16 2003/01/20 10:45:26 southa Exp $
 * $Log: GameNetUtils.cpp,v $
 * Revision 1.16  2003/01/20 10:45:26  southa
 * Singleton tidying
 *
 * Revision 1.15  2003/01/14 17:38:20  southa
 * Mustl web configuration
 *
 * Revision 1.14  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.13  2003/01/12 17:32:55  southa
 * Mushcore work
 *
 * Revision 1.12  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.11  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.10  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/12/13 01:07:25  southa
 * Mustl work
 *
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
#include "GameSTL.h"

#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

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
    MushcoreData<MustlLink>::tMapIterator endValue=MushcoreData<MustlLink>::Sgl().End();

    for (MushcoreData<MustlLink>::tMapIterator p=MushcoreData<MustlLink>::Sgl().Begin(); p != endValue; ++p)
    {
        p->second->Disconnect(MustlProtocol::kReasonCodeUserDisconnect);
    }
}

void
GameNetUtils::KillServersByType(bool inImageIs)
{
    MushcoreData<GameDefServer>::tMapIterator endValue=MushcoreData<GameDefServer>::Sgl().End();

    for (MushcoreData<GameDefServer>::tMapIterator p=MushcoreData<GameDefServer>::Sgl().Begin(); p != endValue; ++p)
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
    MushcoreData<GameDefClient>::tMapIterator endValue=MushcoreData<GameDefClient>::Sgl().End();

    for (MushcoreData<GameDefClient>::tMapIterator p=MushcoreData<GameDefClient>::Sgl().Begin(); p != endValue; ++p)
    {
        if (p->second->ImageIs() == inImageIs)
        {
            p->second->Kill();
        }
    }
}

bool
GameNetUtils::MaintainLinks(vector< MushcoreDataRef<MustlLink> >& inLinks, const string& inClientName, const MustlAddress& inAddress, U32 inLinkNum)
{
    bool linkGood=false;
    U32 size = inLinks.size();
    MUSHCOREASSERT(inLinkNum <= size);
    
    for (U32 i=0; i<inLinkNum; ++i)
    {
        MustlLink *linkPtr = NULL;
        if (inLinks[i].GetIfExists(linkPtr))
        {
            MUSHCOREASSERT(linkPtr != NULL);
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
GameNetUtils::CreateLink(MushcoreDataRef<MustlLink>& outLink, const string& inClientName, const MustlAddress& inAddress)
{
    try
    {
        string linkName=MustlLink::NextLinkNameTake();
        MushcoreData<MustlLink>::Sgl().Give(linkName, new MustlLink(GameNetID(inClientName), inAddress));
        outLink.NameSet(linkName);
    }
    catch (MushcoreNonFatalFail& e)
    {
        MustlLog::Sgl().NetLog() << "Link creation failed: " << e.what() << endl;
    }
}

void
GameNetUtils::ReliableSend(U32& ioLinkNum, vector< MushcoreDataRef<MustlLink> >& inLinks, U32 inLinkNum, MustlData& ioData)
{
    MUSHCOREASSERT(inLinkNum <= inLinks.size());
    for (U32 i=0; i<inLinkNum; ++i)
    {
        ++ioLinkNum;
        if (ioLinkNum >= inLinkNum) ioLinkNum = 0;
        MustlLink *linkPtr = NULL;
        if (inLinks[ioLinkNum].GetIfExists(linkPtr))
        {
            MUSHCOREASSERT(linkPtr != NULL);
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
GameNetUtils::FastSend(U32& ioLinkNum, vector< MushcoreDataRef<MustlLink> >& inLinks, U32 inLinkNum, MustlData& ioData)
{
    MUSHCOREASSERT(inLinkNum <= inLinks.size());
    for (U32 i=0; i<inLinkNum; ++i)
    {
        ++ioLinkNum;
        if (ioLinkNum >= inLinkNum) ioLinkNum = 0;
        MustlLink *linkPtr = NULL;
        if (inLinks[ioLinkNum].GetIfExists(linkPtr))
        {
            MUSHCOREASSERT(linkPtr != NULL);
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
    U32 currentMsec = dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl()).MillisecondsGet();
    {
        MushcoreData<GameDefClient>::tMapIterator endValue = MushcoreData<GameDefClient>::Sgl().End();
        MushcoreData<GameDefClient>::tMapIterator killValue = MushcoreData<GameDefClient>::Sgl().End();
    
        for (MushcoreData<GameDefClient>::tMapIterator p=MushcoreData<GameDefClient>::Sgl().Begin(); p != endValue; ++p)
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
        if (killValue != MushcoreData<GameDefClient>::Sgl().End())
        {
            MushcoreData<GameDefClient>::Sgl().Delete(killValue);
        }
    }
    
    
    bool serverNeeded=false;
    {
        MushcoreData<GameDefServer>::tMapIterator endValue = MushcoreData<GameDefServer>::Sgl().End();
        MushcoreData<GameDefServer>::tMapIterator killValue = MushcoreData<GameDefServer>::Sgl().End();
    
        for (MushcoreData<GameDefServer>::tMapIterator p = MushcoreData<GameDefServer>::Sgl().Begin(); p != endValue; ++p)
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
        if (killValue != MushcoreData<GameDefServer>::Sgl().End())
        {
            MushcoreData<GameDefServer>::Sgl().Delete(killValue);
        }
    }
    
    if (serverNeeded)
    {
        if (!MustlServer::Sgl().IsServing())
        {
            U32 portNum=GameConfig::Sgl().ParameterGet("multiport").U32Get();
    
            try
            {
                MustlServer::Sgl().Connect(portNum);
            }
            catch (MushcoreNonFatalFail& e)
            {
                static U32 failedPortNum=65536;
                if (portNum != failedPortNum)
                {
                    MustlLog::Sgl().NetLog() << "Server creation exception: " << e.what() << endl;
                    PlatformMiscUtils::MinorErrorBox(e.what());
                    failedPortNum=portNum;
                }
            }
        }
    }
    else
    {
        if (MustlServer::Sgl().IsServing())
        {
            MustlServer::Sgl().Disconnect();
        }
    }
}

void
GameNetUtils::WebReceive(void)
{
    try
    {
        MustlWebServer::Sgl().Accept();
        MustlWebRouter::Sgl().ReceiveAll();
    }
    catch (MushcoreNonFatalFail& e)
    {
        MustlLog::Sgl().WebLog() << "Network exception: " << e.what() << endl;
    }
}

void
GameNetUtils::NetReceive(void)
{
    try
    {
        MustlServer::Sgl().Accept();
        MustlRouter::Sgl().ReceiveAll(GameRouter::Sgl());
    }
    catch (MushcoreNonFatalFail& e)
    {
        MustlLog::Sgl().NetLog() << "Network exception: " << e.what() << endl;
    }
}
