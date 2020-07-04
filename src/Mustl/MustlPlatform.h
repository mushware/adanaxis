//%includeGuardStart {
#ifndef MUSTLPLATFORM_H
#define MUSTLPLATFORM_H
//%includeGuardStart } nqRd4O4Umy96dAui4J5yJg
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlPlatform.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } Mf/hs1IYZet816SyDDZZ4A

/*
 * $Id: MustlPlatform.h,v 1.11 2006/06/01 15:39:53 southa Exp $
 * $Log: MustlPlatform.h,v $
 * Revision 1.11  2006/06/01 15:39:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.9  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:29  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.5  2003/01/16 15:58:02  southa
 * Mustl exception handling
 *
 * Revision 1.4  2003/01/16 13:11:32  southa
 * Install and uninstall MustlPlatform
 *
 * Revision 1.3  2003/01/16 12:03:55  southa
 * Platform and invalid socket fixes
 *
 * Revision 1.2  2003/01/14 20:46:12  southa
 * Post data handling
 *
 * Revision 1.1  2003/01/13 15:52:43  southa
 * Merged MustlPlatform
 *
 * Revision 1.6  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
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
#ifdef MUSTL_NO_EXCEPTIONS
public:
#else
private:
#endif
    enum
    {
        kFailValue=0xffffffff
    };

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
    static Mustl::tSocket InvalidSocketValueGet(void);
    
    static Mustl::tSocket TCPConnectNonBlocking(const MustlAddress& inAddress);
    static Mustl::tSocket TCPBindNonBlocking(const MustlAddress& inAddress);
    static Mustl::tSocket UDPBindNonBlocking(Mustl::U32 inPortNetworkOrder);
    
    static bool Accept(Mustl::tSocket& outSocket, MustlAddress& outAddress, Mustl::tSocket inSocket);
    static void SocketClose(Mustl::tSocket inSocket);
    static bool TCPConnectionCompletedHas(Mustl::tSocket inSocket);
    static Mustl::U32 HostToNetworkOrderU16(Mustl::U32 inVal);
    static Mustl::U32 NetworkToHostOrderU16(Mustl::U32 inVal);
    static Mustl::U32 HostToNetworkOrderU32(Mustl::U32 inVal);
    static Mustl::U32 NetworkToHostOrderU32(Mustl::U32 inVal);
    static bool IsLocalAddress(Mustl::U32 inIPNetworkOrder);
    static bool ResolveIPAddressString(MustlAddress& outAddress, const std::string& inIPStr, Mustl::U32 inPortHostOrder);
    static void ResolveHostName(MustlAddress& outAddress, const std::string& inHostName, Mustl::U32 inPortHostOrder);

    static void LaunchURL(const std::string& inURL);    
    static unsigned int DefaultTimer(void);
    
    // Only call this if the local IP address(es) might have changed
    static void LocalAddressesRetrieve(void);

    static void Install();
    static void Uninstall();
    static void NullFunction(void);
    
private:
    static bool m_localAddressesValid;
    static std::map<Mustl::U32, bool> m_localAddressMap;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
