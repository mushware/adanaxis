/*
 * $Id: PlatformNet.cpp,v 1.3 2002/11/02 11:22:51 southa Exp $
 * $Log: PlatformNet.cpp,v $
 * Revision 1.3  2002/11/02 11:22:51  southa
 * Simplified UDP send and receive
 *
 */

/*************************
 *
 *  Mac OS X file
 *
 *************************/

#include "PlatformNet.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

void
PlatformNet::SocketNonBlockingSet(tSocket inSocket)
{
    errno=0;
    if (fcntl(inSocket, F_SETFL, O_NONBLOCK) == -1)
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
        message << "UDP send failed (" << errno << ")";
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
        cerr << "recv " << result << endl;
    
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
