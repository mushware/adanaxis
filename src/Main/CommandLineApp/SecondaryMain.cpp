//%Header {
/*****************************************************************************
 *
 * File: src/Main/CommandLineApp/SecondaryMain.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } a4QmG9GUot9BdRziHdwp7A
/*
 * $Id: SecondaryMain.cpp,v 1.3 2004/01/06 20:46:51 southa Exp $
 * $Log: SecondaryMain.cpp,v $
 * Revision 1.3  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/05 20:13:15  southa
 * Target and test updates
 *
 * Revision 1.1  2004/01/05 14:27:40  southa
 * MushPie work and build fixes
 *
 */

#include "Main/SecondaryMain.h"

#include "mushMushcore.h"

#include <iostream> 

using namespace Mushware;
using namespace std;

int main(int argc, char *argv[])
{
    string str;
    for (int i=1; i<argc; i++)
    {
        str.append(argv[i]);
        if (i+1 != argc) str.append(" ");
    }
    try
    {
        try
        {
            MushcoreInterpreter::Sgl().Execute(str);
        }
        catch (MushcoreNonFatalFail& e)
        {
            cerr << "Exception: " << e.what() << endl;
        }
        
        MushcoreAppHandler::Sgl().Initialise();
        MushcoreAppHandler::Sgl().MainLoop();
    }
    catch (exception& e)
    {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }
    catch (string& ex_str)
    {
        cerr << "Exception: " << ex_str << endl;
        return 1;
    }
    catch (const char *c_str)
    {
        cerr << "Exception: " << c_str << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown exception" << endl;
        return 1;
    }
    return 0;
}
