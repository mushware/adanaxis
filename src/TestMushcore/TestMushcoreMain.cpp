//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreMain.cpp
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
//%Header } kDSiWmAJzu9LMIuKjBEF5Q
/*
 * $Id: TestMushcoreMain.cpp,v 1.7 2006/06/01 15:40:04 southa Exp $
 * $Log: TestMushcoreMain.cpp,v $
 * Revision 1.7  2006/06/01 15:40:04  southa
 * DrawArray verification and fixes
 *
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
