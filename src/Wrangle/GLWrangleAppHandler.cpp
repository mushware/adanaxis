/*
 * $Id: GLWrangleAppHandler.cpp,v 1.1 2002/05/09 17:08:07 southa Exp $
 * $Log: GLWrangleAppHandler.cpp,v $
 * Revision 1.1  2002/05/09 17:08:07  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.2  2002/05/08 16:31:20  southa
 * Created API directory
 *
 * Revision 1.1  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 */

#include "GLWrangleAppHandler.h"

#include "mushCore.h"
#include "mushGL.h"

#include "GraphWrangler.h"

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
