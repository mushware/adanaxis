/*
 * $Id: MediaNetLink.h,v 1.6 2002/11/04 13:11:58 southa Exp $
 * $Log: MediaNetLink.h,v $
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

class MediaNetData;

class MediaNetLink
{
public:
    MediaNetLink(const string& inServer, U32 inPort);
    explicit MediaNetLink(TCPsocket inSocket, U32 inPort);
    ~MediaNetLink();

    void FastSend(MediaNetData& ioData);
    void ReliableSend(MediaNetData& ioData);
    bool Receive(MediaNetData * & outData);
    
    void LinkChecksSend(void);

    void MessageHandle(U32 inType, MediaNetData& ioData);

    void LinkInfoLog(void) const;
    void Print(ostream& ioOut) const;
    
private:
    enum tLinkState
    {
        kLinkStateInvalid,
        kLinkStateNotMade,
        kLinkStateUntested,
        kLinkStateIdle,
        kLinkStateDead
    };

    enum tLinkCheckState
    {
        kLinkCheckStateInvalid,
        kLinkCheckStateIdle,
        kLinkCheckStateAwaitingReply
    };

    class LinkState
    {
    public:
        U32 linkCheckTime;
        tLinkState linkState;
        tLinkCheckState linkCheckState;
        U32 linkPingTime;
        MediaNetData linkData;
        U8 linkCheckSeqNum;
    };

    void Initialise(void);
    void TCPConnect(const string& inServer, U32 inPort);
    void UDPConnect(U32 inPort);
    void TCPSocketTake(TCPsocket inSocket);
    void Disconnect(void);
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
    
    LinkState m_tcpState;
    LinkState m_udpState;
    MediaNetClient m_client;
    U32 m_currentMsec;
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
    ioOut << "linkCheckSeqNum=" << static_cast<U32>(inLinkState.linkCheckSeqNum) << "]";
    return ioOut;
}
