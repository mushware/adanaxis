//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalAppHandler.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 6AHzwdD+EmoONGGTmxE7Fw
/*
 * $Id: InfernalAppHandler.cpp,v 1.9 2006/06/01 15:39:01 southa Exp $
 * $Log: InfernalAppHandler.cpp,v $
 * Revision 1.9  2006/06/01 15:39:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:04  southa
 * Mac release work
 *
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
