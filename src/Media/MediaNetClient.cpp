/*
 * $Id: MediaNetClient.cpp,v 1.5 2002/11/01 18:46:25 southa Exp $
 * $Log: MediaNetClient.cpp,v $
 * Revision 1.5  2002/11/01 18:46:25  southa
 * UDP Links
 *
 * Revision 1.4  2002/11/01 16:56:49  southa
 * Fixed platform inclusion
 *
 * Revision 1.3  2002/11/01 16:15:27  southa
 * Network send and receive
 *
 * Revision 1.2  2002/10/31 19:55:54  southa
 * Network links
 *
 * Revision 1.1  2002/10/31 16:41:33  southa
 * Network client
 *
 */

#include "MediaNetClient.h"
#include "MediaNetData.h"

#include "mushPlatform.h"

// Need to peek into socket structure to set nonblocking.  A bit nasty
struct _TCPsocket
{
    int ready;
    int channel;
};

// This one's just for debug printouts
struct _UDPsocket
{
    int ready;
    int channel;
};

MediaNetClient::MediaNetClient() :
    m_tcpConnected(false),
    m_udpConnected(false)
{
}

MediaNetClient::~MediaNetClient()
{
    if (m_tcpConnected)
    {
        TCPDisconnect();
    }
}

void
MediaNetClient::TCPConnect(const string& inServer, U32 inPort)
{
    if (m_tcpConnected)
    {
        TCPDisconnect();
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
    m_tcpConnected=true;
}

void
MediaNetClient::TCPSocketTake(TCPsocket inSocket)
{
    try
    {
        if (m_tcpConnected)
        {
            TCPDisconnect();
        }
        m_tcpSocket = inSocket;
        PlatformNet::SocketNonBlockingSet(m_tcpSocket->channel);
        ResolveTargetName();
        m_tcpConnected=true;
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
MediaNetClient::UDPConnect(U32 inPort)
{
    if (!m_tcpConnected)
    {
        throw(NetworkFail("Cannot connect UDP without TCP"));
    }
    
    if (m_udpConnected)
    {
        UDPDisconnect();
    }
    
    for (m_udpPort=inPort; m_udpPort < inPort+8; ++m_udpPort)
    {
        m_udpSocket = SDLNet_UDP_Open(m_udpPort);
        if (m_udpSocket != 0) break;
    }
    if (m_udpSocket == 0)
    {
        throw(NetworkFail(string("UDP socket open failed: ")+SDLNet_GetError()));
    }
    cout << "Selected local UDP port " << m_udpPort << endl;

    // Since we've replaced SDLNet_UDP_Send we don't use this bound address,
    // but let's bind it anyway
    int result=SDLNet_UDP_Bind(m_udpSocket, -1, &m_remoteIP);

    if (result == -1)
    {
        throw(NetworkFail(string("UDP socket bind failed: ")+SDLNet_GetError()));
    }

    PlatformNet::SocketNonBlockingSet(m_udpSocket->channel);
    
    m_udpConnected=true;
}


void
MediaNetClient::TCPDisconnect(void)
{
    COREASSERT(m_tcpConnected);
    COREASSERT(m_tcpSocket != NULL);
    SDLNet_TCP_Close(m_tcpSocket);
    m_tcpSocket=NULL;
}

void
MediaNetClient::UDPDisconnect(void)
{
    COREASSERT(m_udpConnected);
    COREASSERT(m_udpSocket != NULL);
    SDLNet_UDP_Unbind(m_udpSocket, 0);
    SDLNet_UDP_Close(m_udpSocket);
    m_udpSocket=NULL;
}

void
MediaNetClient::TCPSend(MediaNetData& ioData)
{
    if (ioData.ReadSizeGet() == 0)
    {
        throw(LogicFail("Attempt to send empty MediaNetData"));
    }
    if (!m_tcpConnected)
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
MediaNetClient::TCPReceive(MediaNetData& outData)
{
    if (!m_tcpConnected)
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
MediaNetClient::UDPSend(MediaNetData& ioData)
{
    if (ioData.ReadSizeGet() == 0)
    {
        throw(LogicFail("Attempt to send empty MediaNetData"));
    }
    if (!m_udpConnected)
    {
        throw(NetworkFail("UDP send on closed socket"));
    }
    COREASSERT(m_udpSocket != NULL);

    U32 dataSize=ioData.ReadSizeGet();

    PlatformNet::UDPSend(m_remoteIP.host, m_remoteIP.port, m_udpSocket->channel, ioData.ReadPtrGet(), dataSize);
    ioData.ReadPosAdd(dataSize);
}

void
MediaNetClient::UDPReceive(MediaNetData& outData)
{
    if (!m_udpConnected)
    {
        throw(NetworkFail("UDP receive on closed socket"));
    }
    COREASSERT(m_udpSocket != NULL);

    outData.PrepareForWrite();
    U32 host, port;
    U32 dataSize=PlatformNet::UDPReceive(host, port, m_udpSocket->channel, outData.WritePtrGet(), outData.WriteSizeGet());

    outData.WritePosAdd(dataSize);   
}

void
MediaNetClient::Print(ostream& ioOut) const
{
    ioOut << "tcpSocket=" << m_tcpSocket->channel << ", udpSocket=" << m_udpSocket->channel << ", udpPort=" << m_udpPort;
    ioOut << ", remoteIP=" << m_remoteIP;
    ioOut << ", remoteName=" << m_remoteName << ", tcpConnected=" << m_tcpConnected << ", udpConnected=" << m_udpConnected;
}

