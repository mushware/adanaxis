/*
 * $Id: GLAppHandler.cpp,v 1.3 2002/03/21 22:07:54 southa Exp $
 * $Log: GLAppHandler.cpp,v $
 * Revision 1.3  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.2  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "GLAppHandler.hp"
#include "GLStandard.hp"
#include "mushCore.hp"

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
    glutPostRedisplay();
    CoreAppHandler::Idle(outQuit, outUSleepFor);
}

void
GLAppHandler::StandardInit(void)
{
    char *argv[] = {"glutInit", ""};
    int argc=sizeof(argv)/sizeof(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    glutVisibilityFunc(VisibilityHandler);
    CheckGLError();
}

void
GLAppHandler::Initialise(void)
{
    StandardInit();
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);
    glutCreateWindow("GLApp");
}

void
GLAppHandler::IdleHandler(void)
{
    bool doQuit;
    int uSleepFor;
    Instance().Idle(doQuit, uSleepFor);
}

void
GLAppHandler::VisibilityHandler(int inState)
{
    if (inState == GLUT_NOT_VISIBLE)
    {
        cerr << "Invisible" << endl;
        Instance().Signal(kSignalNotVisible);
    }
    else if (inState == GLUT_VISIBLE)
    {
        cerr << "Visible" << endl;
        Instance().Signal(kSignalVisible);
    }
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
GLAppHandler::Signal(U32 inSignal)
{
    switch (inSignal)
    {
        case kSignalVisible:
            m_visible=true;
            break;

        case kSignalNotVisible:
            m_visible=false;
            break;
    }
}    

void
GLAppHandler::MainLoop(void)
{
    glutMainLoop();
    CheckGLError();
}

void
GLAppHandler::OrthoPrologue(void)
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
GLAppHandler::OrthoEpilogue(void)
{
    glPopAttrib();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);    
}

