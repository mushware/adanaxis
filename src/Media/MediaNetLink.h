#ifndef MEDIANETLINK_H
#define MEDIANETLINK_H
/*
 * $Id: MediaNetLink.h,v 1.9 2002/11/20 22:35:27 southa Exp $
 * $Log: MediaNetLink.h,v $
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

#include "MediaSDL.h"
#include "MediaNetClient.h"
#include "MediaNetData.h"
#include "MediaNetProtocol.h"

class MediaNetLink
{
public:
    MediaNetLink(const string& inServer, U32 inPort);
    explicit MediaNetLink(TCPsocket inSocket, U32 inPort);
    ~MediaNetLink();

    void FastSend(MediaNetData& ioData);
    void ReliableSend(MediaNetData& ioData);
    bool Receive(MediaNetData * & outData);
    void Tick(void);
    bool IsDead(void);
    void Disconnect(MediaNetProtocol::tReasonCode inCode);
        
    void LinkChecksSend(void);

    void MessageHandle(U32 inType, MediaNetData& ioData);

    const string& TargetNameGet(void) const { return m_targetName; }
    U32 TargetPortGet(void) const { return m_targetPort; }
    
    void LinkInfoLog(void) const;
    void Print(ostream& ioOut) const;
    void WebStatusPrint(ostream& ioOut) const;
    
private:
    enum tLinkState
    {
        kLinkStateInvalid,
        kLinkStateNotMade,
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
    bool LinkIsUp(tLinkState inState);

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
    static bool LinkDeathCheck(LinkState& ioLinkState);

    LinkState m_tcpState;
    LinkState m_udpState;
    MediaNetClient m_client;
    U32 m_currentMsec;
    
    string m_targetName; // These should be exactly what the caller asked for
    U32 m_targetPort;

    bool m_targetIsServer;
    bool m_udpUseServerPort;
    mutable bool m_loggedLinkInfo;
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
