/*
 * $Id: GLUtils.cpp,v 1.2 2002/05/27 12:58:43 southa Exp $
 * $Log: GLUtils.cpp,v $
 * Revision 1.2  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
 * Revision 1.1  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 */

#include "GLUtils.h"

void
GLUtils::OrthoPrologue(void)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, 	glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_ENABLE_BIT);
}

void
GLUtils::OrthoEpilogue(void)
{
    glPopAttrib();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
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
    glutDisplayFunc(SafetyHandler);
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
    glutDisplayFunc(SafetyHandler);
    glutGameModeString("640x480:16@60");
    glutEnterGameMode();
    glutDisplayFunc(SafetyHandler);
    CheckGLError();
}
