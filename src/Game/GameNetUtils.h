/*
 * $Id$
 * $Log$
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
    static void KillServersByType(bool inIsImage);
    static void KillClientsByType(bool inIsImage);

    
};

