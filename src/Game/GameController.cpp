/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameController.cpp,v 1.3 2002/06/06 13:36:55 southa Exp $
 * $Log: GameController.cpp,v $
 * Revision 1.3  2002/06/06 13:36:55  southa
 * Mouse handling
 *
 * Revision 1.2  2002/06/05 16:29:51  southa
 * Mouse control
 *
 * Revision 1.1  2002/06/05 15:53:25  southa
 * Player and keyboard control
 *
 */

#include "GameController.h"
#include "GameAppHandler.h"

GameController::GameController():
    m_leftKey(GLKeys::kKeyLeft),
    m_rightKey(GLKeys::kKeyRight),
    m_upKey(GLKeys::kKeyUp),
    m_downKey(GLKeys::kKeyDown),
    m_lastMouseValid(false)
{


}

void
GameController::StateGet(GameControllerState& outState)
{
    GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());

    outState.leftPressed=gameHandler.KeyStateGet(m_leftKey);
    outState.rightPressed=gameHandler.KeyStateGet(m_rightKey);
    outState.upPressed=gameHandler.KeyStateGet(m_upKey);
    outState.downPressed=gameHandler.KeyStateGet(m_downKey);
    S32 mouseX, mouseY, mouseXDelta, mouseYDelta;
    gameHandler.MousePositionGet(mouseX, mouseY);
    gameHandler.MouseDeltaGet(mouseXDelta, mouseYDelta);
    outState.mouseX=mouseX;
    outState.mouseY=mouseY;
    outState.mouseXDelta=mouseXDelta;
    outState.mouseYDelta=mouseYDelta;
}
