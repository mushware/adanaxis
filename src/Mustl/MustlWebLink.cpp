/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlWebLink.cpp,v 1.19 2003/01/17 13:30:41 southa Exp $
 * $Log: MustlWebLink.cpp,v $
 * Revision 1.19  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.18  2003/01/17 12:20:41  southa
 * Fixed auto_ptr duplication
 *
 * Revision 1.17  2003/01/16 15:58:02  southa
 * Mustl exception handling
 *
 * Revision 1.16  2003/01/16 12:03:55  southa
 * Platform and invalid socket fixes
 *
 * Revision 1.15  2003/01/14 20:46:12  southa
 * Post data handling
 *
 * Revision 1.14  2003/01/14 17:38:22  southa
 * Mustl web configuration
 *
 * Revision 1.13  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.12  2003/01/13 16:50:50  southa
 * win32 support
 *
 * Revision 1.11  2003/01/13 15:01:20  southa
 * Fix Mustl command line build
 *
 * Revision 1.10  2003/01/12 17:33:01  southa
 * Mushcore work
 *
 * Revision 1.9  2003/01/11 17:58:15  southa
 * Mustl fixes
 *
 * Revision 1.8  2003/01/09 14:57:08  southa
 * Created Mushcore
 *
 * Revision 1.7  2003/01/07 17:13:45  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.6  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/29 20:30:57  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/17 12:53:34  southa
 * Mustl library
 *
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

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MUSHCORE_DATA_INSTANCE(MustlWebLink);
MUSHCORE_DESTROY_DATA_INSTANCE(MustlWebLink);

string MustlWebLink::m_webPath="";

MustlWebLink::MustlWebLink(tSocket inSocket) :
    m_receiveState(kReceiveInitial),
    m_tcpSocket(MustlPlatform::InvalidSocketValueGet()),
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
    if (m_tcpSocket != MustlPlatform::InvalidSocketValueGet())
    {
        MustlPlatform::SocketClose(m_tcpSocket);
        m_tcpSocket=MustlPlatform::InvalidSocketValueGet();
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

    // MustlLog::Instance().WebLog() << "Received " << MustlUtils::MakePrintable(outStr) << endl;

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

    // MustlLog::Instance().WebLog() << "Sending " << ioData << endl;
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
        ioStream.read(reinterpret_cast<char *>(netData.WritePtrGet()), netData.WriteSizeGet());
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
                const MushcoreScalar *pScalar;
                if (MushcoreGlobalConfig::Instance().GetIfExists(pScalar, "MUSTL_WEB_PATH"))
                {
                    m_webPath = pScalar->StringGet();
                }
            }
            if (m_webPath == "")
            {
                throw(MustlFail("Path to web files (MUSTL_WEB_PATH) not set"));
            }
            localFilename = m_webPath+"/"+localFilename;
            SendFile(localFilename);
        }
    }
    catch (MushcoreNonFatalFail &e)
    {
        MustlLog::Instance().WebLog() << "Exception: " << e.what() << endl;
        if (!m_isDead)
        {
            try
            {
                SendErrorPage(e.what());
            }
            catch (MushcoreNonFatalFail &e)
            {
                MustlLog::Instance().WebLog() << "Exception sending error page: " << e.what() << endl;
            }
        }
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
        MushcoreCommand command(string("mustlpostvalues('")+inValues+"')");
        command.Execute();
    }
    catch (MushcoreNonFatalFail &e)
    {
        MustlLog::Instance().WebLog() << "Exception: " << e.what() << endl;
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
            // MustlLog::Instance().WebLog() << "Found mush command '" << content << "'" << endl;        

            try
            {
                MushcoreCommand command(content);
                ostringstream commandOutput;
                MushcoreEnvOutput envOutput(MushcoreEnv::Instance(), commandOutput);
                command.Execute();
                dataStr.replace(startPos, endPos - startPos + 2, commandOutput.str());
            }
            catch (MushcoreNonFatalFail& e)
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

    http.Out() << "Mustl test page";
    
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
    http.Out() << "<h1>Error from Mustl web server</h1>";
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
    ioOut << "[";
    ioOut << "requestLine=" << m_requestLine;
    ioOut << ", requestType=" << m_requestType;
    ioOut << ", linkState=" << m_linkState;
    ioOut << ", receiveState=" << m_receiveState;
    ioOut << ", tcpSocket=" << m_tcpSocket;
    ioOut << ", currentMsec=" << m_currentMsec;
    ioOut << ", creationMsec=" << m_creationMsec;
    ioOut << ", lastAccessMsec=" << m_lastAccessMsec;
    ioOut << ", linkErrors=" << m_linkErrors;
    ioOut << ", isDead=" << m_isDead;
    ioOut << ", webPath=" << m_webPath;
    ioOut << "]";
}
