/*
 * $Id: GameNetUtils.h,v 1.1 2002/12/03 20:28:17 southa Exp $
 * $Log: GameNetUtils.h,v $
 * Revision 1.1  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 */

#include "mushCore.h"

class GameNetUtils
{
public:
    static void KillServers(void);
    static void KillServerImages(void);
    static void KillClients(void);
    static void KillClientImages(void);
    static void KillLinks(void);

private:
    static void KillServersByType(bool inImageIs);
    static void KillClientsByType(bool inImageIs);

    
};

