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
 * $Id: GameConfig.cpp,v 1.20 2003/01/09 14:57:00 southa Exp $
 * $Log: GameConfig.cpp,v $
 * Revision 1.20  2003/01/09 14:57:00  southa
 * Created Mushcore
 *
 * Revision 1.19  2003/01/07 17:13:41  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.18  2002/12/29 20:59:54  southa
 * More build fixes
 *
 * Revision 1.17  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.16  2002/12/14 15:04:33  southa
 * Mustl fixes
 *
 * Revision 1.15  2002/12/13 01:07:25  southa
 * Mustl work
 *
 * Revision 1.14  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.13  2002/12/05 13:20:11  southa
 * Client link handling
 *
 * Revision 1.12  2002/11/25 18:02:55  southa
 * Mushware ID work
 *
 * Revision 1.11  2002/11/24 23:18:05  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.10  2002/11/24 12:57:02  southa
 * Added configuration host protection
 *
 * Revision 1.9  2002/11/22 15:00:32  southa
 * Network connection handling
 *
 * Revision 1.8  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.7  2002/11/15 11:47:55  southa
 * Web processing and error handling
 *
 * Revision 1.6  2002/11/14 20:24:43  southa
 * Configurable config elements
 *
 * Revision 1.5  2002/11/14 19:35:30  southa
 * Configuration work
 *
 * Revision 1.4  2002/11/14 17:29:08  southa
 * Config database
 *
 * Revision 1.3  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.2  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
 * Revision 1.1  2002/10/15 14:02:30  southa
 * Mode changes
 *
 */

#include "GameConfig.h"

#include "GameConfigDef.h"

#include "Mustl.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

GameConfig *GameConfig::m_instance=NULL;

MushcoreInstaller GameConfigInstaller(GameConfig::Install);

GameConfig::GameConfig()
{
}

U32
GameConfig::DisplayModeGet(void) const
{
    return MushcoreData<GameConfigDef>::Instance().Get("displaymode")->ValueGet().U32Get();
}

void
GameConfig::DisplayModeSet(U32 inMode)
{
    MushcoreData<GameConfigDef>::Instance().Get("displaymode")->ValueSet(MushcoreScalar(inMode));
    
    try
    {
        SaveToFile();
    }
    catch (exception& e)
    {
        cerr << "Failed to save config: " << e.what() << endl;
    }
}

void
GameConfig::DisplayModeSetDefault(void)
{
    DisplayModeSet(PlatformVideoUtils::Instance().DefaultModeGet());
}

MushcoreScalar
GameConfig::ParameterGet(const string& inName) const
{
    return MushcoreData<GameConfigDef>::Instance().Get(inName)->ValueGet();
}

bool
GameConfig::ParameterExists(const string& inName) const
{
    return MushcoreData<GameConfigDef>::Instance().Exists(inName);
}

void
GameConfig::ParameterSet(const string& inName, const MushcoreScalar& inValue)
{
    MushcoreData<GameConfigDef>::Instance().Get(inName)->ValueSet(inValue);
}

void
GameConfig::PostDataHandle(const string& inData)
{
    bool found=false;
    
    MushcoreData<GameConfigDef>::tMapIterator endValue=MushcoreData<GameConfigDef>::Instance().End();

    for (MushcoreData<GameConfigDef>::tMapIterator p=MushcoreData<GameConfigDef>::Instance().Begin();
         p != endValue; ++p)
    {
        try
        {
            if (p->second->FromPostRetrieve(p->first, inData)) found=true;
        }
        catch (ValueFail& e)
        {
            PlatformMiscUtils::MinorErrorBox(e.what());
        }
    }

    if (found)
    {
        SaveToFile();
    }
}

void
GameConfig::SaveToFile(void) const
{
    string filename;
    MushcoreEnv::Instance().VariableGetIfExists(filename, "CONFIG_FILENAME");
    if (filename != "")
    {
        ofstream outputFile(filename.c_str());
        if (!outputFile) throw(FileFail(filename, "Could not open file"));
        Pickle(outputFile);
    }
}

void
GameConfig::Update(void)
{
    if (ParameterExists("devnetlog"))
    {
        MustlLog::Instance().NetLogSet(ParameterGet("devnetlog").U32Get());
    }
    if (ParameterExists("devweblog"))
    {
        MustlLog::Instance().WebLogSet(ParameterGet("devweblog").U32Get());
    }
    if (ParameterExists("devverboselog"))
    {
        MustlLog::Instance().VerboseLogSet(ParameterGet("devverboselog").U32Get());
    }
    if (ParameterExists("devtrafficlog"))
    {
        MustlLog::Instance().TrafficLogSet(ParameterGet("devtrafficlog").U32Get());
    }
    if (ParameterExists("devcommandlog"))
    {
        MushcoreInterpreter::Instance().LogCommandsSet(ParameterGet("devcommandlog").U32Get());
    }
    if (ParameterExists("devlogfullip"))
    {
MustlUtils::TruncateLogSet(!ParameterGet("devlogfullip").U32Get());
    }
    if (ParameterExists("configperms"))
    {
        string configPerms=ParameterGet("configperms").StringGet();
        if (configPerms == "none")
        {
            MustlWebServer::Instance().PermissionSet(MustlWebServer::kPermissionNone);
        }
        else if (configPerms == "local")
        {
            MustlWebServer::Instance().PermissionSet(MustlWebServer::kPermissionLocal);
        }
        else if (configPerms == "all")
        {
            MustlWebServer::Instance().PermissionSet(MustlWebServer::kPermissionAll);
        }
        else
        {
            MustlLog::Instance().WebLog() << "Unknown value for configerms '" << configPerms << "'" << endl;
        }
    }
    if (ParameterExists("configextra"))
    {
        MustlWebServer::Instance().ExtraAllowedAddrSet(ParameterGet("configextra").StringGet());
    }
    
}

// ----- XML stuff -----

void
GameConfig::HandleValueEnd(MushcoreXML& inXML)
{
    string dataName=inXML.GetAttribOrThrow("name").StringGet();
    if (!MushcoreData<GameConfigDef>::Instance().Exists(dataName))
    {
        inXML.Throw("Config value '"+dataName+"' does not exist");
    }
    MushcoreData<GameConfigDef>::Instance().Get(dataName)->ValueSet(MushcoreScalar(inXML.TopData()));
}

void
GameConfig::HandleConfigStart(MushcoreXML& inXML)
{
    if (inXML.GetAttribOrThrow("version").StringGet() != MushcoreInfo::PackageIDGet())
    {
        inXML.Throw("Config version ("+inXML.GetAttribOrThrow("version").StringGet()+" differs from application ("+MushcoreInfo::PackageIDGet()+")");
    }
    m_pickleState=kPickleData;
}

void
GameConfig::HandleConfigEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameConfig::NullHandler(MushcoreXML& inXML)
{
}

void
GameConfig::Pickle(ostream& inOut, const string& inPrefix) const
{
    time_t now(time(NULL));
    inOut << inPrefix << "<!-- GameConfig file saved at " << ctime(&now) << " -->" << endl;
    inOut << inPrefix << "<!-- This is an autogenerated file." << endl << "To override, create a file named userconfig.xml in the same directory -->" << endl;

    inOut << inPrefix << "<config version=\"" << MushcoreInfo::PackageIDGet() << "\">" << endl;

    bool savePasswords = false;
    if (ParameterExists("savepasswords"))
    {
        savePasswords = ParameterGet("savepasswords").U32Get();
    }
    
    MushcoreData<GameConfigDef>::tMapIterator endValue=MushcoreData<GameConfigDef>::Instance().End();

    for (MushcoreData<GameConfigDef>::tMapIterator p=MushcoreData<GameConfigDef>::Instance().Begin();
         p != endValue; ++p)
    {
        if (dynamic_cast<GameConfigDefPassword *>(p->second) == NULL ||
            savePasswords)
        {
            inOut << inPrefix << "  <value name=\"" << MustlUtils::MakeXMLSafe(p->first) << "\">";
            if (p->second != NULL)
            {
                inOut << MustlUtils::MakeXMLSafe(p->second->ValueGet().StringGet());
            }
            inOut << "</value>" << endl;
        }
    }

    inOut << inPrefix << "</config>" << endl;
}

void
GameConfig::UnpicklePrologue(void)
{
    // Config unpickling appends the pickle config to the current
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleInit]["config"] = &GameConfig::HandleConfigStart;
    m_startTable[kPickleData]["value"] = &GameConfig::NullHandler;
    m_endTable[kPickleData]["value"] = &GameConfig::HandleValueEnd;

    m_endTable[kPickleData]["config"] = &GameConfig::HandleConfigEnd;
    m_pickleState=kPickleInit;
    m_baseThreaded=0;
}

void
GameConfig::Unpickle(MushcoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameConfig::UnpickleEpilogue(void)
{
    m_startTable.resize(0);
    m_endTable.resize(0);
}

void
GameConfig::XMLStartHandler(MushcoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        //        if (m_pickleState == kPickleData)
        //        {
        //            GameConfig::XMLStartHandler(inXML);
        //            m_pickleState=kPickleWithinBase;
        //            ++m_baseThreaded;
        //        }
        //        else
        {
            ostringstream message;
            message << "Unexpected tag <" << inXML.TopTag() << "> in Config.  Potential matches are";
            ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
            while (p != m_startTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameConfig::XMLEndHandler(MushcoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        //        if (m_pickleState == kPickleWithinBase)
        //        {
        //          GameConfig::XMLEndHandler(inXML);
        //            --m_baseThreaded;
        //            if (m_baseThreaded == 0)
        //            {
        //                m_pickleState=kPickleData;
        //            }
        //        }
        //        else
        {
            ostringstream message;
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in Config.  Potential matches are";
            ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
            while (p != m_endTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameConfig::XMLDataHandler(MushcoreXML& inXML)
{
}

MushcoreScalar
GameConfig::GameConfigLoad(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 1)
    {
        throw(CommandFail("Usage: configload(filename)"));
    }
    string filename;
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(LoaderFail(filename, "Could not open file"));
    MushcoreXML xml(inStream, filename);
    GameConfig::Instance().Unpickle(xml);
    GameConfig::Instance().Update();
    return MushcoreScalar(0);
}

MushcoreScalar
GameConfig::GameConfigValueAdd(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 4)
    {
        throw(CommandFail("Usage: configvalueadd(name, default value, low limit, high limit)"));
    }
    string name;
    U32 defaultValue, lowLimit, highLimit;
    ioCommand.PopParam(name);
    ioCommand.PopParam(defaultValue);
    ioCommand.PopParam(lowLimit);
    ioCommand.PopParam(highLimit);
    MushcoreData<GameConfigDef>::Instance().Give(name, new GameConfigDefU32(defaultValue, lowLimit, highLimit));
    return MushcoreScalar(0);
}

MushcoreScalar
GameConfig::GameConfigStringAdd(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams < 2 || numParams > 3)
    {
        throw(CommandFail("Usage: configstringadd(name, default value, menu string)"));
    }
    string name, defaultValue, menuStr;
    ioCommand.PopParam(name);
    ioCommand.PopParam(defaultValue);
    if (numParams >= 3) ioCommand.PopParam(menuStr);
    MushcoreData<GameConfigDef>::Instance().Give(name, new GameConfigDefString(defaultValue, menuStr));
    return MushcoreScalar(0);
}

MushcoreScalar
GameConfig::GameConfigPasswordAdd(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 2)
    {
        throw(CommandFail("Usage: configpasswordadd(name, default value)"));
    }
    string name, defaultValue;
    ioCommand.PopParam(name);
    ioCommand.PopParam(defaultValue);
    MushcoreData<GameConfigDef>::Instance().Give(name, new GameConfigDefPassword(defaultValue));
    return MushcoreScalar(0);
}

MushcoreScalar
GameConfig::GameConfigBoolAdd(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 2)
    {
        throw(CommandFail("Usage: configbooladd(name, default value)"));
    }
    string name;
    U32 defaultValue;
    ioCommand.PopParam(name);
    ioCommand.PopParam(defaultValue);
    MushcoreData<GameConfigDef>::Instance().Give(name, new GameConfigDefBool(defaultValue));
    return MushcoreScalar(0);
}

MushcoreScalar
GameConfig::GameConfigSpecial(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreData<GameConfigDef>::Instance().Give("displaymode", new GameConfigDefU32(PlatformVideoUtils::Instance().DefaultModeGet(), 0, PlatformVideoUtils::Instance().NumModesGet()));
    return MushcoreScalar(0);
}

void
GameConfig::Install(void)
{
    MushcoreInterpreter::Instance().AddHandler("configload", GameConfigLoad);
    MushcoreInterpreter::Instance().AddHandler("configvalueadd", GameConfigValueAdd);
    MushcoreInterpreter::Instance().AddHandler("configstringadd", GameConfigStringAdd);
    MushcoreInterpreter::Instance().AddHandler("configpasswordadd", GameConfigPasswordAdd);
    MushcoreInterpreter::Instance().AddHandler("configbooladd", GameConfigBoolAdd);
    MushcoreInterpreter::Instance().AddHandler("gameconfigspecial", GameConfigSpecial);
}

char *
GameConfig::TypeNameGet(void) const
{
    return "gameconfig";
}

