/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: BuiltinHandler.cpp,v 1.4 2002/06/13 15:15:55 southa Exp $
 * $Log: BuiltinHandler.cpp,v $
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
    if (ioCommand.NumParams() != 1)
    {
        throw(CommandFail("Usage: load <filename>"));
    }
    string filename;
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(LoaderFail(filename, "Could not load file"));
    CoreScript script(inStream);
    script.Execute();
    return CoreScalar(0);
}

void
BuiltinHandler::Install(void)
{
    CoreApp::Instance().AddHandler("load", Load);
}
