/*
 * $Id$
 * $Log$
 */

#include "MediaNetServer.h"

#include "MediaNet.h"
#include "MediaNetLink.h"

MediaNetServer::MediaNetServer(U32 inPort) :
    m_linkCtr(0)
{
    MediaNet::Instance();
    
    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, NULL, inPort) == -1)
    {
        ostringstream message;
        message << "Server creation failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }

    m_serverSocket=SDLNet_TCP_Open(&ip);

    if (m_serverSocket == NULL)
    {
        ostringstream message;
        message << "Server creation failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }
}

MediaNetServer::~MediaNetServer()
{
    SDLNet_TCP_Close(m_serverSocket);
}

void
MediaNetServer::Accept(void)
{
    TCPsocket newSocket=SDLNet_TCP_Accept(m_serverSocket);
    if (newSocket != NULL)
    {
        ostringstream name;
        name << "newlink" << m_linkCtr;
        CoreData<MediaNetLink>::Instance().DataGive(name.str(), new MediaNetLink(newSocket));
        m_linkCtr++;
    }
}
        