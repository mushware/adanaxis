//%includeGuardStart {
#ifndef MUSTLWEBLINK_H
#define MUSTLWEBLINK_H
//%includeGuardStart } zN/s3AZ7Hi+vuNYcQH6q9w
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlWebLink.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } uuLCvps8q/wXKdX5ZZ2vxg
/*
 * $Id: MustlWebLink.h,v 1.11 2006/06/01 15:39:55 southa Exp $
 * $Log: MustlWebLink.h,v $
 * Revision 1.11  2006/06/01 15:39:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/05/19 13:02:20  southa
 * Mac release work
 *
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
