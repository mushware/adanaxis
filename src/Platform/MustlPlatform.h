#ifndef MUSTLPLATFORM_H
#define MUSTLPLATFORM_H

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
 * $Id: MustlPlatform.h,v 1.5 2002/12/17 00:58:29 southa Exp $
 * $Log: MustlPlatform.h,v $
 * Revision 1.5  2002/12/17 00:58:29  southa
 * Added support for libmustl target
 *
 * Revision 1.4  2002/12/14 15:04:34  southa
 * Mustl fixes
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
    static void SocketBlockingSet(Mustl::tSocket inSocket);
    static void SocketReuseAddressSet(Mustl::tSocket inSocket);
    static void SocketTCPNoDelaySet(Mustl::tSocket inSocket);

    static Mustl::U32 TCPSend(Mustl::tSocket inSocket, void *inBuffer, Mustl::U32 inSize);
    static Mustl::U32 TCPReceive(Mustl::tSocket inSocket, void *outBuffer, Mustl::U32 inSize);
    
    static Mustl::U32 UDPSend(const MustlAddress& inAddress, Mustl::tSocket inSocket, void *inBuffer, Mustl::U32 inSize);
    static Mustl::U32 UDPReceive(MustlAddress& outAddress, Mustl::tSocket inSocket, void *outBuffer, Mustl::U32 inSize);

    static Mustl::tSocket TCPUnboundSocketCreate(void);
    static Mustl::tSocket UDPUnboundSocketCreate(void);

    static Mustl::tSocket TCPConnectNonBlocking(const MustlAddress& inAddress);
    static Mustl::tSocket TCPBindNonBlocking(const MustlAddress& inAddress);
    static Mustl::tSocket UDPBindNonBlocking(Mustl::U32 inPortNetworkOrder);
    
    static bool Accept(Mustl::tSocket& outSocket, MustlAddress& outAddress, Mustl::tSocket inSocket);
    static void SocketClose(Mustl::tSocket inSocket);
    static bool TCPSocketConnectionCompleted(Mustl::tSocket inSocket);
    static Mustl::U32 HostToNetworkOrderU16(Mustl::U32 inVal);
    static Mustl::U32 NetworkToHostOrderU16(Mustl::U32 inVal);
    static Mustl::U32 HostToNetworkOrderU32(Mustl::U32 inVal);
    static Mustl::U32 NetworkToHostOrderU32(Mustl::U32 inVal);
    static bool IsLocalAddress(Mustl::U32 inIPNetworkOrder);
    static bool ResolveIPAddressString(MustlAddress& outAddress, const std::string& inIPStr, Mustl::U32 inPortHostOrder);
    static void ResolveHostName(MustlAddress& outAddress, const std::string& inHostName, Mustl::U32 inPortHostOrder);
 
        
    static unsigned int DefaultTimer(void);
    
    // Only call this if the local IP address(es) might have changed
    static void LocalAddressesRetrieve(void);
    
private:
    static bool m_localAddressesValid;
    static std::map<Mustl::U32, bool> m_localAddressMap;
};
#endif
