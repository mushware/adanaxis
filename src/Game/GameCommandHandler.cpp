/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameCommandHandler.cpp,v 1.2 2002/05/10 16:39:34 southa Exp $
 * $Log: GameCommandHandler.cpp,v $
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "GameCommandHandler.h"

#include "mushCore.h"
#include "GameAppHandler.h"

CoreInstaller GameCommandHandlerInstaller(GameCommandHandler::Install);

CoreScalar
GameCommandHandler::Game(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    CoreAppHandler::Instance().Mutate(new GameAppHandler);
    return CoreScalar(0);
}

void
GameCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler("game", Game);
}
