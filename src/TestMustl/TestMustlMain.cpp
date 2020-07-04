//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlMain.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 6U4ayzi93HPvklGHUy05Kg
/*
 * $Id: TestMustlMain.cpp,v 1.13 2006/06/01 15:40:06 southa Exp $
 * $Log: TestMustlMain.cpp,v $
 * Revision 1.13  2006/06/01 15:40:06  southa
 * DrawArray verification and fixes
 *
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

