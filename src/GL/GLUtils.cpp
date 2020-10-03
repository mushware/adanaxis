//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLUtils.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } qWmc/W4seDofyR9nTz8ajg
/*
 * $Id: GLUtils.cpp,v 1.63 2006/11/25 21:26:32 southa Exp $
 * $Log: GLUtils.cpp,v $
 * Revision 1.63  2006/11/25 21:26:32  southa
 * Display mode definitions
 *
 * Revision 1.62  2006/06/01 15:38:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.61  2005/05/20 13:19:00  southa
 * Release work
 *
 * Revision 1.60  2005/05/20 10:26:27  southa
 * Release work
 *
 * Revision 1.59  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.58  2005/01/29 14:06:11  southa
 * OpenGL buffers and extensions
 *
 * Revision 1.57  2004/03/07 12:05:56  southa
 * Rendering work
 *
 * Revision 1.56  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.55  2003/10/04 12:22:58  southa
 * File renaming
 *
 * Revision 1.54  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.53  2003/08/21 23:08:33  southa
 * Fixed file headers
 *
 * Revision 1.52  2003/02/05 16:19:45  southa
 * Build fixes
 *
 * Revision 1.51  2003/01/20 10:45:24  southa
 * Singleton tidying
 *
 * Revision 1.50  2003/01/13 14:31:56  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.49  2003/01/09 14:56:59  southa
 * Created Mushcore
 *
 * Revision 1.48  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.47  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.46  2002/12/03 20:28:14  southa
 * Network, player and control work
 *
 * Revision 1.45  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.44  2002/10/15 14:02:30  southa
 * Mode changes
 *
 * Revision 1.43  2002/10/14 18:13:17  southa
 * GLModeDef work
 *
 * Revision 1.42  2002/10/14 15:12:31  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.41  2002/10/13 12:26:46  southa
 * Facetised map rendering
 *
 * Revision 1.40  2002/10/12 17:56:10  southa
 * Reset normal when drawing sprites
 *
 * Revision 1.39  2002/10/12 15:25:09  southa
 * Facet renderer
 *
 * Revision 1.38  2002/10/11 20:10:14  southa
 * Various fixes and new files
 *
 * Revision 1.37  2002/10/11 14:01:10  southa
 * Lighting work
 *
 * Revision 1.36  2002/10/10 22:47:57  southa
 * Full light definitions
 *
 * Revision 1.35  2002/10/10 18:25:13  southa
 * Light links and test lights
 *
 * Revision 1.34  2002/10/10 13:51:16  southa
 * Speed fixes and various others
 *
 * Revision 1.33  2002/10/08 23:03:55  southa
 * Widen z clipping on OrthoLookAt
 *
 * Revision 1.32  2002/10/08 21:44:08  southa
 * 3D maps
 *
 * Revision 1.31  2002/10/08 17:13:16  southa
 * Tiered maps
 *
 * Revision 1.30  2002/10/07 17:49:44  southa
 * Multiple values per map element
 *
 * Revision 1.29  2002/10/07 12:15:36  southa
 * First specular lighting
 *
 * Revision 1.28  2002/10/06 22:09:58  southa
 * Initial lighting test
 *
 * Revision 1.27.4.1  2002/09/04 10:18:04  southa
 * Fixed for MacOS X 10.2
 *
 * Revision 1.27  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.26  2002/08/24 14:54:00  southa
 * Use GL_LINEAR_MIPMAP_LINEAR for high quality texturing
 *
 * Revision 1.25  2002/08/13 17:50:20  southa
 * Added playsound command
 *
 * Revision 1.24  2002/08/08 18:20:29  southa
 * Plot on screen of dimension 1.0
 *
 * Revision 1.23  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.22  2002/08/01 16:47:10  southa
 * First multi-box collsion checking
 *
 * Revision 1.21  2002/07/31 16:27:15  southa
 * Collision checking work
 *
 * Revision 1.20  2002/07/19 18:35:02  southa
 * More texture tweaks
 *
 * Revision 1.19  2002/07/19 17:51:10  southa
 * Texture tweaks
 *
 * Revision 1.18  2002/07/19 16:25:21  southa
 * Texture tweaks
 *
 * Revision 1.17  2002/07/19 15:44:40  southa
 * Graphic optimisations
 *
 * Revision 1.16  2002/07/08 14:22:02  southa
 * Rotated desks
 *
 * Revision 1.15  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.14  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.13  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 * Revision 1.12  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.11  2002/06/06 16:08:42  southa
 * Changed game screen size to 1024x768
 *
 * Revision 1.10  2002/06/05 12:28:05  southa
 * Map rendered using traits
 *
 * Revision 1.9  2002/06/04 17:02:24  southa
 * More work
 *
 * Revision 1.8  2002/06/02 16:41:18  southa
 * Rotated sprite plotting
 *
 * Revision 1.7  2002/06/02 15:18:52  southa
 * Texture bitmap renderer
 *
 * Revision 1.6  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.5  2002/05/29 10:07:48  southa
 * Fixed Inits for cygwin
 *
 * Revision 1.4  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.3  2002/05/28 13:07:01  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.2  2002/05/27 12:58:43  southa
 * InfernalContract and global configs added
 *
 * Revision 1.1  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 */

#include "GLUtils.h"
#include "GLAppHandler.h"
#include "GLData.h"
#include "GLModeDef.h"
#include "GLPoint.h"
#include "GLRectangle.h"
#include "GLState.h"
#include "GLTexture.h"

#include "mushPlatform.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

tVal GLUtils::m_eyeDistance=60; // Controls how much perspective there is
tVal GLUtils::m_screenScale=20;  // m_screenScale axis units cover the longest screen axis
U32 GLUtils::m_context=1;
bool GLUtils::m_swapValid=false;

void
GLUtils::MoveTo(tVal inX, tVal inY)
{
    glTranslatef(inX-m_x,inY-m_y,0);
    m_x=inX;
    m_y=inY;
}

void
GLUtils::MoveRelative(tVal inX, tVal inY)
{
    glTranslatef(inX,inY,0);
    m_x+=inX;
    m_y+=inY;
}

void
GLUtils::MoveToEdge(tVal inX, tVal inY)
{
    GLPoint screenRatios(ScreenRatiosGet()*0.5);

    tVal newX=screenRatios.x*inX;
    tVal newY=screenRatios.y*inY;
    glTranslatef(newX-m_x,newY-m_y,0);
    m_x=newX;
    m_y=newY;
}

void
GLUtils::IdentityPrologue(void)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void
GLUtils::IdentityEpilogue(void)
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void
GLUtils::OrthoPrologue(void)
{
    // The screen should be enclosed by a square with corners (-0.5,-0.5) and
    // (0.5,0.5) with aspect ratio 1.  The screen is a rectangle within the square
    IdentityPrologue();
    glMatrixMode(GL_PROJECTION);
    GLPoint screenRatios(ScreenRatiosGet()*0.5);
    gluOrtho2D(-screenRatios.x,screenRatios.x,-screenRatios.y,screenRatios.y);
    glMatrixMode(GL_MODELVIEW);
}

void
GLUtils::OrthoEpilogue(void)
{
    IdentityEpilogue();
}

void
GLUtils::VisiblePrologue(void)
{
    // The screen should enclose a square with corners (-0.5,-0.5) and
    // (0.5,0.5) with aspect ratio 1.  The square is fully contained within the screen
    IdentityPrologue();
    glMatrixMode(GL_PROJECTION);
    GLPoint screenRatios(VisibleScreenRatiosGet()*0.5);
    gluOrtho2D(-screenRatios.x, screenRatios.x, -screenRatios.y, screenRatios.y);
    glMatrixMode(GL_MODELVIEW);
}

void
GLUtils::VisibleEpilogue(void)
{
    IdentityEpilogue();
}

void
GLUtils::OrthoLookAt(tVal inX, tVal inY, tVal inAngle)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLPoint screenRatios(ScreenRatiosGet()*0.5);
    glOrtho(-screenRatios.x,screenRatios.x,-screenRatios.y,screenRatios.y,-100,100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(inX, inY, m_eyeDistance, // eye position
              inX, inY, 0, // reference for -z axis
              sin(inAngle),cos(inAngle),0 // direction of up
              );

}

void GLUtils::PerspectiveLookAt(const GLPoint& inPoint, tVal inAngle)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLPoint screenRatios(ScreenRatiosGet()*0.5);
    tVal nearClip=1.0;
    tVal scale=m_screenScale/m_eyeDistance*nearClip;
    glFrustum(-screenRatios.x*scale,screenRatios.x*scale,
              -screenRatios.y*scale,screenRatios.y*scale,
                   nearClip, // zNear clipping plane distance from viewer
                   m_eyeDistance+1.0 // zFar clipping plane distance from viewer
                   );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(inPoint.x, inPoint.y, m_eyeDistance, // eye position
              inPoint.x, inPoint.y, 0.0, // reference for -z axis
              sin(inAngle),cos(inAngle),0 // direction of up
              );
    
    GLUtils::CheckGLError();
}

void
GLUtils::PerspectiveLookAt(const GLVector& inCamera, const GLVector& inLookAt, tVal inAngle)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLPoint screenRatios(ScreenRatiosGet()*0.5);
    tVal nearClip=0.01;
    tVal scale=m_screenScale/m_eyeDistance*nearClip;
    glFrustum(-screenRatios.x*scale,screenRatios.x*scale,
              -screenRatios.y*scale,screenRatios.y*scale,
              nearClip, // zNear clipping plane distance from viewer
              m_eyeDistance*2 // zFar clipping plane distance from viewer
              );
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(inCamera.x, inCamera.y, inCamera.z, // eye position
              inLookAt.x, inLookAt.y, inLookAt.z, // reference for -z axis
              sin(inAngle),cos(inAngle),0 // direction of up
              );
    
    GLUtils::CheckGLError();
}

void
GLUtils::StereoPerspectiveLookAt(const GLVector& inCamera, const GLVector& inLookAt,
                                 tVal inAngle, tVal inOffset)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLPoint screenRatios(ScreenRatiosGet()*0.5);
    tVal nearClip=0.01;
    tVal scale=m_screenScale/m_eyeDistance*nearClip;
    glFrustum((inOffset-screenRatios.x)*scale,(inOffset+screenRatios.x)*scale,
              -screenRatios.y*scale,screenRatios.y*scale,
              nearClip, // zNear clipping plane distance from viewer
              m_eyeDistance*2 // zFar clipping plane distance from viewer
              );
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(inCamera.x, inCamera.y, inCamera.z, // eye position
              inLookAt.x, inLookAt.y, inLookAt.z, // reference for -z axis
              sin(inAngle),cos(inAngle),0 // direction of up
              );
    
    GLUtils::CheckGLError();
}

const GLPoint
GLUtils::ScreenSizeGet(void)
{
    GLAppHandler& glHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());
    return GLPoint(glHandler.WidthGet(), glHandler.HeightGet());
}

const GLPoint
GLUtils::ScreenRatiosGet(void)
{
    return ScreenSizeGet() / LongestScreenAxis();
}

const GLPoint
GLUtils::VisibleScreenRatiosGet(void)
{
    return ScreenSizeGet() / ShortestScreenAxis();
}

tVal
GLUtils::ScreenScaleGet(void)
{
    return m_screenScale;
}

tVal
GLUtils::LongestScreenAxis(void)
{
    GLPoint screenSize(ScreenSizeGet());
    if (screenSize.x > screenSize.y)
    {
        return screenSize.x;
    }
    else
    {
        return screenSize.y;
    }
}    

tVal
GLUtils::ShortestScreenAxis(void)
{
    GLPoint screenSize(ScreenSizeGet());
    if (screenSize.x < screenSize.y)
    {
        return screenSize.x;
    }
    else
    {
        return screenSize.y;
    }
}

void
GLUtils::DisplayPrologue(void)
{
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());

    if (m_swapValid)
    {
        glAppHandler.SwapBuffers();
    }
}

void
GLUtils::DisplayEpilogue(void)
{
    glDrawBuffer(GL_BACK);
    // glFlush();
    m_swapValid=true;
}

void
GLUtils::ClearScreen(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
GLUtils::DrawRectangle(tVal inX1, tVal inY1, tVal inX2, tVal inY2)
{
    glBegin(GL_QUADS);
    glVertex2f(inX1,inY1);
    glVertex2f(inX2,inY1);
    glVertex2f(inX2,inY2);
    glVertex2f(inX1,inY2);
    glEnd();
}

void
GLUtils::DrawTriangle(tVal inX1, tVal inY1, tVal inX2, tVal inY2, tVal inX3, tVal inY3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(inX1,inY1);
    glVertex2f(inX2,inY2);
    glVertex2f(inX3,inY3);
    glEnd();
}

void
GLUtils::RasterPos(tVal inX, tVal inY)
{
    glRasterPos2f(inX, inY);
}

void
GLUtils::BitmapText(const string& inStr)
{
    U32 length=inStr.size();
    for (U32 i=0; i<length; i++)
    {
        // glutBitmapCharacter(GLUT_BITMAP_8_BY_13, inStr[i]);
    }
}


void
GLUtils::DrawSprite(const GLTexture& inTex)
{
    tVal width2=inTex.Width()/2;
    tVal height2=inTex.Height()/2;
    GLState::BindTexture(inTex.BindingNameGet());
    GLState::TextureEnable();
    glNormal3f(0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(-width2,-height2);
    glTexCoord2f(1,0);
    glVertex2f(width2,-height2);
    glTexCoord2f(1,1);
    glVertex2f(width2,height2);
    glTexCoord2f(0,1);
    glVertex2f(-width2,height2);
    glEnd();
    GLState::TextureDisable();
}

void
GLUtils::DrawSprite(const GLTexture& inTex, const GLRectangle& inRectangle)
{
    GLState::BindTexture(inTex.BindingNameGet());
    GLState::TextureEnable();
    glNormal3f(0,0,1);
    glPushMatrix();
    {
        static tVal ctr=0;

        glTranslatef(0,0,0.0*sin((ctr++) / 100000.0));
    }
    glBegin(GL_QUADS);
    glTexCoord2f(inRectangle.xmin,inRectangle.ymin);
    glVertex2f(-0.5,-0.5);
    glTexCoord2f(inRectangle.xmax,inRectangle.ymin);
    glVertex2f(0.5,-0.5);
    glTexCoord2f(inRectangle.xmax,inRectangle.ymax);
    glVertex2f(0.5,0.5);
    glTexCoord2f(inRectangle.xmin,inRectangle.ymax);
    glVertex2f(-0.5,0.5);
    glEnd();
    GLState::TextureDisable();
    glPopMatrix();
}

void
GLUtils::DrawSprite(const GLTexture& inTex, tVal inX, tVal inY)
{
    tVal width=inTex.Width();
    tVal height=inTex.Height();
    GLState::BindTexture(inTex.BindingNameGet());
    GLState::TextureEnable();
    glNormal3f(0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(inX,inY);
    glTexCoord2f(1,0);
    glVertex2f(inX+height,inY);
    glTexCoord2f(1,1);
    glVertex2f(inX+height,inY+width);
    glTexCoord2f(0,1);
    glVertex2f(inX,inY+width);
    glEnd();
    GLState::TextureDisable();
    glNormal3f(0,0,1);
}

void
GLUtils::DrawRotatedSprite(const GLTexture& inTex, tVal inX, tVal inY, tVal inAngle)
{
    tVal width=inTex.Width();
    tVal height=inTex.Height();
    GLState::BindTexture(inTex.BindingNameGet());
    GLState::TextureEnable();
    glNormal3f(0,0,1);
    glPushMatrix();
    tVal xCentre=inX+width/2;
    tVal yCentre=inY+height/2;
    glTranslatef(xCentre, yCentre,0);
    glRotatef(inAngle,0,0,1);
    glTranslatef(-xCentre, -yCentre,0);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(inX,inY);
    glTexCoord2f(1,0);
    glVertex2f(inX+height,inY);
    glTexCoord2f(1,1);
    glVertex2f(inX+height,inY+width);
    glTexCoord2f(0,1);
    glVertex2f(inX,inY+width);
    glEnd();
    glPopMatrix();
    GLState::TextureDisable();
}

// Slow version
#if 0
void
GLUtils::DrawBitmap(const GLTexture& inTex, S32 inX, S32 inY)
{
    GLUtils::RasterPos(0, 0);
    glBitmap(0,0,0,0,inX,inY,NULL);
    glDrawPixels(inTex.Width(), inTex.Height(), inTex.PixelFormat(),
             inTex.PixelType(), inTex.DataPtr());
}
#endif

void GLUtils::PostRedisplay(void)
{
    GLAppHandler& glHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());

    glHandler.PostRedisplay();
}

void
GLUtils::Scale(tVal inXScale, tVal inYScale, tVal inZScale)
{
    glScaled(inXScale, inYScale, inZScale);
}

void
GLUtils::RotateAboutZ(tVal inAngle)
{
    glRotated(inAngle, 0, 0, 1);
}

void GLUtils::Decache(void)
{
    GLData::Sgl().Decache();
    ++m_context;
}

void
GLUtils::CheckGLError(void)
{
    GLenum glErr=glGetError();
    switch (glErr)
    {
        case GL_NO_ERROR:
            break;

        case GL_INVALID_ENUM:
            cerr << "GL invalid enum" << endl;
            break;

        case GL_INVALID_VALUE:
            cerr << "GL invalid value" << endl;
            break;

        case GL_INVALID_OPERATION:
            cerr << "GL invalid operation" << endl;
            break;

        case GL_STACK_OVERFLOW:
            cerr << "GL stack overflow" << endl;
            break;

        case GL_STACK_UNDERFLOW:
            cerr << "GL stack underflow" << endl;
            break;

        case GL_OUT_OF_MEMORY:
            cerr << "GL out of memory" << endl;
            break;

        default:
            cerr << "Unknown GL error " << glErr << endl;
            break;
    }
}

