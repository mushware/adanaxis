//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenAppHandler.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } OijCRan1HZZfoJthbqALOw
/*
 * $Id: MaurheenAppHandler.cpp,v 1.3 2004/01/06 20:46:51 southa Exp $
 * $Log: MaurheenAppHandler.cpp,v $
 */

#include "MaurheenAppHandler.h"

#include "MaurheenSTL.h"

#include "mushMushcore.h"
#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

#include "MaurheenGame.h"

using namespace Mushware;
using namespace std;

MaurheenAppHandler::MaurheenAppHandler()
{
}

MaurheenAppHandler::~MaurheenAppHandler()
{
}

void
MaurheenAppHandler::GameModeEnter(bool inResume)
{
    if (!StateGameIs())
    {
        CurrentSwapOut();
        
        if (!inResume || !MushcoreData<GameBase>::Sgl().Exists("maurheen"))
        {
            PrepareNewGame();
        }
        CurrentSwapIn("maurheen");
        StateGameSet();
    }
}

void
MaurheenAppHandler::PrepareNewGame(void)
{
    MushcoreData<GameBase>::Sgl().Give("maurheen", new MaurheenGame);
}

void
MaurheenAppHandler::CurrentGameEnd(void)
{
    SetupModeEnter();
    MushcoreData<GameBase>::Sgl().Delete("maurheen");
}
