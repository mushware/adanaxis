#ifndef MEDIANETWEBLINK_H
#define MEDIANETWEBLINK_H
/*
 * $Id: MediaNetWebLink.h,v 1.8 2002/11/21 18:06:18 southa Exp $
 * $Log: MediaNetWebLink.h,v $
 * Revision 1.8  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.7  2002/11/12 18:02:13  southa
 * POST handling and handlepostvalues command
 *
 * Revision 1.6  2002/11/12 17:05:01  southa
 * Tidied localweb server
 *
 * Revision 1.5  2002/11/12 11:49:22  southa
 * Initial MHTML processing
 *
 * Revision 1.4  2002/11/08 11:29:24  southa
 * Web fixes and debug
 *
 * Revision 1.3  2002/11/07 00:53:37  southa
 * localweb work
 *
 * Revision 1.2  2002/11/06 14:16:57  southa
 * Basic web server
 *
 * Revision 1.1  2002/11/05 18:15:18  southa
 * Web server
 *
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaNetHTTP;
class MediaNetData;

class MediaNetWebLink
{
public:
    explicit MediaNetWebLink(TCPsocket inSocket);
    ~MediaNetWebLink();

    void Tick(void);
    bool IsDead(void);
    void Disconnect(void);
    bool Receive(string& outStr);
    void Send(MediaNetData& ioData);
    void Send(const string& inStr);
    void Send(istream& ioStream);
    void SendFile(const string& inStr);
    void SendMHTML(istream& ioStream, MediaNetHTTP& ioHTTP);
    void SendTestPage(void);
    void SendErrorPage(const string& inText);
    void ReceivedProcess(const string& inStr);

    void Print(ostream& ioOut) const;

private:
    enum tLinkState
    {
        kLinkStateNew,
        kLinkStateSending,
        kLinkStateDone
    };

    enum tReceiveState
    {
        kReceiveInvalid,
        kReceiveInitial,
        kReceiveHeaders,
        kReceiveBody
    };
    
    enum tRequestType
    {
        kRequestInvalid,
        kRequestGet,
        kRequestPost
    };
    
    enum
    {
        kLinkLifetime=30000, // Times in msec
        kErrorLimit=100
    };

    void GetProcess(const string& inFilename);
    void PostProcess(const string& inValues);
    
    string m_requestLine;
    tRequestType m_requestType;
    tLinkState m_linkState;
    tReceiveState m_receiveState;
    TCPsocket m_tcpSocket;
    U32 m_currentMsec;
    U32 m_creationMsec;
    U32 m_lastAccessMsec;
    U32 m_linkErrors;
    bool m_isDead;

    static string m_webPath;
};

inline ostream&
operator<<(ostream &ioOut, const MediaNetWebLink& inLink)
{
    inLink.Print(ioOut);
    return ioOut;
}
#endif
