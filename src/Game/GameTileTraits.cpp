/*
 * $Id$
 * $Log$
 */

#include "GameTileTraits.h"

void
GameTileTraits::HandleGraphicStart(CoreXML& inXML)
{
    cerr << "Graphics start" << endl;
}

void
GameTileTraits::HandleGraphicEnd(CoreXML& inXML)
{
    cerr << "Graphics end" << endl;
}

void
GameTileTraits::HandleTraitsEnd(CoreXML& inXML)
{
    cerr << "Traits end" << endl;
    inXML.StopHandler();
}

void
GameTileTraits::Pickle(ostream& inOut, const string& inPrefix="") const
{

}

void
GameTileTraits::Unpickle(CoreXML& inXML)
{
    GameTraits::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["graphic"] = &GameTileTraits::HandleGraphicStart;
    m_endTable[kPickleData]["graphic"] = &GameTileTraits::HandleGraphicEnd;
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
            message << "Unexpected tag <" << inXML.TopTag() << ">.  Potential matches are";
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
            message << "Unexpected end of tag </" << inXML.TopTag() << ">.  Potential matches are";
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
