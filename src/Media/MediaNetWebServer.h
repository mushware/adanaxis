/*
 * $Id$
 * $Log$
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
    void Accept(void);

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
