#ifndef MEDIANETCLIENT_H
#define MEDIANETCLIENT_H
/*
 * $Id: MediaNetClient.h,v 1.10 2002/11/23 14:39:05 southa Exp $
 * $Log: MediaNetClient.h,v $
 * Revision 1.10  2002/11/23 14:39:05  southa
 * Store ports in network order
 *
 * Revision 1.9  2002/11/22 18:02:43  southa
 * Wait for TCP connection
 *
 * Revision 1.8  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.7  2002/11/05 18:15:17  southa
 * Web server
 *
 * Revision 1.6  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.5  2002/11/03 18:43:09  southa
 * Network fixes
 *
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

    U32 TCPRemotePortGet(void) const { return m_tcpRemotePort; }

    bool TCPConnectionCompleted(void);
    void ResolveTargetName(void);
    bool UDPConnectedGet(void) const { return m_udpConnected; }
    U32 UDPRemotePortGet(void) const { return m_udpRemotePort; }
    void UDPRemotePortNetworkOrderSet(U32 inPort);
    U32 RemoteIPGet(void) const { return m_remoteIP; }
    void Print(ostream& ioOut) const;
    
private:

    TCPsocket m_tcpSocket;
    UDPsocket m_udpSocket;
    U32 m_udpLocalPort;
    U32 m_remoteIP;
    U32 m_tcpRemotePort;
    U32 m_udpRemotePort;
    bool m_tcpConnected;
    bool m_udpConnected;
};

inline ostream&
operator<<(ostream &ioOut, const MediaNetClient& inClient)
{
    inClient.Print(ioOut);
    return ioOut;
}
#endif
