/*
 * $Id: GameAppHandler.cpp,v 1.1 2002/05/10 15:35:27 southa Exp $
 * $Log: GameAppHandler.cpp,v $
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
    GLTexture& tex=GLData::Instance().GetTexture(0);

    m_pGame = new GameTest;

    StandardInit();

    glutInitWindowSize(tex.Width(), tex.Height());

    glutCreateWindow("Game");
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);
    CheckGLError();
}

void
GameAppHandler::Display(void)
{
    glDrawBuffer(GL_BACK);
    glClearColor(0.2, 0.2, 0.2, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    OrthoPrologue();

    glRasterPos2f(0, 0);
#if 0
    glDrawPixels(tex.Width(), tex.Height(), tex.PixelFormat(),
                 tex.PixelType(), tex.DataPtr());
#endif
    OrthoEpilogue();
    glutSwapBuffers();
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
    outUSleepFor=1000000;
}
