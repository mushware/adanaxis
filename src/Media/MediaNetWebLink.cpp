/*
 * $Id: MediaNetWebLink.cpp,v 1.10 2002/11/14 11:40:28 southa Exp $
 * $Log: MediaNetWebLink.cpp,v $
 * Revision 1.10  2002/11/14 11:40:28  southa
 * Configuration handling
 *
 * Revision 1.9  2002/11/12 18:02:13  southa
 * POST handling and handlepostvalues command
 *
 * Revision 1.8  2002/11/12 17:05:01  southa
 * Tidied localweb server
 *
 * Revision 1.7  2002/11/12 11:49:22  southa
 * Initial MHTML processing
 *
 * Revision 1.6  2002/11/08 11:54:40  southa
 * Web fixes
 *
 * Revision 1.5  2002/11/08 11:29:24  southa
 * Web fixes and debug
 *
 * Revision 1.4  2002/11/08 00:15:31  southa
 * Fixed errors
 *
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

#include "MediaNetData.h"
#include "MediaNetHTTP.h"
#include "MediaNetLog.h"
#include "MediaNetProtocol.h"
#include "MediaNetServer.h"
#include "MediaNetUtils.h"

#include "mushPlatform.h"

auto_ptr< CoreData<MediaNetWebLink> > CoreData<MediaNetWebLink>::m_instance;
string MediaNetWebLink::m_webPath="";

MediaNetWebLink::MediaNetWebLink(TCPsocket inSocket, U32 inPort) :
    m_receiveState(kReceiveInitial),
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
    m_creationMsec=m_currentMsec;
    m_lastAccessMsec=m_currentMsec; // Not used
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
    if (m_isDead ||
        m_currentMsec > m_creationMsec + kLinkLifetime ||
        m_linkErrors > kErrorLimit)
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
            outStr += byte;
            if (byte == 0xa) break;
        }
    } while (result > 0);

    return (outStr.size() != 0);
}

void
MediaNetWebLink::Send(MediaNetData& ioData)
{
    if (m_isDead)
    {
        throw(NetworkFail("Attempt to send on dead WebLink"));
    }
    int result=SDLNet_TCP_Send(m_tcpSocket, ioData.ReadPtrGet(), ioData.ReadSizeGet());
    if (result >= 0 && static_cast<U32>(result) != ioData.ReadSizeGet())
    {
        MediaNetLog::Instance().Log() << "Failed to send data on WebLink: " << SDLNet_GetError();
        ++m_linkErrors;
    }
    else
    {
        ioData.ReadPosAdd(result);
    }
    // MediaNetLog::Instance().Log() << "Sending " << ioData << endl;
}

void
MediaNetWebLink::Send(const string& inStr)
{
    MediaNetData netData;;
    netData.Write(inStr);
    Send(netData);
}

void
MediaNetWebLink::Send(istream& ioStream)
{
    MediaNetData netData;
    while (ioStream.good() && !ioStream.eof())
    {
        netData.PrepareForWrite();
        ioStream.read(netData.WritePtrGet(), netData.WriteSizeGet());
        U32 length=ioStream.gcount();
        netData.WritePosAdd(length);
        if (length == 0) break;
    }
    Send(netData);
}

void
MediaNetWebLink::ReceivedProcess(const string& inStr)
{
    switch (m_receiveState)
    {
        case kReceiveInitial:
        {
            if (inStr.substr(0,3) == "GET")
            {
                m_requestLine = inStr;
                m_requestType = kRequestGet;
            }
            else if (inStr.substr(0,4) == "POST")
            {
                m_requestLine = inStr;
                m_requestType = kRequestPost;
            }
        }
        m_receiveState = kReceiveHeaders;
        break;

        case kReceiveHeaders:
        {
            if (inStr.size() > 0 &&
             (inStr[0] == 0xd || inStr[0] == 0xa))
            {
                m_receiveState=kReceiveBody;
            }
            
            switch (m_requestType)
            {
                case kRequestGet:
                    GetProcess(m_requestLine.substr(4));
                    m_receiveState = kReceiveInitial;
                    break;

                case kRequestPost:
                    break;	

                default:
                    SendErrorPage("Unrecognised request");
                    break;
            }
        }
        break;

        case kReceiveBody:
        {
            switch (m_requestType)
            {
                case kRequestGet:
                    throw(LogicFail("Bad receive state for GET"));
                    break;

                case kRequestPost:
                    PostProcess(inStr);
                    GetProcess(m_requestLine.substr(5));
                    break;

                default:
                    SendErrorPage("Unrecognised request");
                    break;
            }
        }
        break;

        default:
            throw(LogicFail("Bad value for m_receiveState"));
            break;
    }
}

void
MediaNetWebLink::GetProcess(const string& inFilename)
{
    string localFilename;
    U32 dotCount=0;
    U32 slashCount=0;

    MediaNetLog::Instance().Log() << "Serving fetch request for " << MediaNetUtils::MakePrintable(inFilename) << endl;

    try
    {
        for (U32 i=0; i<inFilename.size(); ++i)
        {
            U8 byte=inFilename[i];
            if (byte == '.')
            {
                if (dotCount > 0)
                {
                    throw(NetworkFail("Bad filename (dots)"));
                }
                ++dotCount;
                localFilename+=byte;
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
                localFilename+=byte;
            }
            if (byte <= ' ')
            {
                break;
            }
        }
        if (localFilename == "") localFilename = "index.html";
        
        if (localFilename == "test.html")
        {
            SendTestPage();
        }
        else
        {
            if (m_webPath == "")
            {
                CoreEnv::Instance().VariableGetIfExists(m_webPath, "LOCALWEB_PATH");
            }
            if (m_webPath == "")
            {
                throw(NetworkFail("Path to web files (LOCALWEB_PATH) not set"));
            }
            localFilename = m_webPath+"/"+localFilename;
            SendFile(localFilename);
        }
    }
    catch (NetworkFail &e)
    {
        MediaNetLog::Instance().Log() << "ReceivedProcess exception: " << e.what() << endl;
        SendErrorPage(e.what());
    }
}

void
MediaNetWebLink::PostProcess(const string& inValues)
{
    try
    {
        if (inValues.find("'") != inValues.npos)
        {
            throw(NetworkFail("Dodgy POST values"));
        }
        CoreCommand command(string("handlepostvalues('")+inValues+"')");
        command.Execute();
    }    
    catch (NetworkFail &e)
    {
        MediaNetLog::Instance().Log() << "Network exception: " << e.what() << endl;
    }
    catch (CommandFail &e)
    {
        MediaNetLog::Instance().Log() << "Command failed: " << e.what() << endl;
    }
}

void
MediaNetWebLink::SendFile(const string& inFilename)
{
    bool processFile=false;
    
    ifstream fileStream(inFilename.c_str());
    if (!fileStream)
    {
        throw(NetworkFail("File not found: "+inFilename));
    }
    
    MediaNetHTTP http;
    http.Reply200();

    CoreRegExp re;
    if (re.Search(inFilename, "\\.html$"))
    {
        http.ContentTypeHTML();
    }
    else if (re.Search(inFilename, "\\.mhtml$"))
    {
        http.ContentTypeHTML();
        processFile=true;
    }
    else if (re.Search(inFilename, "\\.(jpg|jpeg)$"))
    {
        http.AllowCachingSet();
        http.ContentType("image/jpeg");
    }
    else if (re.Search(inFilename, "\\.(tif|tiff)$"))
    {
        http.AllowCachingSet();
        http.ContentType("image/tiff");
    }
    else if (re.Search(inFilename, "\\.png$"))
    {
        http.AllowCachingSet();
        http.ContentType("image/png");
    }
    else if (re.Search(inFilename, "\\.css$"))
    {
        http.AllowCachingSet();
        http.ContentType("text/css");
    }
    else
    {
        throw(NetworkFail("Unknown file type: "+inFilename));
    }
        
    if (processFile)
    {
        SendMHTML(fileStream, http);
    }
    else
    {
        http.Endl();
        MediaNetData netData;
        http.ContentGet(netData);
        Send(netData);
        Send(fileStream);
    }
    Disconnect();
}

void
MediaNetWebLink::SendMHTML(istream& ioStream, MediaNetHTTP& ioHTTP)
{
    MediaNetData netData;
    
    ioHTTP.Endl();
    ioHTTP.ContentGet(netData);
    Send(netData);
    
    while (ioStream.good() && !ioStream.eof())
    {
        string dataStr;
        getline(ioStream, dataStr, '\0');

        U32 startPos;
        
        while (startPos = dataStr.find("<?mush"), startPos != dataStr.npos)
        {
            U32 endPos = dataStr.find("?>", startPos);
            if (endPos == dataStr.npos)
            {
                throw(NetworkFail("Unterminated <?mush (expecting ?>)"));
            }

            string content=dataStr.substr(startPos+6, endPos - startPos - 6);
            // MediaNetLog::Instance().Log() << "Found mush command '" << content << "'" << endl;        

            try
            {
                CoreCommand command(content);
                ostringstream commandOutput;
                CoreEnvOutput envOutput(CoreEnv::Instance(), commandOutput);
                command.Execute();
                dataStr.replace(startPos, endPos - startPos + 2, commandOutput.str());
            }
            catch (exception& e)
            {
                ostringstream errorOutput;
                errorOutput << "<pre>Command '" << content << "' failed: " << e.what() << "</pre>" << endl;
                dataStr.replace(startPos, endPos - startPos + 2, errorOutput.str());
            }
        }
        Send(dataStr);
    }
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
    MediaNetData netData;
    http.ContentGet(netData);
    Send(netData);
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

    MediaNetData netData;
    http.ContentGet(netData);
    Send(netData);
    Disconnect();
}

void
MediaNetWebLink::Print(ostream& ioOut) const
{

}
