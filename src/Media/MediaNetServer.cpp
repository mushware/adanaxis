/*
 * $Id: MediaNetServer.cpp,v 1.19 2002/11/27 20:17:28 southa Exp $
 * $Log: MediaNetServer.cpp,v $
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

#include "MediaNetServer.h"

#include "MediaNet.h"
#include "MediaNetData.h"
#include "MediaNetLink.h"
#include "MediaNetLog.h"

#include "mushPlatform.h"

auto_ptr<MediaNetServer> MediaNetServer::m_instance;

MediaNetServer::MediaNetServer() :
    m_linkCtr(0),
    m_serving(false)
{
}

void
MediaNetServer::Connect(U32 inPort)
{
    if (m_serving)
    {
        Disconnect();
    }

    MediaNet::Instance();

    IPaddress ip;

    for (U32 portNum=inPort; ; ++portNum)
    {
        try
        {

            if (SDLNet_ResolveHost(&ip, NULL, portNum) == -1)
            {
                ostringstream message;
                message << "Resolution for server creation failed: " << SDLNet_GetError();
                throw(NetworkFail(message.str()));
            }
            m_tcpSocket=SDLNet_TCP_Open(&ip);
    
            if (m_tcpSocket == NULL)
            {
                ostringstream message;
                message << "Server socket creation failed: " << SDLNet_GetError();
                throw(NetworkFail(message.str()));
            }
    
            m_udpSocket = SDLNet_UDP_Open(portNum);

            if (m_udpSocket == 0)
            {
                SDLNet_TCP_Close(m_tcpSocket);
                throw(NetworkFail(string("UDP socket open failed: ")+SDLNet_GetError()));
            }

            PlatformNet::SocketNonBlockingSet(m_udpSocket->channel);
            m_serverPortHostOrder=portNum;
            break;
        }
    
        catch (exception& e)
        {
            static U32 errCtr=0;
            
            if (++errCtr < 100)
            {
                MediaNetLog::Instance().NetLog() << "Server creation failed on port " << inPort << ": " << e.what() << endl;
            }
            if (portNum > inPort+7) throw;
        }
    }
    COREASSERT(m_tcpSocket != NULL);
    COREASSERT(m_udpSocket != NULL);
    
    MediaNetLog::Instance().NetLog() << "Created server on port " << m_serverPortHostOrder << endl;
    m_serving=true;
}

void
MediaNetServer::Disconnect(void)
{
    if (m_serving)
    {
        COREASSERT(m_tcpSocket != NULL);
        COREASSERT(m_udpSocket != NULL);
        SDLNet_TCP_Close(m_tcpSocket);
        SDLNet_UDP_Close(m_udpSocket);
        m_tcpSocket=NULL;
        m_udpSocket=NULL;
    }
    m_serving=false;
    MediaNetLog::Instance().NetLog() << "Closed server" << endl;
}

MediaNetServer::~MediaNetServer()
{
    if (m_serving)
    {
        COREASSERT(m_tcpSocket != NULL);
        COREASSERT(m_udpSocket != NULL);
        SDLNet_TCP_Close(m_tcpSocket);
        SDLNet_UDP_Close(m_udpSocket);
    }    
}

void
MediaNetServer::Accept(void)
{
    if (m_serving)
    {
        TCPsocket newSocket=SDLNet_TCP_Accept(m_tcpSocket);
        if (newSocket != NULL)
        {
            ostringstream name;
            name << "server" << m_linkCtr;
            CoreData<MediaNetLink>::Instance().Give(name.str(), new MediaNetLink(newSocket, m_serverPortHostOrder));
            m_linkCtr++;
    
            MediaNetLog::Instance().NetLog() << "Accepted connection for " << name.str() << endl;
        }
    }
}

void
MediaNetServer::UDPSend(U32 inHost, U32 inPort, MediaNetData& ioData)
{
    if (ioData.ReadSizeGet() == 0)
    {
        throw(LogicFail("Attempt to send empty MediaNetData"));
    }
    if (!m_serving)
    {
        throw(NetworkFail("Attempt to send on unconnected server"));
    }
    if (inHost == 0 || inPort == 0)
    {
        MediaNetLog::Instance().NetLog() << "UDPSend to bad address (" << MediaNetUtils::IPAddressToLogString(inHost) << ":" << PlatformNet::NetworkToHostOrderU16(inPort) << ")" << endl;
    }
    
    COREASSERT(m_udpSocket != NULL);

    U32 dataSize=ioData.ReadSizeGet();

    PlatformNet::UDPSend(inHost, inPort, m_udpSocket->channel, ioData.ReadPtrGet(), dataSize);
    ioData.ReadPosAdd(dataSize);
    MediaNetLog::Instance().VerboseLog() << "UDPSend (server) to " << MediaNetUtils::IPAddressToLogString(inHost) << ":" << PlatformNet::NetworkToHostOrderU16(inPort) << ": " << ioData << endl;
}

void
MediaNetServer::UDPReceive(MediaNetData& outData)
{
    if (m_serving)
    {
        U32 netHost; // Network order
        U32 netPort; // Network order
        outData.PrepareForWrite();
        U32 dataSize=PlatformNet::UDPReceive(netHost, netPort, m_udpSocket->channel, outData.WritePtrGet(), outData.WriteSizeGet());
        if (dataSize != 0)
        {
            outData.WritePosAdd(dataSize);
            outData.SourceSet(netHost, netPort);
            MediaNetLog::Instance().VerboseLog() << "UDPReceive (server) from " << MediaNetUtils::IPAddressToLogString(netHost) << ":" << PlatformNet::NetworkToHostOrderU16(netPort) << ": " << outData << endl;
        }
    }
}
