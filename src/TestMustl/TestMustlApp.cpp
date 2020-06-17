//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlApp.cpp
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
//%Header } IgDwORq08JLQm8CjbcTLkw
/*
 * $Id: TestMustlApp.cpp,v 1.12 2006/06/01 15:40:06 southa Exp $
 * $Log: TestMustlApp.cpp,v $
 * Revision 1.12  2006/06/01 15:40:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/05/19 13:02:25  southa
 * Mac release work
 *
 * Revision 1.10  2004/09/26 20:43:19  southa
 * TestMustl fixes
 *
 * Revision 1.9  2004/01/02 21:13:18  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:38  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/02/05 16:19:46  southa
 * Build fixes
 *
 * Revision 1.5  2003/01/20 10:45:32  southa
 * Singleton tidying
 *
 * Revision 1.3  2003/01/14 22:02:12  southa
 * Command line build fixes
 *
 * Revision 1.2  2003/01/14 20:46:12  southa
 * Post data handling
 *
 * Revision 1.1  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 */

#include "TestMustlApp.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(TestMustlApp);

MushcoreInstaller TestMustlAppInstaller(TestMustlApp::Install);

void
TestMustlApp::Enter(void)
{
    U32 webPort=7200;
    ostringstream configURL;
    configURL << "http://127.0.0.1:" << webPort << "/";

    cout << "TestMustl application started" << endl;
    cout << "Please view URL " << configURL.str() << " in your web browser," << endl;
    cout << "or press control-C to exit." << endl;

    MustlWebServer::Sgl().Connect(webPort);

    MustlPlatform::LaunchURL(configURL.str());

    m_doQuit = false;

    while (!m_doQuit)
    {
        MustlWebServer::Sgl().Accept();
        MustlWebRouter::Sgl().ReceiveAll();
    }
}

void
TestMustlApp::DoQuit(void)
{
    m_doQuit = true;
}

MushcoreScalar
TestMustlApp::TestMustl(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    ioEnv.Out() << "This application must be started from the mustl directory" << endl;
    ioEnv.Out() << "Number of installed modules=" << MushcoreInstaller::NumInstalledModulesGet() << endl;
    MushcoreGlobalConfig::Sgl().Set("MUSTL_WEB_PATH", "test/mustl");
    MushcoreGlobalConfig::Sgl().Set("MUSTL_START_FILE", "test/mustl/mustlstart.txt");
    
    MushcoreInterpreter::Sgl().Execute("load($MUSTL_START_FILE)");
    
    TestMustlApp::Sgl().Enter();

    return MushcoreScalar(0);
}

void
TestMustlApp::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmustl", TestMustl);
}
