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
 * $Id: GameCommandHandler.cpp,v 1.5 2002/08/07 13:36:48 southa Exp $
 * $Log: GameCommandHandler.cpp,v $
 * Revision 1.5  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:06  southa
 * Build process fixes
 *
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
