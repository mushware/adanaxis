/*
 * $Id: PlatformNet.cpp,v 1.4 2002/11/08 00:41:10 southa Exp $
 * $Log: PlatformNet.cpp,v $
 * Revision 1.4  2002/11/08 00:41:10  southa
 * Removed debug
 *
 * Revision 1.3  2002/11/08 00:25:34  southa
 * Added UDPSend and UDPReceive
 *
 * Revision 1.2  2002/11/01 17:24:49  southa
 * Network links on win32
 *
 */

#include "mushPlatform.h"

#include <windows.h>

void
PlatformNet::SocketNonBlockingSet(tSocket inSocket)
{
    u_long mode = 1;
    int result = ioctlsocket(inSocket, FIONBIO, &mode);

    if (result != 0)
    {
        ostringstream message;
        message << "Failed to set socket non-blocking: " << result;
        throw(NetworkFail(message.str()));
    }
}

void
PlatformNet::UDPSend(U32 inHost, U32 inPort, tSocket inSocket, void *outBuffer, U32 inSize)
{
    COREASSERT(inSize > 0);

    struct sockaddr_in sockAddr;
    sockAddr.sin_addr.s_addr = inHost;
    SDLNet_Write16(inPort, &sockAddr.sin_port);
    sockAddr.sin_family = AF_INET;
    int wsaError;
    int result=sendto(inSocket, reinterpret_cast<const char *>(outBuffer), inSize, 0, reinterpret_cast<sockaddr *>(&sockAddr), sizeof(sockAddr));

    if (result == SOCKET_ERROR)
    {
    	wsaError = WSAGetLastError();

        ostringstream message;
        message << "UDP send failed (error=" << wsaError << ")";
        throw(NetworkFail(message.str()));
    }
    else if (result < 0 || static_cast<U32>(result) != inSize)
    {
        ostringstream message;
        message << "UDP send failed (result=" << result << ")";
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
	int wsaError;
        struct sockaddr_in sockAddr;

        int sockAddrSize=sizeof(sockAddr);
        int result = recvfrom(inSocket, reinterpret_cast<char *>(outBuffer), inSize, 0, reinterpret_cast<sockaddr *>(&sockAddr), &sockAddrSize);
        
        if (result == SOCKET_ERROR)
        {
	    wsaError = WSAGetLastError();

	    if (wsaError == WSAEWOULDBLOCK) break;

	    if (wsaError != WSAEINTR)
            {
                ostringstream message;
                message << "UDP receive failed (" << wsaError << ")";
                throw(NetworkFail(message.str()));
            }
        }
        else if (result <= 0)
        {
            break;
        }
        else
        {
            dataSize += result;

            outHost=sockAddr.sin_addr.s_addr;
	    unsigned short u16Port;
	    SDLNet_Write16(sockAddr.sin_port, &u16Port);
	    outPort=u16Port;
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

    if (connect(sock->channel, (struct sockaddr *)&sock_addr,
                 sizeof(sock_addr)) == SOCKET_ERROR)
    {
    	int wsaError = WSAGetLastError();

        if (wsaError != WSAEWOULDBLOCK)
        {
            ostringstream message;
            message << "Couldn't connect to remote host (" << wsaError << ")";
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

