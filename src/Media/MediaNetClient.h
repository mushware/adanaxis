/*
 * $Id: MediaNetClient.h,v 1.2 2002/10/31 19:55:54 southa Exp $
 * $Log: MediaNetClient.h,v $
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

    void Connect(const string& inServer, U32 inPort);
    void SocketTake(TCPsocket inSocket);
    void Disconnect(void);

    void SendTCP(MediaNetData& inData);
    void ReceiveTCP(MediaNetData& inData);

    void Print(ostream& ioOut) const;
    
private:
    void ResolveTargetName(void);

    TCPsocket m_tcpSocket;
    IPaddress m_remoteIP;
    string m_remoteName;
    bool m_connected;
};

inline ostream&
operator<<(ostream &ioOut, const MediaNetClient& inClient)
{
    inClient.Print(ioOut);
    return ioOut;
}
