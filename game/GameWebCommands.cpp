/*****************************************************************************
*
* (Mushware file header version 1.1)
*
* This file contains original work by Andy Southgate.  Contact details can be
* found at http://www.mushware.com.  This file was placed in the Public
* Domain by Andy Southgate and Mushware Limited in 2002.
*
* This software carries NO WARRANTY of any kind.
*
****************************************************************************/

/*
 * $Id$
 * $Log$
 */

#include "GameWebCommands.h"

#include "mushCore.h"
#include "mushPlatform.h"
#include "GameAppHandler.h"

CoreInstaller GameWebCommandsInstaller(GameWebCommands::Install);

CoreScalar
GameWebCommands::DisplayModesWrite(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    ioEnv.Out() << "<select name=\"displaymode\">";
    ioEnv.Out() << "<option selected value=\"0\">640x480</option>";
    ioEnv.Out() << "<option value=\"0\">800x600</option>";
    ioEnv.Out() << "<option value=\"0\">1024x768</option>";
    ioEnv.Out() << "<option value=\"0\">1280x1024</option>";
    ioEnv.Out() << "</select>";
    return CoreScalar(0);
}

void
GameWebCommands::Install(void)
{
    CoreApp::Instance().AddHandler("displaymodeswrite", DisplayModesWrite);
}
