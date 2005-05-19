//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlApp.cpp
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
//%Header } LBuXrVNBDgZM/rBEdmlbZg
/*
 * $Id: TestMustlApp.cpp,v 1.10 2004/09/26 20:43:19 southa Exp $
 * $Log: TestMustlApp.cpp,v $
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
