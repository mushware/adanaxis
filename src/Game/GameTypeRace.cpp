/*
 * $Id: GameTypeRace.cpp,v 1.10 2002/08/21 10:12:21 southa Exp $
 * $Log: GameTypeRace.cpp,v $
 * Revision 1.10  2002/08/21 10:12:21  southa
 * Time down counter
 *
 * Revision 1.9  2002/08/20 15:00:56  southa
 * Reward tweaks
 *
 * Revision 1.8  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 * Revision 1.7  2002/08/19 23:11:22  southa
 * Lap and split time tweaks
 *
 * Revision 1.6  2002/08/19 22:18:36  southa
 * Display of time differences
 *
 * Revision 1.5  2002/08/19 21:42:38  southa
 * Display of records and lap/split times
 *
 * Revision 1.4  2002/08/19 12:54:54  southa
 * Added time format
 *
 * Revision 1.3  2002/08/19 11:09:56  southa
 * GameTypeRace rendering
 *
 * Revision 1.2  2002/08/19 09:59:36  southa
 * Removed sound callbacks, used polling
 *
 * Revision 1.1  2002/08/18 20:52:28  southa
 * Moved
 *
 * Revision 1.1  2002/08/18 20:44:33  southa
 * Initial chequepoint work
 *
 */

#include "GameTypeRace.h"
#include "GameChequePoint.h"
#include "GameEvent.h"
#include "GameAppHandler.h"
#include "GameData.h"
#include "GameDataUtils.h"
#include "GameDialogue.h"
#include "GameRewards.h"

#include <typeinfo>

GameTypeRace::GameTypeRace():
    m_lapStartTimeValid(false),
    m_chequePointTimeValid(false)
{
}

void
GameTypeRace::EventHandler(GameEvent& inEvent)
{
    if (typeid(inEvent) == typeid(GameEventStandingOn))
    {
        StandingOnHandler(dynamic_cast<GameEventStandingOn&>(inEvent));
    }
}

void
GameTypeRace::StandingOnHandler(GameEventStandingOn& inEvent)
{
    U32 size=m_chequePoints.size();
    for (U32 i=0; i<size; ++i)
    {
        if (m_sequence == m_chequePoints[i]->SequenceGet())
        {
            m_chequePoints[i]->StandingOnHandler(inEvent);
        }
    }
}

void
GameTypeRace::SequenceAdvance(void)
{
    GameTimer& timer(GameData::Instance().TimerGet());
    GameTimer::tMsec gameTime=timer.GameMsecGet();

    tVal judgementRatio=0.0;
    
    if (m_raceState == kPrelude)
    {
        m_startTime=gameTime;
        m_raceState=kRunning;
        GameDataUtils::NamedDialoguesAdd(m_startAction);
    }
    
    U32 lastSequence = m_sequence;

    m_timeAllowance += m_chequePoints[m_sequence]->AddTimeGet();
    
    m_sequence++;
    if (m_sequence >= m_chequePoints.size())
    {
        m_sequence = 0;
    }
    
    if (m_sequence == 1)
    {
        if (m_lapCount == m_laps)
        {
            // Race is finsihed
            GameDataUtils::NamedDialoguesAdd(m_endAction);
            m_raceState = kResult;
            // Calculate the total available time
            tVal extraTime=0;
            for (U32 i=0; i < m_chequePoints.size(); ++i)
            {
                extraTime += m_chequePoints[i]->AddTimeGet();
            }
            judgementRatio = (gameTime - m_startTime) / (m_initialTime + m_laps * extraTime);
        }
        
        // Just passed the lap start
        ++m_lapCount;
        if (m_lapCount == m_laps)
        {
            GameDataUtils::NamedDialoguesAdd(m_finalLapAction);
        }
        if (m_lapStartTimeValid)
        {
            GameTimer::tMsec lapTime = gameTime-m_lapStartTime;
            if (m_records.LapTimeValid())
            {
                GameTimer::tMsec oldLapTime = m_records.LapTimeGet();
                GameDialogue *lapDifference =
                    GameData::Instance().CurrentDialogueAdd("lapdifference",
                        *GameData::Instance().DialogueGet("lapdifference"));
                lapDifference->TextSet(0, GameTimer::MsecDifferenceToString(lapTime - oldLapTime));
            }
            GameDialogue *lapDisplay =
                GameData::Instance().CurrentDialogueAdd("lapdisplay",
                    *GameData::Instance().DialogueGet("lapdisplay"));
            lapDisplay->TextSet(0, GameTimer::MsecToLongString(lapTime));

            m_records.LapTimePropose(lapTime);
            if (judgementRatio == 0.0)
            {
                judgementRatio = lapTime / m_lapParTime;
            }
        }
        m_lapStartTime = gameTime;
        m_lapStartTimeValid = true;
    }
    if (m_chequePointTimeValid)
    {
        GameTimer::tMsec splitTime = gameTime - m_chequePointTime;
        if (m_records.SplitTimeValid(m_sequence))
        {
            GameTimer::tMsec oldSplitTime = m_records.SplitTimeGet(m_sequence);
            GameDialogue *splitDialogue =
                GameData::Instance().CurrentDialogueAdd("splitdifference",
                                        *GameData::Instance().DialogueGet("splitdifference"));
            splitDialogue->TextSet(0, GameTimer::MsecDifferenceToString(splitTime - oldSplitTime));

        }
        GameDialogue *splitDialogue =
            GameData::Instance().CurrentDialogueAdd("splitdisplay",
                                    *GameData::Instance().DialogueGet("splitdisplay"));
        splitDialogue->TextSet(0, GameTimer::MsecToString(splitTime));

        m_records.SplitTimePropose(m_sequence, splitTime);
        if (judgementRatio == 0.0)
        {
            judgementRatio = splitTime / m_chequePoints[lastSequence]->ParTimeGet();
        }
    }
    m_chequePointTime = gameTime;
    m_chequePointTimeValid = true;
    if (judgementRatio != 0.0)
    {
        GameData::Instance().RewardsGet().JudgementPass(judgementRatio);
    }
}

void
GameTypeRace::Render(void)
{
    switch (m_raceState)
    {
        case kPrelude:
        case kRunning:
            UpdateTimes();
            RenderTimes();
            break;

        case kResult:
            RenderTimes();

        case kInvalid:
            throw(LogicFail("m_raceState"));
    }
}

void
GameTypeRace::UpdateTimes(void)
{
    GameTimer& timer(GameData::Instance().TimerGet());
    if (!timer.JudgementValid()) return;
    GameTimer::tMsec gameTime=timer.GameMsecGet();

    switch (m_raceState)
    {
        case kPrelude:
            m_dispRemaining = m_timeAllowance;
            break;

        case kRunning:
            m_dispRemaining = m_startTime + m_timeAllowance - gameTime;
            m_dispLap = gameTime - m_lapStartTime;
            m_dispSplit = gameTime - m_chequePointTime;
            break;

        case kResult:
            break;
            
        default:
            throw(LogicFail("m_raceState"));
    }
}

void
GameTypeRace::RenderTimes(void) const
{
    GLUtils::OrthoPrologue();
    GLUtils::ColourSet(1.0,1.0,1.0,0.75);
    GLUtils orthoGL;
    orthoGL.MoveToEdge(1,1);
    orthoGL.MoveRelative(-0.03,-0.03);
    GLString remainingStr(GameTimer::MsecToLongString(m_dispRemaining),
                          GLFontRef("font-mono1", 0.03), 1.0);
    remainingStr.Render();
    GLUtils::ColourSet(1.0,1.0,0.0,0.75);
    if (m_records.LapTimeValid())
    {
        orthoGL.MoveRelative(0, -0.025);
        GLString lapRecordStr(GameTimer::MsecToLongString(m_records.LapTimeGet()),
                              GLFontRef("font-mono1", 0.02), 1.0);
        lapRecordStr.Render();
    }
    if (m_lapStartTimeValid)
    {
        orthoGL.MoveRelative(0, -0.025);
        GLString lapTimeStr(GameTimer::MsecToLongString(m_dispLap),
                              GLFontRef("font-mono1", 0.02), 1.0);
        lapTimeStr.Render();
    }

    GLUtils::ColourSet(1.0,1.0,1.0,0.75);
    orthoGL.MoveToEdge(-1,1);
    orthoGL.MoveRelative(0.03,-0.03);

    ostringstream lapMessage;
    lapMessage << "LAP " << m_lapCount << " (" << m_laps << ")";
    GLString lapStr(lapMessage.str(),
                    GLFontRef("font-mono1", 0.02), -1.0);
    lapStr.Render();

    GLUtils::ColourSet(0.0,1.0,1.0,0.75);

    U32 nextSequence = m_sequence+1;
    if (nextSequence >= m_chequePoints.size()) nextSequence = 0;

    if (m_records.SplitTimeValid(nextSequence))
    {
        orthoGL.MoveRelative(0, -0.025);
        GLString splitRecordStr(GameTimer::MsecToString(m_records.SplitTimeGet(nextSequence)),
                              GLFontRef("font-mono1", 0.02), -1.0);
        splitRecordStr.Render();
    }
    
    if (m_chequePointTimeValid)
    {
        orthoGL.MoveRelative(0, -0.025);
        GLString splitTimeStr(GameTimer::MsecToString(m_dispSplit),
                            GLFontRef("font-mono1", 0.02), -1.0);
        splitTimeStr.Render();
    }
    GLUtils::OrthoEpilogue();
}

void
GameTypeRace::HandleGameEnd(CoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameTypeRace::HandleLapTimeEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for laptime.  Should be <laptime>45.0</laptime>";

    if (!(data >> m_lapParTime)) inXML.Throw(failMessage);
    m_lapParTime *= 1000;
}

void
GameTypeRace::HandleStartActionEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for startaction.  Should be <startaction>^racestart</startaction>";
    if (!(data >> m_startAction)) inXML.Throw(failMessage);
}

void
GameTypeRace::HandleFinalLapActionEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for finallapaction.  Should be <finallapaction>^finallap</finallapaction>";
    if (!(data >> m_finalLapAction)) inXML.Throw(failMessage);
}

void
GameTypeRace::HandleEndActionEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for endaction.  Should be <endaction>^raceend</endaction>";
    if (!(data >> m_endAction)) inXML.Throw(failMessage);
}

void
GameTypeRace::HandleInitialTimeEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for initialtime.  Should be <initialtime>120</initialtime>";
    if (!(data >> m_initialTime)) inXML.Throw(failMessage);
    m_initialTime *= 1000;
}

void
GameTypeRace::HandleLapsEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for laps.  Should be <laps>5</laps>";
    if (!(data >> m_laps)) inXML.Throw(failMessage);
}

void
GameTypeRace::HandleChequePointStart(CoreXML& inXML)
{
    GameChequePoint *chequePoint=new GameChequePoint;
    m_chequePoints.push_back(chequePoint);
    chequePoint->Unpickle(inXML);
}

void
GameTypeRace::NullHandler(CoreXML& inXML)
{
}

void
GameTypeRace::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<!-- Not implemented -->" << endl;
}

void
GameTypeRace::UnpicklePrologue(void)
{
    GameType::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["chequepoint"] = &GameTypeRace::HandleChequePointStart;
    m_endTable[kPickleData]["chequepoint"] = &GameTypeRace::NullHandler;
    m_startTable[kPickleData]["laptime"] = &GameTypeRace::NullHandler;
    m_endTable[kPickleData]["laptime"] = &GameTypeRace::HandleLapTimeEnd;
    m_startTable[kPickleData]["startaction"] = &GameTypeRace::NullHandler;
    m_endTable[kPickleData]["startaction"] = &GameTypeRace::HandleStartActionEnd;
    m_startTable[kPickleData]["finallapaction"] = &GameTypeRace::NullHandler;
    m_endTable[kPickleData]["finallapaction"] = &GameTypeRace::HandleFinalLapActionEnd;
    m_startTable[kPickleData]["endaction"] = &GameTypeRace::NullHandler;
    m_endTable[kPickleData]["endaction"] = &GameTypeRace::HandleEndActionEnd;
    m_startTable[kPickleData]["initialtime"] = &GameTypeRace::NullHandler;
    m_endTable[kPickleData]["initialtime"] = &GameTypeRace::HandleInitialTimeEnd;
    m_startTable[kPickleData]["laps"] = &GameTypeRace::NullHandler;
    m_endTable[kPickleData]["laps"] = &GameTypeRace::HandleLapsEnd;
    m_endTable[kPickleData]["game"] = &GameTypeRace::HandleGameEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    m_sequence=0;
    m_lapCount=0;
    m_raceState=kPrelude;
}

void
GameTypeRace::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameTypeRace::UnpickleEpilogue(void)
{
    GameType::UnpickleEpilogue();
    m_startTable.resize(0);
    m_endTable.resize(0);
    m_timeAllowance=m_initialTime;
}

void
GameTypeRace::XMLStartHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
//        if (m_pickleState == kPickleData)
//        {
//            GameGraphic::XMLStartHandler(inXML);
//            m_pickleState=kPickleWithinBase;
//            ++m_baseThreaded;
//        }
//        else
        {
            ostringstream message;
            message << "Unexpected tag <" << inXML.TopTag() << "> in TypeRace.  Potential matches are";
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
GameTypeRace::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
//        if (m_pickleState == kPickleWithinBase)
//        {
//          GameGraphic::XMLEndHandler(inXML);
//            --m_baseThreaded;
//            if (m_baseThreaded == 0)
//            {
//                m_pickleState=kPickleData;
//            }
//        }
//        else
        {
            ostringstream message;
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in TypeRace.  Potential matches are";
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
GameTypeRace::XMLDataHandler(CoreXML& inXML)
{
}

string
GameTypeRace::TypeNameGet(void) const
{
    return "race";
}

  
