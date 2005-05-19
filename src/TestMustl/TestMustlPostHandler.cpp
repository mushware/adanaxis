//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlPostHandler.cpp
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
//%Header } 57azgnlqW6b8vHUzfySnzQ
/*
 * $Id: TestMustlPostHandler.cpp,v 1.8 2004/01/02 21:13:18 southa Exp $
 * $Log: TestMustlPostHandler.cpp,v $
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
