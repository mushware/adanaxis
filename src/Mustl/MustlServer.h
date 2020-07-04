//%includeGuardStart {
#ifndef MUSTLSERVER_H
#define MUSTLSERVER_H
//%includeGuardStart } y38UpYTFyDx7kCAytyovtQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlServer.h
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
//%Header } dYG9ifeBUjipQzRUSWi5DQ
/*
 * $Id: MustlServer.h,v 1.14 2006/06/01 15:39:54 southa Exp $
 * $Log: MustlServer.h,v $
 * Revision 1.14  2006/06/01 15:39:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.13  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.12  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.11  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.10  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:09:31  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.7  2003/01/17 00:41:05  southa
 * Configuration updates from POST data
 *
 * Revision 1.6  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.5  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/12/13 19:03:06  southa
 * Mustl interface cleanup
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
 * Revision 1.11  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.10  2002/11/23 14:45:34  southa
 * Replaced access to server port
 *
 * Revision 1.9  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.8  2002/11/22 15:00:33  southa
 * Network connection handling
 *
 * Revision 1.7  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.6  2002/11/20 22:35:28  southa
 * Multiplayer setup
 *
 * Revision 1.5  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.4  2002/11/01 18:46:26  southa
 * UDP Links
 *
 * Revision 1.3  2002/10/31 19:55:54  southa
 * Network links
 *
 * Revision 1.2  2002/10/31 16:41:33  southa
 * Network client
 *
 * Revision 1.1  2002/10/31 15:52:15  southa
 * First network code
 *
 */

#include "MustlStandard.h"

#include "MustlMushcore.h"

class MustlAddress;
class MustlData;

class MustlServer : public MushcoreSingleton<MustlServer>
{
public:
    MustlServer();
    ~MustlServer();

    void Connect(void);
    void Connect(Mustl::U32 inPort);
    void Disconnect(void);
    void Accept(void);
    void UDPSend(const MustlAddress& inAddress, MustlData& ioData);
    void UDPReceive(MustlData& ioData);
    void UDPHarvest(void);
    void UDPDiscard(void);
    bool IsServing(void) const { return m_serving; }
    Mustl::U32 ServerPortHostOrderGet(void) const { return m_serverPortHostOrder; }
    
protected:
    
private:
    Mustl::tSocket m_tcpSocket;
    Mustl::tSocket m_udpSocket;
    Mustl::U32 m_serverPortHostOrder;
    Mustl::U32 m_linkCtr;
    bool m_serving;
    bool m_logTraffic;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
