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
 * $Id$
 * $Log$
 */

#include "TestMushcoreApp.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(TestMushcoreApp);

U32 TestMushcoreApp::m_staticMagic=0;
U32 TestMushcoreApp::m_passCount=0;
TestMushcoreApp::tFails TestMushcoreApp::m_fails;

TestMushcoreApp::TestMushcoreApp()
{
    cout << "Constructed TestMushcoreApp" << endl;
    m_staticMagic = kMagic;
    m_dynamicMagic = kMagic;
}

TestMushcoreApp::~TestMushcoreApp()
{
    if (m_dynamicMagic != kMagic)
    {
        FailureAdd("Magic wrong in ~TestMushcoreApp");
    }
    cout << "Destructed TestMushcoreApp" << endl;    
}

void
TestMushcoreApp::EnterInstance(void)
{
    cout << "Starting tests" << endl;
    RunTest("testauto", "MushcoreAutomonkey");
}

void
TestMushcoreApp::RunTest(const string& inCommandStr, const string& inNameStr)
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
TestMushcoreApp::Enter(void)
{
    Sgl().EnterInstance();
}

bool
TestMushcoreApp::MagicTest(void)
{
    return (m_staticMagic == kMagic);
}

void
TestMushcoreApp::FailureAdd(const std::string& inStr)
{
    m_fails.push_back(inStr);
}

void
TestMushcoreApp::PassAdd(const std::string& inStr)
{
    ++m_passCount;
}

void
TestMushcoreApp::FailuresPrint(void)
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

