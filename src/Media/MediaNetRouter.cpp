/*
 * $Id: MediaNetRouter.cpp,v 1.3 2002/11/04 19:34:47 southa Exp $
 * $Log: MediaNetRouter.cpp,v $
 * Revision 1.3  2002/11/04 19:34:47  southa
 * Network link maintenance
 *
 * Revision 1.2  2002/11/04 13:11:58  southa
 * Link setup work
 *
 * Revision 1.1  2002/11/04 01:02:38  southa
 * Link checks
 *
 */

#include "MediaNetRouter.h"

#include "MediaNetData.h"
#include "MediaNetLog.h"
#include "MediaNetLink.h"
#include "MediaNetProtocol.h"
#include "MediaNetServer.h"
#include "MediaNetUtils.h"

auto_ptr<MediaNetRouter> MediaNetRouter::m_instance;

MediaNetRouter::MediaNetRouter() :
    m_lastTickMsec(0)
{
}

void
MediaNetRouter::ReceiveAll(void)
{
    U32 currentMsec = SDL_GetTicks();
    bool callTick=false;;
    if (m_lastTickMsec + kTickPeriod < currentMsec)
    {
        m_lastTickMsec = currentMsec;
        callTick = true;
    }

    UDPReceiveFromServer();
    
    CoreData<MediaNetLink>::tMapIterator endValue=CoreData<MediaNetLink>::Instance().End();
    CoreData<MediaNetLink>::tMapIterator killValue=CoreData<MediaNetLink>::Instance().End();
    
    for (CoreData<MediaNetLink>::tMapIterator p=CoreData<MediaNetLink>::Instance().Begin();
         p != endValue; ++p)
    {
        MediaNetData *netData=NULL;
        if (p->second->Receive(netData))
        {
            COREASSERT(netData != NULL);
            // cerr << "Received on " << p->first << ": " << *netData << endl;
            U32 messageType = netData->MessageBytePop();
            if (MediaNetProtocol::MessageTypeIsLinkLayer(messageType))
            {
                p->second->MessageHandle(messageType, *netData);
            }
            else
            {
                // pass to application
            }
        }
        if (callTick)
        {
            p->second->Tick();
            if (p->second->IsDead())
            {
                killValue=p;
            }
        }
    }
    if (killValue != CoreData<MediaNetLink>::Instance().End())
    {
        CoreData<MediaNetLink>::Instance().DataDelete(killValue->first);
    }
}

void
MediaNetRouter::UDPIfAddressMatchReceive(MediaNetData& ioData)
{
    CoreData<MediaNetLink>::tMapIterator endValue=CoreData<MediaNetLink>::Instance().End();

    for (CoreData<MediaNetLink>::tMapIterator p=CoreData<MediaNetLink>::Instance().Begin();
         p != endValue; ++p)
    {
        bool outTakeMessage;
        if (p->second->UDPIfAddressMatchReceive(outTakeMessage, ioData))
        {
            if (outTakeMessage)
            {
                U32 messageType = ioData.MessageBytePop();
                if (MediaNetProtocol::MessageTypeIsLinkLayer(messageType))
                {
                    p->second->MessageHandle(messageType, ioData);
                }
                else
                {
                    // pass to application
                }
            }
            // Message handled so return
            return;
        }
    }
    MediaNetLog::Instance().VerboseLog() << "Discarding message from " <<
        MediaNetUtils::IPAddressToLogString(ioData.SourceHostGet()) << ":" <<
        ioData.SourcePortGet() << endl;
}

void
MediaNetRouter::UDPReceiveFromServer(void)
{
    for (U32 i=0; i<100; ++i)
    {
        MediaNetData netData;
        MediaNetServer::Instance().UDPReceive(netData);
        if (netData.ReadSizeGet() != 0)
        {
            UDPIfAddressMatchReceive(netData);
        }
        else
        {
            break;
        }
    }
}
