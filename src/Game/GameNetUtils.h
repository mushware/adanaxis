#ifndef GAMENETUTILS_H
#define GAMENETUTILS_H
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
 * $Id: GameNetUtils.h,v 1.7 2002/12/12 14:00:39 southa Exp $
 * $Log: GameNetUtils.h,v $
 * Revision 1.7  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.6  2002/12/09 23:59:58  southa
 * Network control
 *
 * Revision 1.5  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.4  2002/12/05 23:52:52  southa
 * Network management and status
 *
 * Revision 1.3  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.2  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.1  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 */

#include "mushCore.h"

class MustlAddress;
class MustlData;
class MustlLink;

class GameNetUtils
{
public:
    static void KillServers(void);
    static void KillServerImages(void);
    static void KillClients(void);
    static void KillClientImages(void);
    static void KillLinks(void);

    static bool MaintainLinks(std::vector< CoreDataRef<MustlLink> >& inLinks, const string& inClientName, const MustlAddress& inAddress, Mushware::U32 inLinkNum);
    static void CreateLink(CoreDataRef<MustlLink>& outLink, const string& inClientName, const MustlAddress& inAddress);
    static void ReliableSend(Mushware::U32& ioLinkNum, std::vector< CoreDataRef<MustlLink> >& inLinks, Mushware::U32 inLinkNum, MustlData& ioData);
    static void FastSend(Mushware::U32& ioLinkNum, std::vector< CoreDataRef<MustlLink> >& inLinks, Mushware::U32 inLinkNum, MustlData& ioData);
    static void NetTicker(void);
    static void WebReceive(void);
    static void NetReceive(void);
    
private:
    enum
    {
        kImageLifetimeMsec=33000
    };
    static void KillServersByType(bool inImageIs);
    static void KillClientsByType(bool inImageIs);
};
#endif
