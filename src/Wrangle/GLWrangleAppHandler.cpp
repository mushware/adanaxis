/*
 * $Id: GLWrangleAppHandler.cpp,v 1.4 2002/05/28 16:37:36 southa Exp $
 * $Log: GLWrangleAppHandler.cpp,v $
 * Revision 1.4  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.3  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 * Revision 1.2  2002/05/10 16:40:39  southa
 * Changed .hp files to .h
 *
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
    GLTextureRef texRef("0");
    GLTexture& tex=*texRef.TextureGet();

    m_pWrangler = new GraphWrangler(tex);
    
    GLUtils::StandardInit();
    
    glutInitWindowSize(tex.Width(), tex.Height());

    glutCreateWindow("Wrangling data");
    RegisterHandlers();
    GLUtils::CheckGLError();    
}

void
GLWrangleAppHandler::Display(void)
{
    GLTextureRef texRef("0");
    GLTexture& tex=*texRef.TextureGet();
    
    glDrawBuffer(GL_BACK);
    glClearColor(0.2, 0.2, 0.2, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    GLUtils::OrthoPrologue();
    
    glRasterPos2f(0, 0);
    // glBitmap(0,0,0,0,0,0,NULL);
    glDrawPixels(tex.Width(), tex.Height(), tex.PixelFormat(),
                     tex.PixelType(), tex.DataPtr());

    GLUtils::OrthoEpilogue();
    glutSwapBuffers();
}

void
GLWrangleAppHandler::Idle(void)
{
    bool redraw=false;
    COREASSERT(m_pWrangler != NULL);
    m_pWrangler->Process(redraw);
    if (redraw && IsVisible())
    {
        glutPostRedisplay();
    }
}
