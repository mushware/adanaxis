/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MustlServer.cpp,v 1.17 2003/01/20 10:45:31 southa Exp $
 * $Log: MustlServer.cpp,v $
 * Revision 1.17  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.16  2003/01/17 00:41:05  southa
 * Configuration updates from POST data
 *
 * Revision 1.15  2003/01/16 12:03:55  southa
 * Platform and invalid socket fixes
 *
 * Revision 1.14  2003/01/13 16:50:48  southa
 * win32 support
 *
 * Revision 1.13  2003/01/13 15:01:20  southa
 * Fix Mustl command line build
 *
 * Revision 1.12  2003/01/11 17:58:15  southa
 * Mustl fixes
 *
 * Revision 1.11  2003/01/09 14:57:08  southa
 * Created Mushcore
 *
 * Revision 1.10  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.9  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.8  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/12/17 12:53:34  southa
 * Mustl library
 *
 * Revision 1.6  2002/12/17 00:58:28  southa
 * Added support for libmustl target
 *
 * Revision 1.5  2002/12/14 15:04:34  southa
 * Mustl fixes
 *
 * Revision 1.4  2002/12/13 19:03:06  southa
 * Mustl interface cleanup
 *
 * Revision 1.3  2002/12/13 01:06:54  southa
 * Mustl work
 *
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

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;
//using Mushware::MushcoreData;

MUSHCORE_SINGLETON_INSTANCE(MustlServer);

MustlServer::MustlServer() :
    m_linkCtr(0),
    m_serving(false)
{
}

MustlServer::~MustlServer()
{
    if (m_serving)
    {
        MUSTLASSERT(m_tcpSocket != MustlPlatform::InvalidSocketValueGet());
        MUSTLASSERT(m_udpSocket != MustlPlatform::InvalidSocketValueGet());
        MustlPlatform::SocketClose(m_tcpSocket);
        MustlPlatform::SocketClose(m_udpSocket);
    }
}

void
MustlServer::Connect(void)
{
    U32 portNum = MustlConfig::Sgl().Get("mustlnetport").U32Get();
    Connect(portNum);
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
            MustlPlatform::ResolveHostName(netAddress, "", portNum);

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
                MustlLog::Sgl().NetLog() << "Server creation failed on port " << inPort << ": " << e.what() << endl;
            }
            if (portNum > inPort+7) throw;
        }
    }
    MUSTLASSERT(m_tcpSocket != MustlPlatform::InvalidSocketValueGet());
    MUSTLASSERT(m_udpSocket != MustlPlatform::InvalidSocketValueGet());
    
    MustlLog::Sgl().NetLog() << "Created server on port " << m_serverPortHostOrder << endl;
    m_serving=true;
}

void
MustlServer::Disconnect(void)
{
    if (m_serving)
    {
        MUSTLASSERT(m_tcpSocket != MustlPlatform::InvalidSocketValueGet());
        MUSTLASSERT(m_udpSocket != MustlPlatform::InvalidSocketValueGet());
        MustlPlatform::SocketClose(m_tcpSocket);
        MustlPlatform::SocketClose(m_udpSocket);
        m_tcpSocket = MustlPlatform::InvalidSocketValueGet();
        m_udpSocket = MustlPlatform::InvalidSocketValueGet();
    }
    m_serving=false;
    MustlLog::Sgl().NetLog() << "Closed server" << endl;
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
            MushcoreData<MustlLink>::Sgl().Give(name.str(), new MustlLink(newSocket, remoteAddress));
            m_linkCtr++;
    
            MustlLog::Sgl().NetLog() << "Accepted connection for " << name.str() << endl;
        }
    }
}

void
MustlServer::UDPSend(const MustlAddress& inAddress, MustlData& ioData)
{
    if (ioData.ReadSizeGet() == 0)
    {
        throw(MustlFail("Attempt to send empty MustlData"));
    }
    if (!m_serving)
    {
        throw(MustlFail("Attempt to send on unconnected server"));
    }
    if (inAddress.HostGetNetworkOrder() == 0 || inAddress.PortGetNetworkOrder() == 0)
    {
        MustlLog::Sgl().NetLog() << "UDPSend (server) to bad address (" << inAddress << ")" << endl;
    }
    
    MUSTLASSERT(m_udpSocket != MustlPlatform::InvalidSocketValueGet());

    U32 dataSize = MustlPlatform::UDPSend(inAddress, m_udpSocket, ioData.ReadPtrGet(), ioData.ReadSizeGet());
    ioData.ReadPosAdd(dataSize);

    if (MustlLog::Sgl().TrafficLogGet())
    {
        MustlLog::Sgl().TrafficLog() << "UDPSend (server) to " << inAddress << ": " << ioData << endl;
    }
}

void
MustlServer::UDPReceive(MustlData& ioData)
{
    if (m_serving)
    {
        MustlAddress sourceAddress;
        // Need to set max packet size in PrepareForWrite
        ioData.PrepareForWrite();
        U32 dataSize=MustlPlatform::UDPReceive(sourceAddress, m_udpSocket, ioData.WritePtrGet(), ioData.WriteSizeGet());
        if (dataSize != 0)
        {
            ioData.WritePosAdd(dataSize);
            ioData.SourceSet(sourceAddress);
            if (MustlLog::Sgl().TrafficLogGet())
            {
                MustlLog::Sgl().TrafficLog() << "UDPReceive (server) received " << ioData << endl;
            }
        }
    }
}
