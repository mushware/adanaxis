//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenAppHandler.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } dj+oBRLyniUBj/qrTHMf+Q
/*
 * $Id: MaurheenAppHandler.cpp,v 1.2 2005/05/19 13:02:07 southa Exp $
 * $Log: MaurheenAppHandler.cpp,v $
 * Revision 1.2  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.1  2004/03/06 14:01:42  southa
 * Maurheen created
 *
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
