/*
 * $Id: MediaNetLink.h,v 1.1 2002/10/31 19:55:54 southa Exp $
 * $Log: MediaNetLink.h,v $
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
    explicit MediaNetLink(TCPsocket inSocket);
    ~MediaNetLink();

    void SendTCP(MediaNetData& ioData);
    void ReceiveTCP(MediaNetData& outData);

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
    void Connect(const string& inServer, U32 inPort);
    void SocketTake(TCPsocket inSocket);
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
