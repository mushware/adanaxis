/*
 * $Id$
 * $Log$
 */

#include "GameMotion.h"

void
GameMotion::HandleRectEnd(CoreXML& inXML)
{
    m_motionSpec.shape.Unpickle(inXML);
}

void
GameMotion::HandlePositionEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for position.  Should be <position>64,96,45</position>";
    char comma;
    if (!(data >> m_motionSpec.pos.x)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    if (!(data >> m_motionSpec.pos.y)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    if (!(data >> m_motionSpec.angle)) inXML.Throw(failMessage);
}

void
GameMotion::HandleMotionEnd(CoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameMotion::NullHandler(CoreXML& inXML)
{
}

void
GameMotion::Pickle(ostream& inOut, const string& inPrefix="") const
{
    m_motionSpec.shape.Pickle(inOut, inPrefix);
    inOut << inPrefix << "<position>" << m_motionSpec.pos.x << ",";
    inOut << m_motionSpec.pos.y << "," << m_motionSpec.angle << "</position>" << endl;
}

void
GameMotion::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["rect"] = &GameMotion::NullHandler;
    m_endTable[kPickleData]["rect"] = &GameMotion::HandleRectEnd;
    m_startTable[kPickleData]["position"] = &GameMotion::NullHandler;
    m_endTable[kPickleData]["position"] = &GameMotion::HandlePositionEnd;
    m_endTable[kPickleData]["motion"] = &GameMotion::HandleMotionEnd;
    m_pickleState=kPickleData;
}

void
GameMotion::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameMotion::UnpickleEpilogue(void)
{
    m_startTable.resize(0);
    m_endTable.resize(0);
}

void
GameMotion::XMLStartHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << "> in Motion.  Potential matches are";
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
GameMotion::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << "> in Motion.  Potential matches are";
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
GameMotion::XMLDataHandler(CoreXML& inXML)
{
}
