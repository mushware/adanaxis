/*
 * $Id: GLAppHandler.cpp,v 1.1.1.1 2002/02/11 22:30:09 southa Exp $
 * $Log: GLAppHandler.cpp,v $
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "GLAppHandler.hp"
#include "GLStandard.hp"
#include "CoreAppHandler.hp"

void
GLAppHandler::CheckGLError(void)
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
GLAppHandler::Idle(bool& outQuit, int& outUSleepFor)
{
    Display();
    CoreAppHandler::Idle(outQuit, outUSleepFor);
}

void
GLAppHandler::Initialise(void)
{
    char buf1[]="glutInit";
    char buf2[]="";
    char buf3[]="";
    char *argv[] = {buf1,buf2,buf3};
    int argc=sizeof(argv)/sizeof(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA);
    glutCreateWindow("GLApp");
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    CheckGLError();
}

void
GLAppHandler::IdleHandler(void)
{
    bool doQuit;
    int uSleepFor;
    Instance().Idle(doQuit, uSleepFor);
}

void
GLAppHandler::Display(void)
{
    string str("Hello from OpenGL");

    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    static float lineWidth;
    if ((lineWidth+=0.002)>=1) lineWidth=0;
    glLineWidth(5*lineWidth);

    glDrawBuffer(GL_BACK);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glTranslatef(16, 16, 0);

    glScalef(0.5*lineWidth, 0.5*lineWidth, 0.5*lineWidth);
    glColor3f(lineWidth,lineWidth,lineWidth);
    for (Size i=0; i < str.size(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
        if (str[i] == ' ')
        {
            glTranslatef(-64, 0, 0);

        }
    }
    glPopAttrib();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
    CheckGLError();
}

void
GLAppHandler::MainLoop(void)
{
    glutMainLoop();
    CheckGLError();
}
