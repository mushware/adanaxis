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
 * $Id: CoreBuiltinHandler.cpp,v 1.6 2002/10/22 20:41:57 southa Exp $
 * $Log: CoreBuiltinHandler.cpp,v $
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
 * Name changed to CoreBuiltinHandler
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

#include "CoreBuiltinHandler.h"
#include "CoreApp.h"
#include "CoreException.h"
#include "CoreInstaller.h"
#include "CoreScalar.h"
#include "CoreScript.h"

using namespace Mushware;

CoreInstaller
CoreBuiltinHandlerInstaller(CoreBuiltinHandler::Install);

CoreScalar
CoreBuiltinHandler::Load(CoreCommand& ioCommand, CoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(CommandFail("Usage: load(filename)"));
    }
    string filename;
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(LoaderFail(filename, "Could not load file"));
    CoreScript script(inStream);
    script.Execute();
    return CoreScalar(0);
}

CoreScalar
CoreBuiltinHandler::ConfigSet(CoreCommand& ioCommand, CoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: configset(name,value)"));
    }
    string name;
    string value;
    ioCommand.PopParam(name);
    ioCommand.PopParam(value);
    CoreEnv::Instance().VariableSet(name, value);
    return CoreScalar(0);
}

void
CoreBuiltinHandler::Install(void)
{
    CoreApp::Instance().AddHandler("load", Load);
    CoreApp::Instance().AddHandler("configset", ConfigSet);
}
