/*
 * $Id: MediaNetClient.h,v 1.1 2002/10/31 16:41:33 southa Exp $
 * $Log: MediaNetClient.h,v $
 * Revision 1.1  2002/10/31 16:41:33  southa
 * Network client
 *
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaNetClient
{
public:
    MediaNetClient();
    ~MediaNetClient();

    void Connect(const string& inServer, U32 inPort);
    void SocketTake(TCPsocket inSocket);
    void Disconnect(void);

private:
    TCPsocket m_tcpSocket;
    IPaddress m_remoteIP;
    string m_remoteName;
    bool m_connected;
};