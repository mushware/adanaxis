//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverAppHandler.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } P4EBRx8qMYZcSEDE1oUinw
/*
 * $Id: MeshMoverAppHandler.cpp,v 1.1 2003/10/07 22:40:06 southa Exp $
 * $Log: MeshMoverAppHandler.cpp,v $
 * Revision 1.1  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 */

#include "MeshMoverAppHandler.h"

#include "MeshMoverSTL.h"

#include "Mushcore.h"
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
    if (StateGameIs())
    {
        CurrentSwapOut();

        m_pGame=NULL;

        MUSHCOREASSERT(m_pGame != NULL);
        CurrentSwapIn(m_pGame);
        StateGameSet();
    }
}

void
MeshMoverAppHandler::PrepareNewGame(void)
{
    m_pGame = NULL; // We're about to delete this

    // Work out what the game type is
    GameTypeDetermine();
}

void
MeshMoverAppHandler::CurrentGameEnd(void)
{
    SetupModeEnter();
    m_pGame=NULL;
}
