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
 * $Id: GameWebCommands.cpp,v 1.7 2002/11/17 13:38:30 southa Exp $
 * $Log: GameWebCommands.cpp,v $
 * Revision 1.7  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.6  2002/11/14 19:35:30  southa
 * Configuration work
 *
 * Revision 1.5  2002/11/14 17:29:07  southa
 * Config database
 *
 * Revision 1.4  2002/11/14 11:40:28  southa
 * Configuration handling
 *
 * Revision 1.3  2002/11/12 18:02:13  southa
 * POST handling and handlepostvalues command
 *
 * Revision 1.2  2002/11/12 11:49:21  southa
 * Initial MHTML processing
 *
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "GameWebCommands.h"

#include "GameAppHandler.h"
#include "GameConfig.h"
#include "GameConfigDef.h"

#include "mushCore.h"
#include "mushPlatform.h"

CoreInstaller GameWebCommandsInstaller(GameWebCommands::Install);

CoreScalar
GameWebCommands::HandlePostValues(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(CommandFail("Usage: handlepostvalues(values)"));
    }
    string values;
    ioCommand.PopParam(values);

    CoreRegExp re("(^|&)type=([^&]+)($|&)");
    vector<string> matches;
    if (!re.Search(values, matches))
    {
        throw(CommandFail("No type= element in posted results '"+values+"'"));
    }
    COREASSERT(matches.size() == 3);
    if (matches[1] == "config1")
    {
        GameConfig::Instance().PostDataHandle(values);
    }
    else if (matches[1] == "singleplayer")
    {
        GameConfig::Instance().PostDataHandle(values);
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
        gameHandler.GameModeEnter(false);
    }
    else
    {
        throw(CommandFail("Unknown config type value '"+matches[1]+"'"));
    }
    
    return CoreScalar(0);
}

CoreScalar
GameWebCommands::DisplayModesWrite(CoreCommand& ioCommand, CoreEnv& ioEnv)
{

    U32 selectedMode=GameConfig::Instance().DisplayModeGet();
    U32 size=PlatformVideoUtils::Instance().NumModesGet();

    ioEnv.Out() << "<select name=\"displaymode\">" << endl;
    for (U32 i=0; i<size; ++i)
    {
        ioEnv.Out() << "<option value=\"" << i << "\"";
        if (i == selectedMode) ioEnv.Out() << " selected";
        ioEnv.Out() << ">" << PlatformVideoUtils::Instance().ModeDefGet(i).NameGet() << "</option>" << endl;
    }
    ioEnv.Out() << "</select>" << endl;
    return CoreScalar(0);
}

CoreScalar
GameWebCommands::GameConfigInputWrite(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(CommandFail("Usage: gameconfiginputwrite(name)"));
    }
    
    string dataName;
    ioCommand.PopParam(dataName);

    if (!CoreData<GameConfigDef>::Instance().DataExists(dataName))
    {
        throw(CommandFail("Config value '"+dataName+"' does not exist"));
    }
    CoreData<GameConfigDef>::Instance().DataGet(dataName)->WebInputPrint(ioEnv.Out(), dataName);
    
    return CoreScalar(0);
}

void
GameWebCommands::Install(void)
{
    CoreApp::Instance().AddHandler("handlepostvalues", HandlePostValues);
    CoreApp::Instance().AddHandler("displaymodeswrite", DisplayModesWrite);
    CoreApp::Instance().AddHandler("gameconfiginputwrite", GameConfigInputWrite);
}
