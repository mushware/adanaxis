/*
 * $Id$
 * $Log$
 */

#include "GLTest1AppHandler.hp"

#include "GLStandard.hp"
#include "CoreAppHandler.hp"
#include "GLTexture.hp"
#include "GLData.hp"
#include "CoreApp.hp"

void
GLTest1AppHandler::Initialise(void)
{
    CoreApp::Instance().Process("loadPixmap test_int.gif");
    
    glutInitWindowSize(640,480);

    char buf1[]="glutInit";
    char buf2[]="";
    char buf3[]="";
    char *argv[] = {buf1,buf2,buf3};
    int argc=sizeof(argv)/sizeof(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayString("");
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE /*| GLUT_ALPHA*/);
    if (1)
    {
        glutGameModeString("640x480:16@60");
        glutEnterGameMode();
    }
    else
    {
        glutCreateWindow("GLTest1App");
    }
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void
GLTest1AppHandler::Display(void)
{
    string str("Hello from Test1");

    glLineWidth(5);
    static double ticker=0;
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
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    
    glRasterPos2f(0, 0);
    glBitmap(0,0,0,0,20*sin(ticker), 20*cos(ticker),NULL);
    const GLTexture& tex=GLData::Instance().GetTexture(0);
    static int printCtr=0;
    if (printCtr++ % 256==0) cerr << tex << endl;
    glDrawPixels(tex.Width(0), tex.Height(0), tex.PixelFormat(0),
                tex.PixelType(0), tex.DataPtr(0));
    
    glPopAttrib();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
    ticker+=0.05;
}

void
GLTest1AppHandler::IdleHandler(void)
{
    bool doQuit;
    int uSleepFor;
    Instance().Idle(doQuit, uSleepFor);
}
