/*
 * $Id: MediaNetServer.cpp,v 1.4 2002/11/01 16:15:28 southa Exp $
 * $Log: MediaNetServer.cpp,v $
 * Revision 1.4  2002/11/01 16:15:28  southa
 * Network send and receive
 *
 * Revision 1.3  2002/10/31 19:55:54  southa
 * Network links
 *
 */

#include "MediaNetServer.h"

#include "MediaNet.h"
#include "MediaNetLink.h"

MediaNetServer::MediaNetServer(U32 inPort) :
    m_linkCtr(0)
{
    m_serverPort=inPort;
        
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
        name << "link" << m_linkCtr;
        CoreData<MediaNetLink>::Instance().DataGive(name.str(), new MediaNetLink(newSocket, m_serverPort));
        m_linkCtr++;
    }
}
