#ifndef PLATFORMNET_H
#define PLATFORMNET_H
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
 * $Id: PlatformNet.h,v 1.8 2002/11/24 00:29:08 southa Exp $
 * $Log: PlatformNet.h,v $
 * Revision 1.8  2002/11/24 00:29:08  southa
 * Serve web pages to local addresses only
 *
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
    typedef Mushware::S32 tSocket;

    static void SocketNonBlockingSet(tSocket inSocket);
    static void SocketAsyncSet(tSocket inSocket);
    static void UDPSend(Mushware::U32 inHost, Mushware::U32 inPort, tSocket inSocket, void *outBuffer, Mushware::U32 inSize);
    static Mushware::U32 UDPReceive(Mushware::U32& outHost, Mushware::U32& outPort, tSocket inSocket, void *outBuffer, Mushware::U32 inSize);
    static TCPsocket TCPConnectNonBlocking(IPaddress *ip);
    static bool TCPSocketConnectionCompleted(tSocket inSocket);
    static Mushware::U32 HostToNetworkOrderU16(Mushware::U32 inVal);
    static Mushware::U32 NetworkToHostOrderU16(Mushware::U32 inVal);
    static bool IsLocalAddress(Mushware::U32 inIPNetworkOrder);

private:
    static void LocalAddressesRetrieve(void);
    static bool m_localAddressesValid;
    static std::map<U32, bool> m_localAddressMap;
};
#endif
