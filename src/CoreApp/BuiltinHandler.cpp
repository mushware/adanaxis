/*
 * $Id: BuiltinHandler.cpp,v 1.2 2002/05/10 16:39:38 southa Exp $
 * $Log: BuiltinHandler.cpp,v $
 * Revision 1.2  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 */

#include "BuiltinHandler.h"
#include "CoreInstaller.h"
#include "CoreScalar.h"
#include "CoreApp.h"
#include "CoreScript.h"
#include "CoreException.h"

CoreInstaller
BuiltinHandlerInstaller(BuiltinHandler::Install);

CoreScalar
BuiltinHandler::Load(CoreCommand& ioCommand, CoreEnv &ioEnv)
{
    string filename;
    ioCommand.PopParam(filename);
    throw(CommandFail("Load not implemented"));
    // ioEnv.Enter(CoreScript(filename));
    return CoreScalar(0);
}

void
BuiltinHandler::Install(void)
{
    CoreApp::Instance().AddHandler("load", Load);
}
