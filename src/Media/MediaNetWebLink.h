/*
 * $Id: MediaNetWebLink.h,v 1.1 2002/11/05 18:15:18 southa Exp $
 * $Log: MediaNetWebLink.h,v $
 * Revision 1.1  2002/11/05 18:15:18  southa
 * Web server
 *
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaNetWebLink
{
public:
    MediaNetWebLink(TCPsocket inSocket, U32 inPort);
    ~MediaNetWebLink();

    void Tick(void);
    bool IsDead(void);
    void Disconnect(void);
    bool Receive(string& outStr);
    void Send(vector<U8>& inBytes);
    void Send(const string& inStr);
    void SendTestPage(void);
    void ReceivedProcess(const string& inStr);

    void Print(ostream& ioOut) const;

private:
    enum tLinkState
    {
        kLinkStateNew,
        kLinkStateSending,
        kLinkStateDone
    };

    enum
    {
        kLinkLifetime=5000, // Times in msec
        kTimeoutIdle=30000,
    };

    tLinkState m_linkState;
    TCPsocket m_tcpSocket;
    U32 m_currentMsec;
    U32 m_lastAccessMsec;
    U32 m_linkErrors;
    bool m_isDead;
};

inline ostream&
operator<<(ostream &ioOut, const MediaNetWebLink& inLink)
{
    inLink.Print(ioOut);
    return ioOut;
}
