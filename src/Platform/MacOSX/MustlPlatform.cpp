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
 * $Id: MustlPlatform.cpp,v 1.7 2002/12/29 20:30:57 southa Exp $
 * $Log: MustlPlatform.cpp,v $
 * Revision 1.7  2002/12/29 20:30:57  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.6  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/12/17 00:58:29  southa
 * Added support for libmustl target
 *
 * Revision 1.4  2002/12/15 00:26:20  southa
 * Send, receive and timer work
 *
 * Revision 1.3  2002/12/13 19:03:06  southa
 * Mustl interface cleanup
 *
 * Revision 1.2  2002/12/13 01:07:26  southa
 * Mustl work
 *
 * Revision 1.1  2002/12/12 18:38:58  southa
 * Mustl separation
 *
 * Revision 1.14  2002/12/03 20:28:18  southa
 * Network, player and control work
 *
 * Revision 1.13  2002/11/28 12:05:46  southa
 * Server name work
 *
 * Revision 1.12  2002/11/24 00:29:08  southa
 * Serve web pages to local addresses only
 *
 * Revision 1.11  2002/11/23 15:23:33  southa
 * Fixed network orders for win32
 *
 * Revision 1.10  2002/11/23 14:39:07  southa
 * Store ports in network order
 *
 * Revision 1.9  2002/11/22 18:02:43  southa
 * Wait for TCP connection
 *
 * Revision 1.8  2002/11/22 15:00:33  southa
 * Network connection handling
 *
 * Revision 1.7  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.6  2002/11/18 21:02:40  southa
 * Prevent crash on exit
 *
 * Revision 1.5  2002/11/04 13:11:58  southa
 * Link setup work
 *
 * Revision 1.4  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.3  2002/11/02 11:22:51  southa
 * Simplified UDP send and receive
 *
 */

/*************************
 *
 *  Mac OS X file
 *
 *************************/

#include "MustlPlatform.h"

#include "MustlAddress.h"
#include "MustlFail.h"
#include "MustlSTL.h"

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <fcntl.h>

#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

using namespace Mustl;
using namespace std;

bool MustlPlatform::m_localAddressesValid=false;
map<U32, bool> MustlPlatform::m_localAddressMap;

void
MustlPlatform::SocketNonBlockingSet(tSocket inSocket)
{
    errno=0;
    int flags = fcntl(inSocket, F_GETFL, 0);
    if (flags < 0) flags = 0;
    if (fcntl(inSocket, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        ostringstream message;
        message << "Failed to set socket non-blocking: " << errno;
        throw(MustlFail(message.str()));
    }
}

void
MustlPlatform::SocketBlockingSet(tSocket inSocket)
{
    errno=0;
    int flags = fcntl(inSocket, F_GETFL, 0);
    if (flags < 0) flags = 0;
    if (fcntl(inSocket, F_SETFL, flags & ~O_NONBLOCK) < 0)
    {
        ostringstream message;
        message << "Failed to set socket blocking: " << errno;
        throw(MustlFail(message.str()));
    }
}

void
MustlPlatform::SocketReuseAddressSet(tSocket inSocket)
{
    int value=1;
    errno=0;
    if (setsockopt(inSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&value), sizeof(value)) != 0)
    {
        ostringstream message;
        message << "Failed to set socket address reuse (" << errno << ")";
        throw(MustlFail(message.str()));
    }
    
}

void
MustlPlatform::SocketTCPNoDelaySet(tSocket inSocket)
{
    int value = 1;
    errno=0;
    if (setsockopt(inSocket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char *>(&value), sizeof(value)) != 0)
    {
        ostringstream message;
        message << "Failed to set socket TCP delay (" << errno << ")";
        throw(MustlFail(message.str()));
    }
}

U32
MustlPlatform::TCPSend(tSocket inSocket, void *inBuffer, U32 inSize)
{
    errno=0;
    int result = send(inSocket, inBuffer, inSize, 0);

    if (result < 0)
    {
        ostringstream message;
        message << "TCP send failed (" << errno << ")";
        throw(MustlFail(message.str()));
    }
    return static_cast<U32>(result);
}

U32
MustlPlatform::TCPReceive(tSocket inSocket, void *outBuffer, U32 inSize)
{
    errno=0;

    int result = recv(inSocket, outBuffer, inSize, 0);

    if (result < 0)
    {
        if (errno == EINTR || errno == EAGAIN)
        {
            result = 0;
        }
        else
        {
            ostringstream message;
            message << "TCP receive failed (" << errno << ")";
            throw(MustlFail(message.str()));
        }
    }
    return static_cast<U32>(result);
}

U32
MustlPlatform::UDPSend(const MustlAddress& inAddress, tSocket inSocket, void *inBuffer, U32 inSize)
{
    struct sockaddr_in sockAddr;
    sockAddr.sin_addr.s_addr = inAddress.HostGetNetworkOrder();
    sockAddr.sin_port = inAddress.PortGetNetworkOrder();
    sockAddr.sin_family = AF_INET;
    
    errno=0;
    int result=sendto(inSocket, inBuffer, inSize, 0, reinterpret_cast<sockaddr *>(&sockAddr), sizeof(sockAddr));

    if (result < 0)
    {
        ostringstream message;
        message << "UDP send to " << inAddress << " failed (" << errno << ")";
        throw(MustlFail(message.str()));
    }
    return static_cast<U32>(result);
}

U32
MustlPlatform::UDPReceive(MustlAddress& outAddress, tSocket inSocket, void *outBuffer, U32 inSize)
{
    struct sockaddr_in sockAddr;
    int sockAddrSize=sizeof(sockAddr);

    errno=0;
    int result = recvfrom(inSocket, outBuffer, inSize, 0, reinterpret_cast<sockaddr *>(&sockAddr), &sockAddrSize);

    outAddress.HostSetNetworkOrder(sockAddr.sin_addr.s_addr);
    outAddress.PortSetNetworkOrder(sockAddr.sin_port);
    
    if (result < 0)
    {
        if (errno == EINTR || errno == EAGAIN)
        {
            result = 0;
        }
        else
        {
            ostringstream message;
            message << "UDP receive failed (" << errno << ")";
            throw(MustlFail(message.str()));
        }
    }
    return static_cast<U32>(result);
}

tSocket
MustlPlatform::TCPUnboundSocketCreate(void)
{
    tSocket sockHandle;
    sockHandle = socket(AF_INET, SOCK_STREAM, 0);
    if (sockHandle == -1)
    {
        throw(MustlFail("Couldn't create TCP socket"));
    }
    return sockHandle;
}

tSocket
MustlPlatform::UDPUnboundSocketCreate(void)
{
    tSocket sockHandle;
    sockHandle = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockHandle == -1)
    {
        throw(MustlFail("Couldn't create UDP socket"));
    }
    return sockHandle;
}

tSocket
MustlPlatform::TCPConnectNonBlocking(const MustlAddress& inAddress)
{
    tSocket sockHandle = TCPUnboundSocketCreate();
    SocketNonBlockingSet(sockHandle);

    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inAddress.HostGetNetworkOrder();
    sockAddr.sin_port = inAddress.PortGetNetworkOrder();

    errno=0;
    if (connect(sockHandle, reinterpret_cast<struct sockaddr *>(&sockAddr), sizeof(sockAddr)) != 0)
    {
        if (errno != EINPROGRESS)
        {
            close(sockHandle);
            ostringstream message;
            message << "Couldn't connect to remote host " << inAddress << " (" << errno << ")";
            throw(MustlFail(message.str()));
        }
    }

    SocketTCPNoDelaySet(sockHandle);
    
    return sockHandle;
}

tSocket
MustlPlatform::TCPBindNonBlocking(const MustlAddress& inAddress)
{
    tSocket sockHandle = TCPUnboundSocketCreate();
    SocketNonBlockingSet(sockHandle);
    SocketReuseAddressSet(sockHandle);

    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inAddress.HostGetNetworkOrder();
    sockAddr.sin_port = inAddress.PortGetNetworkOrder();

    errno=0;
    if (bind(sockHandle, reinterpret_cast<struct sockaddr *>(&sockAddr), sizeof(sockAddr)) != 0)
    {
        close(sockHandle);
        ostringstream message;
        message << "Couldn't bind server address " << inAddress << " (" << errno << ")";
        throw(MustlFail(message.str()));
    }
    
    if (listen(sockHandle, 8) != 0)
    {
        close(sockHandle);
        ostringstream message;
        message << "Couldn't listen on server socket " << inAddress << " (" << errno << ")";
        throw(MustlFail(message.str()));
    }
    return sockHandle;
}

tSocket
MustlPlatform::UDPBindNonBlocking(U32 inPortNetworkOrder)
{
    tSocket sockHandle = UDPUnboundSocketCreate();
    SocketNonBlockingSet(sockHandle);
    SocketReuseAddressSet(sockHandle);    
    
    struct sockaddr_in sockAddr;

    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = 0; // Not used
    sockAddr.sin_port = inPortNetworkOrder;

    errno=0;
    if (bind(sockHandle, reinterpret_cast<struct sockaddr *>(&sockAddr), sizeof(sockAddr)) != 0)
    {
        if (errno != EINPROGRESS)
        {
            close(sockHandle);
            ostringstream message;
            message << "Couldn't bind UDP port " << NetworkToHostOrderU16(inPortNetworkOrder) << " (" << errno << ")";
            throw(MustlFail(message.str()));
        }
    }

    return sockHandle;
}

bool
MustlPlatform::Accept(tSocket& outSocket, MustlAddress& outAddress, tSocket inSocket)
{
    struct sockaddr_in sockAddr;
    int sockAddrLen = sizeof(sockAddr);
    errno=0;
    int newSocket = accept(inSocket, reinterpret_cast<struct sockaddr *>(&sockAddr), &sockAddrLen);

    if (newSocket == -1)
    {
        if (errno == EWOULDBLOCK)
        {
            return false;
        }
        ostringstream message;
        message << "Accept failed (" << errno << ")";
        throw(MustlFail(message.str()));
    }
    outSocket = newSocket;
    outAddress.HostSetNetworkOrder(sockAddr.sin_addr.s_addr);
    outAddress.PortSetNetworkOrder(sockAddr.sin_port);
    return true;
}

void
MustlPlatform::SocketClose(tSocket inSocket)
{
    close(inSocket);
}

bool
MustlPlatform::TCPSocketConnectionCompleted(tSocket inSocket)
{
    struct timeval timeVal;
    timeVal.tv_sec = 0;
    timeVal.tv_usec = 0;
    
    fd_set fdSet;
    FD_ZERO(&fdSet);
    FD_SET(inSocket, &fdSet);

    int result = select(inSocket+1, NULL, &fdSet, NULL, &timeVal);

    if (result < 0) return false;
    
    return (FD_ISSET(inSocket, &fdSet));
}

U32
MustlPlatform::HostToNetworkOrderU16(U32 inVal)
{
    return htons(inVal);
}

U32
MustlPlatform::NetworkToHostOrderU16(U32 inVal)
{
    return ntohs(inVal);
}

U32
MustlPlatform::HostToNetworkOrderU32(U32 inVal)
{
    return htonl(inVal);
}

U32
MustlPlatform::NetworkToHostOrderU32(U32 inVal)
{
    return ntohl(inVal);
}

void
MustlPlatform::LocalAddressesRetrieve(void)
{
    m_localAddressMap.clear();
    
    struct ifconf ifConf;
    U8 ipBuffer[16384];
    ifConf.ifc_buf = reinterpret_cast<char *>(ipBuffer);
    ifConf.ifc_len = sizeof(ipBuffer)-256;
    int testSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (testSocket == -1)
    {
        throw(MustlFail("Socket creation failed"));
    }
    errno=0;
    if (ioctl(testSocket, SIOCGIFCONF, &ifConf) != 0)
    {
        close(testSocket);
        ostringstream message;
        message << "ioctl SIOCGIFCONF fail (" << errno << ")";
        throw(MustlFail(message.str()));
    }
    U8 *dataPtr=ipBuffer;
    
    while (dataPtr < ipBuffer+ifConf.ifc_len)
    {
        struct ifreq *ifReq = reinterpret_cast<struct ifreq *>(dataPtr);

        U32 entryLength=ifReq->ifr_addr.sa_len;
        if (entryLength < sizeof(struct sockaddr)) entryLength=sizeof(struct sockaddr);
        if (ifReq->ifr_addr.sa_family == AF_INET)
        {
            if (ioctl(testSocket, SIOCGIFFLAGS, ifReq) == 0)
            {
                if (ifReq->ifr_flags & IFF_UP)
                {
                    if (ioctl(testSocket, SIOCGIFADDR, ifReq) == 0)
                    {
                        struct in_addr ipAddr = ((struct sockaddr_in *)&(ifReq->ifr_addr))->sin_addr;
                        m_localAddressMap[ipAddr.s_addr]=true;
                    }
                }
            }
        }
        dataPtr += sizeof(ifReq->ifr_name) + entryLength;
    }
    close(testSocket);
    m_localAddressesValid=true;
}

bool
MustlPlatform::IsLocalAddress(U32 inIPNetworkOrder)
{
    if (!m_localAddressesValid)
    {
        LocalAddressesRetrieve();
    }
    return m_localAddressMap.find(inIPNetworkOrder) != m_localAddressMap.end();
}

void
MustlPlatform::ResolveHostName(MustlAddress& outAddress, const string& inHostName, U32 inPortHostOrder)
{
    if (inHostName == "")
    {
        outAddress.HostSetNetworkOrder(INADDR_ANY);
        outAddress.PortSetHostOrder(inPortHostOrder);
    }
    else
    {
        if (ResolveIPAddressString(outAddress, inHostName, inPortHostOrder))
        {
            // Done
        }
        else
        {
            struct hostent *hostEnt;

            hostEnt = gethostbyname(inHostName.c_str());
            if (hostEnt != NULL)
            {
                in_addr_t hostIP;
                memcpy(&hostIP, hostEnt->h_addr_list[0], sizeof(hostIP));
                outAddress.HostSetNetworkOrder(hostIP);
                outAddress.PortSetHostOrder(inPortHostOrder);
            }
            else
            {
                throw(MustlFail("Cannot resolve host name '"+inHostName+"'"));
            }
        }
    }
}

bool
MustlPlatform::ResolveIPAddressString(MustlAddress& outAddress, const string& inIPStr, U32 inPortHostOrder)
{
    
    if (inIPStr == "")
    {
        outAddress.HostSetNetworkOrder(INADDR_ANY);
    }
    else
    {
        in_addr_t hostIP = inet_addr(inIPStr.c_str());
        if (hostIP == INADDR_NONE)
        {
            return false;
        }
        else
        {
            outAddress.HostSetNetworkOrder(hostIP);
        }
    }
    outAddress.PortSetHostOrder(inPortHostOrder);
    return true;
}

unsigned int
MustlPlatform::DefaultTimer(void)
{
    static struct timeval firstTime;
    static bool firstTimeValid=false;
    struct timeval currentTime;
    
    if (gettimeofday(&currentTime, NULL) != 0)
    {
        throw(MustlFail("Cannot determine current time"));
    }
    
    if (firstTimeValid)
    {
        long uSec = currentTime.tv_usec - firstTime.tv_usec;
        long sec = currentTime.tv_sec - firstTime.tv_sec;
        return static_cast<unsigned int>(sec * 1000.0 + uSec / 1000.0);
    }
    else
    {
        firstTime = currentTime;
        firstTimeValid=true;
        return 0;
    }
}
