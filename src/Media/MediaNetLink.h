/*
 * $Id: MediaNetLink.h,v 1.2 2002/11/01 16:15:27 southa Exp $
 * $Log: MediaNetLink.h,v $
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

    void Print(ostream& ioOut) const;
    
private:
    enum tLinkState
    {
        kLinkStateInvalid,
        kLinkStateNotMade,
        kLinkStateUntested,
        kLinkStateAwaitingLinkCheck,
        kLinkStateIdle,
        kLinkStateDead
    };
    void TCPConnect(const string& inServer, U32 inPort);
    void UDPConnect(U32 inPort);
    void TCPSocketTake(TCPsocket inSocket);
    void RequestLinkCheck(void);
    bool LinkIsUp(tLinkState inState);

    tLinkState m_tcpState;
    tLinkState m_udpState;
    MediaNetClient m_client;
    bool m_targetIsServer;
};

inline ostream&
operator<<(ostream &ioOut, const MediaNetLink& inLink)
{
    inLink.Print(ioOut);
    return ioOut;
}
