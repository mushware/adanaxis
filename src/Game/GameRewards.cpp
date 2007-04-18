//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameRewards.cpp
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } m2KIs8XHesNErXocE7OiKg
/*
 * $Id: GameRewards.cpp,v 1.20 2006/06/01 15:38:59 southa Exp $
 * $Log: GameRewards.cpp,v $
 * Revision 1.20  2006/06/01 15:38:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.19  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.18  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.17  2004/01/01 21:15:45  southa
 * Created XCode project
 *
 * Revision 1.16  2003/10/07 22:40:05  southa
 * Created MeshMover
 *
 * Revision 1.15  2003/10/04 18:12:13  southa
 * Readded
 *
 * Revision 1.13  2003/10/04 12:23:02  southa
 * File renaming
 *
 * Revision 1.12  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.11  2003/08/21 23:08:53  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/01/13 14:32:00  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.9  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.8  2003/01/07 17:13:43  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.7  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.6  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/11/24 23:18:25  southa
 * Added type name accessor to MushcorePickle
 *
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

#include "GameEvent.h"
#include "GameType.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

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
            GameType::Sgl().EventHandler(GameEventReward(m_judgements[i].dialogueName));
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
                GameType::Sgl().EventHandler(GameEventReward(m_times[i].dialogueName));
                found=true;
            }
        }
    }
    m_lastTimeValid = true;
    m_lastTime = inTime;
    return found;
}

void
GameRewards::HandleJudgementEnd(MushcoreXML& inXML)
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
GameRewards::HandleTimedEnd(MushcoreXML& inXML)
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
GameRewards::HandleRewardsEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameRewards::NullHandler(MushcoreXML& inXML)
{
}

void
GameRewards::Pickle(ostream& inOut, const string& inPrefix) const
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
GameRewards::Unpickle(MushcoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameRewards::XMLStartHandler(MushcoreXML& inXML)
{
    ElementFunctionMap::iterator p2 = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_startTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
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
GameRewards::XMLEndHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p2 = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_endTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
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
GameRewards::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
GameRewards::TypeNameGet(void) const
{
    return "gamerewards";
}

