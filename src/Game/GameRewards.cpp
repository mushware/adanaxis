/*
 * $Id$
 * $Log$
 */

#include "GameRewards.h"
#include "GameDataUtils.h"

bool
GameRewards::JudgementPass(tVal inRatio)
{
    U32 size=m_judgements.size();
    bool found=false;
    
    // Assume rewards in in order, lowest first    
    for (U32 i=0; i<size; ++i)
    {
        if (inRatio < m_judgements[i].ratio)
        {
            GameDataUtils::NamedDialoguesAdd(m_judgements[i].dialogueName);
            found=true;
            break;
        }
    }
    return found;
}
        
void
GameRewards::HandleJudgementEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for judgement.  Should be <judgement>0.8,^impressive</judgement>";
    char comma;
    TimeJudgement judgement;
    if (!(data >> judgement.ratio)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    if (!(data >> judgement.dialogueName)) inXML.Throw(failMessage);
    m_judgements.push_back(judgement);
}

void
GameRewards::HandleRewardsEnd(CoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameRewards::NullHandler(CoreXML& inXML)
{
}

void
GameRewards::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << "<!-- Not implemented -->" << endl;
// Fill me in
}

void
GameRewards::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["judgement"] = &GameRewards::NullHandler;
    m_endTable[kPickleData]["judgement"] = &GameRewards::HandleJudgementEnd;
    m_endTable[kPickleData]["rewards"] = &GameRewards::HandleRewardsEnd;
    m_pickleState=kPickleData;
}

void
GameRewards::UnpickleEpilogue(void)
{
    m_startTable.clear();
    m_endTable.clear();
}

void
GameRewards::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameRewards::XMLStartHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << "> in Rewards.  Potential matches are";
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
GameRewards::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << "> in Rewards.  Potential matches are";
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
GameRewards::XMLDataHandler(CoreXML& inXML)
{
}


