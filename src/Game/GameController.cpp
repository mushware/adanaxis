/*
 * $Id$
 * $Log$
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
}
