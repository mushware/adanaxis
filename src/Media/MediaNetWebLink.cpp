/*
 * $Id$
 * $Log$
 */

#include "MediaNetWebLink.h"

#include "MediaNetLog.h"
#include "MediaNetProtocol.h"
#include "MediaNetServer.h"
#include "MediaNetUtils.h"

#include "mushPlatform.h"

auto_ptr< CoreData<MediaNetWebLink> > CoreData<MediaNetWebLink>::m_instance;

MediaNetWebLink::MediaNetWebLink(TCPsocket inSocket, U32 inPort)
{
    // I am the server end of the link
    try
    {
        m_tcpSocket = inSocket;
        PlatformNet::SocketNonBlockingSet(m_tcpSocket->channel);
    }
    catch (...)
    {
        SDLNet_TCP_Close(inSocket);
        throw;
    }
    m_linkState=kLinkStateNew;
}

MediaNetWebLink::~MediaNetWebLink()
{
    try
    {
        Disconnect();
    }
    catch (exception& e)
    {
        MediaNetLog::Instance().Log() << "~MediaNetWebLink exception: " << e.what() << endl;
    }
}

void
MediaNetWebLink::Disconnect(void)
{
}
 

void
MediaNetWebLink::Tick(void)
{
    m_currentMsec=SDL_GetTicks();
}

bool
MediaNetWebLink::IsDead(void)
{
    return 0;
}

bool
MediaNetWebLink::Receive(string& outStr)
{
    U8 byte='-';
    int result;
    outStr="";
    do
    {
        result=SDLNet_TCP_Recv(m_tcpSocket, &byte, 1);

        if (result == 1)
        {
            if (byte == 0xa) break;
            if (byte >= 32)
            {
                outStr += byte;
            }
        }
    } while (result > 0);
    return (outStr.size() != 0);
}

void
MediaNetWebLink::Send(vector<U8>& inBytes)
{
    int result=SDLNet_TCP_Send(m_tcpSocket, &inBytes[0], inBytes.size());
    if (result >= 0 && static_cast<U32>(result) != inBytes.size())
    {
        throw(NetworkFail(string("Failed to send data on WebLink: ")+SDLNet_GetError()));
    }
}

void
MediaNetWebLink::Print(ostream& ioOut) const
{

}
