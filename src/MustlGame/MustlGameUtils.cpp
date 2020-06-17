//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameUtils.cpp
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
//%Header } meZ4B58eXQ1zYleVNV+iDw
/*
 * $Id: MustlGameUtils.cpp,v 1.5 2006/06/01 15:39:57 southa Exp $
 * $Log: MustlGameUtils.cpp,v $
 * Revision 1.5  2006/06/01 15:39:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/06 22:42:04  southa
 * Include fixes
 *
 * Revision 1.1  2003/10/06 22:22:38  southa
 * Moved from Game to MustlGame
 *
 * Revision 1.19  2003/10/04 12:23:01  southa
 * File renaming
 *
 * Revision 1.18  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.17  2003/08/21 23:08:50  southa
 * Fixed file headers
 *
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

#include "MustlGameUtils.h"

#include "MustlGameClient.h"
#include "MustlGameServer.h"
#include "MustlGameID.h"

#include "mushGame.h"
#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

void
MustlGameUtils::KillServers(void)
{
    KillServersByType(false);
}

void
MustlGameUtils::KillServerImages(void)
{
    KillServersByType(true);
}

void
MustlGameUtils::KillClients(void)
{
    KillClientsByType(false);
}

void
MustlGameUtils::KillClientImages(void)
{
    KillClientsByType(true);
}

void
MustlGameUtils::KillLinks(void)
{
    MushcoreData<MustlLink>::tMapIterator endValue=MushcoreData<MustlLink>::Sgl().End();

    for (MushcoreData<MustlLink>::tMapIterator p=MushcoreData<MustlLink>::Sgl().Begin(); p != endValue; ++p)
    {
        p->second->Disconnect(MustlProtocol::kReasonCodeUserDisconnect);
    }
}

void
MustlGameUtils::KillServersByType(bool inImageIs)
{
    MushcoreData<MustlGameServer>::tMapIterator endValue=MushcoreData<MustlGameServer>::Sgl().End();

    for (MushcoreData<MustlGameServer>::tMapIterator p=MushcoreData<MustlGameServer>::Sgl().Begin(); p != endValue; ++p)
    {
        if (p->second->ImageIs() == inImageIs)
        {
            p->second->Kill();
        }
    }
}

void
MustlGameUtils::KillClientsByType(bool inImageIs)
{
    MushcoreData<MustlGameClient>::tMapIterator endValue=MushcoreData<MustlGameClient>::Sgl().End();

    for (MushcoreData<MustlGameClient>::tMapIterator p=MushcoreData<MustlGameClient>::Sgl().Begin(); p != endValue; ++p)
    {
        if (p->second->ImageIs() == inImageIs)
        {
            p->second->Kill();
        }
    }
}

bool
MustlGameUtils::MaintainLinks(vector< MushcoreDataRef<MustlLink> >& inLinks, const string& inClientName, const MustlAddress& inAddress, U32 inLinkNum)
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
MustlGameUtils::CreateLink(MushcoreDataRef<MustlLink>& outLink, const string& inClientName, const MustlAddress& inAddress)
{
    try
    {
        string linkName=MustlLink::NextLinkNameTake();
        MushcoreData<MustlLink>::Sgl().Give(linkName, new MustlLink(MustlGameID(inClientName), inAddress));
        outLink.NameSet(linkName);
    }
    catch (MushcoreNonFatalFail& e)
    {
        MustlLog::Sgl().NetLog() << "Link creation failed: " << e.what() << endl;
    }
}

void
MustlGameUtils::ReliableSend(U32& ioLinkNum, vector< MushcoreDataRef<MustlLink> >& inLinks, U32 inLinkNum, MustlData& ioData)
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
    throw(MustlFail("Send failed because no links were available"));
}

void
MustlGameUtils::FastSend(U32& ioLinkNum, vector< MushcoreDataRef<MustlLink> >& inLinks, U32 inLinkNum, MustlData& ioData)
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
    throw(MustlFail("Send failed because no links were available"));
}

void
MustlGameUtils::NetTicker(void)
{
    // Needs to be called at least once a second
    U32 currentMsec = dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl()).MillisecondsGet();
    {
        MushcoreData<MustlGameClient>::tMapIterator endValue = MushcoreData<MustlGameClient>::Sgl().End();
        MushcoreData<MustlGameClient>::tMapIterator killValue = MushcoreData<MustlGameClient>::Sgl().End();
    
        for (MushcoreData<MustlGameClient>::tMapIterator p=MushcoreData<MustlGameClient>::Sgl().Begin(); p != endValue; ++p)
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
        if (killValue != MushcoreData<MustlGameClient>::Sgl().End())
        {
            MushcoreData<MustlGameClient>::Sgl().Delete(killValue);
        }
    }
    
    
    bool serverNeeded=false;
    {
        MushcoreData<MustlGameServer>::tMapIterator endValue = MushcoreData<MustlGameServer>::Sgl().End();
        MushcoreData<MustlGameServer>::tMapIterator killValue = MushcoreData<MustlGameServer>::Sgl().End();
    
        for (MushcoreData<MustlGameServer>::tMapIterator p = MushcoreData<MustlGameServer>::Sgl().Begin(); p != endValue; ++p)
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
        if (killValue != MushcoreData<MustlGameServer>::Sgl().End())
        {
            MushcoreData<MustlGameServer>::Sgl().Delete(killValue);
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
MustlGameUtils::WebReceive(void)
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
MustlGameUtils::NetReceive(void)
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
