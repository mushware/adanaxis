/*
 * $Id: GLTest1AppHandler.cpp,v 1.6 2002/03/18 22:22:15 southa Exp $
 * $Log: GLTest1AppHandler.cpp,v $
 * Revision 1.6  2002/03/18 22:22:15  southa
 * Initial wrangle command
 *
 * Revision 1.5  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.4  2002/02/26 17:01:38  southa
 * Completed Sprite loader
 *
 * Revision 1.3  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.2  2002/02/23 20:05:15  southa
 * Added libraries and test files
 *
 * Revision 1.1  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 */

#include "GLTest1AppHandler.hp"

#include "GLStandard.hp"
#include "mushCore.hp"
#include "GLTexture.hp"
#include "GLData.hp"

CoreInstaller
GLTest1CommandHandlerInstaller(GLTest1AppHandler::Install);

void
GLTest1AppHandler::Initialise(void)
{
    CoreApp::Instance().Process("loadpixmap ../test/test.spr;");
    glutInitWindowSize(300,300);

    char buf1[]="glutInit";
    char buf2[]="";
    char *argv[] = {buf1,buf2};
    int argc=sizeof(argv)/sizeof(argv[0]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE /*| GLUT_ALPHA*/);
    if (0)
    {
        glutGameModeString("640x480:16@60");
        glutEnterGameMode();
    }
    else
    {
        glutCreateWindow("GLTest1");
    }
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    CheckGLError();
}

void
GLTest1AppHandler::Display(void)
{
    string str("Hello from Test1");

    glLineWidth(5);
    static double ticker=0;
    static TextureRef texNum=0;
    
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
    glBitmap(0,0,0,0,20+20*sin(ticker), 20+20*cos(ticker),NULL);
    const GLTexture& tex=GLData::Instance().GetTexture(0);
    static int printCtr=0;

    if (printCtr==0)
    {
        printCtr=1;
        cerr << tex << endl;
    }
    glDrawPixels(tex.Width(texNum), tex.Height(texNum), tex.PixelFormat(texNum),
                     tex.PixelType(texNum), tex.DataPtr(texNum));
    
    glPopAttrib();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
    double oldTicker=ticker;
    ticker+=0.10;
    if ((int) ticker != (int) oldTicker)
    {
        for (int i=0; i<256; ++i)
        {    
            texNum++;
            if (texNum >= GLData::Instance().GetTexture(0).NumberOf()) texNum=0;
            if (tex.Valid(texNum)) break;
        }
    }
}

void
GLTest1AppHandler::IdleHandler(void)
{
    bool doQuit;
    int uSleepFor;
    Instance().Idle(doQuit, uSleepFor);
}

CoreScalar
GLTest1AppHandler::GLTest1(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    CoreAppHandler::Instance().Mutate(new GLTest1AppHandler);
    return CoreScalar(0);
}

void
GLTest1AppHandler::Install(void)
{
    CoreApp::Instance().AddHandler("gltest1", GLTest1);
}
