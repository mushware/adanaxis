//%includeGuardStart {
#ifndef MUSTLROUTER_H
#define MUSTLROUTER_H
//%includeGuardStart } NCMc0DuMKKIjbmXlqA1/Hg
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlRouter.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } e8I+rWL/7DySfrvFUJbr3g
/*
 * $Id: MustlRouter.h,v 1.14 2005/05/19 13:02:19 southa Exp $
 * $Log: MustlRouter.h,v $
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
