/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameController.cpp,v 1.10 2002/10/22 20:42:03 southa Exp $
 * $Log: GameController.cpp,v $
 * Revision 1.10  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/17 10:41:51  southa
 * Designer fixes
 *
 * Revision 1.7  2002/08/07 13:36:49  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/19 15:44:41  southa
 * Graphic optimisations
 *
 * Revision 1.5  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:06  southa
 * Build process fixes
 *
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
    m_keyState(4),
    m_lastMouseValid(false)
{
    m_keysOfInterest.push_back(GLKeys::kKeyLeft);
    m_keysOfInterest.push_back(GLKeys::kKeyRight);
    m_keysOfInterest.push_back(GLKeys::kKeyUp);
    m_keysOfInterest.push_back(GLKeys::kKeyDown);
}

void
GameController::StateGet(GameControllerState& outState, U32 inAtMsec)
{
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    
    gameAppHandler.KeysOfInterestSet(m_keysOfInterest);
    S32 unboundedMouseX, unboundedMouseY;

    gameAppHandler.ReadHistoricControlState(unboundedMouseX, unboundedMouseY, m_keyState, inAtMsec);
 
    COREASSERT(m_keyState.size() == 4);
    outState.leftPressed=m_keyState[0];
    outState.rightPressed=m_keyState[1];
    outState.upPressed=m_keyState[2];
    outState.downPressed=m_keyState[3];
    
    tVal mouseX, mouseY;
    gameAppHandler.MousePositionGet(mouseX, mouseY);

    outState.mouseX=mouseX;
    outState.mouseY=mouseY;
    if (m_lastMouseValid)
    {
        outState.mouseXDelta = unboundedMouseX - m_lastUnboundedMouseX;
        outState.mouseYDelta = unboundedMouseY - m_lastUnboundedMouseY;
    }
    else
    {
        outState.mouseXDelta = 0;
        outState.mouseYDelta = 0;
        m_lastMouseValid = true;
    }
    m_lastUnboundedMouseX = unboundedMouseX;
    m_lastUnboundedMouseY = unboundedMouseY;
}
