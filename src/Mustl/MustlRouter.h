#ifndef MUSTLROUTER_H
#define MUSTLROUTER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MustlRouter.h,v 1.9 2003/02/05 18:49:52 southa Exp $
 * $Log: MustlRouter.h,v $
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

#include "MustlMushcoreSingleton.h"

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

#endif
