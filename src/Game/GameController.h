/*
 * $Id: GameController.h,v 1.1 2002/06/05 15:53:25 southa Exp $
 * $Log: GameController.h,v $
 * Revision 1.1  2002/06/05 15:53:25  southa
 * Player and keyboard control
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameControllerState
{
public:
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
