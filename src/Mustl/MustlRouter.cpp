/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlRouter.cpp,v 1.12 2003/01/13 15:01:20 southa Exp $
 * $Log: MustlRouter.cpp,v $
 * Revision 1.12  2003/01/13 15:01:20  southa
 * Fix Mustl command line build
 *
 * Revision 1.11  2003/01/11 17:58:15  southa
 * Mustl fixes
 *
 * Revision 1.10  2003/01/09 14:57:08  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/29 20:59:59  southa
 * More build fixes
 *
 * Revision 1.8  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.7  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/12/17 12:53:34  southa
 * Mustl library
 *
 * Revision 1.5  2002/12/14 15:04:34  southa
 * Mustl fixes
 *
 * Revision 1.4  2002/12/13 19:03:05  southa
 * Mustl interface cleanup
 *
 * Revision 1.3  2002/12/13 01:06:54  southa
 * Mustl work
 *
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

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;
//using Mushware::MushcoreData;

auto_ptr<MustlRouter> MustlRouter::m_instance;

MustlRouter::MustlRouter() :
    m_lastTickMsec(0)
{
}

void
MustlRouter::ProcessMessage(MustlData& ioData, MustlLink& ioLink, MustlMessageHandler& inHandler)
{
    do
    {
        MustlProtocol::Unpack(ioData);
        if (MustlProtocol::MessageTake(ioData))
        {
            U32 messageType = ioData.MessageBytePop();
            if (MustlProtocol::MessageTypeIsLinkLayer(messageType))
            {
                ioLink.MessageHandle(messageType, ioData);
            }
            else
            {
                ioLink.InactivityTimerReset(); // Reset inactivity timer
                MustlProtocol::RemoveLength(ioData, messageType);
                U32 appMessageType = MustlProtocol::LinkToAppType(messageType);
                inHandler.MessageHandle(ioData, ioLink, appMessageType);
            }
        }
        else
        {
            // No message to take
            break;
        }
    } while (ioData.ReadSizeGet() > 0);
}

void
MustlRouter::ReceiveAll(MustlMessageHandler& inHandler)
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
    
    MushcoreData<MustlLink>::tMapIterator endValue=MushcoreData<MustlLink>::Instance().End();
    MushcoreData<MustlLink>::tMapIterator killValue=MushcoreData<MustlLink>::Instance().End();

    if (callTick)
    {
        for (MushcoreData<MustlLink>::tMapIterator p=MushcoreData<MustlLink>::Instance().Begin(); p != endValue; ++p)
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

    if (killValue != MushcoreData<MustlLink>::Instance().End())
    {
        MushcoreData<MustlLink>::Instance().Delete(killValue);
    }
    
    for (MushcoreData<MustlLink>::tMapIterator p=MushcoreData<MustlLink>::Instance().Begin(); p != endValue; ++p)
    {
        MUSTLASSERT(p->second != NULL);
        MustlLink& linkRef = *p->second;

        MustlData *netData=NULL;
        while (linkRef.Receive(netData))
        {
            if (MustlLog::Instance().TrafficLogGet())
            {
                MustlLog::Instance().TrafficLog() << "received on link " << p->first << endl;
            }
            MUSTLASSERT(netData != NULL);
            ProcessMessage(*netData, linkRef, inHandler);
        }
    }
}

void
MustlRouter::UDPIfAddressMatchReceive(MustlData& ioData, MustlMessageHandler& inHandler)
{
    MushcoreData<MustlLink>::tMapIterator endValue=MushcoreData<MustlLink>::Instance().End();

    // Check for an exact address match
    for (MushcoreData<MustlLink>::tMapIterator p=MushcoreData<MustlLink>::Instance().Begin();
         p != endValue; ++p)
    {
        MUSTLASSERT(p->second != NULL);
        MustlLink& linkRef = *p->second;
        if (linkRef.UDPAddressMatchDoes(ioData))
        {
            if (MustlLog::Instance().TrafficLogGet())
            {
                MustlLog::Instance().TrafficLog() << "received on link " << p->first << endl;
            }
            ProcessMessage(ioData, linkRef, inHandler);
            return;
        }
    }

    // Check for a host match where the port number is zero.  This caters for link
    // establishment messages where the port number of the remote end is not yet known
    for (MushcoreData<MustlLink>::tMapIterator p=MushcoreData<MustlLink>::Instance().Begin();
         p != endValue; ++p)
    {
        MUSTLASSERT(p->second != NULL);
        MustlLink& linkRef = *p->second;
        if (linkRef.UDPAddressGet().PortGetNetworkOrder() == 0 &&
            linkRef.UDPHostMatchDoes(ioData))
        {
            if (MustlLog::Instance().TrafficLogGet())
            {
                MustlLog::Instance().TrafficLog() << "received on link " << p->first << endl;
            }
            ProcessMessage(ioData, linkRef, inHandler);
            return;
        }
    }

    MustlLog::Instance().VerboseLog() << "Unrecognised message source; discarding " << ioData.SourceGet() << endl;
}

void
MustlRouter::UDPReceiveFromServer(MustlMessageHandler& inHandler)
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
