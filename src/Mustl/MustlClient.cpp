/*
 * $Id: MustlClient.cpp,v 1.2 2002/12/12 18:38:24 southa Exp $
 * $Log: MustlClient.cpp,v $
 * Revision 1.2  2002/12/12 18:38:24  southa
 * Mustl separation
 *
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

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlNamespace.h"

MustlClient::MustlClient() :
    m_tcpSocket(NULL),
    m_udpSocket(NULL),
    m_remoteAddress(0,0),
    m_tcpConnected(false),
    m_udpConnected(false),
    m_logTraffic(false)
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

    MustlAddress hostAddress;
    hostAddress.ResolveFrom(inServer, inPort);

    m_tcpSocket = MustlPlatform::TCPConnectNonBlocking(hostAddress);

    MustlPlatform::SocketNonBlockingSet(m_tcpSocket);

    // These are set again if ResolveTargetName is successful
    m_remoteAddress = hostAddress;
    m_tcpRemotePort = hostAddress.PortGetNetworkOrder();

    m_tcpConnected=true;
}

void
MustlClient::TCPSocketTake(tSocket inSocket, const MustlAddress& inAddress)
{
    try
    {
        if (m_tcpConnected)
        {
            TCPDisconnect();
        }
        m_tcpSocket = inSocket;
        MustlPlatform::SocketNonBlockingSet(m_tcpSocket);
        m_remoteAddress = inAddress;
        m_tcpRemotePort = inAddress.PortGetNetworkOrder();
        m_tcpConnected=true;
    }
    catch (...)
    {
        MustlPlatform::SocketClose(inSocket);
        throw;
    }
}

void
MustlClient::UDPConnect(U32 inPort)
{
    if (!m_tcpConnected)
    {
        throw(MustlFail("Cannot connect UDP without TCP"));
    }
    
    if (m_udpConnected)
    {
        UDPDisconnect();
    }
    U32 localPort;
    for (localPort=inPort; ; ++localPort)
    {
        try
        {
            m_udpSocket = MustlPlatform::UDPBindNonBlocking(localPort);
            break;
        }
        catch (MustlFail& e)
        {
            if (localPort > inPort+8)
            {
                throw;
            }
            // else try again
        }
    }

    if (localPort != inPort)
    {
        MustlLog::Instance().NetLog() << "Selected local UDP port " << localPort << endl;
    }

    m_udpLocalPort = MustlPlatform::HostToNetworkOrderU16(localPort);

    MustlPlatform::SocketNonBlockingSet(m_udpSocket);
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
        MUSTLASSERT(m_tcpSocket != NULL);
        MustlPlatform::SocketClose(m_tcpSocket);
        m_tcpSocket=NULL;
        m_tcpConnected=false;
    }
}

void
MustlClient::UDPDisconnect(void)
{
    if (m_udpConnected)
    {
        MUSTLASSERT(m_udpSocket != NULL);
        MustlPlatform::SocketClose(m_udpSocket);
        m_udpSocket=NULL;
        m_udpConnected=false;
    }
}

bool
MustlClient::TCPConnectionCompleted(void)
{
    if (!m_tcpConnected)
    {
        throw(MustlFail("CommnectionCompleted call on unconnected link"));
    }
    MUSTLASSERT(m_tcpSocket != NULL);
    bool retVal=MustlPlatform::TCPSocketConnectionCompleted(m_tcpSocket);
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
        throw(MustlFail("TCP send on closed socket"));
    }
    MUSTLASSERT(m_tcpSocket != NULL);
    
    errno=0;
    U32 sentSize = ioData.ReadSizeGet();

    MustlPlatform::TCPSend(m_tcpSocket, ioData.ReadPtrGet(), sentSize);

    ioData.ReadPosAdd(sentSize);
}

void
MustlClient::TCPReceive(MustlData& outData)
{
    if (!m_tcpConnected)
    {
        throw(MustlFail("TCP receive on closed socket"));
    }
    MUSTLASSERT(m_tcpSocket != NULL);

    for (U32 i=0; i<256; ++i)
    {
        outData.PrepareForWrite();
        errno=0;
        int receiveSize = MustlPlatform::TCPReceive(m_tcpSocket, outData.WritePtrGet(), outData.WriteSizeGet());

        if (receiveSize == 0)
        {
            break;
        }
        else
        {
            outData.WritePosAdd(receiveSize);
            outData.SourceSet(m_remoteAddress.HostGetNetworkOrder(), m_tcpRemotePort);
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
        throw(MustlFail("UDP send on closed socket"));
    }
    MUSTLASSERT(m_udpSocket != NULL);

    U32 dataSize=ioData.ReadSizeGet();

    MustlPlatform::UDPSend(m_remoteAddress.HostGetNetworkOrder(), m_udpRemotePort, m_udpSocket, ioData.ReadPtrGet(), dataSize);
    ioData.ReadPosAdd(dataSize);

    if (m_logTraffic)
    {
    MustlLog::Instance().VerboseLog() << "UDPSend to " << MustlUtils::IPAddressToLogString(m_remoteAddress.HostGetNetworkOrder()) << ":" << MustlPlatform:: NetworkToHostOrderU16(m_udpRemotePort) << ": " << ioData << endl;
    }
}

void
MustlClient::UDPReceive(MustlData& outData)
{
    if (!m_udpConnected)
    {
        throw(MustlFail("UDP receive on closed socket"));
    }
    MUSTLASSERT(m_udpSocket != NULL);

    outData.PrepareForWrite();
    U32 netHost, netPort;
    U32 dataSize=MustlPlatform::UDPReceive(netHost, netPort, m_udpSocket, outData.WritePtrGet(), outData.WriteSizeGet());

    if (dataSize != 0)
    {
        outData.WritePosAdd(dataSize);
        outData.SourceSet(netHost, netPort);
        if (m_logTraffic)
        {

            MustlLog::Instance().VerboseLog() << "UDPReceive from " << MustlUtils::IPAddressToLogString(netHost) << ":" << MustlPlatform:: NetworkToHostOrderU16(netPort) << ": " << outData << endl;
        }
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
        ioOut << m_tcpSocket;
    }
    ioOut << ", udpSocket=";
    if (m_udpSocket == NULL)
    {
        ioOut << "NULL";
    }
    else
    {
        ioOut << m_udpSocket;
    }
    ioOut << ", udpLocalPort=" << MustlPlatform:: NetworkToHostOrderU16(m_udpLocalPort);
    ioOut << ", remoteIP=" << MustlUtils::IPAddressToLogString(m_remoteAddress.HostGetNetworkOrder()) << ", tcpRemotePort=" << MustlPlatform:: NetworkToHostOrderU16(m_tcpRemotePort) << ", udpRemotePort=" << MustlPlatform:: NetworkToHostOrderU16(m_udpRemotePort);
    ioOut << ", tcpConnected=" << m_tcpConnected << ", udpConnected=" << m_udpConnected << "]";
}

