/*
 * $Id: GameController.cpp,v 1.1 2002/06/05 15:53:25 southa Exp $
 * $Log: GameController.cpp,v $
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
    S32 mouseX, mouseY;
    gameHandler.MouseStateGet(mouseX, mouseY);
    if (m_lastMouseValid)
    {
        outState.mouseXDelta=mouseX-m_lastMouseX;
        outState.mouseYDelta=mouseY-m_lastMouseY;
    }
    else
    {
        outState.mouseXDelta=0;
        outState.mouseYDelta=0;
    }
    outState.mouseX=mouseX;
    outState.mouseY=mouseY;
    m_lastMouseX=mouseX;
    m_lastMouseY=mouseY;
    m_lastMouseValid=true;
        
}
