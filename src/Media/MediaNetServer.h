/*
 * $Id: MediaNetServer.h,v 1.1 2002/10/31 15:52:15 southa Exp $
 * $Log: MediaNetServer.h,v $
 * Revision 1.1  2002/10/31 15:52:15  southa
 * First network code
 *
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
        TCPsocket remoteSocket;
        IPaddress remoteIP;
    };
        
    TCPsocket m_tcpSocket;
    vector<ClientDef> m_clients;
};

