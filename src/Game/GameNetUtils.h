/*
 * $Id: GameNetUtils.h,v 1.2 2002/12/04 12:54:41 southa Exp $
 * $Log: GameNetUtils.h,v $
 * Revision 1.2  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.1  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 */

#include "mushCore.h"

class MediaNetAddress;
class MediaNetData;
class MediaNetLink;

class GameNetUtils
{
public:
    static void KillServers(void);
    static void KillServerImages(void);
    static void KillClients(void);
    static void KillClientImages(void);
    static void KillLinks(void);

    static bool MaintainLinks(vector< CoreDataRef<MediaNetLink> >& inLinks, const MediaNetAddress& inAddress, U32 inLinkNum);
    static void CreateLink(CoreDataRef<MediaNetLink>& outLink, const MediaNetAddress& inAddress);
    static void ReliableSend(U32& ioLinkNum, vector< CoreDataRef<MediaNetLink> >& inLinks, MediaNetData& ioData);
    
private:
    static void KillServersByType(bool inImageIs);
    static void KillClientsByType(bool inImageIs);
};
