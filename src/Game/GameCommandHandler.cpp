/*
 * $Id: GameCommandHandler.cpp,v 1.1 2002/05/10 15:35:27 southa Exp $
 * $Log: GameCommandHandler.cpp,v $
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
