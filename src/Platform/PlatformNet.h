/*
 * $Id: PlatformNet.h,v 1.7 2002/11/23 17:23:45 southa Exp $
 * $Log: PlatformNet.h,v $
 * Revision 1.7  2002/11/23 17:23:45  southa
 * Sleep in setup
 *
 * Revision 1.6  2002/11/23 14:39:07  southa
 * Store ports in network order
 *
 * Revision 1.5  2002/11/22 18:02:43  southa
 * Wait for TCP connection
 *
 * Revision 1.4  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.3  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.2  2002/11/02 11:22:51  southa
 * Simplified UDP send and receive
 *
 * Revision 1.1  2002/11/01 16:15:28  southa
 * Network send and receive
 *
 */

#include "mushCore.h"

#include "mushMedia.h"

struct _UDPsocket
{
    int ready;
    int channel;
};

struct _TCPsocket {
    int ready;
    int channel;
    IPaddress remoteAddress;
    IPaddress localAddress;
    int sflag;
};

class PlatformNet
{
public:
    typedef S32 tSocket;

    static void SocketNonBlockingSet(tSocket inSocket);
    static void SocketAsyncSet(tSocket inSocket);
    static void UDPSend(U32 inHost, U32 inPort, tSocket inSocket, void *outBuffer, U32 inSize);
    static U32 UDPReceive(U32& outHost, U32& outPort, tSocket inSocket, void *outBuffer, U32 inSize);
    static TCPsocket TCPConnectNonBlocking(IPaddress *ip);
    static bool TCPSocketConnectionCompleted(tSocket inSocket);
    static U32 HostToNetworkOrderU16(U32 inVal);
    static U32 NetworkToHostOrderU16(U32 inVal);
    static bool IsLocalAddress(U32 inIPNetworkOrder);

private:
    static void LocalAddressesRetrieve(void);
    static bool m_localAddressesValid;
    static map<U32, bool> m_localAddressMap;
};
