/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameController.cpp,v 1.15 2003/01/09 14:57:00 southa Exp $
 * $Log: GameController.cpp,v $
 * Revision 1.15  2003/01/09 14:57:00  southa
 * Created Mushcore
 *
 * Revision 1.14  2002/12/29 20:59:54  southa
 * More build fixes
 *
 * Revision 1.13  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.12  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 * Revision 1.11  2002/12/03 20:28:16  southa
 * Network, player and control work
 *
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
#include "GameControlFrameDef.h"
#include "GameSTL.h"

using namespace Mushware;
using namespace std;

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
GameController::StateGet(GameControlFrameDef& outDef, U32 inAtMsec)
{
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Instance());
    
    gameAppHandler.KeysOfInterestSet(m_keysOfInterest);
    
    S32 unboundedMouseX, unboundedMouseY;

    gameAppHandler.ReadHistoricControlState(unboundedMouseX, unboundedMouseY, m_keyState, inAtMsec);

    U32 size=m_keyState.size();

    outDef.keyState = 0;
    for (U32 i=0; i<size; ++i)
    {
        outDef.keyState |= m_keyState[i] << i;
    }
    
    tVal mouseX, mouseY;
    gameAppHandler.MousePositionGet(mouseX, mouseY);

    //outState.mouseX=mouseX;
    //outState.mouseY=mouseY;

    S32 mouseDeltaX, mouseDeltaY;
    
    if (m_lastMouseValid)
    {
        mouseDeltaX = unboundedMouseX - m_lastUnboundedMouseX;
        if (mouseDeltaX < -127) mouseDeltaX = -127;
        if (mouseDeltaX > 127) mouseDeltaX = 127;

        mouseDeltaY = unboundedMouseY - m_lastUnboundedMouseY;
        if (mouseDeltaY < -127) mouseDeltaY = -127;
        if (mouseDeltaY > 127) mouseDeltaY = 127;
    }
    else
    {
        mouseDeltaX = 0;
        mouseDeltaY = 0;
        m_lastUnboundedMouseX = unboundedMouseX;
        m_lastUnboundedMouseY = unboundedMouseY;
        m_lastMouseValid = true;
    }

    outDef.mouseDeltaX = static_cast<S8>(mouseDeltaX);
    outDef.mouseDeltaY = static_cast<S8>(mouseDeltaY);

    m_lastUnboundedMouseX += mouseDeltaX;
    m_lastUnboundedMouseY += mouseDeltaY;
}
