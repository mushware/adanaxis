/*
 * $Id: GameAppHandler.cpp,v 1.3 2002/05/10 22:38:22 southa Exp $
 * $Log: GameAppHandler.cpp,v $
 * Revision 1.3  2002/05/10 22:38:22  southa
 * Checkpoint
 *
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "GameAppHandler.h"

#include "mushCore.h"
#include "mushGL.h"

#include "GameTest.h"

void
GameAppHandler::Initialise(void)
{
    m_pGame = new GameTest;
    
    GLUtils::GameInit();

    //glutInitWindowSize(640,480);
    //glutCreateWindow("Game");
    glutGameModeString("640x480:16@60");
    glutEnterGameMode();
    RegisterHandlers();
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);

    GLUtils::CheckGLError();
}

void
GameAppHandler::Display(void)
{
    COREASSERT(m_pGame != NULL);
    m_pGame->Display();
}

void
GameAppHandler::IdleHandler(void)
{
    bool doQuit=false;
    int uSleepFor=0;
    Instance().Idle(doQuit, uSleepFor);
    if (uSleepFor > 0) usleep(uSleepFor);
}

void
GameAppHandler::Idle(bool& outQuit, int& outUSleepFor)
{
    bool redraw=false;
    COREASSERT(m_pGame != NULL);
    m_pGame->Process(outQuit, redraw);
    if (redraw && IsVisible())
    {
        glutPostRedisplay();
    }
    outUSleepFor=0;
}
