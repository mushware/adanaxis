/*
 * $Id: MediaNetClient.cpp,v 1.2 2002/10/31 19:55:54 southa Exp $
 * $Log: MediaNetClient.cpp,v $
 * Revision 1.2  2002/10/31 19:55:54  southa
 * Network links
 *
 * Revision 1.1  2002/10/31 16:41:33  southa
 * Network client
 *
 */

#include "MediaNetClient.h"
#include "MediaNetData.h"

#include "PlatformNet.h"

// Need to peek into socket structure to set nonblocking.  A bit nasty
struct _TCPsocket
{
    int ready;
    int channel;
};

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
    PlatformNet::SocketNonBlockingSet(m_tcpSocket->channel);
    ResolveTargetName();
    m_connected=true;
}

void
MediaNetClient::SocketTake(TCPsocket inSocket)
{
    try
    {
        if (m_connected)
        {
            Disconnect();
        }
        m_tcpSocket = inSocket;
        PlatformNet::SocketNonBlockingSet(m_tcpSocket->channel);
        ResolveTargetName();
        m_connected=true;
    }
    catch (...)
    {
        SDLNet_TCP_Close(inSocket);
        throw;
    }
}

void
MediaNetClient::ResolveTargetName(void)
{
    IPaddress *remoteIP;
    
    remoteIP = SDLNet_TCP_GetPeerAddress(m_tcpSocket);
    if (remoteIP != NULL)
    {
        m_remoteIP = *remoteIP;

        char *remoteName=SDLNet_ResolveIP(remoteIP);
        if (remoteName != NULL)
        {
            m_remoteName=remoteName;
        }
        else
        {
            m_remoteName="unknown";
        }
    }
    else
    {
        static U32 errCtr=0;
        if (errCtr++ < 100)
        {
            cerr << "Couldn't get hostname for IP: " << SDLNet_GetError() << endl;
        }
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

void
MediaNetClient::SendTCP(MediaNetData& ioData)
{
    if (ioData.ReadSizeGet() == 0)
    {
        throw(LogicFail("Attempt to send empty MediaNetData"));
    }
    if (!m_connected)
    {
        throw(NetworkFail("TCP send on closed socket"));
    }
    COREASSERT(m_tcpSocket != NULL);
    
    errno=0;
    int result=SDLNet_TCP_Send(m_tcpSocket, ioData.ReadPtrGet(), ioData.ReadSizeGet());

    if (result <= 0)
    {
        ostringstream message;
        message << "TCP send failed (" << errno << "): " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }
    else
    {
        ioData.ReadPosAdd(result);
    }
}

void
MediaNetClient::ReceiveTCP(MediaNetData& outData)
{
    if (!m_connected)
    {
        throw(NetworkFail("TCP receive on closed socket"));
    }
    COREASSERT(m_tcpSocket != NULL);

    for (U32 i=0; i<256; ++i)
    {
        outData.PrepareForWrite();
        errno=0;
        int result=SDLNet_TCP_Recv(m_tcpSocket, outData.WritePtrGet(), outData.WriteSizeGet());

        if (result <= 0)
        {
            if (errno != 0 && errno != EINTR && errno != EAGAIN)
            {
                ostringstream message;
                message << "TCP receive failed (" << errno << "): " << SDLNet_GetError();
                throw(NetworkFail(message.str()));
            }
            break;
        }
        else
        {
            outData.WritePosAdd(result);
        }
    }
}

void
MediaNetClient::Print(ostream& ioOut) const
{
    ioOut << "tcpSocket=" << m_tcpSocket->channel << ", remoteIP=" << hex << m_remoteIP.host << dec << ":" << m_remoteIP.port;
    ioOut << ", remoteName=" << m_remoteName << ", connected=" << m_connected;
}
