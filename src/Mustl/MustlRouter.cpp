/*
 * $Id: MustlRouter.cpp,v 1.2 2002/12/12 18:38:25 southa Exp $
 * $Log: MustlRouter.cpp,v $
 * Revision 1.2  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 * Revision 1.11  2002/12/10 20:38:06  southa
 * Server timing
 *
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

#include "MustlRouter.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlNamespace.h"

auto_ptr<MustlRouter> MustlRouter::m_instance;

MustlRouter::MustlRouter() :
    m_lastTickMsec(0)
{
}

void
MustlRouter::ReceiveAll(MustlHandler& inHandler)
{
    tMsec currentMsec = MustlTimer::Instance().CurrentMsecGet();
    bool callTick=false;
    
    if (m_lastTickMsec + kTickPeriod < currentMsec ||
        currentMsec == 0)
    {
        m_lastTickMsec = currentMsec;
        callTick = true;
    }

    UDPReceiveFromServer(inHandler);
    
    CoreData<MustlLink>::tMapIterator endValue=CoreData<MustlLink>::Instance().End();
    CoreData<MustlLink>::tMapIterator killValue=CoreData<MustlLink>::Instance().End();

    if (callTick)
    {
        for (CoreData<MustlLink>::tMapIterator p=CoreData<MustlLink>::Instance().Begin(); p != endValue; ++p)
        {
            MUSTLASSERT(p->second != NULL);
            MustlLink& linkRef = *p->second;
            linkRef.Tick();
            if (linkRef.IsDead())
            {
                killValue=p;
            }
        }
    }

    if (killValue != CoreData<MustlLink>::Instance().End())
    {
        CoreData<MustlLink>::Instance().Delete(killValue);
    }
    
    for (CoreData<MustlLink>::tMapIterator p=CoreData<MustlLink>::Instance().Begin(); p != endValue; ++p)
    {
        MUSTLASSERT(p->second != NULL);
        MustlLink& linkRef = *p->second;

        MustlData *netData=NULL;
        if (linkRef.Receive(netData))
        {
            MUSTLASSERT(netData != NULL);
            // cerr << "Received on " << p->first << ": " << *netData << endl;
            U32 messageType = netData->MessageBytePop();
            if (MustlProtocol::MessageTypeIsLinkLayer(messageType))
            {
                linkRef.MessageHandle(messageType, *netData);
            }
            else
            {
                linkRef.TouchLink(); // Reset inactivity timer
                MustlProtocol::RemoveLength(*netData, messageType);
                U32 appMessageType = MustlProtocol::LinkToAppType(messageType);
                inHandler.MessageHandle(*netData, linkRef, appMessageType);
            }
        }
    }
}

void
MustlRouter::UDPIfAddressMatchReceive(MustlData& ioData, MustlHandler& inHandler)
{
    CoreData<MustlLink>::tMapIterator endValue=CoreData<MustlLink>::Instance().End();

    for (CoreData<MustlLink>::tMapIterator p=CoreData<MustlLink>::Instance().Begin();
         p != endValue; ++p)
    {
        MUSTLASSERT(p->second != NULL);
        MustlLink& linkRef = *p->second;
        bool outTakeMessage;
        if (linkRef.UDPIfAddressMatchReceive(outTakeMessage, ioData))
        {
            // cerr << "Received on " << p->first << ": " << ioData << endl;

            if (outTakeMessage)
            {
                U32 messageType = ioData.MessageBytePop();
                if (MustlProtocol::MessageTypeIsLinkLayer(messageType))
                {
                    linkRef.MessageHandle(messageType, ioData);
                }
                else
                {
                    linkRef.TouchLink(); // Reset inactivity timer
                    MustlProtocol::RemoveLength(ioData, messageType);
                    U32 appMessageType = MustlProtocol::LinkToAppType(messageType);
                    inHandler.MessageHandle(ioData, linkRef, appMessageType);
                }
            }
            // Message handled so return
            return;
        }
    }
    MustlLog::Instance().VerboseLog() << "Discarding message from " <<
        MustlUtils::IPAddressToLogString(ioData.SourceHostGet()) << ":" <<
        MustlPlatform::NetworkToHostOrderU16(ioData.SourcePortGet()) << endl;
}

void
MustlRouter::UDPReceiveFromServer(MustlHandler& inHandler)
{
    for (U32 i=0; i<100; ++i)
    {
        MustlData netData;
        MustlServer::Instance().UDPReceive(netData);
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
