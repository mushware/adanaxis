/*
 * $Id: MediaNetWebLink.h,v 1.5 2002/11/12 11:49:22 southa Exp $
 * $Log: MediaNetWebLink.h,v $
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
    MediaNetWebLink(TCPsocket inSocket, U32 inPort);
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

    enum tRequestType
    {
        kRequestInvalid,
        kRequestGet
    };
    
    enum
    {
        kLinkLifetime=30000, // Times in msec
        kTimeoutIdle=5000,
        kErrorLimit=100
    };
    
    void GetProcess(void);
    
    string m_requestLine;
    tRequestType m_requestType;
    tLinkState m_linkState;
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
