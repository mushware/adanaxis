/*
 * $Id$
 * $Log$
 */

#include "GLAppHandler.hp"
#include "GLStandard.hp"
#include "CoreAppHandler.hp"

void
GLAppHandler::Idle(bool& outQuit, int& outUSleepFor)
{
    Display();
    CoreAppHandler::Idle(outQuit, outUSleepFor);
}

void
GLAppHandler::Initialise(void)
{
    // glutInitWindowSize(winWidth = 512, winHeight = 512);
    char buf1[]="glutInit";
    char buf2[]="";
    char buf3[]="";
    char *argv[] = {buf1,buf2,buf3};
    int argc=sizeof(argv)/sizeof(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayString("");
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA);
    glutCreateWindow("GLApp");
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
}

void
GLAppHandler::MainLoop(void)
{
    glutMainLoop();
}
