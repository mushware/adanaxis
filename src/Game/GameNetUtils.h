//%includeGuardStart {
#ifndef GAMENETUTILS_H
#define GAMENETUTILS_H
//%includeGuardStart } JnczPeo4C04imsnHiRE/9Q
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameNetUtils.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /Gej6Y/YSjpkLrUzzByQvQ
/*
 * $Id: GameNetUtils.h,v 1.12 2003/08/21 23:08:50 southa Exp $
 * $Log: GameNetUtils.h,v $
 * Revision 1.12  2003/08/21 23:08:50  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.10  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.8  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
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

#include "Mushcore.h"

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

    static bool MaintainLinks(std::vector< MushcoreDataRef<MustlLink> >& inLinks, const std::string& inClientName, const MustlAddress& inAddress, Mushware::U32 inLinkNum);
    static void CreateLink(MushcoreDataRef<MustlLink>& outLink, const std::string& inClientName, const MustlAddress& inAddress);
    static void ReliableSend(Mushware::U32& ioLinkNum, std::vector< MushcoreDataRef<MustlLink> >& inLinks, Mushware::U32 inLinkNum, MustlData& ioData);
    static void FastSend(Mushware::U32& ioLinkNum, std::vector< MushcoreDataRef<MustlLink> >& inLinks, Mushware::U32 inLinkNum, MustlData& ioData);
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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
