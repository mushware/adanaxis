//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlMain.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0+Hk1GDkv2UBHJRPkF3mJA
/*
 * $Id: TestMustlMain.cpp,v 1.10 2004/01/02 21:13:18 southa Exp $
 * $Log: TestMustlMain.cpp,v $
 * Revision 1.10  2004/01/02 21:13:18  southa
 * Source conditioning
 *
 * Revision 1.9  2004/01/01 21:15:47  southa
 * Created XCode project
 *
 * Revision 1.8  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:39  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/20 10:45:32  southa
 * Singleton tidying
 *
 * Revision 1.5  2003/01/15 13:27:33  southa
 * Static library linking fixes
 *
 * Revision 1.4  2003/01/14 22:02:12  southa
 * Command line build fixes
 *
 * Revision 1.3  2003/01/14 20:46:12  southa
 * Post data handling
 *
 * Revision 1.2  2003/01/14 17:38:22  southa
 * Mustl web configuration
 *
 * Revision 1.1  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 */

#include "TestMustlMain.h"

#include "TestMustlApp.h"

using namespace Mushware;
using namespace std;

int TestMustlMain(int argc, char *argv[])
{
    try
    {
        cout << "This application must be started from the mustl directory" << endl;
        cout << "Number of installed modules=" << MushcoreInstaller::NumInstalledModulesGet() << endl;
        MushcoreGlobalConfig::Sgl().Set("MUSTL_WEB_PATH", "test/mustl");
        MushcoreGlobalConfig::Sgl().Set("MUSTL_START_FILE", "test/mustl/mustlstart.txt");

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
    
        MushcoreInterpreter::Sgl().Execute("load($MUSTL_START_FILE)");

        TestMustlApp::Sgl().Enter();
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
    return 0;
}

