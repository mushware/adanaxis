/*
 * $Id: MustlClient.cpp,v 1.18 2002/11/23 14:39:05 southa Exp $
 * $Log: MustlClient.cpp,v $
 * Revision 1.18  2002/11/23 14:39:05  southa
 * Store ports in network order
 *
 * Revision 1.17  2002/11/22 18:16:44  southa
 * Network tweaks
 *
 * Revision 1.16  2002/11/22 18:02:43  southa
 * Wait for TCP connection
 *
 * Revision 1.15  2002/11/22 15:33:59  southa
 * More network logging
 *
 * Revision 1.14  2002/11/22 15:00:32  southa
 * Network connection handling
 *
 * Revision 1.13  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.12  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 * Revision 1.11  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.10  2002/11/07 00:53:34  southa
 * localweb work
 *
 * Revision 1.9  2002/11/04 15:50:31  southa
 * Network log
 *
 * Revision 1.8  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.7  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.6  2002/11/02 11:22:51  southa
 * Simplified UDP send and receive
 *
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

#include "MustlClient.h"
#include "MustlData.h"
#include "MustlLog.h"
#include "MustlUtils.h"

#include "mushPlatform.h"

MustlClient::MustlClient() :
    m_tcpSocket(NULL),
    m_udpSocket(NULL),
    m_remoteIP(0),
    m_tcpConnected(false),
    m_udpConnected(false)
{
}

MustlClient::~MustlClient()
{
    TCPDisconnect();
    UDPDisconnect();
}

void
MustlClient::TCPConnect(const string& inServer, U32 inPort)
{
    if (m_tcpConnected)
    {
        TCPDisconnect();
    }

    char buffer[strlen(inServer.c_str())+1];
    strncpy(buffer, inServer.c_str(), strlen(inServer.c_str())+1);

    IPaddress remoteIP;
    if (SDLNet_ResolveHost(&remoteIP, buffer, inPort) == -1)
    {
        ostringstream message;
        message << "Client connection failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }
    
    // m_tcpSocket = SDLNet_TCP_Open(&remoteIP);
    m_tcpSocket = PlatformNet::TCPConnectNonBlocking(&remoteIP);
    if (m_tcpSocket == 0)
    {
        ostringstream message;
        message << "Client connection failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }
    PlatformNet::SocketNonBlockingSet(m_tcpSocket->channel);

    // These are set again if ResolveTargetName is successful
    m_remoteIP = remoteIP.host;
    m_tcpRemotePort = remoteIP.port;

    ResolveTargetName();
    m_tcpConnected=true;
}

void
MustlClient::TCPSocketTake(TCPsocket inSocket)
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
MustlClient::ResolveTargetName(void)
{
    IPaddress *remoteIP;
    
    remoteIP = SDLNet_TCP_GetPeerAddress(m_tcpSocket);
    if (remoteIP != NULL)
    {
        m_remoteIP = remoteIP->host;
        m_tcpRemotePort = remoteIP->port;
    }
    else
    {
        static U32 errCtr=0;
        if (errCtr++ < 100)
        {
            MustlLog::Instance().NetLog() << "Couldn't get hostname for IP: " << SDLNet_GetError() << endl;
        }
    }
}

void
MustlClient::UDPConnect(U32 inPort)
{
    if (!m_tcpConnected)
    {
        throw(NetworkFail("Cannot connect UDP without TCP"));
    }
    
    if (m_udpConnected)
    {
        UDPDisconnect();
    }
    U32 localPort;
    for (localPort=inPort; localPort < inPort+8; ++localPort)
    {
        m_udpSocket = SDLNet_UDP_Open(localPort);
        if (m_udpSocket != 0) break;
    }
    if (m_udpSocket == 0)
    {
        throw(NetworkFail(string("UDP socket open failed: ")+SDLNet_GetError()));
    }
    if (localPort != inPort)
    {
        MustlLog::Instance().NetLog() << "Selected local UDP port " << localPort << endl;
    }

    m_udpLocalPort = PlatformNet::HostToNetworkOrderU16(localPort);

    PlatformNet::SocketNonBlockingSet(m_udpSocket->channel);
    m_udpRemotePort=0; // We don't know
    m_udpConnected=true;
}

void
MustlClient::UDPRemotePortNetworkOrderSet(U32 inPort)
{
    m_udpRemotePort=inPort;
}

void
MustlClient::TCPDisconnect(void)
{
    if (m_tcpConnected)
    {
        COREASSERT(m_tcpSocket != NULL);
        SDLNet_TCP_Close(m_tcpSocket);
        m_tcpSocket=NULL;
        m_tcpConnected=false;
    }
}

void
MustlClient::UDPDisconnect(void)
{
    if (m_udpConnected)
    {
        COREASSERT(m_udpSocket != NULL);
        SDLNet_UDP_Close(m_udpSocket);
        m_udpSocket=NULL;
        m_udpConnected=false;
    }
}

bool
MustlClient::TCPConnectionCompleted(void)
{
    if (!m_tcpConnected)
    {
        throw(NetworkFail("CommnectionCompleted call on unconnected link"));
    }
    COREASSERT(m_tcpSocket != NULL);
    bool retVal=PlatformNet::TCPSocketConnectionCompleted(m_tcpSocket->channel);
    return retVal;
}

void
MustlClient::TCPSend(MustlData& ioData)
{
    if (ioData.ReadSizeGet() == 0)
    {
        throw(LogicFail("Attempt to send empty MustlData"));
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
MustlClient::TCPReceive(MustlData& outData)
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
            outData.SourceSet(m_remoteIP, m_tcpRemotePort);
        }
    }
}

void
MustlClient::UDPSend(MustlData& ioData)
{
    if (ioData.ReadSizeGet() == 0)
    {
        throw(LogicFail("Attempt to send empty MustlData"));
    }
    if (!m_udpConnected)
    {
        throw(NetworkFail("UDP send on closed socket"));
    }
    COREASSERT(m_udpSocket != NULL);

    U32 dataSize=ioData.ReadSizeGet();

    PlatformNet::UDPSend(m_remoteIP, m_udpRemotePort, m_udpSocket->channel, ioData.ReadPtrGet(), dataSize);
    ioData.ReadPosAdd(dataSize);

    MustlLog::Instance().VerboseLog() << "UDPSend to " << MustlUtils::IPAddressToLogString(m_remoteIP) << ":" << PlatformNet:: NetworkToHostOrderU16(m_udpRemotePort) << ": " << ioData << endl;
}

void
MustlClient::UDPReceive(MustlData& outData)
{
    if (!m_udpConnected)
    {
        throw(NetworkFail("UDP receive on closed socket"));
    }
    COREASSERT(m_udpSocket != NULL);

    outData.PrepareForWrite();
    U32 netHost, netPort;
    U32 dataSize=PlatformNet::UDPReceive(netHost, netPort, m_udpSocket->channel, outData.WritePtrGet(), outData.WriteSizeGet());

    if (dataSize != 0)
    {
        outData.WritePosAdd(dataSize);
        outData.SourceSet(netHost, netPort);
MustlLog::Instance().VerboseLog() << "UDPReceive from " << MustlUtils::IPAddressToLogString(netHost) << ":" << PlatformNet:: NetworkToHostOrderU16(netPort) << ": " << outData << endl;
    }
}

void
MustlClient::Print(ostream& ioOut) const
{
    ioOut << "[tcpSocket=";
    if (m_tcpSocket == NULL)
    {
        ioOut << "NULL";
    }
    else
    {
        ioOut << m_tcpSocket->channel;
    }
    ioOut << ", udpSocket=";
    if (m_udpSocket == NULL)
    {
        ioOut << "NULL";
    }
    else
    {
        ioOut << m_udpSocket->channel;
    }
    ioOut << ", udpLocalPort=" << PlatformNet:: NetworkToHostOrderU16(m_udpLocalPort);
    ioOut << ", remoteIP=" << MustlUtils::IPAddressToLogString(m_remoteIP) << ", tcpRemotePort=" << PlatformNet:: NetworkToHostOrderU16(m_tcpRemotePort) << ", udpRemotePort=" << PlatformNet:: NetworkToHostOrderU16(m_udpRemotePort);
    ioOut << ", tcpConnected=" << m_tcpConnected << ", udpConnected=" << m_udpConnected << "]";
}

