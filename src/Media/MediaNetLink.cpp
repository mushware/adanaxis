/*
 * $Id: MediaNetLink.cpp,v 1.2 2002/11/01 16:15:27 southa Exp $
 * $Log: MediaNetLink.cpp,v $
 * Revision 1.2  2002/11/01 16:15:27  southa
 * Network send and receive
 *
 * Revision 1.1  2002/10/31 19:55:54  southa
 * Network links
 *
 */

#include "MediaNetLink.h"

#include "MediaNetData.h"

auto_ptr< CoreData<MediaNetLink> > CoreData<MediaNetLink>::m_instance;

MediaNetLink::MediaNetLink(const string& inServer, U32 inPort)
{
    TCPConnect(inServer, inPort);
    UDPConnect(inPort);
    m_tcpState=kLinkStateUntested;
    m_udpState=kLinkStateUntested;
    RequestLinkCheck();
}

MediaNetLink::MediaNetLink(TCPsocket inSocket, U32 inPort)
{
    TCPSocketTake(inSocket);
    UDPConnect(inPort);
    m_tcpState=kLinkStateUntested;
    m_udpState=kLinkStateUntested;
    RequestLinkCheck();
}

MediaNetLink::~MediaNetLink()
{
}

void
MediaNetLink::TCPConnect(const string& inServer, U32 inPort)
{
    m_client.TCPConnect(inServer, inPort);
    m_targetIsServer=true;
}

void
MediaNetLink::TCPSocketTake(TCPsocket inSocket)
{
    m_client.TCPSocketTake(inSocket);
    m_targetIsServer=false;
}

void
MediaNetLink::UDPConnect(U32 inPort)
{
    m_client.UDPConnect(inPort);
    m_targetIsServer=true;
}

bool
MediaNetLink::LinkIsUp(tLinkState inState)
{
    switch (inState)
    {
        case kLinkStateInvalid:
        case kLinkStateNotMade:
        case kLinkStateDead:
            return false;
            
        case kLinkStateUntested:
        case kLinkStateAwaitingLinkCheck:
        case kLinkStateIdle:
            return true;
    }
    COREASSERT(false);
    return false;
}

void
MediaNetLink::RequestLinkCheck(void)
{


}

void
MediaNetLink::TCPSend(MediaNetData& ioData)
{
    if (!LinkIsUp(m_tcpState))
    {
        // TCPLinkMake();
        COREASSERT(false);
    }
    m_client.TCPSend(ioData);
}

void
MediaNetLink::TCPReceive(MediaNetData& outData)
{
    if (!LinkIsUp(m_tcpState))
    {
        // TCPLinkMake();
        COREASSERT(false);
    }
    m_client.TCPReceive(outData);
}

void
MediaNetLink::UDPSend(MediaNetData& ioData)
{
    if (!LinkIsUp(m_udpState))
    {
        // UDPLinkMake();
        COREASSERT(false);
    }
    m_client.UDPSend(ioData);
}

void
MediaNetLink::UDPReceive(MediaNetData& outData)
{
    if (!LinkIsUp(m_udpState))
    {
        // UDPLinkMake();
        COREASSERT(false);
    }
    m_client.UDPReceive(outData);
}

void
MediaNetLink::Print(ostream& ioOut) const
{
    ioOut << "tcpState=" << m_tcpState << ", udpState=" << m_udpState << ", targetIsServer=" << m_targetIsServer;
    
    ioOut << ", client=[" << m_client << "]";
}
