#ifndef MUSTLROUTER_H
#define MUSTLROUTER_H
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
 * $Id: MustlRouter.h,v 1.6 2003/01/17 13:30:41 southa Exp $
 * $Log: MustlRouter.h,v $
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

#include "MustlMushcoreSingleton.h"

class MustlData;
class MustlLink;
class MustlMessageHandler;

class MustlRouter : public MushcoreSingleton<MustlRouter>
{
public:
    void ReceiveAll(MustlMessageHandler& inHandler);

protected:
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

#endif
