//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTileMap.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } D/TTKukzTYTQ9KA0lxxwDw
/*
 * $Id: InfernalTileMap.cpp,v 1.3 2003/10/04 15:32:11 southa Exp $
 * $Log: InfernalTileMap.cpp,v $
 * Revision 1.3  2003/10/04 15:32:11  southa
 * Module split
 *
 * Revision 1.2  2003/10/04 12:44:36  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:07  southa
 * File renaming
 *
 * Revision 1.27  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.26  2003/08/21 23:08:56  southa
 * Fixed file headers
 *
 * Revision 1.25  2003/01/20 12:23:22  southa
 * Code and interface tidying
 *
 * Revision 1.24  2003/01/20 10:45:27  southa
 * Singleton tidying
 *
 * Revision 1.23  2003/01/13 14:32:00  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.22  2003/01/12 17:32:56  southa
 * Mushcore work
 *
 * Revision 1.21  2003/01/11 17:07:52  southa
 * Mushcore library separation
 *
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
 * Pickleable InfernalContract
 *
 * Revision 1.3  2002/05/30 14:41:12  southa
 * InfernalData and loadtilemap command
 *
 * Revision 1.2  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.1  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 */

#include "InfernalTileMap.h"

#include "InfernalData.h"
#include "InfernalSTL.h"
#include "InfernalSwitches.h"
#include "InfernalTileTraits.h"

#include "mushGame.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller InfernalTileMapInstaller(InfernalTileMap::Install);

const string&
InfernalTileMap::NameGet(U32 inNum) const
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
InfernalTileMap::TraitsExist(U32 inNum) const
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

const InfernalTileSpec&
InfernalTileMap::TileSpecGet(U32 inNum)
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

const InfernalTileSpec&
InfernalTileMap::LookupSpec(U32 inNum)
{
    IFCACHETESTING(cout << "Slow lookup for " << inNum << endl);
    tTraitMap::iterator p = m_map.find(inNum);

    if (p == m_map.end())
    {
        ostringstream message;
        message << "Request for unknown tilemap value " << inNum << endl;
        throw(MushcoreReferenceFail(message.str()));
    }
    else
    {
        InfernalTileSpec& spec=p->second.spec;
        if (spec.TileTraitsAreNull())
        {
            // Do the lookup for this trait the first time it is accessed
            spec.TileTraitsSet(dynamic_cast<InfernalTileTraits *>(InfernalData::Sgl().TraitsGet(p->second.name)));
            MUSHCOREASSERT(!spec.TileTraitsAreNull());
        }
        if (inNum < kMaxVectorSize)
        {
            MUSHCOREASSERT(inNum < m_traits.size());
            m_traits[inNum]=&spec;
        }
        return spec;
    }
}    

void
InfernalTileMap::Load(void)
{
    m_loaderScript.Execute();
}

void
InfernalTileMap::NullHandler(MushcoreXML& inXML)
{
}

void
InfernalTileMap::HandleTileMapStart(MushcoreXML& inXML)
{
    m_state=kData;
}

void
InfernalTileMap::HandleTileMapEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
}

void
InfernalTileMap::HandleScriptStart(MushcoreXML& inXML)
{
}

void
InfernalTileMap::HandleScriptEnd(MushcoreXML& inXML)
{
    m_loaderScript=MushcoreScript(inXML.TopData());
}

void
InfernalTileMap::HandleTraitsStart(MushcoreXML& inXML)
{
    InfernalTileTraits *pTraits(new InfernalTileTraits);
    InfernalData::Sgl().TraitsDeleteAndCreate(inXML.GetAttribOrThrow("name").StringGet(), pTraits);
    pTraits->Unpickle(inXML);
}

void
InfernalTileMap::HandleMapEnd(MushcoreXML& inXML)
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
        m_map[number+i]=TraitDef(name, InfernalTileSpec(NULL, (tVal)i/rotate*360));
    }
}

void
InfernalTileMap::Pickle(ostream& inOut, const string& inPrefix) const
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
InfernalTileMap::Unpickle(MushcoreXML& inXML)
{
    m_startTable.resize(kNumStates);
    m_endTable.resize(kNumStates);
    m_startTable[kInit]["tilemap"] = &InfernalTileMap::HandleTileMapStart;
    m_startTable[kData]["script"] = &InfernalTileMap::HandleScriptStart;
    m_startTable[kData]["map"] = &InfernalTileMap::NullHandler;
    m_startTable[kData]["traits"] = &InfernalTileMap::HandleTraitsStart;
    m_endTable[kData]["tilemap"] = &InfernalTileMap::HandleTileMapEnd;
    m_endTable[kData]["script"] = &InfernalTileMap::HandleScriptEnd;
    m_endTable[kData]["map"] = &InfernalTileMap::HandleMapEnd;

    m_state=kInit;
    m_traits.clear();
    m_map.clear();
    inXML.ParseStream(*this);
}

void
InfernalTileMap::XMLStartHandler(MushcoreXML& inXML)
{
    ElementFunctionMap::iterator p2 = m_startTable[m_state].find(inXML.TopTag());

    if (p2 != m_startTable[m_state].end())
    {
        (this->*p2->second)(inXML);
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
InfernalTileMap::XMLEndHandler(MushcoreXML& inXML)
{
    ElementFunctionMap::iterator p2 = m_endTable[m_state].find(inXML.TopTag());

    if (p2 != m_endTable[m_state].end())
    {
        (this->*p2->second)(inXML);
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
InfernalTileMap::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
InfernalTileMap::TypeNameGet(void) const
{
    return "gametilemap";
}

MushcoreScalar
InfernalTileMap::LoadTileMap(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: loadtilemap <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(MushcoreFileFail(filename, "Could not open file"));
    MushcoreXML xml(inStream, filename);
    InfernalData::Sgl().TileMapGetOrCreate(name)->Unpickle(xml);
    return MushcoreScalar(0);
}

void
InfernalTileMap::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("loadtilemap", LoadTileMap);
}


