/*
 * $Id: MustlWebLink.cpp,v 1.2 2002/12/12 18:38:25 southa Exp $
 * $Log: MustlWebLink.cpp,v $
 * Revision 1.2  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 * Revision 1.14  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.13  2002/11/22 11:42:07  southa
 * Added developer controls
 *
 * Revision 1.12  2002/11/18 14:11:04  southa
 * win32 support
 *
 * Revision 1.11  2002/11/15 11:47:56  southa
 * Web processing and error handling
 *
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

#include "MustlWebLink.h"

#include "Mustl.h"
#include "MustlHTTP.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlNamespace.h"

#include "mustlCore.h"
using Mushware::CoreCommand;
using Mushware::CoreData;
using Mushware::CoreEnv;
using Mushware::CoreEnvOutput;

auto_ptr< CoreData<MustlWebLink> > CoreData<MustlWebLink>::m_instance;
string MustlWebLink::m_webPath="";

MustlWebLink::MustlWebLink(tSocket inSocket) :
    m_receiveState(kReceiveInitial),
    m_linkErrors(0),
    m_isDead(false)
{
    // I am the server end of the link
    try
    {
        m_tcpSocket = inSocket;
        MustlPlatform::SocketNonBlockingSet(m_tcpSocket);
    }
    catch (...)
    {
        MustlPlatform::SocketClose(inSocket);
        throw;
    }
    m_linkState=kLinkStateNew;
    m_currentMsec = MustlTimer::Instance().CurrentMsecGet();
    m_creationMsec=m_currentMsec;
    m_lastAccessMsec=m_currentMsec; // Not used
}

MustlWebLink::~MustlWebLink()
{
    MustlLog::Instance().WebLog() << "Closing web link" << endl;
    try
    {
        Disconnect();
    }
    catch (exception& e)
    {
        MustlLog::Instance().WebLog() << "~MustlWebLink exception: " << e.what() << endl;
    }
}

void
MustlWebLink::Disconnect(void)
{
    if (m_tcpSocket != NULL)
    {
        MustlPlatform::SocketClose(m_tcpSocket);
        m_tcpSocket=NULL;
    }
    m_isDead = true;
}

void
MustlWebLink::Tick(void)
{
    m_currentMsec = MustlTimer::Instance().CurrentMsecGet();
}

bool
MustlWebLink::IsDead(void)
{
    m_currentMsec = MustlTimer::Instance().CurrentMsecGet();
    if (m_isDead ||
        m_currentMsec > m_creationMsec + kLinkLifetime ||
        m_linkErrors > kErrorLimit)
    {
        return true;
    }
    return false;
}

bool
MustlWebLink::Receive(string& outStr)
{
    if (m_isDead) return false;
    
    U8 byte='-';
    int result;
    outStr="";
    do
    {
        result=MustlPlatform::TCPReceive(m_tcpSocket, &byte, 1);

        if (result == 1)
        {
            outStr += byte;
            if (byte == 0xa) break;
        }
    } while (result > 0);

    // MustlLog::Instance().Log() << "Received " << MustlUtils::MakePrintable(outStr) << endl;

    return (outStr.size() != 0);
}

void
MustlWebLink::Send(MustlData& ioData)
{
    if (m_isDead)
    {
        throw(MustlFail("Attempt to send on dead WebLink"));
    }
    U32 sendSize = ioData.ReadSizeGet();
    MustlPlatform::TCPSend(m_tcpSocket, ioData.ReadPtrGet(), sendSize);
    ioData.ReadPosAdd(sendSize);

    // MustlLog::Instance().Log() << "Sending " << ioData << endl;
}

void
MustlWebLink::Send(const string& inStr)
{
    MustlData netData;;
    netData.Write(inStr);
    Send(netData);
}

void
MustlWebLink::Send(istream& ioStream)
{
    MustlData netData;
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
MustlWebLink::ReceivedProcess(const string& inStr)
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
	    bool lineEnd=false;
            if (inStr.size() > 0 &&
             (inStr[0] == 0xd || inStr[0] == 0xa))
            {
                lineEnd=true;
            }
            
            switch (m_requestType)
            {
                case kRequestGet:
		    if (lineEnd)
		    {
                        GetProcess(m_requestLine.substr(4));
                        m_receiveState = kReceiveInitial;
		    }
                    break;

                case kRequestPost:
		    if (lineEnd)
		    {
		        m_receiveState = kReceiveBody;
		    }
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
                    throw(MustlFail("Bad receive state for GET"));
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
            throw(MustlFail("Bad value for m_receiveState"));
            break;
    }
}

void
MustlWebLink::GetProcess(const string& inFilename)
{
    string localFilename;
    U32 dotCount=0;
    U32 slashCount=0;

    MustlLog::Instance().WebLog() << "Serving fetch request for " << MustlUtils::MakePrintable(inFilename) << endl;

    try
    {
        for (U32 i=0; i<inFilename.size(); ++i)
        {
            U8 byte=inFilename[i];
            if (byte == '.')
            {
                if (dotCount > 0)
                {
                    throw(MustlFail("Bad filename (dots)"));
                }
                ++dotCount;
                localFilename+=byte;
            }
            if (byte == '/')
            {
                if (slashCount > 0)
                {
                    throw(MustlFail("Bad filename (slashes)"));
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
                throw(MustlFail("Path to web files (LOCALWEB_PATH) not set"));
            }
            localFilename = m_webPath+"/"+localFilename;
            SendFile(localFilename);
        }
    }
    catch (MustlFail &e)
    {
        MustlLog::Instance().WebLog() << "ReceivedProcess exception: " << e.what() << endl;
        SendErrorPage(e.what());
    }
}

void
MustlWebLink::PostProcess(const string& inValues)
{
    try
    {
        if (inValues.find("'") != inValues.npos)
        {
            throw(MustlFail("Invalid POST values"));
        }
        //CoreCommand command(string("handlepostvalues('")+inValues+"')");
        //command.Execute();
        // Catch CommandFail
    }    
    catch (MustlFail &e)
    {
        MustlLog::Instance().WebLog() << "Network exception: " << e.what() << endl;
    }
}

void
MustlWebLink::SendFile(const string& inFilename)
{
    bool processFile=false;
    
    ifstream fileStream(inFilename.c_str());
    if (!fileStream)
    {
        throw(MustlFail("File not found: "+inFilename));
    }
    
    MustlHTTP http;
    http.Reply200();


    U32 dotPos = inFilename.rfind('.');
    if (dotPos == string::npos)
    {
        throw(MustlFail("Unknown file type: "+inFilename));
    }
    string fileTypeStr = inFilename.substr(dotPos+1);
    
    if (fileTypeStr == "html")
    {
        http.ContentTypeHTML();
    }
    else if (fileTypeStr == "mhtml")
    {
        http.ContentTypeHTML();
        processFile=true;
    }
    else if (fileTypeStr == "jpg" || fileTypeStr == "jpeg")
    {
        http.AllowCachingSet();
        http.ContentType("image/jpeg");
    }
    else if (fileTypeStr == "tif" || fileTypeStr == "tiff")
    {
        http.AllowCachingSet();
        http.ContentType("image/tiff");
    }
    else if (fileTypeStr == "png")
    {
        http.AllowCachingSet();
        http.ContentType("image/png");
    }
    else if (fileTypeStr == "css")
    {
        http.AllowCachingSet();
        http.ContentType("text/css");
    }
    else
    {
        throw(MustlFail("Unknown file type: "+fileTypeStr));
    }
        
    if (processFile)
    {
        SendMHTML(fileStream, http);
    }
    else
    {
        http.Endl();
        MustlData netData;
        http.ContentGet(netData);
        Send(netData);
        Send(fileStream);
    }
    Disconnect();
}

void
MustlWebLink::SendMHTML(istream& ioStream, MustlHTTP& ioHTTP)
{
    MustlData netData;
    
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
                throw(MustlFail("Unterminated <?mush (expecting ?>)"));
            }

            string content=dataStr.substr(startPos+6, endPos - startPos - 6);
            // MustlLog::Instance().Log() << "Found mush command '" << content << "'" << endl;        

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
MustlWebLink::SendTestPage(void)
{
    MustlHTTP http;
    http.Reply200();
    http.ContentTypeHTML();
    http.Endl();
    http.Header();

    http.Out() << "Infernal Contractor II test page";
    
    http.Endl();
    http.Footer();
    MustlData netData;
    http.ContentGet(netData);
    Send(netData);
    Disconnect();
}

void
MustlWebLink::SendErrorPage(const string& inText)
{
    MustlHTTP http;
    http.Reply200();
    http.ContentTypeHTML();
    http.Endl();
    http.Header();
    http.Out() << "<p><font class=\"bigboldtitle\">Error from Mushware localweb server</font></p>";
    http.Out() << "<p>" << inText << "</p>";
    http.Out() << "<p><a target=\"_top\" href=\"/index.html\">Back to main page</a></p>";

    http.Endl();
    http.Footer();

    MustlData netData;
    http.ContentGet(netData);
    Send(netData);
    Disconnect();
}

void
MustlWebLink::Print(ostream& ioOut) const
{

}
