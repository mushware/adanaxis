/*
 * $Id: MediaNetWebServer.h,v 1.1 2002/11/05 18:15:19 southa Exp $
 * $Log: MediaNetWebServer.h,v $
 * Revision 1.1  2002/11/05 18:15:19  southa
 * Web server
 *
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaNetData;

class MediaNetWebServer
{
public:
    ~MediaNetWebServer();

    static MediaNetWebServer& Instance(void);

    void Connect(U32 inPort);
    void Disconnect(void);
    void Accept(void);
    bool IsConnected(void) const;
    
protected:
    MediaNetWebServer();

private:
    TCPsocket m_tcpSocket;
    U32 m_serverPort;
    U32 m_linkCtr;
    bool m_serving;

    static auto_ptr<MediaNetWebServer> m_instance;
};

inline  MediaNetWebServer&
MediaNetWebServer::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MediaNetWebServer);
    return *m_instance;
}
