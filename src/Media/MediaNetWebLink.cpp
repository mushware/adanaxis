/*
 * $Id: MediaNetWebLink.cpp,v 1.3 2002/11/07 00:53:37 southa Exp $
 * $Log: MediaNetWebLink.cpp,v $
 * Revision 1.3  2002/11/07 00:53:37  southa
 * localweb work
 *
 * Revision 1.2  2002/11/06 14:16:57  southa
 * Basic web server
 *
 * Revision 1.1  2002/11/05 18:15:17  southa
 * Web server
 *
 */

#include "MediaNetWebLink.h"

#include "MediaNetHTTP.h"
#include "MediaNetLog.h"
#include "MediaNetProtocol.h"
#include "MediaNetServer.h"
#include "MediaNetUtils.h"

#include "mushPlatform.h"

auto_ptr< CoreData<MediaNetWebLink> > CoreData<MediaNetWebLink>::m_instance;
string MediaNetWebLink::m_webPath="";

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
MediaNetWebLink::Send(istream& ioStream)
{
    vector<U8> bytes;
    while (ioStream.good() && !ioStream.eof())
    {
        U8 byte;
        ioStream.get(byte);
        bytes.push_back(byte);
    }
    Send(bytes);
}

void
MediaNetWebLink::ReceivedProcess(const string& inStr)
{
    if (inStr.substr(0,3) != "GET")
    {
        return;
    }
    string filename;
    U32 dotCount=0;
    U32 slashCount=0;
    try
    {
        for (U32 i=4; i<inStr.size(); ++i)
        {
            U8 byte=inStr[i];
            if (byte == '.')
            {
                if (dotCount > 0)
                {
                    throw(NetworkFail("Bad filename (dots)"));
                }
                ++dotCount;
                filename+=byte;
            }
            if (byte == '/')
            {
                if (slashCount > 0)
                {
                    throw(NetworkFail("Bad filename (slashes)"));
                }
                ++slashCount;
            }
            
            if (byte >= 'a' && byte <= 'z')
            {
                filename+=byte;
            }
            if (byte <= ' ')
            {
                break;
            }
        }
        if (filename == "") filename = "index.html";
        
        if (filename == "test.html")
        {
            SendTestPage();
        }
        else
        {
            // check for dynamic files
            if (m_webPath == "")
            {
                CoreEnv::Instance().VariableGetIfExists(m_webPath, "LOCALWEB_PATH");
            }
            if (m_webPath == "")
            {
                throw(NetworkFail("Path to web files (LOCALWEB_PATH) not set"));
            }
            filename = m_webPath+"/"+filename;
            SendFile(filename);
        }
    }
    catch (NetworkFail &e)
    {
        MediaNetLog::Instance().Log() << "ReceivedProcess exception: " << e.what() << endl;
        SendErrorPage(e.what());
    }
}

void
MediaNetWebLink::SendFile(const string& inFilename)
{
    ifstream fileStream(inFilename.c_str());
    if (!fileStream)
    {
        throw(NetworkFail("File not found: "+inFilename));
    }
    
    MediaNetHTTP http;
    http.Reply200();

    CoreRegExp re;
    if (re.Search(inFilename, "html$"))
    {
        http.ContentTypeHTML();
    }
    else if (re.Search(inFilename, "(jpg|jpeg)$"))
    {
        http.ContentType("image/jpeg");
    }
    else if (re.Search(inFilename, "(tif|tiff)$"))
    {
        http.ContentType("image/tiff");
    }
    else if (re.Search(inFilename, "png$"))
    {
        http.ContentType("image/png");
    }
    else if (re.Search(inFilename, "css$"))
    {
        http.ContentType("text/css");
    }
    else
    {
        throw(NetworkFail("Unknown file type: "+inFilename));
    }
        
    http.Endl();
    Send(fileStream);
    Disconnect();
}

void
MediaNetWebLink::SendTestPage(void)
{
    MediaNetHTTP http;
    http.Reply200();
    http.ContentTypeHTML();
    http.Endl();
    http.Header();


    http.Out() << "Infernal Contractor II test page";
    
    
    http.Endl();
    http.Footer();
    Send(http.ContentGet().str());
    Disconnect();
}

void
MediaNetWebLink::SendErrorPage(const string& inText)
{
    MediaNetHTTP http;
    http.Reply200();
    http.ContentTypeHTML();
    http.Endl();
    http.Header();
    http.Out() << "<p><font class=\"bigboldtitle\">Error from Mushware localweb server</font></p>";
    http.Out() << "<p>" << inText << "</p>";
    http.Out() << "<p><a target=\"_top\" href=\"/index.html\">Back to main page</a></p>";

    http.Endl();
    http.Footer();
    Send(http.ContentGet().str());
    Disconnect();
}

void
MediaNetWebLink::Print(ostream& ioOut) const
{

}
