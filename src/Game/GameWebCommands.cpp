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
 * $Id: GameWebCommands.cpp,v 1.9 2002/11/25 18:02:57 southa Exp $
 * $Log: GameWebCommands.cpp,v $
 * Revision 1.9  2002/11/25 18:02:57  southa
 * Mushware ID work
 *
 * Revision 1.8  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 * Revision 1.7  2002/11/24 22:32:43  southa
 * Host and join displays
 *
 * Revision 1.6  2002/11/23 14:45:34  southa
 * Replaced access to server port
 *
 * Revision 1.5  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.4  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 * Revision 1.3  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.2  2002/11/18 18:55:58  southa
 * Game resume and quit
 *
 * Revision 1.1  2002/11/18 13:40:32  southa
 * Moved to correct place
 *
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
#include "GameDefClient.h"
#include "GameDefServer.h"

#include "mushCore.h"
#include "mushMedia.h"
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
    if (matches[1] == "config1" ||
        matches[1] == "developer1")
    {
        GameConfig::Instance().PostDataHandle(values);
        GameConfig::Instance().Update();
    }
    else if (matches[1] == "singleplayer")
    {
        GameConfig::Instance().PostDataHandle(values);
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
        gameHandler.GameModeEnter(false);
    }
    else if (matches[1] == "resumegame")
    {
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
        gameHandler.GameModeEnter(true); // Resume game
    }
    else if (matches[1] == "endcurrentgame")
    {
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
        gameHandler.CurrentGameEnd(); // End the game
    }
    else if (matches[1] == "mplogin")
    {
        GameConfig::Instance().PostDataHandle(values);
    }
    else if (matches[1] == "joingame")
    {
        GameConfig::Instance().PostDataHandle(values);
        string clientName = GameConfig::Instance().ParameterGet("mpplayername").StringGet();
        GameDefClient& gameDefClient = dynamic_cast<GameDefClient&>(*CoreData<GameDef>::Instance().DataGive(clientName, new GameDefClient(clientName)));
        gameDefClient.JoinGame(GameConfig::Instance().ParameterGet("mpjoinserver").StringGet(),
                               GameConfig::Instance().ParameterGet("mpjoinport").U32Get());
    }
    else if (matches[1] == "hostgame")
    {
        GameConfig::Instance().PostDataHandle(values);
        string serverName=GameConfig::Instance().ParameterGet("mpservername").StringGet();
        string serverMessage=GameConfig::Instance().ParameterGet("mpservermessage").StringGet();
        GameDefServer& gameDefServer = dynamic_cast<GameDefServer&>(*CoreData<GameDef>::Instance().DataGive(serverName, new GameDefServer(serverName)));
        gameDefServer.ServerMessageSet(serverMessage);
        gameDefServer.HostGame(GameConfig::Instance().ParameterGet("mpcontractname").StringGet(),
                               GameConfig::Instance().ParameterGet("mpplayerlimit").U32Get());
    }
    else if (matches[1] == "quit")
    {
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
        gameHandler.QuitModeEnter(); // Quit application
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

CoreScalar
GameWebCommands::GameStatusWrite(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    time_t now(time(NULL));
    ioEnv.Out() << "Status at " << ctime(&now);
    ioEnv.Out() << "<br>Server: ";
    if (MediaNetServer::Instance().IsServing())
    {
        ioEnv.Out() << "Serving on port " << MediaNetServer::Instance().ServerPortHostOrderGet();
    }
    else
    {
        ioEnv.Out() << "Not active";
    }
    ioEnv.Out() << endl;
    
    return CoreScalar(0);
}

CoreScalar
GameWebCommands::GameServerStatusWrite(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    // Server state
    ioEnv.Out() << "<table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;
    ioEnv.Out() << "<tr>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Server</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Contract</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Player Limit</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Status</font></td>";
    ioEnv.Out() << "</tr>";
    
    CoreData<GameDef>::tMapIterator endValue=CoreData<GameDef>::Instance().End();

    for (CoreData<GameDef>::tMapIterator p=CoreData<GameDef>::Instance().Begin(); p != endValue; ++p)
    {
        GameDefServer *serverDef = dynamic_cast<GameDefServer *>(p->second);
        if (serverDef != NULL && !serverDef->IsImage())
        {
            serverDef->WebPrint(ioEnv.Out());
        }
    }

    ioEnv.Out() << "</table>" << endl;
    ioEnv.Out() << "<table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;
    
    ioEnv.Out() << "<tr>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Player</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Server</font></td>";

    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Address</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Status</font></td>";
    ioEnv.Out() << "</tr>";

    // Client images for server
    for (CoreData<GameDef>::tMapIterator p=CoreData<GameDef>::Instance().Begin(); p != endValue; ++p)
    {
        GameDefClient *clientDef=dynamic_cast<GameDefClient *>(p->second);
        if (clientDef != NULL && clientDef->IsImage())
        {
            clientDef->WebPrint(ioEnv.Out());
        }
    }

    ioEnv.Out() << "</table>" << endl;

    return CoreScalar(0);
}

CoreScalar
GameWebCommands::GameClientStatusWrite(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    ioEnv.Out() << "<table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;
    ioEnv.Out() << "<tr>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Server</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Contract</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Player Limit</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Status</font></td>";
    ioEnv.Out() << "</tr>";
    
    CoreData<GameDef>::tMapIterator endValue=CoreData<GameDef>::Instance().End();

    // Image of remote server
    for (CoreData<GameDef>::tMapIterator p=CoreData<GameDef>::Instance().Begin(); p != endValue; ++p)
    {
        GameDefServer *serverDef = dynamic_cast<GameDefServer *>(p->second);
        if (serverDef != NULL && serverDef->IsImage())
        {
            serverDef->WebPrint(ioEnv.Out());
        }
    }

    ioEnv.Out() << "</table>" << endl;
    ioEnv.Out() << "<table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;

    ioEnv.Out() << "<tr>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Player</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Server</font></td>";

    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Address</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Status</font></td>";
    ioEnv.Out() << "</tr>";
    
    // Local clients
    for (CoreData<GameDef>::tMapIterator p=CoreData<GameDef>::Instance().Begin(); p != endValue; ++p)
    {
        GameDefClient *clientDef=dynamic_cast<GameDefClient *>(p->second);
        if (clientDef != NULL && !clientDef->IsImage())
        {
            clientDef->WebPrint(ioEnv.Out());
        }
    }

    ioEnv.Out() << "</table>" << endl;
    
    return CoreScalar(0);
}

CoreScalar
GameWebCommands::GameLinkStatusWrite(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    
    // Link status
    ioEnv.Out() << "<br><br><font class=\"boldtitle\">Link Status</font>" << endl;

    ioEnv.Out() << "<br><br><table class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;
    ioEnv.Out() << "<tr class=\"bgred\"><td class=\"bold\">Target IP</td>";
    ioEnv.Out() << "<td class=\"bold\">Remote port</td><td class=\"bold\">Ping</td>" << endl;
    ioEnv.Out() << "<td class=\"bold\">Remote port</td><td class=\"bold\">Ping</td>" << endl;
    ioEnv.Out() << "</tr>" << endl;

    CoreData<MediaNetLink>::tMapIterator endValue=CoreData<MediaNetLink>::Instance().End();

    for (CoreData<MediaNetLink>::tMapIterator p=CoreData<MediaNetLink>::Instance().Begin();
         p != endValue; ++p)
    {
        ioEnv.Out() << "<tr>";
        p->second->WebStatusPrint(ioEnv.Out());
        ioEnv.Out() << "</tr>";
    }
    ioEnv.Out() << "</table>" << endl;

    return CoreScalar(0);
}

void
GameWebCommands::Install(void)
{
    CoreApp::Instance().AddHandler("handlepostvalues", HandlePostValues);
    CoreApp::Instance().AddHandler("displaymodeswrite", DisplayModesWrite);
    CoreApp::Instance().AddHandler("gameconfiginputwrite", GameConfigInputWrite);
    CoreApp::Instance().AddHandler("gamestatuswrite", GameStatusWrite);
    CoreApp::Instance().AddHandler("gameserverstatuswrite", GameServerStatusWrite);
    CoreApp::Instance().AddHandler("gameclientstatuswrite", GameClientStatusWrite);
    CoreApp::Instance().AddHandler("gamelinkstatuswrite", GameLinkStatusWrite);
}
