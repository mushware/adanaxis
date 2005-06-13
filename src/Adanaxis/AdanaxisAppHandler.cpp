//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisAppHandler.cpp
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
//%Header } FKajV+XmiJxXxTV/Dm/mLQ
/*
 * $Id: AdanaxisAppHandler.cpp,v 1.5 2005/06/03 13:36:44 southa Exp $
 * $Log: AdanaxisAppHandler.cpp,v $
 */

#include "AdanaxisAppHandler.h"

#include "AdanaxisSTL.h"

#include "mushMushcore.h"
#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

#include "AdanaxisGame.h"

using namespace Mushware;
using namespace std;

AdanaxisAppHandler::AdanaxisAppHandler()
{
}

AdanaxisAppHandler::~AdanaxisAppHandler()
{
}

void
AdanaxisAppHandler::SetupModeEnter(void)
{
    GameModeEnter(false);
}

void
AdanaxisAppHandler::GameModeEnter(bool inResume)
{
    if (!StateGameIs())
    {
        CurrentSwapOut();
        
        if (!inResume || !MushcoreData<GameBase>::Sgl().Exists("adanaxis"))
        {
            PrepareNewGame();
        }
        CurrentSwapIn("adanaxis");
        StateGameSet();
    }
}

void
AdanaxisAppHandler::PrepareNewGame(void)
{
    
    MushcoreData<GameBase>::Sgl().Give("adanaxis", new AdanaxisGame);
}

void
AdanaxisAppHandler::CurrentGameEnd(void)
{
    QuitModeEnter();
    MushcoreData<GameBase>::Sgl().Delete("adanaxis");
}

void
AdanaxisAppHandler::KeyboardSignal(const GLKeyboardSignal& inSignal)
{
    bool keyHandled=false;
    if (inSignal.keyValue.ValueGet() == 27 && inSignal.keyDown)
    {
        QuitModeEnter();
        keyHandled=true;
    }
    if (!keyHandled)
    {
        GameAppHandler::KeyboardSignal(inSignal);
    }
}
