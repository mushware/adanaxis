//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreMain.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } v98A6zMKka50f5ALagSTvw
/*
 * $Id: TestMushcoreMain.cpp,v 1.4 2004/01/01 21:15:47 southa Exp $
 * $Log: TestMushcoreMain.cpp,v $
 * Revision 1.4  2004/01/01 21:15:47  southa
 * Created XCode project
 *
 * Revision 1.3  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:37  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/20 15:38:28  southa
 * Created MushcoreTest
 *
 */

#include "TestMushcoreMain.h"

#include "TestMushcoreApp.h"

using namespace Mushware;
using namespace std;

int TestMushcoreMain(int argc, char *argv[])
{
    try
    {
        cout << "Mushcore test application" << endl;
        cout << "Number of installed modules=" << MushcoreInstaller::NumInstalledModulesGet() << endl;

        for (int i=1; i<argc; ++i)
        {
            string argStr=argv[i];
            if (argStr.substr(0, 4) == "-psn")
            {
                // Ignore Mac OS X funnies
                ++i;
            }
            else
            {
                MushcoreInterpreter::Sgl().Execute(argStr);
            }
        }
    
        TestMushcoreApp::Enter();
        cout << endl << "Final test report" << endl;
        cout << "=================" << endl;
        TestMushcoreApp::FailuresPrint();
        cout << endl << "--- report ends" << endl;
        cout << "The message 'Destructed TestMushcoreApp' should follow this line" << endl;
    }
    catch (exception& e)
    {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown exception" << endl;
        return 1;
    }
    if (!TestMushcoreApp::MagicTest())
    {
        cerr << "Magic test failed" << endl;
        return 1;
    }
    return 0;
}
