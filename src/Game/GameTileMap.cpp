/*
 * $Id: GameTileMap.cpp,v 1.4 2002/05/30 16:21:53 southa Exp $
 * $Log: GameTileMap.cpp,v $
 * Revision 1.4  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
 * Revision 1.3  2002/05/30 14:41:12  southa
 * GameData and loadtilemap command
 *
 * Revision 1.2  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.1  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 */

#include "GameTileMap.h"
#include "GameData.h"
#include "GameTileTraits.h"

CoreInstaller GameTileMapInstaller(GameTileMap::Install);

const string&
GameTileMap::NameGet(U32 inNum) const
{
    map<U32, string>::const_iterator p = m_map.find(inNum);

    if (p != m_map.end())
    {
        return p->second;
    }
    else
    {
        static const string unknown("_unknown");
        return unknown;
    }
}

void
GameTileMap::Load(void)
{
    m_loaderScript.Execute();
}

void
GameTileMap::NullHandler(CoreXML& inXML)
{
}

void
GameTileMap::HandleTileMapStart(CoreXML& inXML)
{
    m_state=kData;
}

void
GameTileMap::HandleTileMapEnd(CoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameTileMap::HandleScriptStart(CoreXML& inXML)
{
}

void
GameTileMap::HandleScriptEnd(CoreXML& inXML)
{
    m_loaderScript=CoreScript(inXML.TopData());
}

void
GameTileMap::HandleTraitsStart(CoreXML& inXML)
{
    GameTileTraits *pTraits(new GameTileTraits);
    GameData::Instance().TraitsDeleteAndCreate("trait", pTraits);
    pTraits->Unpickle(inXML);
}

void
GameTileMap::HandleTraitsEnd(CoreXML& inXML)
{
    // Never gets called
    cerr << "Traits end handler" << endl;
}

void
GameTileMap::HandleMapEnd(CoreXML& inXML)
{
    istringstream inStream(inXML.TopData());
    U32 number;
    string name;
    if (!(inStream >> number >> name)) throw (XMLFail("Expecting <map>number name</map>"));
    m_map[number]=name;
}

void
GameTileMap::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<tilemap version=\"0.0\">" << endl;
    inOut << inPrefix << "<script type=\"text/core\">" << endl;
    inOut << m_loaderScript;
    inOut << inPrefix << "</script>" << endl;
    for (map<U32, string>::const_iterator p = m_map.begin(); p != m_map.end(); ++p)
    {
        inOut << inPrefix << "<map>" << p->first << " " << p->second << "</map>" << endl;
    }
    inOut << inPrefix << "</tilemap>";
}

void
GameTileMap::Unpickle(CoreXML& inXML)
{
    m_startTable.resize(kNumStates);
    m_endTable.resize(kNumStates);
    m_startTable[kInit]["tilemap"] = &GameTileMap::HandleTileMapStart;
    m_startTable[kData]["script"] = &GameTileMap::HandleScriptStart;
    m_startTable[kData]["map"] = &GameTileMap::NullHandler;
    m_startTable[kData]["traits"] = &GameTileMap::HandleTraitsStart;
    m_endTable[kData]["tilemap"] = &GameTileMap::HandleTileMapEnd;
    m_endTable[kData]["script"] = &GameTileMap::HandleScriptEnd;
    m_endTable[kData]["map"] = &GameTileMap::HandleMapEnd;
    m_endTable[kData]["traits"] = &GameTileMap::HandleTraitsEnd;

    m_map.clear();
    inXML.ParseStream(*this);
}

void
GameTileMap::XMLStartHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_state].find(inXML.TopTag());

    if (p != m_startTable[m_state].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << "> in TileMap.  Potential matches are";
        ElementFunctionMap::iterator p = m_startTable[m_state].begin();
        while (p != m_startTable[m_state].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameTileMap::XMLEndHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_endTable[m_state].find(inXML.TopTag());

    if (p != m_endTable[m_state].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << "> in TileMap.  Potential matches are";
        ElementFunctionMap::iterator p = m_endTable[m_state].begin();
        while (p != m_endTable[m_state].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameTileMap::XMLDataHandler(CoreXML& inXML)
{
}

CoreScalar
GameTileMap::LoadTileMap(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: loadtilemap <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(LoaderFail(filename, "Could not open file"));
    CoreXML xml(inStream, filename);
    GameData::Instance().TileMapGetOrCreate(name)->Unpickle(xml);
    return CoreScalar(0);
}

void
GameTileMap::Install(void)
{
    CoreApp::Instance().AddHandler("loadtilemap", LoadTileMap);
}


