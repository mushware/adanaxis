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
 * $Id: GameAppHandler.cpp,v 1.41 2002/12/29 20:59:53 southa Exp $
 * $Log: GameAppHandler.cpp,v $
 * Revision 1.41  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.40  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.39  2002/12/04 12:54:40  southa
 * Network control work
 *
 * Revision 1.38  2002/12/03 20:28:15  southa
 * Network, player and control work
 *
 * Revision 1.37  2002/11/20 22:35:25  southa
 * Multiplayer setup
 *
 * Revision 1.36  2002/11/18 18:55:57  southa
 * Game resume and quit
 *
 * Revision 1.35  2002/11/18 14:11:04  southa
 * win32 support
 *
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
 * MushcoreXML loader
 *
 * Revision 1.5  2002/05/25 17:16:14  southa
 * MushcoreXML implementation
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

#include "GameConfig.h"
#include "GameContract.h"
#include "GameData.h"
#include "GameDefClient.h"
#include "GameDefServer.h"
#include "GameFloorMap.h"
#include "GameGlobalConfig.h"
#include "GameQuit.h"
#include "GameSetup.h"

#include "mushMedia.h"

using namespace Mushware;
using namespace std;

GameAppHandler::GameAppHandler() :
    m_pSetup(NULL),
    m_pGame(NULL),
    m_pCurrent(NULL),
    m_appState(kAppStateStartup),
    m_gameType(kGameTypeInvalid)
{
    MushcoreEnv::Instance().PushConfig(GameGlobalConfig::Instance());
}

GameAppHandler::~GameAppHandler()
{
    MushcoreEnv::Instance().PopConfig(GameGlobalConfig::Instance());
    if (m_pSetup != NULL) delete m_pSetup;
    if (m_pGame != NULL) delete m_pGame;
}

void
GameAppHandler::Initialise(void)
{
    Idle();
}

void
GameAppHandler::Display(void)
{
    if (m_pCurrent != NULL)
    {
        m_pCurrent->Display(*this);
    }
}

void
GameAppHandler::Idle(void)
{
    try
    {
        if (m_pCurrent == NULL)
        {
            SetupModeEnter();
        }
        else
        {
            m_pCurrent->Process(*this);
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
    if (m_appState != kAppStateSetup)
    {
        if (m_pCurrent != NULL)
        {
            m_pCurrent->SwapOut(*this);
        }
        if (m_pSetup == NULL) m_pSetup = new GameSetup;
        m_pCurrent=m_pSetup;
        m_pCurrent->SwapIn(*this);
        m_appState=kAppStateSetup;
    }   
}

void
GameAppHandler::GameModeEnter(bool inResume)
{
    if (m_appState != kAppStateGame)
    {
        if (m_pCurrent != NULL)
        {
            m_pCurrent->SwapOut(*this);
        }

        if (!inResume || !GameData::Instance().ContractExists("contract1"))
        {
            PrepareNewGame();
        }
        m_pGame=GameData::Instance().ContractGet("contract1");

        COREASSERT(m_pGame != NULL);
        m_pCurrent=m_pGame;
        m_pCurrent->SwapIn(*this);
        m_appState=kAppStateGame;
    }
}

void
GameAppHandler::QuitModeEnter(void)
{
    if (m_appState != kAppStateQuit)
    {
        m_pCurrent=new GameQuit;  // leaked
    }
}

void
GameAppHandler::GameTypeDetermine(void)
{
    m_gameType = kGameTypeInvalid;
    
    MushcoreData<GameDefServer>::tMapIterator endValue = MushcoreData<GameDefServer>::Instance().End();

    for (MushcoreData<GameDefServer>::tMapIterator p = MushcoreData<GameDefServer>::Instance().Begin(); p != endValue; ++p)
    {
        if (!p->second->ImageIs())
        {
            m_gameType = kGameTypeServer;
        }
    }

    if (m_gameType == kGameTypeInvalid)
    {
        MushcoreData<GameDefClient>::tMapIterator endValue = MushcoreData<GameDefClient>::Instance().End();

        for (MushcoreData<GameDefClient>::tMapIterator p = MushcoreData<GameDefClient>::Instance().Begin(); p != endValue; ++p)
        {
            if (!p->second->ImageIs())
            {
                m_gameType = kGameTypeClient;
            }
        }
    }

    if (m_gameType == kGameTypeInvalid)
    {
        m_gameType = kGameTypeSingle;
    }
}

void
GameAppHandler::PrepareNewGame(void)
{
    m_pGame = NULL; // We're about to delete this
    
    // Work out what the game type is
    GameTypeDetermine();

    // Delete the old contract and all of its data
    GameData::Instance().Clear();

    // Create the contract path
    string contractRoot=MushcoreGlobalConfig::Instance().Get("CONTRACT_ROOT").StringGet();
    string contractName;
    if (MultiplayerIs())
    {
        contractName=GameConfig::Instance().ParameterGet("mpcontractname").StringGet();
    }
    else
    {
        contractName=GameConfig::Instance().ParameterGet("spcontractname").StringGet();
    }
    string contractPath=contractRoot+"/"+contractName;
    MushcoreGlobalConfig::Instance().Set("CONTRACT_PATH", contractPath);

    MushcoreCommand command("loadcontract('contract1',$CONTRACT_PATH+'/contract.xml')");
    command.Execute();
    
    // Get a pointer to the newly created contract
    m_pGame=GameData::Instance().ContractGet("contract1");
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

void
GameAppHandler::CurrentGameEnd(void)
{
    SetupModeEnter();
    m_pGame=NULL;
    GameData::Instance().Clear();
}
