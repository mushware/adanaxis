#ifndef MEDIANETLINK_H
#define MEDIANETLINK_H
/*
 * $Id: MediaNetLink.h,v 1.15 2002/11/27 16:35:10 southa Exp $
 * $Log: MediaNetLink.h,v $
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

#include "mushCore.h"

#include "MediaNetAddress.h"
#include "MediaNetClient.h"
#include "MediaNetData.h"
#include "MediaNetProtocol.h"
#include "MediaSDL.h"

class MediaNetAddress;

class MediaNetLink
{
public:
    MediaNetLink(const string& inServer, U32 inPort);
    explicit MediaNetLink(const MediaNetAddress& inAddress);
    explicit MediaNetLink(TCPsocket inSocket, U32 inPort);
    ~MediaNetLink();

    void FastSend(MediaNetData& ioData);
    void ReliableSend(MediaNetData& ioData);
    bool UDPIfAddressMatchReceive(bool& outTakeMessage, MediaNetData& ioData);
    bool Receive(MediaNetData * & outData);
    void Tick(void);
    bool IsDead(void);
    void Disconnect(MediaNetProtocol::tReasonCode inCode);
        
    void LinkChecksSend(void);

    void MessageHandle(U32 inType, MediaNetData& ioData);

    const string& TargetNameGet(void) const { return m_targetName; }
    U32 TCPTargetIPGet(void) const { return m_client.RemoteIPGet(); }
    U32 TCPTargetPortGet(void) const { return m_client.TCPRemotePortGet(); }
    MediaNetAddress TCPTargetAddressGet(void) const { return MediaNetAddress(m_client.RemoteIPGet(), m_client.TCPRemotePortGet()); }
    U32 UDPTargetIPGet(void) const { return m_client.RemoteIPGet(); }
    U32 UDPTargetPortGet(void) const { return m_client.UDPRemotePortGet(); }
    U32 CreationMsecGet(void) const { return m_creationMsec; }
    
    void LinkInfoLog(void) const;
    void Print(ostream& ioOut) const;
    void WebStatusPrint(ostream& ioOut) const;

    static string NextLinkNameTake(void);
    
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
        kLinkCheckDeadTime=500, // Time after sending link check when we can't send another
        kLinkInitTimeoutMsec=6000, // Timeout to kill link if not up for send
        kLinkIdleTimeoutMsec=35000, // Timeout to disconnect if no activity
        kErrorTotalLimit=100,
        kErrorsSinceGoodLimit=4
    };
    
    class LinkState
    {
    public:
        U32 linkCheckTime;
        tLinkState linkState;
        tLinkCheckState linkCheckState;
        U32 linkPingTime;
        U32 linkErrorsSinceGood;
        U32 linkErrorTotal;
        U32 linkSendCtr;
        U32 linkReceiveCtr;
        MediaNetData linkData;
        U8 linkCheckSeqNum;
    };

    void Initialise(void);
    void TCPConnect(const string& inServer, U32 inPort);
    void UDPConnect(U32 inPort);
    void TCPSocketTake(TCPsocket inSocket);
    void TCPLinkCheckSend(void);
    void UDPLinkCheckSend(void);
    bool LinkIsUpForSend(tLinkState inState);
    bool LinkIsUpForReceive(tLinkState inState);
    bool LinkDeathCheck(LinkState& ioLinkState);

    void TCPSend(MediaNetData& inData);
    void TCPReceive(MediaNetData& outData);
    void UDPSend(MediaNetData& inData);
    void UDPReceive(MediaNetData& outData);

    void MessageTCPLinkCheckHandle(MediaNetData& ioData);
    void MessageTCPLinkCheckReplyHandle(MediaNetData& ioData);
    void MessageUDPLinkCheckHandle(MediaNetData& ioData);
    void MessageUDPLinkCheckReplyHandle(MediaNetData& ioData);
    void MessageKillLinkHandle(MediaNetData& ioData);

    static string LinkStateToBG(const LinkState& inLinkState);

    LinkState m_tcpState;
    LinkState m_udpState;
    MediaNetClient m_client;
    U32 m_currentMsec;
    U32 m_creationMsec;
    U32 m_lastActivityMsec;
    
    string m_targetName; // This should be exactly what the caller asked for

    bool m_targetIsServer;
    bool m_udpUseServerPort;
    mutable bool m_loggedLinkInfo;

    static U32 m_linkNameNum;
};

inline ostream&
operator<<(ostream &ioOut, const MediaNetLink& inLink)
{
    inLink.Print(ioOut);
    return ioOut;
}

inline ostream&
operator<<(ostream &ioOut, const MediaNetLink::LinkState& inLinkState)
{
    ioOut << "[linkCheckTime=" << inLinkState.linkCheckTime << ", ";
    ioOut << "linkState=" << inLinkState.linkState << ", ";
    ioOut << "linkCheckState=" << inLinkState.linkCheckState << ", ";
    ioOut << "linkPingTime=" << inLinkState.linkPingTime << ", ";
    ioOut << "linkErrorsSinceGood=" << inLinkState.linkErrorsSinceGood << ", ";
    ioOut << "linkErrorTotal=" << inLinkState.linkErrorTotal << ", ";
    ioOut << "linkSendCtr=" << inLinkState.linkSendCtr << ", ";
    ioOut << "linkReceiveCtr=" << inLinkState.linkReceiveCtr << ", ";
    ioOut << "linkCheckSeqNum=" << static_cast<U32>(inLinkState.linkCheckSeqNum) << "]";
    return ioOut;
}
#endif
