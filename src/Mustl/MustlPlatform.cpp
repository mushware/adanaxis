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
 * $Id: MustlPlatform.cpp,v 1.13 2003/02/04 19:07:12 southa Exp $
 * $Log: MustlPlatform.cpp,v $
 * Revision 1.13  2003/02/04 19:07:12  southa
 * Build fixes
 *
 * Revision 1.12  2003/02/04 14:54:51  southa
 * Build fixes
 *
 * Revision 1.11  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.10  2003/01/16 16:38:36  southa
 * Error codes for win32
 *
 * Revision 1.9  2003/01/16 15:58:01  southa
 * Mustl exception handling
 *
 * Revision 1.8  2003/01/16 13:11:32  southa
 * Install and uninstall MustlPlatform
 *
 * Revision 1.7  2003/01/16 12:03:55  southa
 * Platform and invalid socket fixes
 *
 * Revision 1.6  2003/01/14 23:43:00  southa
 * Fixes for win32
 *
 * Revision 1.5  2003/01/14 22:02:12  southa
 * Command line build fixes
 *
 * Revision 1.4  2003/01/14 20:46:11  southa
 * Post data handling
 *
 * Revision 1.3  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.2  2003/01/13 16:50:48  southa
 * win32 support
 *
 * Revision 1.1  2003/01/13 15:52:43  southa
 * Merged MustlPlatform
 *
 * Revision 1.8  2002/12/29 21:00:00  southa
 * More build fixes
 *
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

#include "MustlPlatform.h"

#include "MustlAddress.h"
#include "MustlFail.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"
#include "MustlPlatformError.h"
#include "MustlPlatformHeaders.h"

using namespace Mustl;
using namespace std;

bool MustlPlatform::m_localAddressesValid=false;
map<U32, bool> MustlPlatform::m_localAddressMap;

MushcoreInstaller MustlPlatformInstaller(MustlPlatform::Install);
MushcoreUninstaller MustlPlatformUninstaller(MustlPlatform::Uninstall);

void
MustlPlatform::SocketClose(tSocket inSocket)
{
#ifdef MUSTL_WIN32
    closesocket(inSocket);
#else
    close(inSocket);
#endif
}

void
MustlPlatform::SocketNonBlockingSet(tSocket inSocket)
{
    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;

#ifdef MUSTL_WIN32
    u_long mode = 1;
    int result = ioctlsocket(inSocket, FIONBIO, &mode);
#else
    int flags = fcntl(inSocket, F_GETFL, 0);
    if (flags < 0) flags = 0;
    int result = fcntl(inSocket, F_SETFL, flags | O_NONBLOCK);
#endif
        
    if (result < 0)
    {
        MUSTL_ERROR_FETCH;
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "Failed to set socket non-blocking");
    }
}

void
MustlPlatform::SocketBlockingSet(tSocket inSocket)
{
    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;

#ifdef MUSTL_WIN32
    u_long mode = 1;
    int result = ioctlsocket(inSocket, FIONBIO, &mode);
#else
    int flags = fcntl(inSocket, F_GETFL, 0);
    if (flags < 0) flags = 0;
    int result = fcntl(inSocket, F_SETFL, flags & ~O_NONBLOCK);
#endif
    
    if (result < 0)
    {
        MUSTL_ERROR_FETCH;
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "Failed to set socket blocking");
    }
}

void
MustlPlatform::SocketReuseAddressSet(tSocket inSocket)
{
    int value=1;
    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;
    
    if (setsockopt(inSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&value), sizeof(value)) != 0)
    {
        MUSTL_ERROR_FETCH;
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "Failed to set socket address reuse");
    }
}

void
MustlPlatform::SocketTCPNoDelaySet(tSocket inSocket)
{
    int value=1;
    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;
    
    if (setsockopt(inSocket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char *>(&value), sizeof(value)) != 0)
    {
        MUSTL_ERROR_FETCH;
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "Failed to set socket TCP delay");
    }
}

U32
MustlPlatform::TCPSend(tSocket inSocket, void *inBuffer, U32 inSize)
{
    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;
    int result = send(inSocket, reinterpret_cast<const char *>(inBuffer), inSize, 0);

    if (result < 0)
    {
        MUSTL_ERROR_FETCH;
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "TCP send failed");
        return kFailValue;
    }
    return static_cast<U32>(result);
}

U32
MustlPlatform::TCPReceive(tSocket inSocket, void *outBuffer, U32 inSize)
{
    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;

    int result = recv(inSocket, reinterpret_cast<char *>(outBuffer), inSize, 0);

    if (result < 0)
    {
        MUSTL_ERROR_FETCH;

        if (MUSTL_ERROR_VALUE == MUSTL_ERROR_EINTR || MUSTL_ERROR_VALUE == MUSTL_ERROR_EAGAIN)
        {
            result = 0;
        }
        else
        {
            MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "TCP receive failed");
            return kFailValue;
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

    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;
    
    int result=sendto(inSocket, reinterpret_cast<const char *>(inBuffer), inSize, 0, reinterpret_cast<sockaddr *>(&sockAddr), sizeof(sockAddr));

    if (result < 0)
    {
        MUSTL_ERROR_FETCH;
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "UDP send to "+inAddress.StringGet()+" failed");
        return kFailValue;
    }
    return static_cast<U32>(result);
}

U32
MustlPlatform::UDPReceive(MustlAddress& outAddress, tSocket inSocket, void *outBuffer, U32 inSize)
{
    struct sockaddr_in sockAddr;
    MUSTL_SOCKLEN_T sockAddrSize=sizeof(sockAddr);

    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;
    
    int result = recvfrom(inSocket, reinterpret_cast<char *>(outBuffer), inSize, 0, reinterpret_cast<sockaddr *>(&sockAddr), &sockAddrSize);

    outAddress.HostSetNetworkOrder(sockAddr.sin_addr.s_addr);
    outAddress.PortSetNetworkOrder(sockAddr.sin_port);
    
    if (result < 0)
    {
        MUSTL_ERROR_FETCH;

        if (MUSTL_ERROR_VALUE == MUSTL_ERROR_EINTR || MUSTL_ERROR_VALUE == MUSTL_ERROR_EAGAIN)
        {
            result = 0;
        }
        else
        {
            MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "UDP receive failed");
            return kFailValue;
        }
    }
    return static_cast<U32>(result);
}

tSocket
MustlPlatform::TCPUnboundSocketCreate(void)
{
    tSocket sockHandle;

    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;

    sockHandle = socket(AF_INET, SOCK_STREAM, 0);
    if (sockHandle == MUSTL_INVALID_SOCKET)
    {
        MUSTL_ERROR_FETCH;
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "Couldn't create TCP socket");
        return MUSTL_INVALID_SOCKET;
    }
    return sockHandle;
}

tSocket
MustlPlatform::UDPUnboundSocketCreate(void)
{
    tSocket sockHandle;
    
    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;
    
    sockHandle = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockHandle == MUSTL_INVALID_SOCKET)
    {
        MUSTL_ERROR_FETCH;
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "Couldn't create UDP socket");
        return MUSTL_INVALID_SOCKET;
    }
    return sockHandle;
}

tSocket
MustlPlatform::InvalidSocketValueGet(void)
{
    return MUSTL_INVALID_SOCKET;
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

    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;

    if (connect(sockHandle, reinterpret_cast<struct sockaddr *>(&sockAddr), sizeof(sockAddr)) != 0)
    {
        MUSTL_ERROR_FETCH;

        if (MUSTL_ERROR_VALUE != MUSTL_ERROR_EINPROGRESS)
        {
            SocketClose(sockHandle);
            MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "Couldn't connect to remote host "+inAddress.StringGet());
            return MUSTL_INVALID_SOCKET;
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

    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;
    if (bind(sockHandle, reinterpret_cast<struct sockaddr *>(&sockAddr), sizeof(sockAddr)) != 0)
    {
        MUSTL_ERROR_FETCH;
        
        SocketClose(sockHandle);
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "Couldn't bind server address "+inAddress.StringGet());
        return MUSTL_INVALID_SOCKET;
    }
    
    if (listen(sockHandle, 8) != 0)
    {
        MUSTL_ERROR_FETCH;
        
        SocketClose(sockHandle);
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "Couldn't listen on server socket "+inAddress.StringGet());
        return MUSTL_INVALID_SOCKET;
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

    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;
    
    if (bind(sockHandle, reinterpret_cast<struct sockaddr *>(&sockAddr), sizeof(sockAddr)) != 0)
    {
        MUSTL_ERROR_FETCH;

        if (MUSTL_ERROR_VALUE != MUSTL_ERROR_EINPROGRESS)
        {
            SocketClose(sockHandle);
            ostringstream message;
            message << "Couldn't bind UDP port " << NetworkToHostOrderU16(inPortNetworkOrder);
            MustlPlatformError::Throw(MUSTL_ERROR_VALUE, message.str());
            return MUSTL_INVALID_SOCKET;
        }
    }

    return sockHandle;
}

bool
MustlPlatform::Accept(tSocket& outSocket, MustlAddress& outAddress, tSocket inSocket)
{
    struct sockaddr_in sockAddr;
    MUSTL_SOCKLEN_T sockAddrLen = sizeof(sockAddr);

    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;
    int newSocket = accept(inSocket, reinterpret_cast<struct sockaddr *>(&sockAddr), &sockAddrLen);

    if (newSocket == MUSTL_INVALID_SOCKET)
    {
        MUSTL_ERROR_FETCH;

        if (MUSTL_ERROR_VALUE == MUSTL_ERROR_EWOULDBLOCK)
        {
            return false;
        }
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "Accept failed");
        return false;
    }
    outSocket = newSocket;
    outAddress.HostSetNetworkOrder(sockAddr.sin_addr.s_addr);
    outAddress.PortSetNetworkOrder(sockAddr.sin_port);
    return true;
}

bool
MustlPlatform::TCPConnectionCompletedHas(tSocket inSocket)
{
    struct timeval timeVal;
    timeVal.tv_sec = 0;
    timeVal.tv_usec = 0;
    
    fd_set fdSet;
    FD_ZERO(&fdSet);
    FD_SET(inSocket, &fdSet);

    int result = select(inSocket+1, NULL, &fdSet, NULL, &timeVal);

    if (result < 0) return false;
    
    return !(!(FD_ISSET(inSocket, &fdSet)));
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
                U32 hostIP;
                memcpy(&hostIP, hostEnt->h_addr_list[0], sizeof(hostIP));
                outAddress.HostSetNetworkOrder(hostIP);
                outAddress.PortSetHostOrder(inPortHostOrder);
            }
            else
            {
                MustlPlatformError::Throw("Cannot resolve host name '"+inHostName+"'");
                outAddress.HostSetNetworkOrder(INADDR_NONE);
                outAddress.PortSetHostOrder(0);
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
        U32 hostIP = inet_addr(inIPStr.c_str());
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

#ifdef MUSTL_WIN32
// Start of win32 block
void
MustlPlatform::LocalAddressesRetrieve(void)
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
        MustlPlatformError::Throw(message.str());
        return;
    }
    DWORD numEntries = ipAddrTable->dwNumEntries;

    if (numEntries > 256)
    {
        ostringstream message;
        message << "Too many entries from GetIpAddrTable (" << numEntries << ")";
        MustlPlatformError::Throw(message.str());
        return;
    }

    for (U32 i=0; i<numEntries; ++i)
    {
        MIB_IPADDRROW *ipAddrRow = &ipAddrTable->table[i];
        m_localAddressMap[ipAddrRow->dwAddr]=true;
    }
    m_localAddressesValid=true;
}

unsigned int
MustlPlatform::DefaultTimer(void)
{
    static DWORD firstTime;
    static bool firstTimeValid=false;
    DWORD currentTime;
    
    currentTime = timeGetTime();

    if (firstTimeValid)
    {
        return static_cast<unsigned int>(currentTime - firstTime);
    }
    else
    {
        firstTime = currentTime;
        firstTimeValid=true;
        return 0;
    }
}

void
MustlPlatform::LaunchURL(const string& inURL)
{
    int status = reinterpret_cast<int>(ShellExecute(NULL, "open", inURL.c_str(), NULL, NULL, SW_SHOWDEFAULT));
    if (status < 32)
    {
        ostringstream message;
        message << "URL launch failed for '" << inURL << "': " << status;
        MustlPlatformError::Throw(message.str());
    }
}
// End of win32 block
#endif

#ifdef MUSTL_MACOSX
// Start of Mac OS X only block
void
MustlPlatform::LaunchURL(const string& inURL)
{
#ifdef MUSTL_NO_CARBON
    MustlPlatformError::Throw("Cannot open URL '"+inURL+"' because Mustl was compiled with MUSTL_NO_CARBON");
#else
    CFStringRef destName = CFStringCreateWithCString(NULL, inURL.c_str(), kCFStringEncodingMacRoman);
    if (destName)
    {
        CFURLRef pathRef = CFURLCreateWithString(NULL, destName, NULL);
        if (pathRef)
        {
            LSOpenCFURLRef(pathRef, NULL);
            CFRelease(pathRef);
        }
        else
        {
            MustlPlatformError::Throw("Cannot open URL '"+inURL+"'");
        }
        CFRelease(destName);
    }
    else
    {
        MustlPlatformError::Throw("Cannot open URL '"+inURL+"'");
    }
#endif
}
// End of Mac OS X only block
#endif

#ifdef MUSTL_POSIX_NOT_MACOSX
// Start of POSIX only block (not including Mac OS X)
void
MustlPlatform::LaunchURL(const string& inURL)
{
    MustlPlatformError::Throw("Cannot automatically open URL '"+inURL+"' on this platform");
}    
// End of POSIX only block
#endif

#ifdef MUSTL_POSIX_OR_MACOSX
// Start of POSIX or Mac OS X block
void
MustlPlatform::LocalAddressesRetrieve(void)
{
    m_localAddressMap.clear();

    struct ifconf ifConf;
    U8 ipBuffer[16384];
    ifConf.ifc_buf = reinterpret_cast<char *>(ipBuffer);
    ifConf.ifc_len = sizeof(ipBuffer)-256;
    tSocket testSocket = TCPUnboundSocketCreate();

    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;

    if (ioctl(testSocket, SIOCGIFCONF, &ifConf) != 0)
    {
        MUSTL_ERROR_FETCH;
        
        SocketClose(testSocket);
        MustlPlatformError::Throw(MUSTL_ERROR_VALUE, "ioctl SIOCGIFCONF fail");
    }
    U8 *dataPtr=ipBuffer;

    while (dataPtr < ipBuffer+ifConf.ifc_len)
    {
        struct ifreq *ifReq = reinterpret_cast<struct ifreq *>(dataPtr);

#ifdef HAVE_SOCKADDR_SA_LEN
        U32 entryLength=ifReq->ifr_addr.sa_len;
	if (entryLength < sizeof(struct sockaddr)) entryLength=sizeof(struct sockaddr);
#else
        U32 entryLength=sizeof(struct sockaddr);
#endif
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
    SocketClose(testSocket);
    m_localAddressesValid=true;
}

unsigned int
MustlPlatform::DefaultTimer(void)
{
    static struct timeval firstTime;
    static bool firstTimeValid=false;
    struct timeval currentTime;
    
    if (gettimeofday(&currentTime, NULL) != 0)
    {
        MustlPlatformError::Throw("Cannot determine current time");
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
// End of POSIX or Mac OS X block
#endif

void
MustlPlatform::Install(void)
{
#ifdef MUSTL_WIN32
    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    int result = WSAStartup(wVersionRequested, &wsaData);
    if (result != 0)
    {
        cerr << "WSAStartup failed (" << result << ")";
    }
#endif
}

void
MustlPlatform::Uninstall(void)
{
#ifdef MUSTL_WIN32
    MUSTL_ERROR_PROLOGUE;
    MUSTL_ERROR_RESET;

    if (WSACleanup() != 0)
    {
        MUSTL_ERROR_FETCH;
        cerr << "WSACleanup failed (" << MUSTL_ERROR_VALUE << ")";
    }
#endif
}

void
MustlPlatform::NullFunction(void)
{
}
