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
 * $Id: PlatformNet.cpp,v 1.10 2002/12/29 21:00:01 southa Exp $
 * $Log: PlatformNet.cpp,v $
 * Revision 1.10  2002/12/29 21:00:01  southa
 * More build fixes
 *
 * Revision 1.9  2002/12/20 13:17:48  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/11/24 11:16:37  southa
 * Added local IP address detection
 *
 * Revision 1.7  2002/11/23 15:08:08  southa
 * Store ports in network order
 *
 * Revision 1.6  2002/11/22 18:12:57  southa
 * Added TCPConnectionCompleted
 *
 * Revision 1.5  2002/11/21 18:48:52  southa
 * Added TCPConnectNonBlocking
 *
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

#include <iphlpapi.h>
#include <windows.h>

using namespace Mushware;
using namespace std;

bool PlatformNet::m_localAddressesValid=false;
map<U32, bool> PlatformNet::m_localAddressMap;

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
    sockAddr.sin_port = inPort;
    sockAddr.sin_family = AF_INET;
    int wsaError;
    int result=sendto(inSocket, reinterpret_cast<const char *>(outBuffer), inSize, 0, reinterpret_cast<sockaddr *>(&sockAddr), sizeof(sockAddr));

    if (result == SOCKET_ERROR)
    {
    	wsaError = WSAGetLastError();

        ostringstream message;
        message << "UDP send to port " << PlatformNet::NetworkToHostOrderU16(inPort) << "failed (error=" << wsaError << ")";
        throw(NetworkFail(message.str()));
    }
    else if (result < 0 || static_cast<U32>(result) != inSize)
    {
        ostringstream message;
        message << "UDP send to port " << PlatformNet::NetworkToHostOrderU16(inPort) << " failed (result=" << result << ")";
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
	    outPort=sockAddr.sin_port;
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

    if (result == SOCKET_ERROR) return false;
    
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

void
PlatformNet::LocalAddressesRetrieve(void)
{
    m_localAddressMap.clear();

    U8 ipBuffer[16384];
    PMIB_IPADDRTABLE ipAddrTable = reinterpret_cast<PMIB_IPADDRTABLE>(ipBuffer);
    ULONG bufSize=sizeof(ipBuffer)-256;
    DWORD result = GetIpAddrTable(ipAddrTable, &bufSize, 0);

    if (result != NO_ERROR)
    {
        ostringstream message;
        message << "GetIpAddrTable failed (" << result << ")";
        throw(NetworkFail(message.str()));
    }
    DWORD numEntries = ipAddrTable->dwNumEntries;
    
    if (numEntries > 256)
    {
        ostringstream message;
        message << "Too many entries from GetIpAddrTable (" << numEntries << ")";
        throw(NetworkFail(message.str()));
    }
    
    for (U32 i=0; i<numEntries; ++i)
    {
        MIB_IPADDRROW *ipAddrRow = &ipAddrTable->table[i];
        m_localAddressMap[ipAddrRow->dwAddr]=true;
    }
    m_localAddressesValid=true;
}

bool
PlatformNet::IsLocalAddress(U32 inIPNetworkOrder)
{
    if (!m_localAddressesValid)
    {
        LocalAddressesRetrieve();
    }
    return m_localAddressMap.find(inIPNetworkOrder) != m_localAddressMap.end();
}

