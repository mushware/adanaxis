//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreBuiltinHandler.cpp
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
//%Header } yuPFY4zcZOda3kXP+y5bYQ
/*
 * $Id: MushcoreBuiltinHandler.cpp,v 1.18 2006/06/01 15:39:42 southa Exp $
 * $Log: MushcoreBuiltinHandler.cpp,v $
 * Revision 1.18  2006/06/01 15:39:42  southa
 * DrawArray verification and fixes
 *
 * Revision 1.17  2005/05/19 13:02:14  southa
 * Mac release work
 *
 * Revision 1.16  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
 *
 * Revision 1.15  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.14  2004/01/05 20:13:15  southa
 * Target and test updates
 *
 * Revision 1.13  2004/01/05 14:27:41  southa
 * MushPie work and build fixes
 *
 * Revision 1.12  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.11  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:09:06  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/01/20 17:03:21  southa
 * Command line expression evaluator enhancements
 *
 * Revision 1.8  2003/01/20 12:23:22  southa
 * Code and interface tidying
 *
 * Revision 1.7  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.6  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.5  2003/01/15 11:19:39  southa
 * Fixed library linking
 *
 * Revision 1.4  2003/01/12 17:32:58  southa
 * Mushcore work
 *
 * Revision 1.3  2003/01/11 17:44:27  southa
 * Mushcore fixes
 *
 * Revision 1.2  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.7  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.2  2002/07/02 14:27:12  southa
 * First floor map designer build
 *
 * Revision 1.1  2002/07/02 09:10:06  southa
 * Name changed to MushcoreBuiltinHandler
 *
 * Revision 1.5  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.4  2002/06/13 15:15:55  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.3  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.2  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 */

#include "MushcoreBuiltinHandler.h"

#include "MushcoreCommand.h"
#include "MushcoreEnv.h"
#include "MushcoreFail.h"
#include "MushcoreInstaller.h"
#include "MushcoreInterpreter.h"
#include "MushcoreScalar.h"
#include "MushcoreScript.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller
MushcoreBuiltinHandlerInstaller(MushcoreBuiltinHandler::Install);

MushcoreScalar
MushcoreBuiltinHandler::Load(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MushcoreCommandFail("Usage: load(filename)"));
    }
    string filename;
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(MushcoreFileFail(filename, "Could not load file"));
    MushcoreScript script(inStream);
    script.Execute();
    return MushcoreScalar(0);
}

MushcoreScalar
MushcoreBuiltinHandler::ConfigSet(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: configset(name,value)"));
    }
    string nameStr;
    MushcoreScalar valueScalar;
    ioCommand.PopParam(nameStr);
    ioCommand.PopParam(valueScalar);
    MushcoreEnv::Sgl().VariableSet(nameStr, valueScalar);
    return MushcoreScalar(0);
}

MushcoreScalar
MushcoreBuiltinHandler::Test(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    std::vector<std::string> commandVec;
    U32 numParams = ioCommand.NumParams();
    if (numParams == 0)
    {
        MushcoreInterpreter::Sgl().CommandsGet(commandVec, "^test\\w");
    }
    for (U32 i=0; i<numParams; ++i)
    {
        string moduleStr;
        ioCommand.PopParam(moduleStr);
        MushcoreInterpreter::Sgl().CommandsGet(commandVec, "^test"+moduleStr);
    }

    std::vector<std::string> failsVec;
    U32 passCount = 0;
    
    for (U32 i=0; i<commandVec.size(); ++i)
    {
        cout << "Test " << commandVec[i] << "... ";
        try
        {
            MushcoreInterpreter::Sgl().Execute(commandVec[i]);
            ++passCount;
            cout << "passed";
        }
        catch (MushcoreFail& e)
        {
            cout << "FAILED";
            failsVec.push_back(commandVec[i]+": "+e.what());
        }
        cout << endl;
    }
    
    if (failsVec.size() == 0)
    {
        cout << "All " << passCount << " tests passed" << endl;
    }
    else
    {
        cout << "****** " << failsVec.size() << " test failures" << endl;
        cout << "Failure report:" << endl;
        for (U32 i=0; i<failsVec.size(); ++i)
        {
            cout << failsVec[i] << endl;
        }
        throw MushcoreCommandFail("Testing failed");
    }
        
    return MushcoreScalar(0);    
}

void
MushcoreBuiltinHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("load", Load);
    MushcoreInterpreter::Sgl().HandlerAdd("configset", ConfigSet);
    MushcoreInterpreter::Sgl().HandlerAdd("MushcoreTest", Test);
}

void
MushcoreBuiltinHandler::NullFunction(void)
{
}
