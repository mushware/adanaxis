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

#include "TestMustlApp.h"

using namespace Mushware;
using namespace std;

void
TestMustlApp::Enter(void)
{
    U32 webPort=7200;

    cout << "TestMustl application started" << endl;
    cout << "Please view URL http://127.0.0.1:" << webPort << " in your web browser," << endl;
    cout << "or press control-C to exit." << endl;

    MustlWebServer::Instance().Connect(webPort);

    ostringstream configURL;
    configURL << "http://127.0.0.1:" << webPort << "/";

    m_doQuit = false;

    while (!m_doQuit)
    {
        MustlWebServer::Instance().Accept();
        MustlWebRouter::Instance().ReceiveAll();
    }
}
