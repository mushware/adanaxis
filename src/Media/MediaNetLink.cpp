/*
 * $Id$
 * $Log$
 */

#include "MediaNetLink.h"

auto_ptr< CoreData<MediaNetLink> > CoreData<MediaNetLink>::m_instance;

MediaNetLink::MediaNetLink(const string& inServer, U32 inPort)
{
    Connect(inServer, inPort);
    m_state=kLinkStateUntested;
    RequestLinkCheck();
}

MediaNetLink::MediaNetLink(TCPsocket inSocket)
{
    SocketTake(inSocket);
    m_state=kLinkStateUntested;
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

void
MediaNetLink::RequestLinkCheck(void)
{


}