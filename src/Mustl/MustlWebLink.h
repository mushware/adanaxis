//%includeGuardStart {
#ifndef MUSTLWEBLINK_H
#define MUSTLWEBLINK_H
//%includeGuardStart } zN/s3AZ7Hi+vuNYcQH6q9w
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlWebLink.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } OQ72Jnko8GwtYwxhvcBf2Q
/*
 * $Id: MustlWebLink.h,v 1.9 2004/01/02 21:13:16 southa Exp $
 * $Log: MustlWebLink.h,v $
 * Revision 1.9  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.8  2003/10/06 22:23:45  southa
 * Game to GameMustl move
 *
 * Revision 1.7  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:33  southa
 * Fixed file headers
 *
 * Revision 1.5  2002/12/29 20:30:57  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/13 01:06:54  southa
 * Mustl work
 *
 * Revision 1.2  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:27  southa
 * Created Mustl
 *
 * Revision 1.9  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
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

#include "MustlStandard.h"

class MustlHTTP;
class MustlData;

class MustlWebLink
{
public:
    explicit MustlWebLink(Mustl::tSocket inSocket);
    ~MustlWebLink();

    void Tick(void);
    bool IsDead(void);
    void Disconnect(void);
    bool Receive(std::string& outStr);
    void Send(MustlData& ioData);
    void Send(const std::string& inStr);
    void Send(std::istream& ioStream);
    void SendFile(const std::string& inStr);
    void SendMHTML(std::istream& ioStream, MustlHTTP& ioHTTP);
    void SendTestPage(void);
    void SendErrorPage(const std::string& inText);
    void ReceivedProcess(const std::string& inStr);

    void Print(std::ostream& ioOut) const;

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
        kErrorLimit=5
    };

    void GetProcess(const std::string& inFilename);
    void PostProcess(const std::string& inValues);

    std::string m_requestLine;
    tRequestType m_requestType;
    tLinkState m_linkState;
    tReceiveState m_receiveState;
    Mustl::tSocket m_tcpSocket;
    Mustl::tMsec m_currentMsec;
    Mustl::tMsec m_creationMsec;
    Mustl::tMsec m_lastAccessMsec;
    Mustl::U32 m_linkErrors;
    bool m_isDead;

    static std::string m_webPath;
};

inline std::ostream&
operator<<(std::ostream &ioOut, const MustlWebLink& inLink)
{
    inLink.Print(ioOut);
    return ioOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
