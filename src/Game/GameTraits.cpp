/*
 * $Id: GameTraits.cpp,v 1.1 2002/06/04 14:12:25 southa Exp $
 * $Log: GameTraits.cpp,v $
 * Revision 1.1  2002/06/04 14:12:25  southa
 * Traits loader first stage
 *
 */

#include "GameTraits.h"
#include "GameData.h"

void
GameTraits::Verify(void)
{
    if (!m_traitsValid) RebuildTraits();
    if (!m_traitsValid)
    {
        string message("Trait with bases");
        for (U32 i=0; i<m_baseNames.size(); ++i)
        {
            message+=" ";
            message+=m_baseNames[i];
        }
        message+=" failed to build because";
        message+=m_failMessage;
        message+=" were missing";
        throw(VerifyFail(message));
    }
}

U32
GameTraits::NumberOfTraitsGet(void) const
{
    if (!m_traitsValid) RebuildTraits();
    return m_baseTraits.size();
}

const GameTraits& GameTraits::GetTraits(U32 inIndex) const
{
    if (!m_traitsValid)
    {
        throw(LogicFail("Use of invalid traits"));
    }
    COREASSERT(inIndex < m_baseTraits.size());
    return *m_baseTraits[inIndex];
}

void
GameTraits::RebuildTraits(void) const
{
    COREASSERT(!m_traitsValid);
    m_baseTraits.resize(0);
    m_failMessage.erase();
    bool success=true;    
    for (U32 i=0;i<m_baseNames.size(); ++i)
    {
        try
        {
            m_baseTraits.push_back(GameData::Instance().TraitsGet(m_baseNames[i]));
        }
        catch (GameDataNotPresent& e)
        {
            success=false;
            m_failMessage+=" ";
            m_failMessage+=e.StringGet();
        }
    }
    m_traitsValid=success;
}

void
GameTraits::HandleBaseStart(CoreXML& inXML)
{
    m_pickleState=kPickleData;
}

void
GameTraits::HandleBaseEnd(CoreXML& inXML)
{
    // inXML.StopHandler();
}

void
GameTraits::Pickle(ostream& inOut, const string& inPrefix="") const
{
    if (m_baseNames.size() != 0)
    {
        inOut << inPrefix << "<base>";
        for (U32 i=0; i<m_baseNames.size(); i++)
        {
            inOut << m_baseNames[i];
            if (i+1 < m_baseNames.size()) inOut << ",";
        }
        inOut << "</base>" << endl;
    }
}

void
GameTraits::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleInit]["base"] = &GameTraits::HandleBaseStart;
    m_endTable[kPickleData]["base"] = &GameTraits::HandleBaseEnd;
    m_pickleState=kPickleInit;
    m_baseNames.clear();
}

void
GameTraits::UnpickleEpilogue(void)
{
    m_startTable.clear();
    m_endTable.clear();
}

void
GameTraits::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
    UnpickleEpilogue();
}

void
GameTraits::XMLStartHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << "> in Traits.  Potential matches are";
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
GameTraits::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << "> in Traits.  Potential matches are";
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
GameTraits::XMLDataHandler(CoreXML& inXML)
{
}

const string
GameTraits::TraitsNameGet(void) const
{
    return "base";
}

