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
 * $Id: GameAppHandler.cpp,v 1.34 2002/11/18 11:31:13 southa Exp $
 * $Log: GameAppHandler.cpp,v $
 * Revision 1.34  2002/11/18 11:31:13  southa
 * Return to game mode
 *
 * Revision 1.33  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.32  2002/11/16 12:43:20  southa
 * GameApp mode switching
 *
 * Revision 1.31  2002/11/15 18:58:33  southa
 * Configuration mode
 *
 * Revision 1.30  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.29  2002/10/17 12:35:29  southa
 * Save path and update check
 *
 * Revision 1.28  2002/10/15 19:04:09  southa
 * Windows error box
 *
 * Revision 1.27  2002/10/15 14:02:30  southa
 * Mode changes
 *
 * Revision 1.26  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 * Revision 1.25  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.24  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.23  2002/07/19 15:44:40  southa
 * Graphic optimisations
 *
 * Revision 1.22  2002/07/10 16:37:39  southa
 * Cursor removal
 *
 * Revision 1.21  2002/07/08 14:22:02  southa
 * Rotated desks
 *
 * Revision 1.20  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.19  2002/07/02 14:27:08  southa
 * First floor map designer build
 *
 * Revision 1.18  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.17  2002/06/23 10:42:34  southa
 * SDL input
 *
 * Revision 1.16  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 * Revision 1.15  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.14  2002/06/20 11:06:14  southa
 * Updated for cygwin
 *
 * Revision 1.13  2002/06/13 15:15:55  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.12  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 * Revision 1.11  2002/06/04 20:27:35  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.10  2002/06/02 16:41:18  southa
 * Rotated sprite plotting
 *
 * Revision 1.9  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.8  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
 * Revision 1.7  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
 * Revision 1.6  2002/05/26 16:08:48  southa
 * CoreXML loader
 *
 * Revision 1.5  2002/05/25 17:16:14  southa
 * CoreXML implementation
 *
 * Revision 1.4  2002/05/24 16:23:07  southa
 * Config and typenames
 *
 * Revision 1.3  2002/05/10 22:38:22  southa
 * Checkpoint
 *
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "GameAppHandler.h"

#include "mushCore.h"
#include "mushGL.h"
#include "mushPlatform.h"

#include "GameContract.h"
#include "GameGlobalConfig.h"
#include "GameFloorMap.h"
#include "GameData.h"
#include "GameConfig.h"
#include "GameSetup.h"

#include "mushMedia.h"

GameAppHandler::GameAppHandler() :
    m_pSetup(NULL),
    m_pGame(NULL),
    m_appState(kAppStateStartup)
{
}

GameAppHandler::~GameAppHandler()
{
    if (m_pSetup != NULL) delete m_pSetup;
    if (m_pGame != NULL) delete m_pGame;
}

void
GameAppHandler::Initialise(void)
{
    CoreEnv::Instance().PushConfig(GameGlobalConfig::Instance());
    Idle();
}

void
GameAppHandler::Display(void)
{
    switch (m_appState)
    {
        case kAppStateSetup:
            COREASSERT(m_pSetup != NULL);
            m_pSetup->Display();
            break;

        case kAppStateGame:
            COREASSERT(m_pGame != NULL);
            m_pGame->Display();
            break;

        case kAppStateStartup:
            break;
            
        default:
            throw(LogicFail("Bad value for m_appState"));
    }
}

void
GameAppHandler::Idle(void)
{
    try
    {
        switch (m_appState)
        {
            case kAppStateSetup:
                COREASSERT(m_pSetup != NULL);
                m_pSetup->Process();
                break;

            case kAppStateGame:
                COREASSERT(m_pGame != NULL);
                m_pGame->Process();
                break;

            case kAppStateStartup:
                SetupModeEnter();
                break;
                
            default:
                throw(LogicFail("Bad value for m_appState"));
        }
    }
    catch (exception& e)
    {
        cerr << "Exception in idle handler: " << e.what() << endl;

        PlatformMiscUtils::ErrorBox(string("Error: ") + e.what());
        exit(1);
    }
}

void
GameAppHandler::SetupModeEnter(void)
{
    switch (m_appState)
    {
        case kAppStateGame:
            COREASSERT(m_pGame != NULL);
            m_pGame->SwapOut();
            // Drop through
        case kAppStateStartup:
            if (m_pSetup == NULL) m_pSetup = new GameSetup;
            m_pSetup->SwapIn();
            m_appState=kAppStateSetup;
            break;

        case kAppStateSetup:
            break;

        default:
            throw(LogicFail("Bad value for m_appState"));
    }
}

void
GameAppHandler::GameModeEnter(bool inResume)
{
    switch (m_appState)
    {
        case kAppStateSetup:
            COREASSERT(m_pSetup != NULL);
            m_pSetup->SwapOut();
            // Drop through
        case kAppStateStartup:
            if (!inResume || !GameData::Instance().ContractExists("contract1"))
            {
                PrepareNewGame();
            }
            m_pGame=GameData::Instance().ContractGet("contract1");
                
            COREASSERT(m_pGame != NULL);
            m_pGame->SwapIn();
            m_appState=kAppStateGame;
            break;

        case kAppStateGame:
            break;

        default:
            throw(LogicFail("Bad value for m_appState"));
    }
}

void
GameAppHandler::PrepareNewGame(void)
{
    // Needs to be done in GameContract
    string contractRoot=CoreGlobalConfig::Instance().Get("CONTRACT_ROOT").StringGet();
    string contractName=GameConfig::Instance().ParameterGet("contractname").StringGet();
    string contractPath=contractRoot+"/"+contractName;
    CoreGlobalConfig::Instance().Set("CONTRACT_PATH", contractPath);

    CoreCommand command("loadcontract('contract1',$CONTRACT_PATH+'/contract.xml')");
    command.Execute();
    m_pGame=GameData::Instance().ContractGet("contract1");
    m_pGame->ScriptFunction("load");
}

void
GameAppHandler::KeyboardSignal(const GLKeyboardSignal& inSignal)
{
    bool keyHandled=false;
    if (inSignal.keyValue.ValueGet() == 27 && inSignal.keyDown)
    {
        if (m_appState == kAppStateGame)
        {
            SetupModeEnter();
            keyHandled=true;
        }
    }
    if (!keyHandled)
    {
        SDLAppHandler::KeyboardSignal(inSignal);
    }
}
