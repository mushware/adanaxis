/*
 * $Id: GameWebCommands.h,v 1.5 2002/11/14 19:35:30 southa Exp $
 * $Log: GameWebCommands.h,v $
 * Revision 1.5  2002/11/14 19:35:30  southa
 * Configuration work
 *
 * Revision 1.4  2002/11/14 17:29:07  southa
 * Config database
 *
 * Revision 1.3  2002/11/14 11:40:28  southa
 * Configuration handling
 *
 * Revision 1.2  2002/11/12 18:02:13  southa
 * POST handling and handlepostvalues command
 *
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
    static CoreScalar GameConfigInputWrite(CoreCommand& ioCommand, CoreEnv& ioEnv);

private:

};

