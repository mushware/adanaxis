#ifndef GAMEWEBCOMMANDS_H
#define GAMEWEBCOMMANDS_H
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
 * $Id: GameWebCommands.h,v 1.3 2002/11/27 13:23:26 southa Exp $
 * $Log: GameWebCommands.h,v $
 * Revision 1.3  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.2  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.1  2002/11/18 13:40:32  southa
 * Moved to correct place
 *
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
    static CoreScalar GameStatusWrite(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar GameServerStatusWrite(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar GameClientStatusWrite(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar GameLinkStatusWrite(CoreCommand& ioCommand, CoreEnv& ioEnv);

private:

};

#endif
