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
 * $Id: GameWebCommands.h,v 1.5 2003/01/09 14:57:04 southa Exp $
 * $Log: GameWebCommands.h,v $
 * Revision 1.5  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.4  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
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

#include "Mushcore.h"

class GameWebCommands
{
public:
    static void Install(void);
    static MushcoreScalar HandlePostValues(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar DisplayModesWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameConfigInputWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameServerStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameClientStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameLinkStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);

private:

};

#endif
