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
 * $Id: GameWebCommands.cpp,v 1.24 2002/12/29 20:59:58 southa Exp $
 * $Log: GameWebCommands.cpp,v $
 * Revision 1.24  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.23  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.22  2002/12/12 18:38:58  southa
 * Mustl separation
 *
 * Revision 1.21  2002/12/12 14:00:40  southa
 * Created Mustl
 *
 * Revision 1.20  2002/12/05 23:52:52  southa
 * Network management and status
 *
 * Revision 1.19  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.18  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.17  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.16  2002/11/28 18:05:36  southa
 * Print link ages
 *
 * Revision 1.15  2002/11/28 16:19:25  southa
 * Fix delete object messaging
 *
 * Revision 1.14  2002/11/28 12:05:45  southa
 * Server name work
 *
 * Revision 1.13  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.12  2002/11/27 20:17:27  southa
 * Basic network cleardown
 *
 * Revision 1.11  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.10  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
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
#include "GameNetUtils.h"

#include "mushCore.h"
#include "mushMedia.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller GameWebCommandsInstaller(GameWebCommands::Install);

MushcoreScalar
GameWebCommands::HandlePostValues(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(CommandFail("Usage: handlepostvalues(values)"));
    }
    string values;
    ioCommand.PopParam(values);

    MushcoreRegExp re("(^|&)type=([^&]+)($|&)");
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
        GameNetUtils::KillServers();
        GameNetUtils::KillClients();

        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Instance());
        gameHandler.GameModeEnter(false);
    }
    else if (matches[1] == "mpentergame")
    {
        GameConfig::Instance().PostDataHandle(values);
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Instance());
        gameHandler.GameModeEnter(false);
    }
    else if (matches[1] == "resumegame")
    {
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Instance());
        gameHandler.GameModeEnter(true); // Resume game
    }
    else if (matches[1] == "endcurrentgame")
    {
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Instance());
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
        GameDefClient *gameDefClient = MushcoreData<GameDefClient>::Instance().Give(clientName, new GameDefClient(clientName));
        try
        {
            gameDefClient->JoinGame(GameConfig::Instance().ParameterGet("mpjoinserver").StringGet(),
                                    GameConfig::Instance().ParameterGet("mpjoinport").U32Get());
        }
        catch (MustlFail& e)
        {
            ostringstream message;
            message << "Join game failed: " << e.what() << endl;
            PlatformMiscUtils::MinorErrorBox(message.str());
            MustlLog::Instance().NetLog() << message.str() << endl;
            gameDefClient->Kill();
        }
    }
    else if (matches[1] == "hostgame")
    {
        GameConfig::Instance().PostDataHandle(values);
        string serverName=GameConfig::Instance().ParameterGet("mpservername").StringGet();
        string serverMessage=GameConfig::Instance().ParameterGet("mpservermessage").StringGet();
        GameDefServer *gameDefServer = MushcoreData<GameDefServer>::Instance().Give(serverName, new GameDefServer(serverName));
        gameDefServer->ServerMessageSet(serverMessage);
        gameDefServer->HostGame(GameConfig::Instance().ParameterGet("mpcontractname").StringGet(),
                               GameConfig::Instance().ParameterGet("mpplayerlimit").U32Get());
    }
    else if (matches[1] == "linkcleardown")
    {
        GameNetUtils::KillLinks();
    }
    else if (matches[1] == "hostcleardown")
    {
        // Kill server first so that it can tell anything with a client image that it's going
        GameNetUtils::KillServers();
        GameNetUtils::KillClientImages();
    }
    else if (matches[1] == "joincleardown")
    {
        // Kill clients first so that they can tell the servers with images that they're going
        GameNetUtils::KillClients();
        GameNetUtils::KillServerImages();
    }
    else if (matches[1] == "quit")
    {
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Instance());
        gameHandler.QuitModeEnter(); // Quit application
    }
    else
    {
        throw(CommandFail("Unknown config type value '"+matches[1]+"'"));
    }
    
    return MushcoreScalar(0);
}

MushcoreScalar
GameWebCommands::DisplayModesWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
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
    return MushcoreScalar(0);
}

MushcoreScalar
GameWebCommands::GameConfigInputWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(CommandFail("Usage: gameconfiginputwrite(name)"));
    }
    
    string dataName;
    ioCommand.PopParam(dataName);

    if (!MushcoreData<GameConfigDef>::Instance().Exists(dataName))
    {
        throw(CommandFail("Config value '"+dataName+"' does not exist"));
    }
    MushcoreData<GameConfigDef>::Instance().Get(dataName)->WebInputPrint(ioEnv.Out(), dataName);
    
    return MushcoreScalar(0);
}

MushcoreScalar
GameWebCommands::GameStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    time_t now(time(NULL));
    ioEnv.Out() << "Status at " << ctime(&now);
    ioEnv.Out() << "<br>Server: ";
    if (MustlServer::Instance().IsServing())
    {
        ioEnv.Out() << "Serving on port " << MustlServer::Instance().ServerPortHostOrderGet();
    }
    else
    {
        ioEnv.Out() << "Not active";
    }
    ioEnv.Out() << endl;
    
    return MushcoreScalar(0);
}

MushcoreScalar
GameWebCommands::GameServerStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    // Server state
    ioEnv.Out() << "<table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;
    ioEnv.Out() << "<tr>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Server</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Address</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Contract</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Player Limit</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Status</font></td>";
    ioEnv.Out() << "</tr>";

    {
        MushcoreData<GameDefServer>::tMapIterator endValue=MushcoreData<GameDefServer>::Instance().End();

        for (MushcoreData<GameDefServer>::tMapIterator p=MushcoreData<GameDefServer>::Instance().Begin(); p != endValue; ++p)
        {
            if (!p->second->ImageIs())
            {
                p->second->WebPrint(ioEnv.Out());
            }
        }
    }
    
    ioEnv.Out() << "</table>" << endl;
    ioEnv.Out() << "<table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;

    ioEnv.Out() << "<tr>";
    GameDefClient::WebHeaderPrint(ioEnv.Out());
    ioEnv.Out() << "</tr>";

    {
        MushcoreData<GameDefClient>::tMapIterator endValue=MushcoreData<GameDefClient>::Instance().End();

        // Client images for server
        for (MushcoreData<GameDefClient>::tMapIterator p=MushcoreData<GameDefClient>::Instance().Begin(); p != endValue; ++p)
        {
            if (p->second->ImageIs())
            {
                p->second->WebPrint(ioEnv.Out());
            }
        }
    }
    ioEnv.Out() << "</table>" << endl;

    return MushcoreScalar(0);
}

MushcoreScalar
GameWebCommands::GameClientStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    ioEnv.Out() << "<table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;
    ioEnv.Out() << "<tr>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Server</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Address</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Contract</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Player Limit</font></td>";
    ioEnv.Out() << "<td class=\"bgred\"><font class=\"bold\">Status</font></td>";
    ioEnv.Out() << "</tr>";

    {
        // Server images
        MushcoreData<GameDefServer>::tMapIterator endValue=MushcoreData<GameDefServer>::Instance().End();

        for (MushcoreData<GameDefServer>::tMapIterator p=MushcoreData<GameDefServer>::Instance().Begin(); p != endValue; ++p)
        {
            if (p->second->ImageIs())
            {
                p->second->WebPrint(ioEnv.Out());
            }
        }
    }
    
    ioEnv.Out() << "</table>" << endl;
    ioEnv.Out() << "<table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;

    ioEnv.Out() << "<tr>";
    GameDefClient::WebHeaderPrint(ioEnv.Out());
    ioEnv.Out() << "</tr>";

    {
        MushcoreData<GameDefClient>::tMapIterator endValue=MushcoreData<GameDefClient>::Instance().End();
        // Local clients
        for (MushcoreData<GameDefClient>::tMapIterator p=MushcoreData<GameDefClient>::Instance().Begin(); p != endValue; ++p)
        {
            if (!p->second->ImageIs())
            {
                ioEnv.Out() << "<tr>";
                p->second->WebPrint(ioEnv.Out());
                ioEnv.Out() << "</tr>";
            }
        }
    }

    ioEnv.Out() << "</table>" << endl;
    
    return MushcoreScalar(0);
}

MushcoreScalar
GameWebCommands::GameLinkStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    
    // Link status
    ioEnv.Out() << "<font class=\"boldtitle\">Link Status</font>" << endl;

    ioEnv.Out() << "<br><br><table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;

    MustlLink::WebStatusHeaderPrint(ioEnv.Out());

    MushcoreData<MustlLink>::tMapIterator endValue=MushcoreData<MustlLink>::Instance().End();

    for (MushcoreData<MustlLink>::tMapIterator p=MushcoreData<MustlLink>::Instance().Begin();
         p != endValue; ++p)
    {
        ioEnv.Out() << "<tr>";
        p->second->WebStatusPrint(ioEnv.Out());
        ioEnv.Out() << "</tr>";
    }
    ioEnv.Out() << "</table>" << endl;

    return MushcoreScalar(0);
}

void
GameWebCommands::Install(void)
{
    MushcoreApp::Instance().AddHandler("handlepostvalues", HandlePostValues);
    MushcoreApp::Instance().AddHandler("displaymodeswrite", DisplayModesWrite);
    MushcoreApp::Instance().AddHandler("gameconfiginputwrite", GameConfigInputWrite);
    MushcoreApp::Instance().AddHandler("gamestatuswrite", GameStatusWrite);
    MushcoreApp::Instance().AddHandler("gameserverstatuswrite", GameServerStatusWrite);
    MushcoreApp::Instance().AddHandler("gameclientstatuswrite", GameClientStatusWrite);
    MushcoreApp::Instance().AddHandler("gamelinkstatuswrite", GameLinkStatusWrite);
}
