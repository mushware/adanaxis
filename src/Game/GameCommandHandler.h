/*
 * $Id$
 * $Log$
 */

#include "mushCore.hp"

class GameCommandHandler
{
public:
    static void Install(void);
    static CoreScalar Game(CoreCommand& ioCommand, CoreEnv& ioEnv);
};
