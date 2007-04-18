//%includeGuardStart {
#ifndef MUSTLCLIENT_H
#define MUSTLCLIENT_H
//%includeGuardStart } 72ii6tRCfX48vehyuqEuHg
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlClient.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ggh+kbnBjVu8r5r3UlnkLQ
/*
 * $Id: MustlClient.h,v 1.12 2006/06/01 15:39:50 southa Exp $
 * $Log: MustlClient.h,v $
 * Revision 1.12  2006/06/01 15:39:50  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.10  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:09:21  southa
 * Fixed file headers
 *
 * Revision 1.7  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/12/15 00:26:20  southa
 * Send, receive and timer work
 *
 * Revision 1.5  2002/12/14 15:04:33  southa
 * Mustl fixes
 *
 * Revision 1.4  2002/12/13 19:03:05  southa
 * Mustl interface cleanup
 *
 * Revision 1.3  2002/12/13 01:06:53  southa
 * Mustl work
 *
 * Revision 1.2  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.11  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.10  2002/11/23 14:39:05  southa
 * Store ports in network order
 *
 * Revision 1.9  2002/11/22 18:02:43  southa
 * Wait for TCP connection
 *
 * Revision 1.8  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.7  2002/11/05 18:15:17  southa
 * Web server
 *
 * Revision 1.6  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.5  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.4  2002/11/01 18:46:25  southa
 * UDP Links
 *
 * Revision 1.3  2002/11/01 16:15:27  southa
 * Network send and receive
 *
 * Revision 1.2  2002/10/31 19:55:54  southa
 * Network links
 *
 * Revision 1.1  2002/10/31 16:41:33  southa
 * Network client
 *
 */

#include "MustlAddress.h"
#include "MustlStandard.h"

class MustlData;

class MustlClient
{
public:
    MustlClient();
    ~MustlClient();

    void TCPConnect(const MustlAddress& inAddress);
    void TCPSocketTake(Mustl::tSocket inSocket, const MustlAddress& inAddress);
    void UDPConnect(const MustlAddress& inAddress);
    void TCPDisconnect(void);
    void UDPDisconnect(void);

    void TCPSend(MustlData& inData);
    void TCPReceive(MustlData& outData);
    void UDPSend(MustlData& inData);
    void UDPReceive(MustlData& outData);

    bool TCPConnectionCompletedHas(void);
    bool UDPConnectedIs(void) const { return m_udpConnected; }

    const MustlAddress& TCPAddressGet(void) const { return m_tcpAddress; }
    const MustlAddress& UDPAddressGet(void) const { return m_udpAddress; }

    void UDPRemotePortSetHostOrder(Mustl::U32 inPortHostOrder);
    void UDPAddressSet(const MustlAddress& inAddress) { m_udpAddress = inAddress; }

    void Print(std::ostream& ioOut) const;
    
private:
    enum
    {
        kEthernetMTU=1500 // Bytes in Ehternet Maximum Trasfer Unit
    };
    
    Mustl::tSocket m_tcpSocket;
    Mustl::tSocket m_udpSocket;
    MustlAddress m_tcpAddress;
    MustlAddress m_udpAddress;
    bool m_tcpConnected;
    bool m_udpConnected;
};

inline std::ostream&
operator<<(std::ostream &ioOut, const MustlClient& inClient)
{
    inClient.Print(ioOut);
    return ioOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
