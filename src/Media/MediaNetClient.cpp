/*
 * $Id$
 * $Log$
 */

#include "MediaNetClient.h"

MediaNetClient::MediaNetClient() :
    m_connected(false)
{

}

MediaNetClient::~MediaNetClient()
{
    if (m_connected)
    {
        Disconnect();
    }
}

void
MediaNetClient::Connect(const string& inServer, U32 inPort)
{
    IPaddress ip;

    char buffer[strlen(inServer.c_str())+1];
    strncpy(buffer, inServer.c_str(), strlen(inServer.c_str())+1);
    
    if (SDLNet_ResolveHost(&ip, buffer, inPort) == -1)
    {
        ostringstream message;
        message << "Client connection failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }
    
    m_tcpSocket = SDLNet_TCP_Open(&ip);
    if (m_tcpSocket == 0)
    {
        ostringstream message;
        message << "Client connection failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }
    m_connected=true;
}

void
MediaNetClient::Disconnect(void)
{
    COREASSERT(m_connected);
    COREASSERT(m_tcpSocket != NULL);
    SDLNet_TCP_Close(m_tcpSocket);
    m_tcpSocket=NULL;
}
