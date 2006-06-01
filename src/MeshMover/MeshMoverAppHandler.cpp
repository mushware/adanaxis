//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverAppHandler.cpp
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
//%Header } My1M0PbqyrABJRZg+NS9bg
/*
 * $Id: MeshMoverAppHandler.cpp,v 1.5 2005/05/19 13:02:08 southa Exp $
 * $Log: MeshMoverAppHandler.cpp,v $
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
