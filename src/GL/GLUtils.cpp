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
 * $Id: GLUtils.cpp,v 1.40 2002/10/12 17:56:10 southa Exp $
 * $Log: GLUtils.cpp,v $
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
 * GameContract and global configs added
 *
 * Revision 1.1  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 */

#include "GLUtils.h"
#include "GLTexture.h"
#include "GLAppHandler.h"
#include "GLPoint.h"
#include "GLRectangle.h"
#include "GLState.h"
#include "mushPlatform.h"

tVal GLUtils::m_eyeDistance=60; // Controls how much perspective there is
tVal GLUtils::m_screenScale=20;  // m_screenScale axis units cover the longest screen axis

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

void GLUtils::PerspectiveLookAt(GLPoint inPoint, tVal inAngle)
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

const GLPoint
GLUtils::ScreenSizeGet(void)
{
    GLAppHandler& glHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());
    return GLPoint(glHandler.WidthGet(), glHandler.HeightGet());
}

const GLPoint
GLUtils::ScreenRatiosGet(void)
{
    return ScreenSizeGet() / LongestScreenAxis();
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

void
GLUtils::DisplayPrologue(void)
{
    GLAppHandler& glHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());
    glFinish();
    PlatformMiscUtils::VBLWait();
    glHandler.SwapBuffers();
    glDrawBuffer(GL_BACK);
}

void
GLUtils::DisplayEpilogue(void)
{

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
    tSize length=inStr.size();
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
    GLAppHandler& glHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());

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

