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
 * $Id: GameTileMap.cpp,v 1.11 2002/08/07 13:36:51 southa Exp $
 * $Log: GameTileMap.cpp,v $
 * Revision 1.11  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.10  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.9  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.8  2002/06/05 12:28:05  southa
 * Map rendered using traits
 *
 * Revision 1.7  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.6  2002/06/04 17:02:11  southa
 * More work
 *
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
#include "GameSwitches.h"

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

bool
GameTileMap::TraitsExist(U32 inNum) const
{
    if (inNum < m_traits.size() && m_traits[inNum] != NULL)
    {
        return true;
    }
    else
    {
        IFCACHETESTING(cout << "Slow existence test" << endl);
        return (m_map.find(inNum) != m_map.end());
    }
}


GameTraits *
GameTileMap::TraitsPtrGet(U32 inNum) const
{
    if (inNum < kMaxVectorSize)
    {
        if (inNum < m_traits.size())
        {
            if (m_traits[inNum] != NULL)
            {
                // Trait exists and is in the fast lookup table
                return m_traits[inNum];
            }
            else
            {
                // Trait is in the range of the fast lookup table but NULL
                return LookupTrait(inNum);
            }
        }
        else
        {
            // Trait is outside of the fast lookup table
            m_traits.resize(inNum+1);
            return LookupTrait(inNum);
        }            
    }
    else
    {
        // Trait number is larger than the maximum size of the fast lookup table
        if (!m_warned)
        {
            cerr << "Warning: Use of map values above " << kMaxVectorSize << " is deoptimising" << endl;
            m_warned=true;
        }
        return LookupTrait(inNum);
    }
}

GameTraits *
GameTileMap::LookupTrait(U32 inNum) const
{
    IFCACHETESTING(cout << "Slow lookup for " << inNum << endl);
    map<U32, string>::const_iterator p = m_map.find(inNum);

    if (p == m_map.end())
    {
        ostringstream message;
        message << "Request for unknown tilemap value " << inNum << endl;
        throw(ReferenceFail(message.str()));
    }
    else
    {
        GameTraits *traitsPtr=GameData::Instance().TraitsGet(p->second);
        if (inNum < kMaxVectorSize)
        {
            COREASSERT(inNum < m_traits.size());
            m_traits[inNum]=traitsPtr;
        }
        return traitsPtr;
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
    GameData::Instance().TraitsDeleteAndCreate(inXML.GetAttribOrThrow("name").StringGet(), pTraits);
    pTraits->Unpickle(inXML);
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
    inOut << inPrefix << "<script type=\"text/core\">" << endl;
    inOut << m_loaderScript;
    inOut << inPrefix << "</script>" << endl;
    for (map<U32, string>::const_iterator p = m_map.begin(); p != m_map.end(); ++p)
    {
        inOut << inPrefix << "<map>" << p->first << " " << p->second << "</map>" << endl;
    }
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


