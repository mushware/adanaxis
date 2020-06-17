//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverAppHandler.cpp
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
//%Header } he27ZG5S9mb+Ua5x6YgivQ
/*
 * $Id: MeshMoverAppHandler.cpp,v 1.6 2006/06/01 15:39:14 southa Exp $
 * $Log: MeshMoverAppHandler.cpp,v $
 * Revision 1.6  2006/06/01 15:39:14  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.4  2005/02/03 21:02:58  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 */

#include "MeshMoverAppHandler.h"

#include "MeshMoverSTL.h"

#include "mushMushcore.h"
#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MeshMoverAppHandler::MeshMoverAppHandler() :
m_pGame(NULL)
{
}

MeshMoverAppHandler::~MeshMoverAppHandler()
{
    if (m_pGame != NULL) delete m_pGame;
}

void
MeshMoverAppHandler::GameModeEnter(bool inResume)
{
    if (!StateGameIs())
    {
        CurrentSwapOut();
        
        if (!inResume || !MushcoreData<GameBase>::Sgl().Exists("meshmover"))
        {
            PrepareNewGame();
        }
        CurrentSwapIn("meshmover");
        StateGameSet();
    }
}

void
MeshMoverAppHandler::PrepareNewGame(void)
{
    //MushcoreData<GameBase>::Sgl().Give("meshmover", new MeshMoverGame);
}

void
MeshMoverAppHandler::CurrentGameEnd(void)
{
    SetupModeEnter();
    MushcoreData<GameBase>::Sgl().Delete("meshmover");
}
