/*
 * $Id: MediaNetWebServer.cpp,v 1.2 2002/11/06 14:16:57 southa Exp $
 * $Log: MediaNetWebServer.cpp,v $
 * Revision 1.2  2002/11/06 14:16:57  southa
 * Basic web server
 *
 * Revision 1.1  2002/11/05 18:15:18  southa
 * Web server
 *
 */

#include "MediaNetWebServer.h"

#include "MediaNet.h"
#include "MediaNetLog.h"
#include "MediaNetWebLink.h"

#include "mushPlatform.h"

auto_ptr<MediaNetWebServer> MediaNetWebServer::m_instance;

MediaNetWebServer::MediaNetWebServer() :
m_linkCtr(0),
m_serving(false)
{
}

void
MediaNetWebServer::Connect(U32 inPort)
{
    if (m_serving)
    {
        Disconnect();
    }
    
    m_serverPort=inPort;

    MediaNet::Instance();

    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, NULL, inPort) == -1)
    {
        ostringstream message;
        message << "Server creation failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }

    m_tcpSocket=SDLNet_TCP_Open(&ip);

    if (m_tcpSocket == NULL)
    {
        ostringstream message;
        message << "Server creation failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }

    MediaNetLog::Instance().Log() << "Created web server on port " << inPort << endl;
    m_serving=true;
}

void
MediaNetWebServer::Disconnect(void)
{
    if (m_serving)
    {
        SDLNet_TCP_Close(m_tcpSocket);
        m_tcpSocket = NULL;
        m_serving=false;
    }
}
        
MediaNetWebServer::~MediaNetWebServer()
{
    MediaNetLog::Instance().Log() << "Closing web server" << endl;
    // Close all of the links first
    CoreData<MediaNetWebLink>::Instance().Clear();
    SDLNet_TCP_Close(m_tcpSocket);
    MediaNetLog::Instance().Log() << "Closed web server" << endl;
}

void
MediaNetWebServer::Accept(void)
{
    if (m_serving)
    {
        COREASSERT(m_tcpSocket != NULL);
        TCPsocket newSocket=SDLNet_TCP_Accept(m_tcpSocket);
        if (newSocket != NULL)
        {
            ostringstream name;
            name << "web" << m_linkCtr;
            CoreData<MediaNetWebLink>::Instance().DataGive(name.str(), new MediaNetWebLink(newSocket, m_serverPort));
            m_linkCtr++;
            MediaNetLog::Instance().Log() << "Accepted web connection " << name.str() << endl;
        }
    }
}

bool
MediaNetWebServer::IsConnected(void) const
{
    return m_serving;
}

