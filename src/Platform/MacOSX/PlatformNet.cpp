/*
 * $Id: PlatformNet.cpp,v 1.10 2002/11/23 14:39:07 southa Exp $
 * $Log: PlatformNet.cpp,v $
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

#include "mushPlatform.h"

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>

void
PlatformNet::SocketNonBlockingSet(tSocket inSocket)
{
    errno=0;
    int flags = fcntl(inSocket, F_GETFL, 0);
    if (flags < 0) flags = 0;
    if (fcntl(inSocket, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        ostringstream message;
        message << "Failed to set socket non-blocking: " << errno;
        throw(NetworkFail(message.str()));
    }
}

void
PlatformNet::UDPSend(U32 inHost, U32 inPort, tSocket inSocket, void *outBuffer, U32 inSize)
{
    COREASSERT(inSize > 0);

    struct sockaddr_in sockAddr;
    sockAddr.sin_addr.s_addr = inHost;
    sockAddr.sin_port = inPort;
    sockAddr.sin_family = AF_INET;
    
    errno=0;
    int result=sendto(inSocket, outBuffer, inSize, 0, reinterpret_cast<sockaddr *>(&sockAddr), sizeof(sockAddr));

    if (result < 0 || static_cast<U32>(result) != inSize)
    {
        ostringstream message;
        message << "UDP send to port " << PlatformNet::NetworkToHostOrderU16(inPort) << " failed (" << errno << ")";
        throw(NetworkFail(message.str()));
    }
}

U32
PlatformNet::UDPReceive(U32& outHost, U32& outPort, tSocket inSocket, void *outBuffer, U32 inSize)
{
    COREASSERT(inSize > 0);
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
                throw(NetworkFail(message.str()));
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

TCPsocket
PlatformNet::TCPConnectNonBlocking(IPaddress *ip)
{
    TCPsocket sock;
    struct sockaddr_in sock_addr;

    sock = reinterpret_cast<TCPsocket>(malloc(sizeof(*sock)));
    if (sock == NULL)
    {
        throw(NetworkFail("Couldn't create socket"));
    }

    sock->channel = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->channel == -1)
    {
        free(sock);
        throw(NetworkFail("Couldn't create socket"));
    }

    SocketNonBlockingSet(sock->channel);
    
    // Use the SDL function for listening sockets
    COREASSERT((ip->host != INADDR_NONE) && (ip->host != INADDR_ANY));

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = ip->host;
    sock_addr.sin_port = ip->port;

    errno=0;
    if (connect(sock->channel, (struct sockaddr *)&sock_addr,
                 sizeof(sock_addr)) != 0)
    {
        if (errno != EINPROGRESS)
        {
            ostringstream message;
            message << "Couldn't connect to remote host (" << errno << ")";
            throw(NetworkFail(message.str()));
        }
    }
    sock->sflag = 0;
    sock->ready = 0;

    {
        int yes = 1;
        setsockopt(sock->channel, IPPROTO_TCP, TCP_NODELAY, (char*)&yes, sizeof(yes));
    }

    sock->remoteAddress.host = sock_addr.sin_addr.s_addr;
    sock->remoteAddress.port = sock_addr.sin_port;

    return(sock);
}

bool
PlatformNet::TCPSocketConnectionCompleted(tSocket inSocket)
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
PlatformNet::HostToNetworkOrderU16(U32 inVal)
{
    return htons(inVal);
}

U32
PlatformNet::NetworkToHostOrderU16(U32 inVal)
{
    return ntohs(inVal);
}

