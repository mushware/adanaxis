/*
 * $Id$
 * $Log$
 */

#include "BuiltinHandler.hp"
#include "CoreInstaller.hp"
#include "CoreScalar.hp"
#include "CoreApp.hp"
#include "CoreScript.hp"

CoreInstaller
BuiltinHandlerInstaller(BuiltinHandler::Install);

CoreScalar
BuiltinHandler::Load(CoreCommand& ioCommand, CoreEnv &ioEnv)
{
    string filename;
    ioCommand.PopParam(filename);
    ioEnv.Enter(CoreScript(filename));
    return CoreScalar(0);
}

void
BuiltinHandler::Install(void)
{
    CoreApp::Instance().AddHandler("load", Load);
}
