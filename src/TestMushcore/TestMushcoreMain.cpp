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
 * $Id$
 * $Log$
 */

#include "TestMushcoreMain.h"

#include "TestMushcoreApp.h"

using namespace Mushware;
using namespace std;

int main(int argc, char *argv[])
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
