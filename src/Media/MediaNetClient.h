/*
 * $Id: MediaNetClient.h,v 1.4 2002/11/01 18:46:25 southa Exp $
 * $Log: MediaNetClient.h,v $
 * Revision 1.4  2002/11/01 18:46:25  southa
 * UDP Links
 *
 * Revision 1.3  2002/11/01 16:15:27  southa
 * Network send and receive
 *
 * Revision 1.2  2002/10/31 19:55:54  southa
 * Network links
 *
 * Revision 1.1  2002/10/31 16:41:33  southa
 * Network client
 *
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaNetData;

class MediaNetClient
{
public:
    MediaNetClient();
    ~MediaNetClient();

    void TCPConnect(const string& inServer, U32 inPort);
    void TCPSocketTake(TCPsocket inSocket);
    void UDPConnect(U32 inPort);
    void TCPDisconnect(void);
    void UDPDisconnect(void);

    void TCPSend(MediaNetData& inData);
    void TCPReceive(MediaNetData& inData);
    void UDPSend(MediaNetData& inData);
    void UDPReceive(MediaNetData& inData);

    U32 UDPRemotePortGet(void) { return m_udpRemotePort; }
    void UDPRemotePortSet(U32 inPort);
    U32 UDPRemoteIPGet(void) { return m_remoteIP; }
    void Print(ostream& ioOut) const;
    
private:
    void ResolveTargetName(void);

    TCPsocket m_tcpSocket;
    UDPsocket m_udpSocket;
    U32 m_udpLocalPort;
    U32 m_remoteIP;
    U32 m_tcpRemotePort;
    U32 m_udpRemotePort;
    string m_remoteName;
    bool m_tcpConnected;
    bool m_udpConnected;
};

inline ostream&
operator<<(ostream &ioOut, const MediaNetClient& inClient)
{
    inClient.Print(ioOut);
    return ioOut;
}
