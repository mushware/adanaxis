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
 * $Id: GameConfig.cpp,v 1.11 2002/11/24 23:18:05 southa Exp $
 * $Log: GameConfig.cpp,v $
 * Revision 1.11  2002/11/24 23:18:05  southa
 * Added type name accessor to CorePickle
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

#include "mushPlatform.h"

GameConfig *GameConfig::m_instance=NULL;

CoreInstaller GameConfigInstaller(GameConfig::Install);

GameConfig::GameConfig()
{
}

U32
GameConfig::DisplayModeGet(void) const
{
    return CoreData<GameConfigDef>::Instance().DataGet("displaymode")->ValueGet().U32Get();
}

void
GameConfig::DisplayModeSet(U32 inMode)
{
    CoreData<GameConfigDef>::Instance().DataGet("displaymode")->ValueSet(CoreScalar(inMode));
    
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

CoreScalar
GameConfig::ParameterGet(const string& inName) const
{
    return CoreData<GameConfigDef>::Instance().DataGet(inName)->ValueGet();
}

bool
GameConfig::ParameterExists(const string& inName) const
{
    return CoreData<GameConfigDef>::Instance().DataExists(inName);
}

void
GameConfig::ParameterSet(const string& inName, const CoreScalar& inValue)
{
    CoreData<GameConfigDef>::Instance().DataGet(inName)->ValueSet(inValue);
}

void
GameConfig::PostDataHandle(const string& inData)
{
    bool found=false;
    
    CoreData<GameConfigDef>::tMapIterator endValue=CoreData<GameConfigDef>::Instance().End();

    for (CoreData<GameConfigDef>::tMapIterator p=CoreData<GameConfigDef>::Instance().Begin();
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
    CoreEnv::Instance().VariableGetIfExists(filename, "CONFIG_FILENAME");
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
        MediaNetLog::Instance().NetLogSet(ParameterGet("devnetlog").U32Get());
    }
    if (ParameterExists("devweblog"))
    {
        MediaNetLog::Instance().WebLogSet(ParameterGet("devweblog").U32Get());
    }
    if (ParameterExists("devverboselog"))
    {
        MediaNetLog::Instance().VerboseLogSet(ParameterGet("devverboselog").U32Get());
    }
    if (ParameterExists("devcommandlog"))
    {
        CoreInterpreter::Instance().LogCommandsSet(ParameterGet("devcommandlog").U32Get());
    }
    if (ParameterExists("devlogfullip"))
    {
MediaNetUtils::TruncateLogSet(!ParameterGet("devlogfullip").U32Get());
    }
    if (ParameterExists("configperms"))
    {
        string configPerms=ParameterGet("configperms").StringGet();
        if (configPerms == "none")
        {
            MediaNetWebServer::Instance().PermissionSet(MediaNetWebServer::kPermissionNone);
        }
        else if (configPerms == "local")
        {
            MediaNetWebServer::Instance().PermissionSet(MediaNetWebServer::kPermissionLocal);
        }
        else if (configPerms == "all")
        {
            MediaNetWebServer::Instance().PermissionSet(MediaNetWebServer::kPermissionAll);
        }
        else
        {
            MediaNetLog::Instance().WebLog() << "Unknown value for configerms '" << configPerms << "'" << endl;
        }
    }
    if (ParameterExists("configextra"))
    {
        MediaNetWebServer::Instance().ExtraAllowedAddrSet(ParameterGet("configextra").StringGet());
    }
    
}

// ----- XML stuff -----

void
GameConfig::HandleValueEnd(CoreXML& inXML)
{
    string dataName=inXML.GetAttribOrThrow("name").StringGet();
    if (!CoreData<GameConfigDef>::Instance().DataExists(dataName))
    {
        inXML.Throw("Config value '"+dataName+"' does not exist");
    }
    CoreData<GameConfigDef>::Instance().DataGet(dataName)->ValueSet(CoreScalar(inXML.TopData()));
}

void
GameConfig::HandleConfigStart(CoreXML& inXML)
{
    if (inXML.GetAttribOrThrow("version").StringGet() != CoreInfo::PackageIDGet())
    {
        inXML.Throw("Config version ("+inXML.GetAttribOrThrow("version").StringGet()+" differs from application ("+CoreInfo::PackageIDGet()+")");
    }
    m_pickleState=kPickleData;
}

void
GameConfig::HandleConfigEnd(CoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameConfig::NullHandler(CoreXML& inXML)
{
}

void
GameConfig::Pickle(ostream& inOut, const string& inPrefix="") const
{
    time_t now(time(NULL));
    inOut << inPrefix << "<!-- GameConfig file saved at " << ctime(&now) << " -->" << endl;
    inOut << inPrefix << "<!-- This is an autogenerated file." << endl << "To override, create a file named userconfig.xml in the same directory -->" << endl;

    inOut << inPrefix << "<config version=\"" << CoreInfo::PackageIDGet() << "\">" << endl;

    bool savePasswords = false;
    if (ParameterExists("savepasswords"))
    {
        savePasswords = ParameterGet("savepasswords").U32Get();
    }
    
    CoreData<GameConfigDef>::tMapIterator endValue=CoreData<GameConfigDef>::Instance().End();

    for (CoreData<GameConfigDef>::tMapIterator p=CoreData<GameConfigDef>::Instance().Begin();
         p != endValue; ++p)
    {
        if (dynamic_cast<GameConfigDefPassword *>(p->second) == NULL ||
            savePasswords)
        {
            inOut << inPrefix << "  <value name=\"" << MediaNetUtils::MakeXMLSafe(p->first) << "\">";
            if (p->second != NULL)
            {
                inOut << MediaNetUtils::MakeXMLSafe(p->second->ValueGet().StringGet());
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
GameConfig::Unpickle(CoreXML& inXML)
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
GameConfig::XMLStartHandler(CoreXML& inXML)
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
GameConfig::XMLEndHandler(CoreXML& inXML)
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
GameConfig::XMLDataHandler(CoreXML& inXML)
{
}

CoreScalar
GameConfig::GameConfigLoad(CoreCommand& ioCommand, CoreEnv& ioEnv)
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
    CoreXML xml(inStream, filename);
    GameConfig::Instance().Unpickle(xml);
    GameConfig::Instance().Update();
    return CoreScalar(0);
}

CoreScalar
GameConfig::GameConfigValueAdd(CoreCommand& ioCommand, CoreEnv& ioEnv)
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
    CoreData<GameConfigDef>::Instance().DataGive(name, new GameConfigDefU32(defaultValue, lowLimit, highLimit));
    return CoreScalar(0);
}

CoreScalar
GameConfig::GameConfigStringAdd(CoreCommand& ioCommand, CoreEnv& ioEnv)
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
    CoreData<GameConfigDef>::Instance().DataGive(name, new GameConfigDefString(defaultValue, menuStr));
    return CoreScalar(0);
}

CoreScalar
GameConfig::GameConfigPasswordAdd(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 2)
    {
        throw(CommandFail("Usage: configpasswordadd(name, default value)"));
    }
    string name, defaultValue;
    ioCommand.PopParam(name);
    ioCommand.PopParam(defaultValue);
    CoreData<GameConfigDef>::Instance().DataGive(name, new GameConfigDefPassword(defaultValue));
    return CoreScalar(0);
}

CoreScalar
GameConfig::GameConfigBoolAdd(CoreCommand& ioCommand, CoreEnv& ioEnv)
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
    CoreData<GameConfigDef>::Instance().DataGive(name, new GameConfigDefBool(defaultValue));
    return CoreScalar(0);
}

CoreScalar
GameConfig::GameConfigSpecial(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    CoreData<GameConfigDef>::Instance().DataGive("displaymode", new GameConfigDefU32(PlatformVideoUtils::Instance().DefaultModeGet(), 0, PlatformVideoUtils::Instance().NumModesGet()));
    return CoreScalar(0);
}

void
GameConfig::Install(void)
{
    CoreApp::Instance().AddHandler("configload", GameConfigLoad);
    CoreApp::Instance().AddHandler("configvalueadd", GameConfigValueAdd);
    CoreApp::Instance().AddHandler("configstringadd", GameConfigStringAdd);
    CoreApp::Instance().AddHandler("configpasswordadd", GameConfigPasswordAdd);
    CoreApp::Instance().AddHandler("configbooladd", GameConfigBoolAdd);
    CoreApp::Instance().AddHandler("gameconfigspecial", GameConfigSpecial);
}

char *
GameConfig::TypeNameGet(void) const
{
    return "gameconfig";
}

