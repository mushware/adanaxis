#ifndef MUSTLPLATFORM_H
#define MUSTLPLATFORM_H

/*
 * $Id: MustlPlatform.h,v 1.1 2002/12/12 18:38:58 southa Exp $
 * $Log: MustlPlatform.h,v $
 * Revision 1.1  2002/12/12 18:38:58  southa
 * Mustl separation
 *
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

#include "MustlStandard.h"

class MustlAddress;

class MustlPlatform
{
public:
    static void SocketNonBlockingSet(Mustl::tSocket inSocket);
    static void SocketAsyncSet(Mustl::tSocket inSocket);
    static void TCPSend(Mustl::tSocket inSocket, void *inBuffer, Mustl::U32 inSize);
    static Mustl::U32 TCPReceive(Mustl::tSocket inSocket, void *outBuffer, Mustl::U32 inSize);

    static void UDPSend(Mustl::U32 inHost, Mustl::U32 inPort, Mustl::tSocket inSocket, void *outBuffer, Mustl::U32 inSize);
    static Mustl::U32 UDPReceive(Mustl::U32& outHost, Mustl::U32& outPort, Mustl::tSocket inSocket, void *outBuffer, Mustl::U32 inSize);
    static Mustl::tSocket TCPConnectNonBlocking(const MustlAddress& inAddress);
    static Mustl::tSocket TCPBindNonBlocking(const MustlAddress& inAddress);
    static Mustl::tSocket UDPBindNonBlocking(Mustl::U32 inPortNetworkOrder);
    static bool Accept(Mustl::tSocket& outSocket, MustlAddress& outAddress, Mustl::tSocket inSocket);
    static void SocketClose(Mustl::tSocket inSocket);
    static bool TCPSocketConnectionCompleted(Mustl::tSocket inSocket);
    static Mustl::U32 HostToNetworkOrderU16(Mustl::U32 inVal);
    static Mustl::U32 NetworkToHostOrderU16(Mustl::U32 inVal);
    static bool IsLocalAddress(Mustl::U32 inIPNetworkOrder);
    static void ResolveAddress(MustlAddress& outAddress, const std::string& inHostName, Mustl::U32 inPortHostOrder);
    static unsigned int DefaultTimer(void);

private:
    static void LocalAddressesRetrieve(void);

    static bool m_localAddressesValid;
    static map<Mustl::U32, bool> m_localAddressMap;
};
#endif
