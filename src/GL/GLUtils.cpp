/*
 * $Id: GLUtils.cpp,v 1.9 2002/06/04 17:02:24 southa Exp $
 * $Log: GLUtils.cpp,v $
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

void
GLUtils::MoveTo(tVal inX, tVal inY)
{
    glTranslatef(inX-m_x,inY-m_y,0);
    m_x=inX;
    m_y=inY;
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
    glPushAttrib(GL_ENABLE_BIT);
}

void
GLUtils::IdentityEpilogue(void)
{
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void
GLUtils::OrthoPrologue(void)
{
    IdentityPrologue();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, 	glutGet(GLUT_WINDOW_HEIGHT));
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
    tVal width=glutGet(GLUT_WINDOW_WIDTH);
    tVal height=glutGet(GLUT_WINDOW_HEIGHT);
    gluOrtho2D(-width/2, width/2, -height/2, height/2);
    
#if 1
    gluLookAt(inX, inY, 0.1, // eye position
              inX, inY, 0, // point we're looking at
              sin(inAngle),cos(inAngle),0 // direction of up
              );
#endif
}    

void
GLUtils::DisplayPrologue(void)
{
    glDrawBuffer(GL_BACK);
}

void
GLUtils::DisplayEpilogue(void)
{
    glutSwapBuffers();
}

void
GLUtils::ClearScreen(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void
GLUtils::SetColour(float inRed, float inGreen, float inBlue)
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
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, inStr[i]);
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
    glutPostRedisplay();
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

void
GLUtils::SafetyHandler(void)
{
}

void
GLUtils::StandardInit(void)
{
    char *argv[] = {"glutInit", ""};
    int argc=sizeof(argv)/sizeof(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE /* | GLUT_ALPHA */);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    // This kills glut on cygwin
    // glutDisplayFunc(SafetyHandler);
    glutInitWindowSize(640,480);
    glutCreateWindow("Game");
    glutDisplayFunc(SafetyHandler);
    CheckGLError();
}

void
GLUtils::GameInit(void)
{
    char *argv[] = {"glutInit", ""};
    int argc=sizeof(argv)/sizeof(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    // This kills glut on cygwin
    // glutDisplayFunc(SafetyHandler);
    glutGameModeString("640x480:16@60");
    glutEnterGameMode();
    glutDisplayFunc(SafetyHandler);
    CheckGLError();
}
