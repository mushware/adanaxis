/*
 * $Id: GLCommandHandler.cpp,v 1.5 2002/02/23 20:05:15 southa Exp $
 * $Log: GLCommandHandler.cpp,v $
 * Revision 1.5  2002/02/23 20:05:15  southa
 * Added libraries and test files
 *
 * Revision 1.4  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.3  2002/02/18 22:43:53  southa
 * First stage GIF loader
 *
 * Revision 1.2  2002/02/18 22:04:37  southa
 * Initial texture loading
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "GLCommandHandler.hp"
#include "CoreApp.hp"
#include "CoreTest.hp"
#include "Installer.hp"
#include "GLAppHandler.hp"
#include "GLData.hp"
#include "GLTextureGIF.hp"
#include "GLTest.hp"

GLCommandHandler *GLCommandHandler::m_instance = NULL;

Installer GLCommandHandlerInstaller(GLCommandHandler::Install);

bool
GLCommandHandler::HandleCommand(const string& inStr)
{
    try
    {
        if (inStr.substr(0,6) == "initGL") InitGL(inStr.substr(6));
        else if (inStr.substr(0,10) == "loadPixmap") LoadPixmap(inStr.substr(11));
        else if (inStr == "glTest1") GLTest::Test1(inStr);
        else return false;
    }
    catch (TestFail& f)
    {
        cerr << "Test failed: " << f;
    }
    return true;
}

void
GLCommandHandler::InitGL(const string& inStr)
{
    // Save inStr to context
    CoreAppHandler::Instance().Mutate(new GLAppHandler);
}

void GLCommandHandler::LoadPixmap(const string& inStr)
{
    try
    {
        GLData::Instance().AddTexture(GLTextureGIF(inStr));
    }
    catch (LoaderFail f)
    {
        cerr << f;
    }
}

void
GLCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler(Instance());
}