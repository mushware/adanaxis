//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreMain.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5vaLykc2dqGzmLCLGIM+rQ
/*
 * $Id: TestMushcoreMain.cpp,v 1.6 2005/05/19 13:02:24 southa Exp $
 * $Log: TestMushcoreMain.cpp,v $
 * Revision 1.6  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:18  southa
 * Source conditioning
 *
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
