//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalAppHandler.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } OK79NjKAFVFPIyTLS5wV9g
/*
 * $Id: InfernalAppHandler.cpp,v 1.4 2004/01/06 20:46:50 southa Exp $
 * $Log: InfernalAppHandler.cpp,v $
 * Revision 1.4  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/01 23:04:02  southa
 * XCode fixes
 *
 * Revision 1.2  2004/01/01 21:15:45  southa
 * Created XCode project
 *
 * Revision 1.1  2003/10/04 15:32:09  southa
 * Module split
 *
 */

#include "InfernalAppHandler.h"

#include "InfernalContract.h"
#include "InfernalData.h"
#include "InfernalFloorMap.h"
#include "InfernalInfo.h"
#include "InfernalSTL.h"
#include "InfernalWebCommands.h"

#include "mushMushcore.h"
#include "mushGL.h"
#include "mushGame.h"
#include "mushMedia.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

InfernalAppHandler::InfernalAppHandler() :
    m_pGame(NULL)
{
}

InfernalAppHandler::~InfernalAppHandler()
{
    if (m_pGame != NULL) delete m_pGame;
}

void
InfernalAppHandler::Initialise(void)
{
    GameAppHandler::Initialise();
    MushcoreInfo::SingletonMutate(new InfernalInfo);
    InfernalWebCommands::Install();
}

void
InfernalAppHandler::GameModeEnter(bool inResume)
{
    if (!StateGameIs())
    {
        CurrentSwapOut();

        if (!inResume || !InfernalData::Sgl().ContractExists("contract1"))
        {
            PrepareNewGame();
        }
        m_pGame=InfernalData::Sgl().ContractGet("contract1");

        MUSHCOREASSERT(m_pGame != NULL);
        CurrentSwapIn(m_pGame);
        StateGameSet();
    }
}

void
InfernalAppHandler::PrepareNewGame(void)
{
    m_pGame = NULL; // We're about to delete this
    
    // Work out what the game type is
    GameTypeDetermine();

    // Delete the old contract and all of its data
    InfernalData::Sgl().Clear();

    // Create the contract path
    string contractRoot=MushcoreGlobalConfig::Sgl().Get("CONTRACT_ROOT").StringGet();
    string contractName;
    if (MultiplayerIs())
    {
        contractName=GameConfig::Sgl().ParameterGet("mpcontractname").StringGet();
    }
    else
    {
        contractName=GameConfig::Sgl().ParameterGet("spcontractname").StringGet();
    }
    string contractPath=contractRoot+"/"+contractName;
    MushcoreGlobalConfig::Sgl().Set("CONTRACT_PATH", contractPath);

    MushcoreCommand command("loadcontract('contract1',$CONTRACT_PATH+'/contract.xml')");
    command.Execute();
    
    // Get a pointer to the newly created contract
    m_pGame=InfernalData::Sgl().ContractGet("contract1");
}

void
InfernalAppHandler::CurrentGameEnd(void)
{
    SetupModeEnter();
    m_pGame=NULL;
    InfernalData::Sgl().Clear();
}
