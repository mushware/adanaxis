/*
 * $Id: MediaNetWebLink.cpp,v 1.1 2002/11/05 18:15:17 southa Exp $
 * $Log: MediaNetWebLink.cpp,v $
 * Revision 1.1  2002/11/05 18:15:17  southa
 * Web server
 *
 */

#include "MediaNetWebLink.h"

#include "MediaNetLog.h"
#include "MediaNetProtocol.h"
#include "MediaNetServer.h"
#include "MediaNetUtils.h"

#include "mushPlatform.h"

auto_ptr< CoreData<MediaNetWebLink> > CoreData<MediaNetWebLink>::m_instance;

MediaNetWebLink::MediaNetWebLink(TCPsocket inSocket, U32 inPort) :
    m_linkErrors(0),
    m_isDead(false)
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
    m_currentMsec=SDL_GetTicks();
    m_lastAccessMsec=m_currentMsec;
}

MediaNetWebLink::~MediaNetWebLink()
{
    MediaNetLog::Instance().Log() << "Closing web link" << endl;
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
    if (m_tcpSocket != NULL)
    {
        SDLNet_TCP_Close(m_tcpSocket);
        m_tcpSocket=NULL;
    }
    m_isDead = true;
}

void
MediaNetWebLink::Tick(void)
{
    m_currentMsec=SDL_GetTicks();
}

bool
MediaNetWebLink::IsDead(void)
{
    m_currentMsec=SDL_GetTicks();
    if (m_isDead || m_currentMsec > m_lastAccessMsec + kTimeoutIdle)
    {
        return true;
    }
    return (false);
}

bool
MediaNetWebLink::Receive(string& outStr)
{
    if (m_isDead) return false;
    
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
    if (m_isDead)
    {
        throw(NetworkFail("Attempt to send on dead WebLink"));
    }
    int result=SDLNet_TCP_Send(m_tcpSocket, &inBytes[0], inBytes.size());
    if (result >= 0 && static_cast<U32>(result) != inBytes.size())
    {
        MediaNetLog::Instance().Log() << "Failed to send data on WebLink: " << SDLNet_GetError();
        ++m_linkErrors;
    }
}


void
MediaNetWebLink::Send(const string& inStr)
{
MediaNetLog::Instance().Log() << "sending " << MediaNetUtils::MakePrintable(inStr) << endl; 
    vector<U8> bytes;
    U32 size=inStr.size();
    bytes.resize(size);
    for (U32 i=0; i<size; ++i)
    {
        bytes[i]=inStr[i];
    }
    Send(bytes);
}

void
MediaNetWebLink::ReceivedProcess(const string& inStr)
{
    if(inStr.substr(0,3) == "GET")
    {
        SendTestPage();
    }
}

void
MediaNetWebLink::SendTestPage(void)
{
    string eolStr;
    eolStr += (U8)0xd;
    eolStr += (U8)0xa;
    
    ostringstream page;
    page << "HTTP/1.1 200 OK" << eolStr;
    page << "Content-Type: text/html" << eolStr;
    page << eolStr;
    page << "<html><head><title>ic2 configuration page</title></head>" << eolStr;
    page << "<body>Infernal contractor II configuration page</body></html>" << eolStr;
    Send(page.str());
    Disconnect();
}

void
MediaNetWebLink::Print(ostream& ioOut) const
{

}
