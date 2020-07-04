//%includeGuardStart {
#ifndef MUSTLROUTER_H
#define MUSTLROUTER_H
//%includeGuardStart } NCMc0DuMKKIjbmXlqA1/Hg
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlRouter.h
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
//%Header } aaJSH8TFeljbK5+IHggWYg
/*
 * $Id: MustlRouter.h,v 1.15 2006/06/01 15:39:54 southa Exp $
 * $Log: MustlRouter.h,v $
 * Revision 1.15  2006/06/01 15:39:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.14  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.13  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.12  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.11  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:09:30  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/02/05 18:49:52  southa
 * Build fixes
 *
 * Revision 1.8  2003/02/05 17:06:38  southa
 * Build fixes
 *
 * Revision 1.7  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.6  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.5  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/14 15:04:34  southa
 * Mustl fixes
 *
 * Revision 1.2  2002/12/13 01:06:54  southa
 * Mustl work
 *
 * Revision 1.1  2002/12/12 14:00:27  southa
 * Created Mustl
 *
 * Revision 1.6  2002/11/25 12:06:19  southa
 * Received net message routing
 *
 * Revision 1.5  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.4  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.3  2002/11/22 15:00:33  southa
 * Network connection handling
 *
 * Revision 1.2  2002/11/04 19:34:47  southa
 * Network link maintenance
 *
 * Revision 1.1  2002/11/04 01:02:38  southa
 * Link checks
 *
 */

#include "MustlStandard.h"

#include "MustlMushcore.h"

class MustlData;
class MustlLink;
class MustlMessageHandler;

class MustlRouter : public MushcoreSingleton<MustlRouter>
{
public:
    void ReceiveAll(MustlMessageHandler& inHandler);

protected:
    friend class MushcoreSingleton<MustlRouter>;
    MustlRouter();
    void UDPIfAddressMatchReceive(MustlData& ioData, MustlMessageHandler& inHandler);
    void UDPReceiveFromServer(MustlMessageHandler& inHandler);
    
private:
    enum
    {
        kTickPeriod=100,
        kUDPReceivePacketLimit=100
    };

    void ProcessMessage(MustlData& ioData, MustlLink& ioLink, MustlMessageHandler& inHandler);
    
    Mustl::tMsec m_lastTickMsec;

}; 

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
