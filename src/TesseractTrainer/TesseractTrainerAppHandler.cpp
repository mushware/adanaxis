//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerAppHandler.cpp
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
//%Header } HKlEiaDB1fmKuKCQIsadYQ
/*
 * $Id: TesseractTrainerAppHandler.cpp,v 1.6 2006/06/01 15:39:59 southa Exp $
 * $Log: TesseractTrainerAppHandler.cpp,v $
 * Revision 1.6  2006/06/01 15:39:59  southa
 * DrawArray verification and fixes
 *
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
