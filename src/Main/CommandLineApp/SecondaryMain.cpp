//%Header {
/*****************************************************************************
 *
 * File: src/Main/CommandLineApp/SecondaryMain.cpp
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
//%Header } JrTU9zfjsqBf4SXg1FcdpQ
/*
 * $Id: SecondaryMain.cpp,v 1.6 2006/06/01 15:39:11 southa Exp $
 * $Log: SecondaryMain.cpp,v $
 * Revision 1.6  2006/06/01 15:39:11  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.4  2004/09/26 19:42:05  southa
 * Added MushMesh, fixed typenames and release target
 *
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
