/*
 * $Id: TestCommandHandler.cpp,v 1.2 2002/02/23 11:43:36 southa Exp $
 * $Log: TestCommandHandler.cpp,v $
 * Revision 1.2  2002/02/23 11:43:36  southa
 * Added AutoMonkey
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */
 
#include "TestCommandHandler.hp"
#include "CoreApp.hp"
#include "CoreInstaller.hp"

#include "Test.hp"

CoreInstaller testCommandHandlerInstaller(TestCommandHandler::Install);

CoreScalar
TestCommandHandler::Execute(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    string str;
    ioCommand.PopParam(str);
    
    try
    {
        if (str == "1") Test::Test1();
        else if (str == "2") Test::Test2();
        else if (str == "3") Test::Test3();
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
    CoreApp::Instance().AddHandler("test", Execute);
}
