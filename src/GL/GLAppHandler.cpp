/*
 * $Id: GLAppHandler.cpp,v 1.5 2002/05/10 16:41:42 southa Exp $
 * $Log: GLAppHandler.cpp,v $
 * Revision 1.5  2002/05/10 16:41:42  southa
 * Changed .hp files to .h
 *
 * Revision 1.4  2002/05/08 16:31:20  southa
 * Created API directory
 *
 * Revision 1.3  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.2  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "GLAppHandler.h"
#include "GLStandard.h"
#include "GLUtils.h"
#include "mushCore.h"

void
GLAppHandler::Idle(bool& outQuit, int& outUSleepFor)
{
    glutPostRedisplay();
    CoreAppHandler::Idle(outQuit, outUSleepFor);
}

void
GLAppHandler::Initialise(void)
{
    GLUtils::StandardInit();
    RegisterHandlers();
    glutCreateWindow("GLApp");
}

void
GLAppHandler::RegisterHandlers(void)
{
    glutVisibilityFunc(VisibilityHandler);
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);
}

void
GLAppHandler::IdleHandler(void)
{
    bool doQuit;
    int uSleepFor;
    Instance().Idle(doQuit, uSleepFor);
}

void
GLAppHandler::VisibilityHandler(int inState)
{
    if (inState == GLUT_NOT_VISIBLE)
    {
        cerr << "Invisible" << endl;
        Instance().Signal(kSignalNotVisible);
    }
    else if (inState == GLUT_VISIBLE)
    {
        cerr << "Visible" << endl;
        Instance().Signal(kSignalVisible);
    }
}

void
GLAppHandler::Display(void)
{
    string str("Hello from OpenGL");

    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    static float lineWidth;
    if ((lineWidth+=0.002)>=1) lineWidth=0;
    glLineWidth(5*lineWidth);

    glDrawBuffer(GL_BACK);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glTranslatef(16, 16, 0);

    glScalef(0.5*lineWidth, 0.5*lineWidth, 0.5*lineWidth);
    glColor3f(lineWidth,lineWidth,lineWidth);
    for (Size i=0; i < str.size(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
        if (str[i] == ' ')
        {
            glTranslatef(-64, 0, 0);

        }
    }
    glPopAttrib();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
    GLUtils::CheckGLError();
}

void
GLAppHandler::Signal(U32 inSignal)
{
    switch (inSignal)
    {
        case kSignalVisible:
            m_visible=true;
            break;

        case kSignalNotVisible:
            m_visible=false;
            break;
    }
}    

void
GLAppHandler::MainLoop(void)
{
    glutMainLoop();
    GLUtils::CheckGLError();
}



