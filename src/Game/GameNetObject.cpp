/*
 * $Id$
 * $Log$
 */

#include "GameNetObject.h"

GameNetObject::~GameNetObject()
{
}

void
GameNetObject::NullHandler(CoreXML& inXML)
{
}

void
GameNetObject::HandleNetObjectStart(CoreXML& inXML)
{
    inXML.Throw("Not expecting a <netobject> element");
}

void
GameNetObject::HandleNetObjectEnd(CoreXML& inXML)
{
    inXML.Throw("Not expecting expect a </netobject> element");
    inXML.StopHandler();
}

void
GameNetObject::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<!-- Cannot pickle GameNetObject -->" << endl;
}

void
GameNetObject::Unpickle(CoreXML& inXML)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleInit]["netobject"] = &GameNetObject::HandleNetObjectStart;
    m_endTable[kPickleData]["netobject"] = &GameNetObject::HandleNetObjectEnd;

    m_pickleState=kPickleData;
    inXML.ParseStream(*this);
}

void
GameNetObject::XMLStartHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
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

void
GameNetObject::XMLEndHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
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

void
GameNetObject::XMLDataHandler(CoreXML& inXML)
{
}

char *
GameNetObject::TypeNameGet(void) const
{
    return "gamenetobject";
}
