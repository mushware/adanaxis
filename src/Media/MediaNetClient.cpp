/*
 * $Id: MediaNetClient.cpp,v 1.1 2002/10/31 16:41:33 southa Exp $
 * $Log: MediaNetClient.cpp,v $
 * Revision 1.1  2002/10/31 16:41:33  southa
 * Network client
 *
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
    if (m_connected)
    {
        Disconnect();
    }

    char buffer[strlen(inServer.c_str())+1];
    strncpy(buffer, inServer.c_str(), strlen(inServer.c_str())+1);
    
    if (SDLNet_ResolveHost(&m_remoteIP, buffer, inPort) == -1)
    {
        ostringstream message;
        message << "Client connection failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }
    
    m_tcpSocket = SDLNet_TCP_Open(&m_remoteIP);
    if (m_tcpSocket == 0)
    {
        ostringstream message;
        message << "Client connection failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }
    m_connected=true;
}

void
MediaNetClient::SocketTake(TCPsocket inSocket)
{
    if (m_connected)
    {
        Disconnect();
    }

    IPaddress *remoteIP;
    
    remoteIP = SDLNet_TCP_GetPeerAddress(inSocket);
    if (remoteIP != NULL)
    {
        m_remoteIP = *remoteIP;
        m_tcpSocket=inSocket;

        char *remoteName=SDLNet_ResolveIP(remoteIP);
        if (remoteName != NULL)
        {
            m_remoteName=remoteName;
        }
        else
        {
            m_remoteName="unknown";
        }
        m_connected=true;
    }
    else
    {
        static U32 errCtr=0;
        if (errCtr++ < 100)
        {
            cerr << "Couldn't get IP for connection attempt: " << SDLNet_GetError() << endl;
        }
        SDLNet_TCP_Close(inSocket);
    }
}

void
MediaNetClient::Disconnect(void)
{
    COREASSERT(m_connected);
    COREASSERT(m_tcpSocket != NULL);
    SDLNet_TCP_Close(m_tcpSocket);
    m_tcpSocket=NULL;
}
