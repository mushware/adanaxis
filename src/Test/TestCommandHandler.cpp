/*
 * $Id: TestCommandHandler.cpp,v 1.5 2002/05/10 16:39:35 southa Exp $
 * $Log: TestCommandHandler.cpp,v $
 * Revision 1.5  2002/05/10 16:39:35  southa
 * Changed .hp files to .h
 *
 * Revision 1.4  2002/05/09 18:01:39  southa
 * Rebuild under cygwin
 *
 * Revision 1.3  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.2  2002/02/23 11:43:36  southa
 * Added AutoMonkey
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */
 
#include "TestCommandHandler.h"
#include "mushCore.h"

#include "Test.h"

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
        else if (str == "4") Test::Test4();
        else if (str == "5") Test::Test5();
        else
        {
            cerr << "Unknown test " << str << endl;
            return false;
        }
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
