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
 * $Id: GameCommandHandler.cpp,v 1.10 2002/12/20 13:17:37 southa Exp $
 * $Log: GameCommandHandler.cpp,v $
 * Revision 1.10  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.8  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/17 12:35:29  southa
 * Save path and update check
 *
 * Revision 1.6  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "GameCommandHandler.h"

#include "GameAppHandler.h"
#include "mushCore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

CoreInstaller GameCommandHandlerInstaller(GameCommandHandler::Install);

CoreScalar
GameCommandHandler::Game(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    CoreAppHandler::Instance().Mutate(new GameAppHandler);
    return CoreScalar(0);
}

CoreScalar
GameCommandHandler::SetSavePath(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams < 2)
    {
        throw(CommandFail("Usage: setsavepath(name,root,...)"));
    }
    string dirName;
    string rootName;
    ioCommand.PopParam(dirName);
    bool found=false;
    string dirPath="/nopath";
    for (U32 i=0; !found && i+1<numParams; ++i)
    {
        ioCommand.PopParam(rootName);
        dirPath=rootName+"/"+dirName;
        if (PlatformMiscUtils::DirectoryExists(dirPath))
        {
            found=true;
        }
        else
        {
            try
            {
                PlatformMiscUtils::MakeDirectory(dirPath);
                CoreGlobalConfig::Instance().Set("FIRST_RUN", 1);

                found=true;
            }
            catch (CommandFail& e)
            {
                cerr << e.what() << endl;
            }
        }
    }
    if (found)
    {
        CoreGlobalConfig::Instance().Set("GLOBAL_SAVE_PATH", dirPath);
        cout << "Save path is '" << dirPath << "'" << endl;
    }
    else
    {
        cerr << "*** Couldn't find working save path - cannot save data" << endl;
    }
    return CoreScalar(0);
}

CoreScalar
GameCommandHandler::UpdateCheck(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    PlatformMiscUtils::UpdateCheck();
    return CoreScalar(0);
}

CoreScalar
GameCommandHandler::ReadDirectoryToMenu(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams < 2 || numParams > 3)
    {
        throw(CommandFail("Usage: readdirectorytomenu(var name,dir name,[filter regexp])"));
    }
    string varName;
    string dirName;
    string filterRegExp="^.*$";
    ioCommand.PopParam(varName);
    ioCommand.PopParam(dirName);
    if (numParams > 2) ioCommand.PopParam(filterRegExp);

    vector<string> dirEntries;
    PlatformMiscUtils::ReadDirectory(dirEntries, dirName);

    CoreRegExp re(filterRegExp);
    string menuStr;
    U32 size=dirEntries.size();
    for (U32 i=0; i<size; ++i)
    {
        if (re.Search(dirEntries[i]))
        {
            if (menuStr.size() > 0)
            {
                menuStr+="&";
            }
            menuStr += dirEntries[i]+"="+dirEntries[i];
        }
    }
    CoreGlobalConfig::Instance().Set(varName, menuStr);
    return CoreScalar(0);
}

void
GameCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler("game", Game);
    CoreApp::Instance().AddHandler("setsavepath", SetSavePath);
    CoreApp::Instance().AddHandler("updatecheck", UpdateCheck);
    CoreApp::Instance().AddHandler("readdirectorytomenu", ReadDirectoryToMenu);
}
