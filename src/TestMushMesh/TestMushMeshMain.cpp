//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshMain.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Cbbe6WzOopW+pMqHiBIxvw
/*
 * $Id: TestMushMeshMain.cpp,v 1.2 2004/01/01 21:15:47 southa Exp $
 * $Log: TestMushMeshMain.cpp,v $
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

