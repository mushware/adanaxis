//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlApp.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0bJDpFWP9zvx0y/lGUlbSA
/*
 * $Id: TestMustlApp.cpp,v 1.8 2003/09/17 19:40:39 southa Exp $
 * $Log: TestMustlApp.cpp,v $
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
    try
    {
        MustlPlatform::LaunchURL(configURL.str());
    }
    catch (MushcoreNonFatalFail& e)
    {
        cerr << "Exception: " << e.what() << endl;
    }
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
