/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameRewards.cpp,v 1.4 2002/10/22 20:42:05 southa Exp $
 * $Log: GameRewards.cpp,v $
 * Revision 1.4  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:25  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.1  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 */

#include "GameRewards.h"
#include "GameDataUtils.h"

bool
GameRewards::JudgementPass(tVal inRatio)
{
    U32 size=m_judgements.size();
    bool found=false;

    // Assume rewards are in order, lowest first
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

bool
GameRewards::TimeCountdownPass(tVal inTime)
{
    bool found=false;
    if (m_lastTimeValid)
    {
        U32 size=m_times.size();

        for (U32 i=0; i<size; ++i)
        {
            if (inTime <= m_times[i].time &&
                m_lastTime > m_times[i].time)
            {
                GameDataUtils::NamedDialoguesAdd(m_times[i].dialogueName);
                found=true;
            }
        }
    }
    m_lastTimeValid = true;
    m_lastTime = inTime;
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
GameRewards::HandleTimedEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for timed.  Should be <timed>10,^ten-second-warning</timed>";
    char comma;
    TimedCount timeCount;
    if (!(data >> timeCount.time)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    if (!(data >> timeCount.dialogueName)) inXML.Throw(failMessage);
    timeCount.time *= 1000;
    m_times.push_back(timeCount);
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
    m_startTable[kPickleData]["timed"] = &GameRewards::NullHandler;
    m_endTable[kPickleData]["timed"] = &GameRewards::HandleTimedEnd;
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

char *
GameRewards::TypeNameGet(void) const
{
    return "gamerewards";
}

