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
 * $Id$
 * $Log$
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
    SetupModeEnter();
    MushcoreData<GameBase>::Sgl().Delete("tesseracttrainer");
}
