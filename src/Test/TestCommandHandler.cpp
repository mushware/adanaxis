/*
 * $Id: TestCommandHandler.cpp,v 1.1.1.1 2002/02/11 22:30:09 southa Exp $
 * $Log: TestCommandHandler.cpp,v $
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
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
        else if (str == "test3") Test::Test3();
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