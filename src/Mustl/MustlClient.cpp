/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlClient.cpp,v 1.9 2003/01/13 16:50:48 southa Exp $
 * $Log: MustlClient.cpp,v $
 * Revision 1.9  2003/01/13 16:50:48  southa
 * win32 support
 *
 * Revision 1.8  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.7  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/12/15 00:26:20  southa
 * Send, receive and timer work
 *
 * Revision 1.5  2002/12/14 15:04:33  southa
 * Mustl fixes
 *
 * Revision 1.4  2002/12/13 19:03:05  southa
 * Mustl interface cleanup
 *
 * Revision 1.3  2002/12/13 01:06:52  southa
 * Mustl work
 *
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

using namespace Mustl;
using namespace std;

MustlClient::MustlClient() :
    m_tcpSocket(0),
    m_udpSocket(0),
    m_tcpAddress(0,0),
    m_udpAddress(0,0),
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
MustlClient::TCPConnect(const MustlAddress& inAddress)
{
    if (m_tcpConnected)
    {
        TCPDisconnect();
    }

    m_tcpSocket = MustlPlatform::TCPConnectNonBlocking(inAddress);

    m_tcpAddress = inAddress;
    
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
        m_tcpAddress = inAddress;
        m_tcpConnected = true;
    }
    catch (...)
    {
        MustlPlatform::SocketClose(inSocket);
        throw;
    }
}

void
MustlClient::UDPConnect(const MustlAddress& inAddress)
{
    // Caveat:  The incoming address is the remote IP address but the local port number
    if (m_udpConnected)
    {
        UDPDisconnect();
    }

    // The client chooses a UDP port to bind locally
    
    U32 localPort=inAddress.PortGetHostOrder(); // Should be configurable
    U32 failCtr=0;
    do
    {
        try
        {
            m_udpSocket = MustlPlatform::UDPBindNonBlocking(localPort);
            break;
        }
        catch (MushcoreNonFatalFail& e)
        {
            ++localPort;
            if (++failCtr > 8) // Should be configurable
            {
                throw;
            }
        }
    } while(1);

    if (failCtr > 0)
    {
        MustlLog::Instance().NetLog() << "Selected local UDP port " << localPort << endl;
    }

    m_udpAddress = inAddress;
    m_udpConnected=true;
}

void
MustlClient::UDPRemotePortSetHostOrder(U32 inPortHostOrder)
{
    m_udpAddress.PortSetHostOrder(inPortHostOrder);
}

void
MustlClient::TCPDisconnect(void)
{
    if (m_tcpConnected)
    {
        MustlPlatform::SocketClose(m_tcpSocket);
        m_tcpSocket=0;
        m_tcpConnected=false;
    }
}

void
MustlClient::UDPDisconnect(void)
{
    if (m_udpConnected)
    {
        MustlPlatform::SocketClose(m_udpSocket);
        m_udpSocket=0;
        m_udpConnected=false;
    }
}

bool
MustlClient::TCPConnectionCompletedHas(void)
{
    if (!m_tcpConnected)
    {
        throw(MustlFail("TCPConnectionCompletedHas call on unconnected link"));
    }
    return MustlPlatform::TCPSocketConnectionCompleted(m_tcpSocket);
}

void
MustlClient::TCPSend(MustlData& ioData)
{
    if (!m_tcpConnected)
    {
        throw(MustlFail("TCP send on closed socket"));
    }
    
    U32 sentSize = MustlPlatform::TCPSend(m_tcpSocket, ioData.ReadPtrGet(), ioData.ReadSizeGet());

    ioData.ReadPosAdd(sentSize);
    
    if (MustlLog::Instance().TrafficLogGet())
    {
        MustlLog::Instance().TrafficLog() << "TCPSend to " << m_tcpAddress << ": " << ioData << endl;
    }
}

void
MustlClient::TCPReceive(MustlData& outData)
{
    if (!m_tcpConnected)
    {
        throw(MustlFail("TCP receive on closed socket"));
    }
    MUSTLASSERT(m_tcpSocket != 0);

    outData.PrepareForWrite(kEthernetMTU);
    U32 receiveSize = MustlPlatform::TCPReceive(m_tcpSocket, outData.WritePtrGet(), outData.WriteSizeGet());

    if (receiveSize == 0) return;

    do
    {
        outData.WritePosAdd(receiveSize);
        outData.PrepareForWrite();
        receiveSize = MustlPlatform::TCPReceive(m_tcpSocket, outData.WritePtrGet(), outData.WriteSizeGet());
    } while (receiveSize != 0);
    
    outData.SourceSet(m_tcpAddress);
    
    if (MustlLog::Instance().TrafficLogGet())
    {
        MustlLog::Instance().TrafficLog() << "TCPReceive from " << m_tcpAddress << ": " << outData << endl;
    }
}

void
MustlClient::UDPSend(MustlData& ioData)
{
    if (!m_udpConnected)
    {
        throw(MustlFail("UDP send on closed socket"));
    }
    MUSTLASSERT(m_udpSocket != 0);

    U32 receiveSize, sentSize;
    
    do
    {
        receiveSize = ioData.ReadSizeGet();
        sentSize = MustlPlatform::UDPSend(m_udpAddress, m_udpSocket, ioData.ReadPtrGet(), receiveSize);
        
        ioData.ReadPosAdd(sentSize);
        
    } while (sentSize > 0 && sentSize != receiveSize);
    
    if (MustlLog::Instance().TrafficLogGet())
    {
        MustlLog::Instance().TrafficLog() << "UDPSend to " << m_udpAddress << ": " << ioData << endl;
    }
}

void
MustlClient::UDPReceive(MustlData& outData)
{
    if (!m_udpConnected)
    {
        throw(MustlFail("UDP receive on closed socket"));
    }
    MUSTLASSERT(m_udpSocket != 0);

    MustlAddress receiveAddress;
    outData.PrepareForWrite(kEthernetMTU);
    U32 receiveSize = MustlPlatform::UDPReceive(receiveAddress, m_udpSocket, outData.WritePtrGet(), outData.WriteSizeGet());

    // Exit quickly if nothing to receive
    if (receiveSize == 0) return;

    outData.SourceSet(receiveAddress);

    // Multiple reception support.  This is the client end of a link (server ends use
    // the server port) so we expect every reception to come from the same source
    do
    {
        outData.WritePosAdd(receiveSize);
        outData.PrepareForWrite();
        receiveSize = MustlPlatform::UDPReceive(receiveAddress, m_udpSocket, outData.WritePtrGet(), outData.WriteSizeGet());

        if (receiveAddress != outData.SourceGet())
        {
            ostringstream message;
            message << "UDPReceive source address mismatch: " << receiveAddress << " != " << outData.SourceGet();
            throw(MustlFail(message.str()));
        }
    } while (receiveSize != 0);
    
    if (MustlLog::Instance().TrafficLogGet())
    {
        MustlLog::Instance().TrafficLog() << "UDPReceive from " << receiveAddress << ": " << outData << endl;
    }
}

void
MustlClient::Print(ostream& ioOut) const
{
    ioOut << "tcpSocket=" << m_tcpSocket;
    ioOut << ", udpSocket=" << m_udpSocket;
    ioOut << ", tcpAddress=" << m_tcpAddress;
    ioOut << ", udpAddress=" << m_udpAddress;
    ioOut << ", tcpConnected=" << m_tcpConnected;
    ioOut << ", udpConnected=" << m_udpConnected;
}
