/*
 * $Id$
 * $Log$
 */

#include "GLCommandHandler.hp"
#include "CoreApp.hp"
#include "Installer.hp"
#include "GLAppHandler.hp"

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
    }

void
GLCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler(Instance());
}