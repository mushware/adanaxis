/*
 * $Id: MediaNetLink.h,v 1.3 2002/11/01 18:46:26 southa Exp $
 * $Log: MediaNetLink.h,v $
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

class MediaNetData;

class MediaNetLink
{
public:
    MediaNetLink(const string& inServer, U32 inPort);
    explicit MediaNetLink(TCPsocket inSocket, U32 inPort);
    ~MediaNetLink();

    void TCPSend(MediaNetData& inData);
    void TCPReceive(MediaNetData& inData);
    void UDPSend(MediaNetData& inData);
    void UDPReceive(MediaNetData& inData);

    void RequestLinkChecks(void);
        
    void Print(ostream& ioOut) const;
    
private:
    enum tLinkState
    {
        kLinkStateInvalid,
        kLinkStateNotMade,
        kLinkStateUntested,
        kLinkStateIdle,
        kLinkStateDead,
        kLinkStateUseServer
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
        U8 linkCheckSeqNum;
    };

    void Initialise(void);
    void TCPConnect(const string& inServer, U32 inPort);
    void UDPConnect(U32 inPort);
    void TCPSocketTake(TCPsocket inSocket);
    void RequestLinkCheck(void);
    void BuildLinkCheck(MediaNetData& outData, LinkState& ioState);
    bool LinkIsUp(tLinkState inState);

    LinkState m_tcpState;
    LinkState m_udpState;
    MediaNetClient m_client;
    U32 m_currentMsec;
    bool m_targetIsServer;
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
