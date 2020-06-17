//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshApp.cpp
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
//%Header } 8fqDJ4PXpfNG9FqKjz8BFQ
/*
 * $Id: TestMushMeshApp.cpp,v 1.11 2006/06/01 15:40:01 southa Exp $
 * $Log: TestMushMeshApp.cpp,v $
 * Revision 1.11  2006/06/01 15:40:01  southa
 * DrawArray verification and fixes
 *
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

