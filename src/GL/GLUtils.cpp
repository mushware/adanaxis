/*
 * $Id: GLUtils.cpp,v 1.1 2002/05/10 22:38:23 southa Exp $
 * $Log: GLUtils.cpp,v $
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
