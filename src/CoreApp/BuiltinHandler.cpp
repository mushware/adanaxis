/*
 * $Id: BuiltinHandler.cpp,v 1.1 2002/03/07 22:24:32 southa Exp $
 * $Log: BuiltinHandler.cpp,v $
 * Revision 1.1  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 */

#include "BuiltinHandler.h"
#include "CoreInstaller.h"
#include "CoreScalar.h"
#include "CoreApp.h"
#include "CoreScript.h"

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
