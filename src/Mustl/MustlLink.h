#ifndef MUSTLLINK_H
#define MUSTLLINK_H
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
 * $Id: MustlLink.h,v 1.6 2002/12/20 13:17:46 southa Exp $
 * $Log: MustlLink.h,v $
 * Revision 1.6  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/12/14 15:04:34  southa
 * Mustl fixes
 *
 * Revision 1.4  2002/12/13 19:03:05  southa
 * Mustl interface cleanup
 *
 * Revision 1.3  2002/12/13 01:06:54  southa
 * Mustl work
 *
 * Revision 1.2  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:26  southa
 * Created Mustl
 *
 * Revision 1.22  2002/12/10 20:38:06  southa
 * Server timing
 *
 * Revision 1.21  2002/12/09 23:59:59  southa
 * Network control
 *
 * Revision 1.20  2002/12/09 16:18:00  southa
 * Link ID transfer
 *
 * Revision 1.19  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.18  2002/12/05 13:20:13  southa
 * Client link handling
 *
 * Revision 1.17  2002/11/28 18:05:36  southa
 * Print link ages
 *
 * Revision 1.16  2002/11/28 15:14:14  southa
 * Multiplayer setup timing
 *
 * Revision 1.15  2002/11/27 16:35:10  southa
 * Client and server image handling
 *
 * Revision 1.14  2002/11/27 13:23:27  southa
 * Server and client data exchange
 *
 * Revision 1.13  2002/11/22 18:02:43  southa
 * Wait for TCP connection
 *
 * Revision 1.12  2002/11/22 15:33:59  southa
 * More network logging
 *
 * Revision 1.11  2002/11/22 15:00:33  southa
 * Network connection handling
 *
 * Revision 1.10  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.9  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.8  2002/11/04 19:34:46  southa
 * Network link maintenance
 *
 * Revision 1.7  2002/11/04 15:50:31  southa
 * Network log
 *
 * Revision 1.6  2002/11/04 13:11:58  southa
 * Link setup work
 *
 * Revision 1.5  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.4  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.3  2002/11/01 18:46:26  southa
 * UDP Links
 *
 * Revision 1.2  2002/11/01 16:15:27  southa
 * Network send and receive
 *
 * Revision 1.1  2002/10/31 19:55:54  southa
 * Network links
 *
 */

#include "MustlAddress.h"
#include "MustlClient.h"
#include "MustlData.h"
#include "MustlProtocol.h"
#include "MustlStandard.h"

class MustlID;

class MustlLink
{
public:
    MustlLink(const MustlID& inID, const MustlAddress& inAddress);
    MustlLink(Mustl::tSocket inSocket, const MustlAddress& inAddress);
    ~MustlLink();

    void InactivityTimerReset(void);
    void FastSend(MustlData& ioData);
    void ReliableSend(MustlData& ioData);
    bool UDPAddressMatchDoes(const MustlData& ioData) const;
    bool UDPHostMatchDoes(const MustlData& ioData) const;

    bool Receive(MustlData *& outData);
    void Tick(void);
    bool IsDead(void);
    bool ReadyIs(void) const;
    bool TargetServerIs(void) const { return m_targetIsServer; }
    void Disconnect(MustlProtocol::tReasonCode inCode);
    void MessageHandle(Mustl::U32 inType, MustlData& ioData);
    
    bool NetIDExists(void) const { return m_netID != NULL; }
    const MustlID& NetIDGet(void) const;
    void NetIDSet(const MustlID& inID);
    
    const MustlAddress& TCPAddressGet(void) const { return m_client.TCPAddressGet(); }
    const MustlAddress& UDPAddressGet(void) const { return m_client.UDPAddressGet(); }

    Mustl::tMsec CreationMsecGet(void) const { return m_creationMsec; }
    
    void Print(std::ostream& ioOut) const;
    void WebStatusPrint(std::ostream& ioOut) const;

    static void WebStatusHeaderPrint(std::ostream& ioOut);
    static std::string NextLinkNameTake(void);

private:
    enum tLinkState
    {
        kLinkStateInvalid,
        kLinkStateNotMade,
        kLinkStateWaitingForPort,
        kLinkStateConnecting,
        kLinkStateUntested,
        kLinkStateTesting,
        kLinkStateIdle,
        kLinkStateDead
    };

    enum tLinkCheckState
    {
        kLinkCheckStateInvalid,
        kLinkCheckStateIdle,
        kLinkCheckStateAwaitingReply
    };

    enum
    {
        kTCPFastLinkCheckPeriod=5000, // Times in msec
        kTCPSlowLinkCheckPeriod=31020,
        kUDPFastLinkCheckPeriod=1000, // Times in msec
        kUDPSlowLinkCheckPeriod=30000,
        kIDRequestPeriod=1000, // Time between requests for ID transfer
        kLinkInitTimeoutMsec=6000, // Timeout to kill link if not up for send
        kLinkIdleTimeoutMsec=35000, // Timeout to disconnect if no activity
        kErrorTotalLimit=10,
        kErrorsSinceGoodLimit=4
    };
    
    class LinkState
    {
    public:
        Mustl::tMsec linkCheckMsec;
        tLinkState linkState;
        tLinkCheckState linkCheckState;
        Mustl::tMsec linkPingMsec;
        Mustl::U32 linkErrorsSinceGood;
        Mustl::U32 linkErrorTotal;
        Mustl::U32 linkSendCtr;
        Mustl::U32 linkReceiveCtr;
        MustlData linkData;
        Mustl::U8 linkCheckSeqNum;
    };

    void Initialise(void);
    void TCPConnect(const MustlAddress& inAddress);
    void UDPConnect(const MustlAddress& inAddress);
    void TCPSocketTake(Mustl::tSocket inSocket, const MustlAddress& inAddress);
    void LinkChecksSend(void);
    void TCPLinkCheckSend(void);
    void TCPLinkCheckAppend(MustlData& ioData);
    void UDPLinkCheckSend(void);
    void UDPLinkCheckAppend(MustlData& ioData);
    void IDRequestSend(void);
    bool LinkIsUpForSend(tLinkState inState);
    bool LinkIsUpForReceive(tLinkState inState);
    bool LinkDeathCheck(LinkState& ioLinkState);
    bool TCPConnectingCheck(void);
    void TCPLinkEnteredIdle(void);
    void UDPLinkEnteredIdle(void);
    void TCPSend(MustlData& inData);
    void TCPReceive(MustlData& outData);
    void UDPSend(MustlData& inData);
    void UDPReceive(MustlData& outData);

    void MessageTCPLinkCheckHandle(MustlData& ioData);
    void MessageTCPLinkCheckReplyHandle(MustlData& ioData);
    void MessageUDPLinkCheckHandle(MustlData& ioData);
    void MessageUDPLinkCheckReplyHandle(MustlData& ioData);
    void MessageKillLinkHandle(MustlData& ioData);
    void MessageIDRequestHandle(MustlData& ioData);

    void LinkInfoLog(void) const;

    static std::string LinkStateToBG(const LinkState& inLinkState);

    LinkState m_tcpState;
    LinkState m_udpState;
    MustlClient m_client;
    Mustl::tMsec m_creationMsec;
    Mustl::tMsec m_lastActivityMsec;
    Mustl::tMsec m_lastIDRequestMsec;
    
    MustlID *m_netID;

    bool m_syncedID;
    bool m_targetIsServer;
    bool m_udpUseServerPort;

    mutable Mustl::tMsec m_currentMsec;
    mutable bool m_loggedLinkInfo;

    static Mustl::U32 m_linkNameNum;
};

inline bool
MustlLink::UDPAddressMatchDoes(const MustlData& ioData) const
{
    return ioData.SourceGet() == UDPAddressGet();
}

inline bool
MustlLink::UDPHostMatchDoes(const MustlData& ioData) const
{
    return ioData.SourceGet().HostGetNetworkOrder() == UDPAddressGet().HostGetNetworkOrder();
}

inline std::ostream&
operator<<(std::ostream &ioOut, const MustlLink& inLink)
{
    inLink.Print(ioOut);
    return ioOut;
}
#endif
