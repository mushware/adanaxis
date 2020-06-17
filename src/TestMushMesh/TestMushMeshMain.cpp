//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshMain.cpp
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
//%Header } BT+AlNDfC7QVuO21aSk+Dw
/*
 * $Id: TestMushMeshMain.cpp,v 1.5 2006/06/01 15:40:01 southa Exp $
 * $Log: TestMushMeshMain.cpp,v $
 * Revision 1.5  2006/06/01 15:40:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.2  2004/01/01 21:15:47  southa
 * Created XCode project
 *
 * Revision 1.1  2003/10/14 13:07:26  southa
 * MushMesh vector creation
 *
 */


#include "TestMushMeshMain.h"

#include "TestMushMeshApp.h"

using namespace Mushware;
using namespace std;

int TestMushMeshMain(int argc, char *argv[])
{
    try
    {
        cout << "MushMesh test application" << endl;
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
    
        TestMushMeshApp::Enter();
        cout << endl << "Final test report" << endl;
        cout << "=================" << endl;
        TestMushMeshApp::FailuresPrint();
        cout << endl << "--- report ends" << endl;
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

