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
 * $Id: TestMustlPostHandler.cpp,v 1.3 2003/01/17 13:30:42 southa Exp $
 * $Log: TestMustlPostHandler.cpp,v $
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
    MushcoreInterpreter::Sgl().AddHandler("posthandler", PostHandler);
}
