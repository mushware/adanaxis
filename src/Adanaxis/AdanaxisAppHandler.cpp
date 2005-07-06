//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisAppHandler.cpp
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } sZjJcPKhF62mPX+WEmXvZw
/*
 * $Id: AdanaxisAppHandler.cpp,v 1.3 2005/06/14 20:39:40 southa Exp $
 * $Log: AdanaxisAppHandler.cpp,v $
 * Revision 1.3  2005/06/14 20:39:40  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/14 13:25:32  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
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

AdanaxisAppHandler::AdanaxisAppHandler(const std::string& inName) :
    MushGameAppHandler(inName)
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
    
    MushcoreData<GameBase>::Sgl().Give("adanaxis", new AdanaxisGame("adanaxis"));
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
