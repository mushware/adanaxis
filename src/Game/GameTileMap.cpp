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
 * $Id: GameTileMap.cpp,v 1.20 2003/01/09 14:57:03 southa Exp $
 * $Log: GameTileMap.cpp,v $
 * Revision 1.20  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.19  2003/01/07 17:13:43  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.18  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.17  2002/12/20 13:17:43  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.16  2002/11/24 23:18:25  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.15  2002/11/18 11:31:14  southa
 * Return to game mode
 *
 * Revision 1.14  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.13  2002/10/13 12:26:47  southa
 * Facetised map rendering
 *
 * Revision 1.12  2002/08/27 08:56:26  southa
 * Source conditioning
 *
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
#include "GameSwitches.h"
#include "GameTileTraits.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller GameTileMapInstaller(GameTileMap::Install);

const string&
GameTileMap::NameGet(U32 inNum) const
{
    tTraitMap::const_iterator p = m_map.find(inNum);

    if (p != m_map.end())
    {
        return p->second.name;
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

const GameTileSpec&
GameTileMap::TileSpecGet(U32 inNum)
{
    if (inNum < kMaxVectorSize)
    {
        if (inNum < m_traits.size())
        {
            if (m_traits[inNum] != NULL)
            {
                // Trait exists and is in the fast lookup table
                return *m_traits[inNum];
            }
            else
            {
                // Trait is in the range of the fast lookup table but NULL
                return LookupSpec(inNum);
            }
        }
        else
        {
            // Trait is outside of the fast lookup table
            m_traits.resize(inNum+1, NULL);
            return LookupSpec(inNum);
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
        return LookupSpec(inNum);
    }
}

const GameTileSpec&
GameTileMap::LookupSpec(U32 inNum)
{
    IFCACHETESTING(cout << "Slow lookup for " << inNum << endl);
    tTraitMap::iterator p = m_map.find(inNum);

    if (p == m_map.end())
    {
        ostringstream message;
        message << "Request for unknown tilemap value " << inNum << endl;
        throw(ReferenceFail(message.str()));
    }
    else
    {
        GameTileSpec& spec=p->second.spec;
        if (spec.TileTraitsAreNull())
        {
            // Do the lookup for this trait the first time it is accessed
            spec.TileTraitsSet(dynamic_cast<GameTileTraits *>(GameData::Instance().TraitsGet(p->second.name)));
            COREASSERT(!spec.TileTraitsAreNull());
        }
        if (inNum < kMaxVectorSize)
        {
            COREASSERT(inNum < m_traits.size());
            m_traits[inNum]=&spec;
        }
        return spec;
    }
}    

void
GameTileMap::Load(void)
{
    m_loaderScript.Execute();
}

void
GameTileMap::NullHandler(MushcoreXML& inXML)
{
}

void
GameTileMap::HandleTileMapStart(MushcoreXML& inXML)
{
    m_state=kData;
}

void
GameTileMap::HandleTileMapEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameTileMap::HandleScriptStart(MushcoreXML& inXML)
{
}

void
GameTileMap::HandleScriptEnd(MushcoreXML& inXML)
{
    m_loaderScript=MushcoreScript(inXML.TopData());
}

void
GameTileMap::HandleTraitsStart(MushcoreXML& inXML)
{
    GameTileTraits *pTraits(new GameTileTraits);
    GameData::Instance().TraitsDeleteAndCreate(inXML.GetAttribOrThrow("name").StringGet(), pTraits);
    pTraits->Unpickle(inXML);
}

void
GameTileMap::HandleMapEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for map.  Should be <map rotate=\"4\">200,desk1</map>";
    char comma;
    U32 number;
    string name;
    if (!(data >> number)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    if (!(data >> name)) inXML.Throw(failMessage);

    MushcoreScalar rotateScalar(MushcoreScalar(1));
    inXML.GetAttrib(rotateScalar, "rotate");
    U32 rotate=rotateScalar.U32Get();
    if (rotate < 1) inXML.Throw("rotate value must be >= 1");
    for (U32 i=0; i<rotate; ++i)
    {
        m_map[number+i]=TraitDef(name, GameTileSpec(NULL, (tVal)i/rotate*360));
    }
}

void
GameTileMap::Pickle(ostream& inOut, const string& inPrefix) const
{
    inOut << inPrefix << "<script type=\"text/core\">" << endl;
    inOut << m_loaderScript;
    inOut << inPrefix << "</script>" << endl;
    for (tTraitMap::const_iterator p = m_map.begin(); p != m_map.end(); ++p)
    {
        inOut << inPrefix << "<map>" << p->first << " " << "<!-- Incomplete -->" << "</map>" << endl;
    }
}

void
GameTileMap::Unpickle(MushcoreXML& inXML)
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

    m_state=kInit;
    m_traits.clear();
    m_map.clear();
    inXML.ParseStream(*this);
}

void
GameTileMap::XMLStartHandler(MushcoreXML& inXML)
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
GameTileMap::XMLEndHandler(MushcoreXML& inXML)
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
GameTileMap::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
GameTileMap::TypeNameGet(void) const
{
    return "gametilemap";
}

MushcoreScalar
GameTileMap::LoadTileMap(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
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
    MushcoreXML xml(inStream, filename);
    GameData::Instance().TileMapGetOrCreate(name)->Unpickle(xml);
    return MushcoreScalar(0);
}

void
GameTileMap::Install(void)
{
    MushcoreInterpreter::Instance().AddHandler("loadtilemap", LoadTileMap);
}


