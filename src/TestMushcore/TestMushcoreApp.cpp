//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreApp.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } RQtkWWJl16gsxy24ZbLFsg
/*
 * $Id: TestMushcoreApp.cpp,v 1.8 2006/06/01 15:40:03 southa Exp $
 * $Log: TestMushcoreApp.cpp,v $
 * Revision 1.8  2006/06/01 15:40:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.6  2004/01/05 14:27:41  southa
 * MushPie work and build fixes
 *
 * Revision 1.5  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:36  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/20 17:03:22  southa
 * Command line expression evaluator enhancements
 *
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
    RunTest("testmushcoreauto", "Automonkey");
    RunTest("testmushcorecommand", "Command interpreter");
    RunTest("testmushcoreio", "Input/output");
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

