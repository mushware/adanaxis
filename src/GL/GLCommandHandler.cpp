/*
 * $Id: GLCommandHandler.cpp,v 1.2 2002/02/18 22:04:37 southa Exp $
 * $Log: GLCommandHandler.cpp,v $
 * Revision 1.2  2002/02/18 22:04:37  southa
 * Initial texture loading
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "GLCommandHandler.hp"
#include "CoreApp.hp"
#include "Installer.hp"
#include "GLAppHandler.hp"
#include "GLData.hp"
#include "GLTexture.hp"

GLCommandHandler *GLCommandHandler::m_instance = NULL;

Installer GLCommandHandlerInstaller(GLCommandHandler::Install);

bool
GLCommandHandler::HandleCommand(const string& inStr)
{
    if (inStr.substr(0,6) == "initGL") InitGL(inStr.substr(6));
    else if (inStr.substr(0,10) == "loadPixmap") LoadPixmap(inStr.substr(10));
        else return false;

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
        GLData::Instance().AddTexture(GLTexture("test.gif"));
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