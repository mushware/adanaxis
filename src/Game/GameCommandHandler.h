/*
 * $Id: GameCommandHandler.h,v 1.1 2002/05/10 15:35:27 southa Exp $
 * $Log: GameCommandHandler.h,v $
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "mushCore.h"

class GameCommandHandler
{
public:
    static void Install(void);
    static CoreScalar Game(CoreCommand& ioCommand, CoreEnv& ioEnv);
};
