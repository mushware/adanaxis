#ifndef MEDIANETSERVER_H
#define MEDIANETSERVER_H
/*
 * $Id: MediaNetServer.h,v 1.9 2002/11/23 14:39:06 southa Exp $
 * $Log: MediaNetServer.h,v $
 * Revision 1.9  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.8  2002/11/22 15:00:33  southa
 * Network connection handling
 *
 * Revision 1.7  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.6  2002/11/20 22:35:28  southa
 * Multiplayer setup
 *
 * Revision 1.5  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.4  2002/11/01 18:46:26  southa
 * UDP Links
 *
 * Revision 1.3  2002/10/31 19:55:54  southa
 * Network links
 *
 * Revision 1.2  2002/10/31 16:41:33  southa
 * Network client
 *
 * Revision 1.1  2002/10/31 15:52:15  southa
 * First network code
 *
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaNetData;

class MediaNetServer
{
public:
    ~MediaNetServer();

    static MediaNetServer& Instance(void);

    void Connect(U32 inPort);
    void Disconnect(void);
    void Accept(void);
    void UDPSend(U32 inHost, U32 inPort, MediaNetData& inData);
    void UDPReceive(MediaNetData& inData);
    void UDPHarvest(void);
    void UDPDiscard(void);
    bool IsServing(void) const { return m_serving; }
    U32 ServerPortHostOrderGet(void) const { return m_serverPortHostOrder; }
    
protected:
    MediaNetServer();
    
private:
    TCPsocket m_tcpSocket;
    UDPsocket m_udpSocket;
    U32 m_serverPortHostOrder;
    U32 m_linkCtr;
    bool m_serving;

    static auto_ptr<MediaNetServer> m_instance;
};

inline  MediaNetServer&
MediaNetServer::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MediaNetServer);
    return *m_instance;
}
#endif
