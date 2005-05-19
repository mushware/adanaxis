//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshMain.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } 3qr3aeVjdwNzkhYOLlMo7g
/*
 * $Id: TestMushMeshMain.cpp,v 1.3 2004/01/02 21:13:17 southa Exp $
 * $Log: TestMushMeshMain.cpp,v $
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

