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
 * $Id: GameWebCommands.cpp,v 1.1 2002/11/07 11:59:02 southa Exp $
 * $Log: GameWebCommands.cpp,v $
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "GameWebCommands.h"

#include "GameAppHandler.h"
#include "GameConfig.h"

#include "mushCore.h"
#include "mushPlatform.h"

CoreInstaller GameWebCommandsInstaller(GameWebCommands::Install);

CoreScalar
GameWebCommands::DisplayModesWrite(CoreCommand& ioCommand, CoreEnv& ioEnv)
{

    U32 selectedMode=GameConfig::Instance().DisplayModeGet();
    U32 size=PlatformVideoUtils::Instance().NumModesGet();
    
    ioEnv.Out() << "<select name=\"displaymode\">";
    for (U32 i=0; i<size; ++i)
    {
        ioEnv.Out() << "<option ";
        if (i == selectedMode) ioEnv.Out() << "selected ";

        ioEnv.Out() << "value=\"" << i << "\">";
        ioEnv.Out() << PlatformVideoUtils::Instance().ModeDefGet(i).NameGet();
        ioEnv.Out() << "</option>";
    }
    ioEnv.Out() << "</select>";
    return CoreScalar(0);
}

void
GameWebCommands::Install(void)
{
    CoreApp::Instance().AddHandler("displaymodeswrite", DisplayModesWrite);
}
