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

#include "TestMustlMain.h"

#include "TestMustlApp.h"

using namespace Mushware;
using namespace std;

int main(int argc, char *argv[])
{
    string argStr;
    for (int i=1; i<argc; i++)
    {
        argStr += argv[i];
        if (i+1 != argc) argStr+=" ";
    }

    MustlConfig::Instance().Set("MUSTL_WEB_PATH", "test/mustl");

    if (argStr != "")
    {
        MushcoreInterpreter::Instance().Execute(argStr);
    }
    
    try
    {
        TestMustlApp mustlApp;
        mustlApp.Enter();
    }
    catch (exception& e)
    {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown exception" << endl;
        return 1;
    }
    return 0;
}
