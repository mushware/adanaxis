/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: TestCommandHandler.cpp,v 1.16 2003/01/11 17:07:53 southa Exp $
 * $Log: TestCommandHandler.cpp,v $
 * Revision 1.16  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.15  2003/01/11 13:03:18  southa
 * Use Mushcore header
 *
 * Revision 1.14  2003/01/09 14:57:09  southa
 * Created Mushcore
 *
 * Revision 1.13  2002/12/29 21:00:01  southa
 * More build fixes
 *
 * Revision 1.12  2002/12/20 13:17:49  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/27 08:56:30  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/07 13:36:52  southa
 * Conditioned source
 *
 * Revision 1.8  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.7  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.6  2002/05/24 18:09:39  southa
 * MushcoreXML and game map
 *
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
#include "Mushcore.h"

#include "Test.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller testCommandHandlerInstaller(TestCommandHandler::Install);

MushcoreScalar
TestCommandHandler::Execute(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
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
    catch (MushcoreLogicFail& f)
    {
        cerr << "Test failed: " << f.what();
    }
    return true;
}

void
TestCommandHandler::Install(void)
{
    MushcoreInterpreter::Instance().AddHandler("test", Execute);
}
