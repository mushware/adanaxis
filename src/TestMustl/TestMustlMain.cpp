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
 * $Id: TestMustlMain.cpp,v 1.6 2003/01/20 10:45:32 southa Exp $
 * $Log: TestMustlMain.cpp,v $
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

int main(int argc, char *argv[])
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
