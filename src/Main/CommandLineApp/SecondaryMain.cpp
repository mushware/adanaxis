//%Header {
/*****************************************************************************
 *
 * File: src/Main/CommandLineApp/SecondaryMain.cpp
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
//%Header } 1UkBzza2JXMWvp5cmF5bhg
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
