/*
 * $Id$
 * $Log$
 */
 
#include "TestCommandHandler.hp"
#include "CoreApp.hp"
#include "Installer.hp"

#include "Test.hp"

TestCommandHandler *TestCommandHandler::m_instance = NULL;

Installer testCommandHandlerInstaller(TestCommandHandler::Install);

bool
TestCommandHandler::HandleCommand(const string& str)
{
    try
    {
        if (str == "test1") Test::Test1();
        else if (str == "test2") Test::Test2();
        else return false;
    }
    catch (TestFail& f)
    {
        cerr << "Test failed: " << f;
    }
    return true;
}

void
TestCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler(Instance());
}