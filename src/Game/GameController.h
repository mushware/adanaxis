#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
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
 * $Id: GameController.h,v 1.7 2002/08/27 08:56:23 southa Exp $
 * $Log: GameController.h,v $
 * Revision 1.7  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/17 10:41:51  southa
 * Designer fixes
 *
 * Revision 1.5  2002/08/07 13:36:49  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/05 16:29:51  southa
 * Mouse control
 *
 * Revision 1.1  2002/06/05 15:53:25  southa
 * Player and keyboard control
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameControllerState
{
public:
    GLPoint MouseGet(void) { return GLPoint(mouseX, mouseY); }
    GLPoint MouseDeltaGet(void) { return GLPoint(mouseXDelta, mouseYDelta); }
    
    bool leftPressed;
    bool rightPressed;
    bool upPressed;
    bool downPressed;
    tVal mouseX;
    tVal mouseY;
    tVal mouseXDelta;
    tVal mouseYDelta;
};

// Will be subclassed and pickleable
class GameController
{
public:
    GameController();
    void StateGet(GameControllerState& outState);

private:
    GLKeys m_leftKey;
    GLKeys m_rightKey;
    GLKeys m_upKey;
    GLKeys m_downKey;
    tVal m_lastMouseX;
    tVal m_lastMouseY;
    bool m_lastMouseValid;
};
#endif
