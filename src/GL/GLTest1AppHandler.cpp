/*
 * $Id: GLTest1AppHandler.cpp,v 1.9 2002/05/10 22:38:23 southa Exp $
 * $Log: GLTest1AppHandler.cpp,v $
 * Revision 1.9  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 * Revision 1.8  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.7  2002/05/08 16:31:21  southa
 * Created API directory
 *
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

#include "GLTest1AppHandler.h"

#include "GLStandard.h"
#include "mushCore.h"
#include "GLTexture.h"
#include "GLData.h"
#include "GLUtils.h"

CoreInstaller
GLTest1CommandHandlerInstaller(GLTest1AppHandler::Install);

void
GLTest1AppHandler::Initialise(void)
{
    CoreApp::Instance().Process("loadpixmap ../test/test.tiff;");

    GLUtils::StandardInit();
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);
    GLUtils::CheckGLError();
}

void
GLTest1AppHandler::Display(void)
{
    string str("Hello from Test1");

    glLineWidth(5);
    static double ticker=0;
    static TextureRef texNum=0;

    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();

    GLUtils::RasterPos(0, 0);
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
    

    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
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
