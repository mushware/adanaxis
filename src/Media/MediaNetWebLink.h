/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaNetWebLink
{
public:
    MediaNetWebLink(TCPsocket inSocket, U32 inPort);
    ~MediaNetWebLink();

    void Disconnect(void);
    void Tick(void);
    bool IsDead(void);
    bool Receive(string& outStr);
    void Send(vector<U8>& inBytes);

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
    };

    tLinkState m_linkState;
    TCPsocket m_tcpSocket;
    U32 m_currentMsec;
};

inline ostream&
operator<<(ostream &ioOut, const MediaNetWebLink& inLink)
{
    inLink.Print(ioOut);
    return ioOut;
}
