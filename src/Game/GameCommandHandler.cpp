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
 * $Id: GameCommandHandler.cpp,v 1.15 2003/01/12 17:32:52 southa Exp $
 * $Log: GameCommandHandler.cpp,v $
 * Revision 1.15  2003/01/12 17:32:52  southa
 * Mushcore work
 *
 * Revision 1.14  2003/01/11 17:07:51  southa
 * Mushcore library separation
 *
 * Revision 1.13  2003/01/11 13:03:12  southa
 * Use Mushcore header
 *
 * Revision 1.12  2003/01/09 14:56:59  southa
 * Created Mushcore
 *
 * Revision 1.11  2002/12/29 20:59:54  southa
 * More build fixes
 *
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
#include "GameSTL.h"

#include "Mushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller GameCommandHandlerInstaller(GameCommandHandler::Install);

MushcoreScalar
GameCommandHandler::Game(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreAppHandler::Instance().Mutate(new GameAppHandler);
    return MushcoreScalar(0);
}

MushcoreScalar
GameCommandHandler::SetSavePath(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams < 2)
    {
        throw(MushcoreCommandFail("Usage: setsavepath(name,root,...)"));
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
                MushcoreGlobalConfig::Instance().Set("FIRST_RUN", 1);

                found=true;
            }
            catch (MushcoreCommandFail& e)
            {
                cerr << e.what() << endl;
            }
        }
    }
    if (found)
    {
        MushcoreGlobalConfig::Instance().Set("GLOBAL_SAVE_PATH", dirPath);
        cout << "Save path is '" << dirPath << "'" << endl;
    }
    else
    {
        cerr << "*** Couldn't find working save path - cannot save data" << endl;
    }
    return MushcoreScalar(0);
}

MushcoreScalar
GameCommandHandler::UpdateCheck(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    PlatformMiscUtils::UpdateCheck();
    return MushcoreScalar(0);
}

MushcoreScalar
GameCommandHandler::ReadDirectoryToMenu(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams < 2 || numParams > 3)
    {
        throw(MushcoreCommandFail("Usage: readdirectorytomenu(var name,dir name,[filter regexp])"));
    }
    string varName;
    string dirName;
    string filterRegExp="^.*$";
    ioCommand.PopParam(varName);
    ioCommand.PopParam(dirName);
    if (numParams > 2) ioCommand.PopParam(filterRegExp);

    vector<string> dirEntries;
    PlatformMiscUtils::ReadDirectory(dirEntries, dirName);

    MushcoreRegExp re(filterRegExp);
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
    MushcoreGlobalConfig::Instance().Set(varName, menuStr);
    return MushcoreScalar(0);
}

void
GameCommandHandler::Install(void)
{
    MushcoreInterpreter::Instance().AddHandler("game", Game);
    MushcoreInterpreter::Instance().AddHandler("setsavepath", SetSavePath);
    MushcoreInterpreter::Instance().AddHandler("updatecheck", UpdateCheck);
    MushcoreInterpreter::Instance().AddHandler("readdirectorytomenu", ReadDirectoryToMenu);
}
