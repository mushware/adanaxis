/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: TestMustlPostHandler.cpp,v 1.5 2003/01/20 12:23:24 southa Exp $
 * $Log: TestMustlPostHandler.cpp,v $
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
