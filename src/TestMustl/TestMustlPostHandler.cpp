/*
 * $Id$
 * $Log$
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
        TestMustlApp::Instance().DoQuit();
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
    MushcoreInterpreter::Instance().AddHandler("posthandler", PostHandler);
}
