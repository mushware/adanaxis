/*
 * $Id: GameWebCommands.h,v 1.1 2002/11/07 11:59:02 southa Exp $
 * $Log: GameWebCommands.h,v $
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "mushCore.h"

class GameWebCommands
{
public:
    static void Install(void);
    static CoreScalar HandlePostValues(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar DisplayModesWrite(CoreCommand& ioCommand, CoreEnv& ioEnv);
};

