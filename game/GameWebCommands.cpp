/*****************************************************************************
*
* (Mushware file header version 1.1)
*
* This file contains original work by Andy Southgate.  Contact details can be
* found at http://www.mushware.com.  This file was placed in the Public
* Domain by Andy Southgate and Mushware Limited in 2002.
*
* This software carries NO WARRANTY of any kind.
*
****************************************************************************/

/*
 * $Id: GameWebCommands.cpp,v 1.3 2002/11/12 18:02:13 southa Exp $
 * $Log: GameWebCommands.cpp,v $
 * Revision 1.3  2002/11/12 18:02:13  southa
 * POST handling and handlepostvalues command
 *
 * Revision 1.2  2002/11/12 11:49:21  southa
 * Initial MHTML processing
 *
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "GameWebCommands.h"

#include "GameAppHandler.h"
#include "GameConfig.h"

#include "mushCore.h"
#include "mushPlatform.h"

CoreInstaller GameWebCommandsInstaller(GameWebCommands::Install);

CoreScalar
GameWebCommands::HandlePostValues(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(CommandFail("Usage: handlepostvalues(values)"));
    }
    string values;
    ioCommand.PopParam(values);

    CoreRegExp re("type=([^&]+)&");
    vector<string> matches;
    if (!re.Search(values, matches))
    {
        throw(CommandFail("No type= element in posted results '"+values+"'"));
    }
    COREASSERT(matches.size() == 1);
    if (matches[0] == "config1")
    {
        ProcessConfig1(values);
    }
    else
    {
        throw(CommandFail("Unknown config type value '"+matches[0]+"'"));
    }
    
    return CoreScalar(0);
}

void
GameWebCommands::ProcessConfig1(const string& inValues)
{
    U32 value;
    if (PostU32Retrieve(value, inValues, "displaymode", PlatformVideoUtils::PlatformVideoUtils::Instance().NumModesGet()))
    {
        GameConfig::Instance().DisplayModeSet(value);
    }
}

bool
GameWebCommands::PostU32Retrieve(U32& outValue, const string& inValues, const string& inName, U32 inHighLimit)
{
    bool found=false;
    CoreRegExp re(inName+"=([^&]+)&");
    vector<string> matches;
    if (re.Search(inValues, matches))
    {
        COREASSERT(matches.size() == 1);
        istringstream valueStream(matches[0]);
        U32 value;
        if (valueStream >> value)
        {
            if (value >= inHighLimit)
            {
                ostringstream message;
                message << "Value for " << inName <<" too large (" << value << " > " << inHighLimit << ")";
                throw(CommandFail(message.str()));
            }
            outValue = value;
            found=true;
        }
    }
    return found;
}

CoreScalar
GameWebCommands::DisplayModesWrite(CoreCommand& ioCommand, CoreEnv& ioEnv)
{

    U32 selectedMode=GameConfig::Instance().DisplayModeGet();
    U32 size=PlatformVideoUtils::Instance().NumModesGet();
    
    ioEnv.Out() << "<select name=\"displaymode\">";
    for (U32 i=0; i<size; ++i)
    {
        ioEnv.Out() << "<option ";
        if (i == selectedMode) ioEnv.Out() << "selected ";

        ioEnv.Out() << "value=\"" << i << "\">";
        ioEnv.Out() << PlatformVideoUtils::Instance().ModeDefGet(i).NameGet();
        ioEnv.Out() << "</option>";
    }
    ioEnv.Out() << "</select>";
    return CoreScalar(0);
}

void
GameWebCommands::Install(void)
{
    CoreApp::Instance().AddHandler("handlepostvalues", HandlePostValues);
    CoreApp::Instance().AddHandler("displaymodeswrite", DisplayModesWrite);
}
