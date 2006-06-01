//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlMain.cpp
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
//%Header } SdRTI625GkbgvxMBKKjwjA
/*
 * $Id: TestMustlMain.cpp,v 1.12 2005/05/19 13:02:25 southa Exp $
 * $Log: TestMustlMain.cpp,v $
 * Revision 1.12  2005/05/19 13:02:25  southa
 * Mac release work
 *
 * Revision 1.11  2004/09/26 20:43:19  southa
 * TestMustl fixes
 *
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

