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
 * $Id: TestMustlApp.cpp,v 1.2 2003/01/14 20:46:12 southa Exp $
 * $Log: TestMustlApp.cpp,v $
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

auto_ptr<TestMustlApp> TestMustlApp::m_instance;

void
TestMustlApp::Enter(void)
{
    U32 webPort=7200;
    ostringstream configURL;
    configURL << "http://127.0.0.1:" << webPort << "/";

    cout << "TestMustl application started" << endl;
    cout << "Please view URL " << configURL.str() << " in your web browser," << endl;
    cout << "or press control-C to exit." << endl;

    MustlWebServer::Instance().Connect(webPort);

    MustlPlatform::LaunchURL(configURL.str());
    m_doQuit = false;

    while (!m_doQuit)
    {
        MustlWebServer::Instance().Accept();
        MustlWebRouter::Instance().ReceiveAll();
    }
}

void
TestMustlApp::DoQuit(void)
{
    m_doQuit = true;
}    