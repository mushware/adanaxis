/*
 * $Id: MustlServer.cpp,v 1.2 2002/12/12 18:38:25 southa Exp $
 * $Log: MustlServer.cpp,v $
 * Revision 1.2  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 * Revision 1.20  2002/12/05 13:20:13  southa
 * Client link handling
 *
 * Revision 1.19  2002/11/27 20:17:28  southa
 * Basic network cleardown
 *
 * Revision 1.18  2002/11/27 17:44:20  southa
 * Network fixes
 *
 * Revision 1.17  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.16  2002/11/22 18:02:43  southa
 * Wait for TCP connection
 *
 * Revision 1.15  2002/11/22 15:33:59  southa
 * More network logging
 *
 * Revision 1.14  2002/11/22 15:00:33  southa
 * Network connection handling
 *
 * Revision 1.13  2002/11/22 11:42:07  southa
 * Added developer controls
 *
 * Revision 1.12  2002/11/21 18:39:42  southa
 * Added m_serving check to Accept
 *
 * Revision 1.11  2002/11/20 22:35:28  southa
 * Multiplayer setup
 *
 * Revision 1.10  2002/11/18 21:02:39  southa
 * Prevent crash on exit
 *
 * Revision 1.9  2002/11/05 18:15:17  southa
 * Web server
 *
 * Revision 1.8  2002/11/04 15:50:32  southa
 * Network log
 *
 * Revision 1.7  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.6  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.5  2002/11/01 18:46:26  southa
 * UDP Links
 *
 * Revision 1.4  2002/11/01 16:15:28  southa
 * Network send and receive
 *
 * Revision 1.3  2002/10/31 19:55:54  southa
 * Network links
 *
 */

#include "MustlServer.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlNamespace.h"

auto_ptr<MustlServer> MustlServer::m_instance;

MustlServer::MustlServer() :
    m_linkCtr(0),
    m_serving(false),
    m_logTraffic(false)
{
}

void
MustlServer::Connect(U32 inPort)
{
    if (m_serving)
    {
        Disconnect();
    }

    MustlAddress netAddress;

    for (U32 portNum=inPort; ; ++portNum)
    {
        try
        {
            MustlPlatform::ResolveAddress(netAddress, "", portNum);

            m_tcpSocket = MustlPlatform::TCPBindNonBlocking(netAddress);
            m_udpSocket = MustlPlatform::UDPBindNonBlocking(portNum);

            m_serverPortHostOrder=portNum;
            break;
        }
    
        catch (exception& e)
        {
            static U32 errCtr=0;
            
            if (++errCtr < 100)
            {
                MustlLog::Instance().NetLog() << "Server creation failed on port " << inPort << ": " << e.what() << endl;
            }
            if (portNum > inPort+7) throw;
        }
    }
    MUSTLASSERT(m_tcpSocket != NULL);
    MUSTLASSERT(m_udpSocket != NULL);
    
    MustlLog::Instance().NetLog() << "Created server on port " << m_serverPortHostOrder << endl;
    m_serving=true;
}

void
MustlServer::Disconnect(void)
{
    if (m_serving)
    {
        MUSTLASSERT(m_tcpSocket != NULL);
        MUSTLASSERT(m_udpSocket != NULL);
        MustlPlatform::SocketClose(m_tcpSocket);
        MustlPlatform::SocketClose(m_udpSocket);
        m_tcpSocket=NULL;
        m_udpSocket=NULL;
    }
    m_serving=false;
    MustlLog::Instance().NetLog() << "Closed server" << endl;
}

MustlServer::~MustlServer()
{
    if (m_serving)
    {
        MUSTLASSERT(m_tcpSocket != NULL);
        MUSTLASSERT(m_udpSocket != NULL);
        MustlPlatform::SocketClose(m_tcpSocket);
        MustlPlatform::SocketClose(m_udpSocket);
    }    
}

void
MustlServer::Accept(void)
{
    if (m_serving)
    {
        MustlAddress remoteAddress;
        tSocket newSocket;
        if (MustlPlatform::Accept(newSocket, remoteAddress, m_tcpSocket))
        {
            ostringstream name;
            name << "server" << m_linkCtr;
            CoreData<MustlLink>::Instance().Give(name.str(), new MustlLink(newSocket, m_serverPortHostOrder, remoteAddress));
            m_linkCtr++;
    
            MustlLog::Instance().NetLog() << "Accepted connection for " << name.str() << endl;
        }
    }
}

void
MustlServer::UDPSend(U32 inHost, U32 inPort, MustlData& ioData)
{
    if (ioData.ReadSizeGet() == 0)
    {
        throw(LogicFail("Attempt to send empty MustlData"));
    }
    if (!m_serving)
    {
        throw(MustlFail("Attempt to send on unconnected server"));
    }
    if (inHost == 0 || inPort == 0)
    {
        MustlLog::Instance().NetLog() << "UDPSend to bad address (" << MustlUtils::IPAddressToLogString(inHost) << ":" << MustlPlatform::NetworkToHostOrderU16(inPort) << ")" << endl;
    }
    
    MUSTLASSERT(m_udpSocket != NULL);

    U32 dataSize=ioData.ReadSizeGet();

    MustlPlatform::UDPSend(inHost, inPort, m_udpSocket, ioData.ReadPtrGet(), dataSize);
    ioData.ReadPosAdd(dataSize);
    if (m_logTraffic)
    {
        MustlLog::Instance().VerboseLog() << "UDPSend (server) to " << MustlUtils::IPAddressToLogString(inHost) << ":" << MustlPlatform::NetworkToHostOrderU16(inPort) << ": " << ioData << endl;
    }
}

void
MustlServer::UDPReceive(MustlData& outData)
{
    if (m_serving)
    {
        U32 netHost; // Network order
        U32 netPort; // Network order
        outData.PrepareForWrite();
        U32 dataSize=MustlPlatform::UDPReceive(netHost, netPort, m_udpSocket, outData.WritePtrGet(), outData.WriteSizeGet());
        if (dataSize != 0)
        {
            outData.WritePosAdd(dataSize);
            outData.SourceSet(netHost, netPort);
            if (m_logTraffic)
            {
                MustlLog::Instance().VerboseLog() << "UDPReceive (server) from " << MustlUtils::IPAddressToLogString(netHost) << ":" << MustlPlatform::NetworkToHostOrderU16(netPort) << ": " << outData << endl;
            }
        }
    }
}
