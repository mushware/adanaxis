/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaNetServer
{
public:
    explicit MediaNetServer(U32 inPort);
    ~MediaNetServer();

    void Accept(void);
    
private:
    class ClientDef
    {
    public:
        IPaddress remoteIP;
    };
        
    TCPsocket m_tcpSocket;
    vector<ClientDef> m_clients;
};

