/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLWrangleAppHandler.cpp,v 1.14 2002/12/29 21:00:01 southa Exp $
 * $Log: GLWrangleAppHandler.cpp,v $
 * Revision 1.14  2002/12/29 21:00:01  southa
 * More build fixes
 *
 * Revision 1.13  2002/12/20 13:17:49  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.12  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.11  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 * Revision 1.10  2002/08/27 08:56:30  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/07 13:36:52  southa
 * Conditioned source
 *
 * Revision 1.8  2002/07/06 18:04:20  southa
 * More designer work
 *
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

#include "Mushcore.h"
#include "mushGL.h"

#include "GraphWrangler.h"

using namespace Mushware;
using namespace std;

void
GLWrangleAppHandler::Initialise(void)
{
    GLTextureRef texRef("0");
    GLTexture& tex=*texRef.TextureGet();

    m_pWrangler = new GraphWrangler(tex);

    EnterScreen(GLModeDef::Default());
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
