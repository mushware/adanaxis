/*
 * $Id$
 * $Log$
 */

#include "GameTileMap.h"

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
    inXML.Stop();
}

void
GameTileMap::HandleScriptStart(CoreXML& inXML)
{
}

void
GameTileMap::HandleScriptEnd(CoreXML& inXML)
{
    cerr << "Script content was '" << inXML.TopData() << "'" << endl;
    m_loaderScript=CoreScript(inXML.TopData());
    cerr << "Script is:" << endl << m_loaderScript << endl;
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
GameTileMap::Pickle(ostream& inOut) const
{
}

void
GameTileMap::Unpickle(CoreXML& inXML)
{
    m_startTable.resize(kNumStates);
    m_endTable.resize(kNumStates);
    m_startTable[kInit]["tilemap"] = &GameTileMap::HandleTileMapStart;
    m_startTable[kData]["script"] = &GameTileMap::HandleScriptStart;
    m_startTable[kData]["map"] = &GameTileMap::NullHandler;
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
        message << "Unexpected tag <" << inXML.TopTag() << ">.  Potential matches are";
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
        message << "Unexpected end of tag </" << inXML.TopTag() << ">.  Potential matches are";
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
