/*
 * $Id$
 * $Log$
 */

#include "GLWrangleAppHandler.hp"

#include "CoreApp.hp"
#include "CoreAppHandler.hp"
#include "CorePOSIX.hp"

#include "GL/GLStandard.hp"
#include "GL/GLTexture.hp"
#include "GL/GLData.hp"

#include "GraphWrangler.hp"

void
GLWrangleAppHandler::Initialise(void)
{
    GLTexture& tex=GLData::Instance().GetTexture(0);

    m_pWrangler = new GraphWrangler(tex);
    
    StandardInit();
    
    glutInitWindowSize(tex.Width(), tex.Height());

    glutCreateWindow("Wrangling data");
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);
    CheckGLError();    
}

void
GLWrangleAppHandler::Display(void)
{
    const GLTexture& tex=GLData::Instance().GetTexture(0);
    
    glDrawBuffer(GL_BACK);
    glClearColor(0.2, 0.2, 0.2, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    OrthoPrologue();
    
    glRasterPos2f(0, 0);
    // glBitmap(0,0,0,0,0,0,NULL);
    glDrawPixels(tex.Width(), tex.Height(), tex.PixelFormat(),
                     tex.PixelType(), tex.DataPtr());

    OrthoEpilogue();
    glutSwapBuffers();
}

void
GLWrangleAppHandler::IdleHandler(void)
{
    bool doQuit=false;
    int uSleepFor=0;
    Instance().Idle(doQuit, uSleepFor);
    if (uSleepFor > 0) usleep(uSleepFor);
}

void
GLWrangleAppHandler::Idle(bool& outQuit, int& outUSleepFor)
{
    bool redraw=false;
    COREASSERT(m_pWrangler != NULL);
    m_pWrangler->Process(outQuit, redraw);
    if (redraw && IsVisible())
    {
        glutPostRedisplay();
    }
    outUSleepFor=1000000;
}
