/*
 * $Id$
 * $Log$
 */

#include "GameCommandHandler.h"

#include "mushCore.hp"
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
