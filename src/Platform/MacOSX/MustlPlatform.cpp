/*
 * $Id: MustlPlatform.cpp,v 1.1 2002/12/12 18:38:58 southa Exp $
 * $Log: MustlPlatform.cpp,v $
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
#include "MustlNamespace.h"
#include "MustlSTL.h"

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>

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
MustlPlatform::TCPSend(tSocket inSocket, void *inBuffer, U32 inSize)
{
    MUSTLASSERT(inSize > 0);

    errno=0;
    int result=send(inSocket, inBuffer, inSize, 0);

    if (result < 0 || static_cast<U32>(result) != inSize)
    {
        ostringstream message;
        message << "TCP send failed (" << errno << ")";
        throw(MustlFail(message.str()));
    }
}

U32
MustlPlatform::TCPReceive(tSocket inSocket, void *outBuffer, U32 inSize)
{
    MUSTLASSERT(inSize > 0);
    U32 dataSize=0;
    for (U32 i=0; i<1; ++i) // Needs fixing to advance into outBuffer if you allow i>0
    {
        errno=0;
        int result = recv(inSocket, outBuffer, inSize, 0);

        if (result < 0)
        {
            if (errno == EAGAIN) break;

            if (errno != EINTR)
            {
                ostringstream message;
                message << "TCP receive failed (" << errno << ")";
                throw(MustlFail(message.str()));
            }
        }
        else if (result == 0)
        {
            break;
        }
        else
        {
            dataSize += result;
        }
    }
    return dataSize;
}

void
MustlPlatform::UDPSend(U32 inHost, U32 inPort, tSocket inSocket, void *inBuffer, U32 inSize)
{
    MUSTLASSERT(inSize > 0);

    struct sockaddr_in sockAddr;
    sockAddr.sin_addr.s_addr = inHost;
    sockAddr.sin_port = inPort;
    sockAddr.sin_family = AF_INET;
    
    errno=0;
    int result=sendto(inSocket, inBuffer, inSize, 0, reinterpret_cast<sockaddr *>(&sockAddr), sizeof(sockAddr));

    if (result < 0 || static_cast<U32>(result) != inSize)
    {
        ostringstream message;
        message << "UDP send to port " << MustlPlatform::NetworkToHostOrderU16(inPort) << " failed (" << errno << ")";
        throw(MustlFail(message.str()));
    }
}

U32
MustlPlatform::UDPReceive(U32& outHost, U32& outPort, tSocket inSocket, void *outBuffer, U32 inSize)
{
    MUSTLASSERT(inSize > 0);
    U32 dataSize=0;
    for (U32 i=0; i<1; ++i) // Needs fixing to advance into outBuffer if you allow i>0
    {
        struct sockaddr_in sockAddr;

        errno=0;
        int sockAddrSize=sizeof(sockAddr);
        int result = recvfrom(inSocket, outBuffer, inSize, 0, reinterpret_cast<sockaddr *>(&sockAddr), &sockAddrSize);
    
        outHost=sockAddr.sin_addr.s_addr;
        outPort=sockAddr.sin_port;
        
        if (result < 0)
        {
            if (errno == EAGAIN) break;
            
            if (errno != EINTR)
            {
                ostringstream message;
                message << "UDP receive failed (" << errno << ")";
                throw(MustlFail(message.str()));
            }
        }
        else if (result == 0)
        {
            break;
        }
        else
        {
            dataSize += result;
        }
    }
    return dataSize;
}

tSocket
MustlPlatform::TCPConnectNonBlocking(const MustlAddress& inAddress)
{
    tSocket socketHandle;
    struct sockaddr_in sock_addr;

    socketHandle = socket(AF_INET, SOCK_STREAM, 0);
    if (socketHandle == -1)
    {
        throw(MustlFail("Couldn't create socket"));
    }

    SocketNonBlockingSet(socketHandle);
    
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inAddress.HostGetNetworkOrder();
    sock_addr.sin_port = inAddress.PortGetNetworkOrder();

    errno=0;
    if (connect(socketHandle, (struct sockaddr *)&sock_addr,
                 sizeof(sock_addr)) != 0)
    {
        if (errno != EINPROGRESS)
        {
            close(socketHandle);
            ostringstream message;
            message << "Couldn't connect to remote host (" << errno << ")";
            throw(MustlFail(message.str()));
        }
    }
    
    {
        int yes = 1;
        setsockopt(socketHandle, IPPROTO_TCP, TCP_NODELAY, (char*)&yes, sizeof(yes));
    }

    return socketHandle;
}

tSocket
MustlPlatform::TCPBindNonBlocking(const MustlAddress& inAddress)
{
    tSocket socketHandle;
    struct sockaddr_in sock_addr;

    socketHandle = socket(AF_INET, SOCK_STREAM, 0);
    if (socketHandle == -1)
    {
        throw(MustlFail("Couldn't create socket"));
    }

    SocketNonBlockingSet(socketHandle);

    int value = 1;
    setsockopt(socketHandle, SOL_SOCKET, SO_REUSEADDR, (char *)&value, sizeof(value));
    
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inAddress.HostGetNetworkOrder();
    sock_addr.sin_port = inAddress.PortGetNetworkOrder();

    errno=0;
    if (bind(socketHandle, (struct sockaddr *)&sock_addr,
             sizeof(sock_addr)) != 0)
    {
        close(socketHandle);
        ostringstream message;
        message << "Couldn't bind server address (" << errno << ")";
        throw(MustlFail(message.str()));
    }
    
    if (listen(socketHandle, 8) != 0)
    {
        close(socketHandle);
        ostringstream message;
        message << "Couldn't listen on server socket (" << errno << ")";
        throw(MustlFail(message.str()));
    }
    return socketHandle;
}

tSocket
MustlPlatform::UDPBindNonBlocking(U32 inPortNetworkOrder)
{
    tSocket socketHandle;
    struct sockaddr_in sock_addr;

    socketHandle = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketHandle == -1)
    {
        throw(MustlFail("Couldn't create socket"));
    }

    SocketNonBlockingSet(socketHandle);

    int value = 1;
    setsockopt(socketHandle, SOL_SOCKET, SO_REUSEADDR, (char *)&value, sizeof(value));
    
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = 0; // Not used
    sock_addr.sin_port = inPortNetworkOrder;

    errno=0;
    if (bind(socketHandle, (struct sockaddr *)&sock_addr,
                sizeof(sock_addr)) != 0)
    {
        if (errno != EINPROGRESS)
        {
            close(socketHandle);
            ostringstream message;
            message << "Couldn't connect to remote host (" << errno << ")";
            throw(MustlFail(message.str()));
        }
    }

    return socketHandle;
}

bool
MustlPlatform::Accept(tSocket& outSocket, MustlAddress& outAddress, tSocket inSocket)
{
    struct sockaddr_in sockAddrIn;
    int sockAddrLen = sizeof(sockAddrIn);
    errno=0;
    int newSocket = accept(inSocket, reinterpret_cast<struct sockaddr *>(&sockAddrIn), &sockAddrLen);

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
    outAddress.HostSetNetworkOrder(sockAddrIn.sin_addr.s_addr);
    outAddress.PortSetNetworkOrder(sockAddrIn.sin_port);
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
    int result=select(inSocket+1, NULL, &fdSet, NULL, &timeVal);

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
MustlPlatform::ResolveAddress(MustlAddress& outAddress, const string& inHostName, U32 inPortHostOrder)
{
    if (inHostName == "")
    {
        outAddress.HostSetNetworkOrder(INADDR_ANY);
    }
    else
    {
        in_addr_t hostIP = inet_addr(inHostName.c_str());
        if (hostIP != INADDR_NONE )
        {
            outAddress.HostSetNetworkOrder(hostIP);
        }
        else
        {
            struct hostent *hostEnt;

            hostEnt = gethostbyname(inHostName.c_str());
            if (hostEnt != NULL)
            {
                memcpy(&hostIP, hostEnt->h_addr_list[0], sizeof(hostIP));
                outAddress.HostSetNetworkOrder(hostIP);
            }
            else
            {
                throw(MustlFail("Cannot resolve host name '"+inHostName+"'"));
            }
        }
    }
    outAddress.PortSetHostOrder(inPortHostOrder);
}

unsigned int
MustlPlatform::DefaultTimer(void)
{
    return static_cast<unsigned int>(clock() * (double) 1000.0 / CLOCKS_PER_SEC);
}
