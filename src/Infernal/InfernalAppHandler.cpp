//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalAppHandler.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } qEKzkDDSG7ZROztf+xl76w
/*
 * $Id: InfernalAppHandler.cpp,v 1.7 2004/09/28 23:05:53 southa Exp $
 * $Log: InfernalAppHandler.cpp,v $
 * Revision 1.7  2004/09/28 23:05:53  southa
 * MSVC build of ic2
 *
 * Revision 1.6  2004/09/26 20:43:19  southa
 * TestMustl fixes
 *
 * Revision 1.5  2004/03/06 13:13:42  southa
 * Maurheen created
 *
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

        if (!inResume || !MushcoreData<GameBase>::Sgl().Exists("contract1"))
        {
            PrepareNewGame();
        }
        m_pGame=MushcoreData<GameBase>::Sgl().Get("contract1");

        MUSHCOREASSERT(m_pGame != NULL);
        CurrentSwapIn("contract1");
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
    m_pGame=MushcoreData<GameBase>::Sgl().Get("contract1");
}

void
InfernalAppHandler::CurrentGameEnd(void)
{
    SetupModeEnter();
    m_pGame=NULL;
    InfernalData::Sgl().Clear();
}
