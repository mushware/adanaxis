/*
 * $Id$
 * $Log$
 */

#include "MustlWebCommands.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MushcoreInstaller MustlWebCommandsInstaller(MustlWebCommands::Install);

MushcoreScalar
MustlWebCommands::MustlPostValues(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MustlFail("Usage: mustlpostvalues(values)"));
    }
    string valueStr;
    ioCommand.PopParam(valueStr);

    MushcoreRegExp re("(^|&)type=([^&]+)($|&)");
    vector<string> matchStrs;
    if (!re.Search(valueStr, matchStrs))
    {
        throw(MustlFail("No type= element at start of posted results '"+valueStr+"'"));
    }
    MUSHCOREASSERT(matchStrs.size() == 3);
    string typeStr = matchStrs[1];
    
    if (typeStr.substr(0,5) == "mustl")
    {
        MustlConfig::Instance().PostDataHandle(valueStr);
        // MustlConfig::Instance().Update();
    }

    if (typeStr.substr(0,9) != "mustlonly")
    {
        MushcoreInterpreter::Instance().Execute("$MUSTL_POST_HANDLER('"+valueStr+"')");
    }
    
    return MushcoreScalar(0);
}

MushcoreScalar
MustlWebCommands::MustlInputWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MustlFail("Usage: mustlinputwrite(name)"));
    }
    
    string dataName;
    ioCommand.PopParam(dataName);

    MustlConfigDef *configDef;
    if (MushcoreData<MustlConfigDef>::Instance().GetIfExists(configDef, dataName))
    {
        configDef->WebInputPrint(ioEnv.Out(), dataName);
    }
    else
    {
        throw(MustlFail("Config value '"+dataName+"' does not exist"));
    }    
    
    return MushcoreScalar(0);
}

MushcoreScalar
MustlWebCommands::MustlServerStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    // time_t now(time(NULL));
    // ioEnv.Out() << "Status at " << ctime(&now);
    // ioEnv.Out() << "<br>Server: ";
    if (MustlServer::Instance().IsServing())
    {
        ioEnv.Out() << "Serving on port " << MustlServer::Instance().ServerPortHostOrderGet();
    }
    else
    {
        ioEnv.Out() << "Not active";
    }
    ioEnv.Out() << endl;
    
    return MushcoreScalar(0);
}

MushcoreScalar
MustlWebCommands::MustlLinkStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    
    // Link status
    ioEnv.Out() << "<font class=\"boldtitle\">Link Status</font>" << endl;

    ioEnv.Out() << "<br><br><table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;

    MustlLink::WebStatusHeaderPrint(ioEnv.Out());

    MushcoreData<MustlLink>::tMapIterator endValue=MushcoreData<MustlLink>::Instance().End();

    for (MushcoreData<MustlLink>::tMapIterator p=MushcoreData<MustlLink>::Instance().Begin();
         p != endValue; ++p)
    {
        ioEnv.Out() << "<tr>";
        p->second->WebStatusPrint(ioEnv.Out());
        ioEnv.Out() << "</tr>";
    }
    ioEnv.Out() << "</table>" << endl;

    return MushcoreScalar(0);
}

void
MustlWebCommands::Install(void)
{
    MushcoreInterpreter::Instance().AddHandler("mustlpostvalues", MustlPostValues);
    MushcoreInterpreter::Instance().AddHandler("mustlinputwrite", MustlInputWrite);
    MushcoreInterpreter::Instance().AddHandler("mustlserverstatuswrite", MustlServerStatusWrite);
    MushcoreInterpreter::Instance().AddHandler("mustllinkstatuswrite", MustlLinkStatusWrite);
}
