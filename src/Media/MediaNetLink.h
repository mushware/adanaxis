/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "MediaSDL.h"
#include "MediaNetClient.h"

class MediaNetLink
{
public:
    MediaNetLink(const string& inServer, U32 inPort);
    explicit MediaNetLink(TCPsocket inSocket);
    ~MediaNetLink();
    
private:
    enum tLinkState
    {
        kLinkStateInvalid,
        kLinkStateUntested,
        kLinkStateAwaitingLinkCheck,
        kLinkStateIdle
    };
    void Connect(const string& inServer, U32 inPort);
    void SocketTake(TCPsocket inSocket);
    void RequestLinkCheck(void);
    
    tLinkState m_state;
    MediaNetClient m_client;
    bool m_targetIsServer;
};
