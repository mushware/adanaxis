/*
 * $Id: MediaNetRouter.cpp,v 1.10 2002/12/09 23:59:59 southa Exp $
 * $Log: MediaNetRouter.cpp,v $
 * Revision 1.10  2002/12/09 23:59:59  southa
 * Network control
 *
 * Revision 1.9  2002/12/07 18:32:16  southa
 * Network ID stuff
 *
 * Revision 1.8  2002/12/05 13:20:13  southa
 * Client link handling
 *
 * Revision 1.7  2002/11/27 16:35:10  southa
 * Client and server image handling
 *
 * Revision 1.6  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 * Revision 1.5  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.4  2002/11/22 15:00:33  southa
 * Network connection handling
 *
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
#include "MediaNetHandler.h"
#include "MediaNetLog.h"
#include "MediaNetLink.h"
#include "MediaNetProtocol.h"
#include "MediaNetServer.h"
#include "MediaNetUtils.h"

#include "mushPlatform.h"

auto_ptr<MediaNetRouter> MediaNetRouter::m_instance;

MediaNetRouter::MediaNetRouter() :
    m_lastTickMsec(0)
{
}

void
MediaNetRouter::ReceiveAll(MediaNetHandler& inHandler)
{
    U32 currentMsec = SDL_GetTicks();
    bool callTick=false;;
    if (m_lastTickMsec + kTickPeriod < currentMsec)
    {
        m_lastTickMsec = currentMsec;
        callTick = true;
    }

    UDPReceiveFromServer(inHandler);
    
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
                // Make data look like it came from the TCP address in all cases
                // netData->SourcePortSet(p->second->TCPTargetPortGet());
                p->second->TouchLink(); // Reset inactivity timer
                MediaNetProtocol::RemoveLength(*netData, messageType);
                U32 appMessageType = MediaNetProtocol::LinkToAppType(messageType);
                inHandler.MessageHandle(*netData, *p->second, appMessageType);
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
        CoreData<MediaNetLink>::Instance().Delete(killValue);
    }
}

void
MediaNetRouter::UDPIfAddressMatchReceive(MediaNetData& ioData, MediaNetHandler& inHandler)
{
    CoreData<MediaNetLink>::tMapIterator endValue=CoreData<MediaNetLink>::Instance().End();

    for (CoreData<MediaNetLink>::tMapIterator p=CoreData<MediaNetLink>::Instance().Begin();
         p != endValue; ++p)
    {
        bool outTakeMessage;
        if (p->second->UDPIfAddressMatchReceive(outTakeMessage, ioData))
        {
            // cerr << "Received on " << p->first << ": " << ioData << endl;

            if (outTakeMessage)
            {
                U32 messageType = ioData.MessageBytePop();
                if (MediaNetProtocol::MessageTypeIsLinkLayer(messageType))
                {
                    p->second->MessageHandle(messageType, ioData);
                }
                else
                {
                    p->second->TouchLink(); // Reset inactivity timer
                    MediaNetProtocol::RemoveLength(ioData, messageType);
                    U32 appMessageType = MediaNetProtocol::LinkToAppType(messageType);
                    inHandler.MessageHandle(ioData, *p->second, appMessageType);
                }
            }
            // Message handled so return
            return;
        }
    }
    MediaNetLog::Instance().VerboseLog() << "Discarding message from " <<
        MediaNetUtils::IPAddressToLogString(ioData.SourceHostGet()) << ":" <<
        PlatformNet::NetworkToHostOrderU16(ioData.SourcePortGet()) << endl;
}

void
MediaNetRouter::UDPReceiveFromServer(MediaNetHandler& inHandler)
{
    for (U32 i=0; i<100; ++i)
    {
        MediaNetData netData;
        MediaNetServer::Instance().UDPReceive(netData);
        if (netData.ReadSizeGet() != 0)
        {
            UDPIfAddressMatchReceive(netData, inHandler);
        }
        else
        {
            break;
        }
    }
}
