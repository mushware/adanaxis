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
 * $Id: GLUtils.cpp,v 1.30 2002/10/07 17:49:44 southa Exp $
 * $Log: GLUtils.cpp,v $
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
#include "mushPlatform.h"

GLUtils::tBlendType GLUtils::m_blendState=GLUtils::kBlendInvalid;
bool GLUtils::m_modulateState=false;
GLUtils::tDisplayQuality GLUtils::m_displayQuality=GLUtils::kQualityNotSet;
bool GLUtils::m_polygonSmoothing=false;
bool GLUtils::m_useLighting=true;
tVal GLUtils::m_eyeDistance=20;

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
    gluOrtho2D(-screenRatios.x,screenRatios.x,-screenRatios.y,screenRatios.y);
    gluLookAt(inX, inY, -1.0, // eye position
              inX, inY, -2.0, // reference for -z axis
              sin(inAngle),cos(inAngle),0 // direction of up
              );
    glMatrixMode(GL_MODELVIEW);
}

void GLUtils::PerspectiveLookAt(GLPoint inPoint, tVal inAngle)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLPoint screenRatios(ScreenRatiosGet()*0.5);
    tVal nearClip=1.0;
    glFrustum(-screenRatios.x*nearClip,screenRatios.x*nearClip,
              -screenRatios.y*nearClip,screenRatios.y*nearClip,
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
    return m_eyeDistance;
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
    glDrawBuffer(GL_BACK);
}

void
GLUtils::DisplayEpilogue(void)
{
    GLAppHandler& glHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());
    glFinish();
    PlatformMiscUtils::VBLWait();
    glHandler.SwapBuffers();
}

void
GLUtils::ClearScreen(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void
GLUtils::ColourSet(float inRed, float inGreen, float inBlue)
{
    glColor3f(inRed, inGreen, inBlue);
}

void
GLUtils::DrawRectangle(tVal inX1, tVal inY1, tVal inX2, tVal inY2)
{
    glBegin(GL_QUADS);
    glVertex2f(inX1,inY1);
    glVertex2f(inX1,inY2);
    glVertex2f(inX2,inY2);
    glVertex2f(inX2,inY1);
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
    glBindTexture(GL_TEXTURE_2D, inTex.BindingNameGet());
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(-width2,-height2);
    glTexCoord2f(0,1);
    glVertex2f(-width2,height2);
    glTexCoord2f(1,1);
    glVertex2f(width2,height2);
    glTexCoord2f(1,0);
    glVertex2f(width2,-height2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void
GLUtils::DrawSprite(const GLTexture& inTex, const GLRectangle& inRectangle)
{
    glBindTexture(GL_TEXTURE_2D, inTex.BindingNameGet());
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    {
        static tVal ctr=0;

        glTranslatef(0,0,0.0*sin((ctr++) / 100000.0));
    }
    glBegin(GL_QUADS);
    glTexCoord2f(inRectangle.xmin,inRectangle.ymin);
    glVertex2f(-0.5,-0.5);
    glTexCoord2f(inRectangle.xmin,inRectangle.ymax);
    glVertex2f(-0.5,0.5);
    glTexCoord2f(inRectangle.xmax,inRectangle.ymax);
    glVertex2f(0.5,0.5);
    glTexCoord2f(inRectangle.xmax,inRectangle.ymin);
    glVertex2f(0.5,-0.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void
GLUtils::DrawSprite(const GLTexture& inTex, tVal inX, tVal inY)
{
    tVal width=inTex.Width();
    tVal height=inTex.Height();
    glBindTexture(GL_TEXTURE_2D, inTex.BindingNameGet());
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(inX,inY);
    glTexCoord2f(0,1);
    glVertex2f(inX,inY+width);
    glTexCoord2f(1,1);
    glVertex2f(inX+height,inY+width);
    glTexCoord2f(1,0);
    glVertex2f(inX+height,inY);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void
GLUtils::DrawRotatedSprite(const GLTexture& inTex, tVal inX, tVal inY, tVal inAngle)
{
    tVal width=inTex.Width();
    tVal height=inTex.Height();
    glBindTexture(GL_TEXTURE_2D, inTex.BindingNameGet());
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    tVal xCentre=inX+width/2;
    tVal yCentre=inY+height/2;
    glTranslatef(xCentre, yCentre,0);
    glRotatef(inAngle,0,0,1);
    glTranslatef(-xCentre, -yCentre,0);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(inX,inY);
    glTexCoord2f(0,1);
    glVertex2f(inX,inY+width);
    glTexCoord2f(1,1);
    glVertex2f(inX+height,inY+width);
    glTexCoord2f(1,0);
    glVertex2f(inX+height,inY);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
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
GLUtils::BlendSet(tBlendType inValue)
{
    if (m_blendState != inValue)
    {
        switch (inValue)
        {
            case kBlendTransparent:
                glDisable(GL_POLYGON_SMOOTH);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_BLEND);
                break;

            case kBlendLine:
            {
                glDisable(GL_POLYGON_SMOOTH);
                if (m_displayQuality != kQualityLow)
                {
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glEnable(GL_BLEND);
                }
                else
                {
                    glDisable(GL_BLEND);
                }
            }
            break;

            case kBlendNone:
                glDisable(GL_POLYGON_SMOOTH);
                glDisable(GL_BLEND);
                break;

            case kBlendSolid:
                if (m_polygonSmoothing)
                {
                    // Set up polygon anti-aliasing
                    glEnable(GL_POLYGON_SMOOTH);
                    glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
                    glEnable(GL_BLEND);
                }
                else
                {
                    glDisable(GL_BLEND);
                }
                break;

            default:
                throw(LogicFail("Invalid value to GLUtils::BlendSet"));
                break;
        }
        m_blendState = inValue;
    }
}

void
GLUtils::AmbientLightSet(tVal inAmbient)
{
    GLfloat ambient[4]={inAmbient, inAmbient, inAmbient, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
}

void
GLUtils::ModulationSet(tModulationType inValue)
{
    if (m_modulateState != inValue)
    {
        switch (inValue)
        {
            case kModulationNone:
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                glDisable(GL_LIGHTING);
                break;
                
            case kModulationColour:
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                glDisable(GL_LIGHTING);
                break;

            case kModulationLighting:
            if (m_useLighting)
            {
                GLfloat ambient[4]={1.0,1.0,1.0,1};
                glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
                
                GLfloat specular[4]={1.0,1.0,1.0,1};
                glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

                GLfloat diffuse[4]={0.0,0.0,0.0,1};
                glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

                glMaterialf(GL_FRONT, GL_SHININESS, 20);
                
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                glEnable(GL_LIGHTING);
                glNormal3f(0,0,1);
            }
            else
            {
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                glDisable(GL_LIGHTING);
                ColourSet(1,1,1,1);
            }
            break;

            default:
                throw(LogicFail("Invalid value to GLUtils::ModulationSet"));
                break;
        }
        m_modulateState=inValue;
    }
}

GLUtils::tDisplayQuality
GLUtils::DisplayQualityGet(void)
{
    if (m_displayQuality == kQualityNotSet)
    {
        string displayQuality("low");
        CoreEnv::Instance().VariableGetIfExists(displayQuality, "DISPLAY_QUALITY");
        if (displayQuality == "low")
        {
            m_displayQuality = kQualityLow;
        }
        else if (displayQuality == "medium")
        {
            m_displayQuality = kQualityMedium;
        }
        else if (displayQuality == "high")
        {
            m_displayQuality = kQualityHigh;
        }
        else
        {
            throw(CommandFail("Bad value for DISPLAY_QUALITY: should be low, medium or high"));
        }
    }
    return m_displayQuality;
}

void
GLUtils::TextureParamsReset(void)
{
    switch (DisplayQualityGet())
    {
        case kQualityLow:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
            break;

        case kQualityMedium:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            break;

        case kQualityHigh:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            break;

        default:
            throw(LogicFail("Bad value for m_displayQuality"));
    }
}

void
GLUtils::Reset(void)
{
    TextureParamsReset();
    
    switch (DisplayQualityGet())
    {
        case kQualityLow:
            break;
            
        case kQualityMedium:    
            break;

        case kQualityHigh:
            glEnable(GL_POINT_SMOOTH);
            glEnable(GL_LINE_SMOOTH);
            break;

        default:
            throw(LogicFail("Bad value for m_displayQuality"));
    }
    glDisable(GL_DEPTH_TEST);
    m_modulateState=kModulationInvalid;
    ModulationSet(kModulationNone);
}

void
GLUtils::PolygonSmoothingSet(bool inValue)
{
    m_polygonSmoothing=inValue;
}
    
void
GLUtils::UseLightingSet(bool inValue)
{
    m_useLighting=inValue;
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

