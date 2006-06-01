//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshApp.cpp
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
//%Header } 9CfN3r3VLVO5Y8CgtzkNdA
/*
 * $Id: TestMushMeshApp.cpp,v 1.10 2005/05/19 13:02:22 southa Exp $
 * $Log: TestMushMeshApp.cpp,v $
 * Revision 1.10  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.9  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.8  2003/10/24 12:39:09  southa
 * Triangular mesh work
 *
 * Revision 1.7  2003/10/23 20:03:58  southa
 * End mesh work
 *
 * Revision 1.6  2003/10/20 13:02:54  southa
 * Patch fixes and testing
 *
 * Revision 1.5  2003/10/17 12:27:20  southa
 * Line end fixes and more mesh work
 *
 * Revision 1.4  2003/10/15 12:23:10  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.3  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
 * Revision 1.2  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 * Revision 1.1  2003/10/14 13:07:26  southa
 * MushMesh vector creation
 *
 */

#include "TestMushMeshApp.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(TestMushMeshApp);

U32 TestMushMeshApp::m_passCount=0;
TestMushMeshApp::tFails TestMushMeshApp::m_fails;

void
TestMushMeshApp::EnterInstance(void)
{
    cout << "Starting tests" << endl;
    RunTest("testvector", "MushMeshVector");
    RunTest("testbox", "MushMeshBox");
    RunTest("testarray", "MushMeshArray");
    RunTest("testtriangulararray", "MushMeshTriangularArray");
    RunTest("testutils", "MushMeshUtils");
    RunTest("testpatch", "MushMeshPatch");
    RunTest("testsubdivide", "MushMeshSubdivide");
}

void
TestMushMeshApp::RunTest(const string& inCommandStr, const string& inNameStr)
{
    cout << "Test " << inNameStr << "... ";
    try
    {
        MushcoreInterpreter::Sgl().Execute(inCommandStr);
        PassAdd(inNameStr);
        cout << "passed";
    }
    catch (MushcoreFail& e)
    {
        cout << "FAILED";
        FailureAdd(inNameStr+": "+e.what());
    }
    cout << endl;
}
        
void
TestMushMeshApp::Enter(void)
{
    Sgl().EnterInstance();
}

void
TestMushMeshApp::FailureAdd(const std::string& inStr)
{
    m_fails.push_back(inStr);
}

void
TestMushMeshApp::PassAdd(const std::string& inStr)
{
    ++m_passCount;
}

void
TestMushMeshApp::FailuresPrint(void)
{
    if (m_fails.size() == 0)
    {
        cout << "All " << m_passCount << " tests passed" << endl;
    }
    else
    {
        cout << "****** " << m_fails.size() << " test failures" << endl;
        cout << "Failure report:" << endl;
    }
    for (tFails::const_iterator p = m_fails.begin(); p != m_fails.end(); ++p)
    {
        cout << *p << endl;
    }
}

