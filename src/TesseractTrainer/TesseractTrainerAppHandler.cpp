//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerAppHandler.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Xj4GDjQD+0YwgfSGVwf86A
/*
 * $Id: TesseractTrainerAppHandler.cpp,v 1.1 2005/02/03 15:46:55 southa Exp $
 * $Log: TesseractTrainerAppHandler.cpp,v $
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
