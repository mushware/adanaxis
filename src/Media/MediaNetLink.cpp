/*
 * $Id: MediaNetLink.cpp,v 1.1 2002/10/31 19:55:54 southa Exp $
 * $Log: MediaNetLink.cpp,v $
 * Revision 1.1  2002/10/31 19:55:54  southa
 * Network links
 *
 */

#include "MediaNetLink.h"

#include "MediaNetData.h"

auto_ptr< CoreData<MediaNetLink> > CoreData<MediaNetLink>::m_instance;

MediaNetLink::MediaNetLink(const string& inServer, U32 inPort)
{
    Connect(inServer, inPort);
    m_tcpState=kLinkStateUntested;
    m_udpState=kLinkStateNotMade;
    RequestLinkCheck();
}

MediaNetLink::MediaNetLink(TCPsocket inSocket)
{
    SocketTake(inSocket);
    m_tcpState=kLinkStateUntested;
    m_udpState=kLinkStateNotMade;
    RequestLinkCheck();
}

MediaNetLink::~MediaNetLink()
{
}

void
MediaNetLink::Connect(const string& inServer, U32 inPort)
{
    m_client.Connect(inServer, inPort);
    m_targetIsServer=true;
}

void
MediaNetLink::SocketTake(TCPsocket inSocket)
{
    m_client.SocketTake(inSocket);
    m_targetIsServer=false;
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
MediaNetLink::SendTCP(MediaNetData& ioData)
{
    if (!LinkIsUp(m_tcpState))
    {
        // TCPLinkMake();
        COREASSERT(false);
    }
    m_client.SendTCP(ioData);
}

void
MediaNetLink::ReceiveTCP(MediaNetData& outData)
{
    if (!LinkIsUp(m_tcpState))
    {
        // TCPLinkMake();
        COREASSERT(false);
    }
    m_client.ReceiveTCP(outData);
}

void
MediaNetLink::Print(ostream& ioOut) const
{
    ioOut << "tcpState=" << m_tcpState << ", udpState=" << m_udpState << ", targetIsServer=" << m_targetIsServer;
    
    ioOut << ", client=[" << m_client << "]";
}
