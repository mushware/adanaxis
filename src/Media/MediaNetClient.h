/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaNetClient
{
public:
    MediaNetClient();
    ~MediaNetClient();

    void Connect(const string& inServer, U32 inPort);
    void Disconnect(void);

private:
    TCPsocket m_tcpSocket;    
    bool m_connected;    
    
};