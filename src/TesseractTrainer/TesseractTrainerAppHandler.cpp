//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerAppHandler.cpp
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
//%Header } pFJXwjfsxnqEWjg7kf4NCw
/*
 * $Id: TesseractTrainerAppHandler.cpp,v 1.5 2005/06/03 13:36:44 southa Exp $
 * $Log: TesseractTrainerAppHandler.cpp,v $
 * Revision 1.5  2005/06/03 13:36:44  southa
 * win32 build fixes
 *
 * Revision 1.4  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.3  2005/04/19 23:25:43  southa
 * Mode switching and recognition
 *
 * Revision 1.2  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.1  2005/02/03 15:46:55  southa
 * Quaternion work
 *
 */

#include "TesseractTrainerAppHandler.h"

#include "TesseractTrainerSTL.h"

#include "mushMushcore.h"
#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

#include "TesseractTrainerGame.h"

using namespace Mushware;
using namespace std;

TesseractTrainerAppHandler::TesseractTrainerAppHandler()
{
}

TesseractTrainerAppHandler::~TesseractTrainerAppHandler()
{
}

void
TesseractTrainerAppHandler::SetupModeEnter(void)
{
    GameModeEnter(false);
}

void
TesseractTrainerAppHandler::GameModeEnter(bool inResume)
{
    if (!StateGameIs())
    {
        CurrentSwapOut();
        
        if (!inResume || !MushcoreData<GameBase>::Sgl().Exists("tesseracttrainer"))
        {
            PrepareNewGame();
        }
        CurrentSwapIn("tesseracttrainer");
        StateGameSet();
    }
}

void
TesseractTrainerAppHandler::PrepareNewGame(void)
{
    
    MushcoreData<GameBase>::Sgl().Give("tesseracttrainer", new TesseractTrainerGame);
}

void
TesseractTrainerAppHandler::CurrentGameEnd(void)
{
    QuitModeEnter();
    MushcoreData<GameBase>::Sgl().Delete("tesseracttrainer");
}

void
TesseractTrainerAppHandler::KeyboardSignal(const GLKeyboardSignal& inSignal)
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
