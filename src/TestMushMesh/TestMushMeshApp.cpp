//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshApp.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 8XvmBalkJaw8zlwB0njizA
/*
 * $Id$
 * $Log$
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

