/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: GLWrangleAppHandler.cpp,v 1.7 2002/06/27 12:36:09 southa Exp $
 * $Log: GLWrangleAppHandler.cpp,v $
 * Revision 1.7  2002/06/27 12:36:09  southa
 * Build process fixes
 *
 * Revision 1.6  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.5  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
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
    
    EnterScreen(kWindow);
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
    if (redraw /*&& IsVisible()*/)
    {
        glutPostRedisplay();
    }
}
