//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalWebCommands.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Oqf24n6H6L5K+Ki53Vpj+Q
/*
 * $Id: InfernalWebCommands.cpp,v 1.2 2003/10/04 15:32:12 southa Exp $
 * $Log: InfernalWebCommands.cpp,v $
 * Revision 1.2  2003/10/04 15:32:12  southa
 * Module split
 *
 * Revision 1.1  2003/10/04 12:23:07  southa
 * File renaming
 *
 * Revision 1.35  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.34  2003/08/21 23:08:59  southa
 * Fixed file headers
 *
 * Revision 1.33  2003/01/20 12:23:22  southa
 * Code and interface tidying
 *
 * Revision 1.32  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.31  2003/01/17 13:30:39  southa
 * Source conditioning and build fixes
 *
 * Revision 1.30  2003/01/14 17:38:20  southa
 * Mustl web configuration
 *
 * Revision 1.29  2003/01/13 14:32:01  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.28  2003/01/12 17:32:57  southa
 * Mushcore work
 *
 * Revision 1.27  2003/01/11 17:07:52  southa
 * Mushcore library separation
 *
 * Revision 1.26  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.25  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
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

#include "InfernalWebCommands.h"

#include "mushGame.h"
#include "InfernalSTL.h"

#include "Mushcore.h"
#include "mushMedia.h"
#include "mushMustlGame.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller InfernalWebCommandsInstaller(InfernalWebCommands::Install);

MushcoreScalar
InfernalWebCommands::PostHandler(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: posthandler(type, valueStr)"));
    }
    string typeStr, valueStr;
    ioCommand.PopParam(typeStr);
    ioCommand.PopParam(valueStr);

    if (typeStr == "config1" ||
        typeStr == "developer1")
    {
        GameConfig::Sgl().PostDataHandle(valueStr);
        GameConfig::Sgl().Update();
    }
    else if (typeStr == "singleplayer")
    {
        GameConfig::Sgl().PostDataHandle(valueStr);
        MustlGameUtils::KillServers();
        MustlGameUtils::KillClients();

        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
        gameHandler.GameModeEnter(false);
    }
    else if (typeStr == "mpentergame")
    {
        GameConfig::Sgl().PostDataHandle(valueStr);
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
        gameHandler.GameModeEnter(false);
    }
    else if (typeStr == "resumegame")
    {
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
        gameHandler.GameModeEnter(true); // Resume game
    }
    else if (typeStr == "endcurrentgame")
    {
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
        gameHandler.CurrentGameEnd(); // End the game
    }
    else if (typeStr == "mplogin")
    {
        GameConfig::Sgl().PostDataHandle(valueStr);
    }
    else if (typeStr == "joingame")
    {
        GameConfig::Sgl().PostDataHandle(valueStr);
        string clientName = GameConfig::Sgl().ParameterGet("mpplayername").StringGet();
        MustlGameClient *gameDefClient = MushcoreData<MustlGameClient>::Sgl().Give(clientName, new MustlGameClient(clientName));
        try
        {
            gameDefClient->JoinGame(GameConfig::Sgl().ParameterGet("mpjoinserver").StringGet(),
                                    GameConfig::Sgl().ParameterGet("mpjoinport").U32Get());
        }
        catch (MushcoreNonFatalFail& e)
        {
            ostringstream message;
            message << "Join game failed: " << e.what() << endl;
            PlatformMiscUtils::MinorErrorBox(message.str());
            MustlLog::Sgl().NetLog() << message.str() << endl;
            gameDefClient->Kill();
        }
    }
    else if (typeStr == "hostgame")
    {
        GameConfig::Sgl().PostDataHandle(valueStr);
        string serverName=GameConfig::Sgl().ParameterGet("mpservername").StringGet();
        string serverMessage=GameConfig::Sgl().ParameterGet("mpservermessage").StringGet();
        MustlGameServer *gameDefServer = MushcoreData<MustlGameServer>::Sgl().Give(serverName, new MustlGameServer(serverName));
        gameDefServer->ServerMessageSet(serverMessage);
        gameDefServer->HostGame(GameConfig::Sgl().ParameterGet("mpcontractname").StringGet(),
                               GameConfig::Sgl().ParameterGet("mpplayerlimit").U32Get());
    }
    else if (typeStr == "linkcleardown")
    {
        MustlGameUtils::KillLinks();
    }
    else if (typeStr == "hostcleardown")
    {
        // Kill server first so that it can tell anything with a client image that it's going
        MustlGameUtils::KillServers();
        MustlGameUtils::KillClientImages();
    }
    else if (typeStr == "joincleardown")
    {
        // Kill clients first so that they can tell the servers with images that they're going
        MustlGameUtils::KillClients();
        MustlGameUtils::KillServerImages();
    }
    else if (typeStr == "quit")
    {
        GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
        gameHandler.QuitModeEnter(); // Quit application
    }
    else
    {
        throw(MushcoreCommandFail("Unknown config type value '"+typeStr+"'"));
    }
    
    return MushcoreScalar(0);
}

MushcoreScalar
InfernalWebCommands::DisplayModesWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{

    U32 selectedMode=GameConfig::Sgl().DisplayModeGet();
    U32 size=PlatformVideoUtils::Sgl().NumModesGet();

    ioEnv.Out() << "<select name=\"displaymode\">" << endl;
    for (U32 i=0; i<size; ++i)
    {
        ioEnv.Out() << "<option value=\"" << i << "\"";
        if (i == selectedMode) ioEnv.Out() << " selected";
        ioEnv.Out() << ">" << PlatformVideoUtils::Sgl().ModeDefGet(i).NameGet() << "</option>" << endl;
    }
    ioEnv.Out() << "</select>" << endl;
    return MushcoreScalar(0);
}

MushcoreScalar
InfernalWebCommands::GameConfigInputWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MushcoreCommandFail("Usage: gameconfiginputwrite(name)"));
    }
    
    string dataName;
    ioCommand.PopParam(dataName);

    if (!MushcoreData<GameConfigDef>::Sgl().Exists(dataName))
    {
        throw(MushcoreCommandFail("Config value '"+dataName+"' does not exist"));
    }
    MushcoreData<GameConfigDef>::Sgl().Get(dataName)->WebInputPrint(ioEnv.Out(), dataName);
    
    return MushcoreScalar(0);
}

MushcoreScalar
InfernalWebCommands::GameStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    time_t now(time(NULL));
    ioEnv.Out() << "Status at " << ctime(&now);
    ioEnv.Out() << "<br>Server: ";
    if (MustlServer::Sgl().IsServing())
    {
        ioEnv.Out() << "Serving on port " << MustlServer::Sgl().ServerPortHostOrderGet();
    }
    else
    {
        ioEnv.Out() << "Not active";
    }
    ioEnv.Out() << endl;
    
    return MushcoreScalar(0);
}

MushcoreScalar
InfernalWebCommands::GameServerStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
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
        MushcoreData<MustlGameServer>::tMapIterator endValue=MushcoreData<MustlGameServer>::Sgl().End();

        for (MushcoreData<MustlGameServer>::tMapIterator p=MushcoreData<MustlGameServer>::Sgl().Begin(); p != endValue; ++p)
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
    MustlGameClient::WebHeaderPrint(ioEnv.Out());
    ioEnv.Out() << "</tr>";

    {
        MushcoreData<MustlGameClient>::tMapIterator endValue=MushcoreData<MustlGameClient>::Sgl().End();

        // Client images for server
        for (MushcoreData<MustlGameClient>::tMapIterator p=MushcoreData<MustlGameClient>::Sgl().Begin(); p != endValue; ++p)
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
InfernalWebCommands::GameClientStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
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
        MushcoreData<MustlGameServer>::tMapIterator endValue=MushcoreData<MustlGameServer>::Sgl().End();

        for (MushcoreData<MustlGameServer>::tMapIterator p=MushcoreData<MustlGameServer>::Sgl().Begin(); p != endValue; ++p)
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
    MustlGameClient::WebHeaderPrint(ioEnv.Out());
    ioEnv.Out() << "</tr>";

    {
        MushcoreData<MustlGameClient>::tMapIterator endValue=MushcoreData<MustlGameClient>::Sgl().End();
        // Local clients
        for (MushcoreData<MustlGameClient>::tMapIterator p=MushcoreData<MustlGameClient>::Sgl().Begin(); p != endValue; ++p)
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
InfernalWebCommands::GameLinkStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    
    // Link status
    ioEnv.Out() << "<font class=\"boldtitle\">Link Status</font>" << endl;

    ioEnv.Out() << "<br><br><table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;

    MustlLink::WebStatusHeaderPrint(ioEnv.Out());

    MushcoreData<MustlLink>::tMapIterator endValue=MushcoreData<MustlLink>::Sgl().End();

    for (MushcoreData<MustlLink>::tMapIterator p=MushcoreData<MustlLink>::Sgl().Begin();
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
InfernalWebCommands::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("posthandler", PostHandler);
    MushcoreInterpreter::Sgl().HandlerAdd("displaymodeswrite", DisplayModesWrite);
    MushcoreInterpreter::Sgl().HandlerAdd("gameconfiginputwrite", GameConfigInputWrite);
    MushcoreInterpreter::Sgl().HandlerAdd("gamestatuswrite", GameStatusWrite);
    MushcoreInterpreter::Sgl().HandlerAdd("gameserverstatuswrite", GameServerStatusWrite);
    MushcoreInterpreter::Sgl().HandlerAdd("gameclientstatuswrite", GameClientStatusWrite);
    MushcoreInterpreter::Sgl().HandlerAdd("gamelinkstatuswrite", GameLinkStatusWrite);
}
