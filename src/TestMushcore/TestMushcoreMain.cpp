/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: TestMushcoreMain.cpp,v 1.1 2003/01/20 15:38:28 southa Exp $
 * $Log: TestMushcoreMain.cpp,v $
 * Revision 1.1  2003/01/20 15:38:28  southa
 * Created MushcoreTest
 *
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
