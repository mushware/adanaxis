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
 * $Id: MustlWebCommands.cpp,v 1.7 2003/04/06 12:35:23 southa Exp $
 * $Log: MustlWebCommands.cpp,v $
 * Revision 1.7  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.6  2003/01/20 12:23:24  southa
 * Code and interface tidying
 *
 * Revision 1.5  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.4  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.3  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.2  2003/01/14 20:46:12  southa
 * Post data handling
 *
 * Revision 1.1  2003/01/14 17:38:21  southa
 * Mustl web configuration
 *
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

    MushcoreRegExp regExp("(^|&)type=([^&]+)($|&)");
    MushcoreRegExp::tMatches matchStrs;
    if (!regExp.Search(matchStrs, valueStr))
    {
        throw(MustlFail("No type= element at start of posted results '"+valueStr+"'"));
    }
    MUSHCOREASSERT(matchStrs.size() == 3);
    string typeStr = matchStrs[1];
    
    if (typeStr.substr(0,5) == "mustl")
    {
        MustlConfig::Sgl().PostDataHandle(valueStr);
        // MustlConfig::Sgl().Update();
    }

    if (typeStr.substr(0,9) != "mustlonly")
    {
        MushcoreInterpreter::Sgl().Execute("$MUSTL_POST_HANDLER('"+typeStr+"','"+valueStr+"')");
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
    if (MushcoreData<MustlConfigDef>::Sgl().GetIfExists(configDef, dataName))
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
    if (MustlServer::Sgl().IsServing())
    {
        ioEnv.Out() << "Serving on port " << MustlServer::Sgl().ServerPortHostOrderGet();
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

    MushcoreData<MustlLink>::tMapIterator endValue=MushcoreData<MustlLink>::Sgl().End();

    for (MushcoreData<MustlLink>::tMapIterator p=MushcoreData<MustlLink>::Sgl().Begin();
         p != endValue; ++p)
    {
        ioEnv.Out() << "<tr>";
        p->second->WebStatusPrint(ioEnv.Out());
        ioEnv.Out() << "</tr>";
    }
    ioEnv.Out() << "</table>" << endl;

    return MushcoreScalar(0);
}

MushcoreScalar
MustlWebCommands::MustlPrintPackageID(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    ioEnv.Out() << MushcoreInfo::Sgl().PackageIDGet();
    return MushcoreScalar(0);
}

MushcoreScalar
MustlWebCommands::MustlPrintMetaPackageID(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    ioEnv.Out() << MustlUtils::InsertMeta(MushcoreInfo::Sgl().PackageIDGet());
    return MushcoreScalar(0);
}

MushcoreScalar
MustlWebCommands::MustlPrintApplicationName(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    ioEnv.Out() << MushcoreInfo::Sgl().ApplicationNameGet();
    return MushcoreScalar(0);
}

void
MustlWebCommands::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("mustlpostvalues", MustlPostValues);
    MushcoreInterpreter::Sgl().HandlerAdd("mustlinputwrite", MustlInputWrite);
    MushcoreInterpreter::Sgl().HandlerAdd("mustlserverstatuswrite", MustlServerStatusWrite);
    MushcoreInterpreter::Sgl().HandlerAdd("mustllinkstatuswrite", MustlLinkStatusWrite);
    MushcoreInterpreter::Sgl().HandlerAdd("mustlprintpackageid", MustlPrintPackageID);
    MushcoreInterpreter::Sgl().HandlerAdd("mustlprintmetapackageid", MustlPrintMetaPackageID);
    MushcoreInterpreter::Sgl().HandlerAdd("mustlprintapplicationname", MustlPrintApplicationName);
}

void
MustlWebCommands::NullFunction(void)
{
}

