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
 * $Id: TestMustlMain.cpp,v 1.2 2003/01/14 17:38:22 southa Exp $
 * $Log: TestMustlMain.cpp,v $
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
        MushcoreGlobalConfig::Instance().Set("MUSTL_WEB_PATH", "test/mustl");
        MushcoreGlobalConfig::Instance().Set("MUSTL_START_FILE", "test/mustl/mustlstart.txt");

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
                MushcoreInterpreter::Instance().Execute(argStr);
            }
        }
    
        MushcoreInterpreter::Instance().Execute("load($MUSTL_START_FILE)");

        TestMustlApp::Instance().Enter();
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
