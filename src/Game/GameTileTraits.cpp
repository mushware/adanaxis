/*
 * $Id: GameTileTraits.cpp,v 1.2 2002/06/04 17:02:11 southa Exp $
 * $Log: GameTileTraits.cpp,v $
 * Revision 1.2  2002/06/04 17:02:11  southa
 * More work
 *
 * Revision 1.1  2002/06/04 14:12:25  southa
 * Traits loader first stage
 *
 */

#include "GameTileTraits.h"
#include "GameGraphicSprite.h"

GameTileTraits::~GameTileTraits()
{
    for (U32 i=0; i<m_graphics.size(); ++i)
    {
        delete m_graphics[i];
    }
}

void
GameTileTraits::HandleGraphicStart(CoreXML& inXML)
{
    GameGraphicSprite *pSprite(new GameGraphicSprite);
    m_graphics.push_back(pSprite);
    pSprite->Unpickle(inXML);
}

void
GameTileTraits::HandleTraitsEnd(CoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameTileTraits::Pickle(ostream& inOut, const string& inPrefix="") const
{
    GameTraits::Pickle(inOut, inPrefix);
    for (U32 i=0; i<m_graphics.size(); ++i)
    {
        inOut << inPrefix << "<graphic type=\"" << m_graphics[i]->TypeNameGet() << "\">" << endl;
        m_graphics[i]->Pickle(inOut, inPrefix+"  ");
        inOut << inPrefix << "</graphic>" << endl;
    }
}

void
GameTileTraits::Unpickle(CoreXML& inXML)
{
    GameTraits::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["graphic"] = &GameTileTraits::HandleGraphicStart;
    m_endTable[kPickleData]["traits"] = &GameTileTraits::HandleTraitsEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    
    inXML.ParseStream(*this);
}

void
GameTileTraits::XMLStartHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleData)
        {
            GameTraits::XMLStartHandler(inXML);
            m_pickleState=kPickleWithinBase;
            ++m_baseThreaded;
        }
        else
        {
            ostringstream message;
            message << "Unexpected tag <" << inXML.TopTag() << "> in TileTraits.  Potential matches are";
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
GameTileTraits::XMLEndHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleWithinBase)
        {
            GameTraits::XMLEndHandler(inXML);
            --m_baseThreaded;
            if (m_baseThreaded == 0)
            {
                m_pickleState=kPickleData;
            }
        }
        else
        {
            ostringstream message;
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in TileTraits.  Potential matches are";
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
GameTileTraits::XMLDataHandler(CoreXML& inXML)
{
}
