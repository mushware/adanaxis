//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlPostHandler.cpp
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
//%Header } zrvP6HfW5moIJ/pyhInrPA
/*
 * $Id: TestMustlPostHandler.cpp,v 1.10 2006/06/01 15:40:06 southa Exp $
 * $Log: TestMustlPostHandler.cpp,v $
 * Revision 1.10  2006/06/01 15:40:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:25  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:18  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:39  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/20 12:23:24  southa
 * Code and interface tidying
 *
 * Revision 1.4  2003/01/20 10:45:32  southa
 * Singleton tidying
 *
 * Revision 1.3  2003/01/17 13:30:42  southa
 * Source conditioning and build fixes
 *
 * Revision 1.2  2003/01/17 00:41:06  southa
 * Configuration updates from POST data
 *
 * Revision 1.1  2003/01/14 20:46:12  southa
 * Post data handling
 *
 */

#include "TestMustlPostHandler.h"

#include "TestMustlApp.h"

using namespace Mustl;
using namespace std;

MushcoreInstaller TestMustlPostHandlerInstaller(TestMustlPostHandler::Install);

MushcoreScalar
TestMustlPostHandler::PostHandler(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: posthandler(type, values)"));
    }
    
    string typeStr, valueStr;
    ioCommand.PopParam(typeStr);
    ioCommand.PopParam(valueStr);

    if (typeStr == "quit")
    {
        TestMustlApp::Sgl().DoQuit();
    }
    else if (typeStr == "startserver")
    {
        MustlServer::Sgl().Connect();
    }
    else if (typeStr == "stopserver")
    {
        MustlServer::Sgl().Disconnect();
    }
    else
    {
        throw(MushcoreCommandFail("Unrecognised type value in post values '"+typeStr+"'"));
    }
    return MushcoreScalar(0);
}

void
TestMustlPostHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("posthandler", PostHandler);
}
