/*
 * $Id$
 * $Log$
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
