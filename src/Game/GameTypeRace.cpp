/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameTypeRace.cpp,v 1.24 2002/08/26 12:44:37 southa Exp $
 * $Log: GameTypeRace.cpp,v $
 * Revision 1.24  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.23  2002/08/24 18:52:55  southa
 * Fixed add on times
 *
 * Revision 1.22  2002/08/24 17:08:32  southa
 * Split time fixes
 *
 * Revision 1.21  2002/08/24 15:57:35  southa
 * Reset player position
 *
 * Revision 1.20  2002/08/24 15:42:24  southa
 * Race state change
 *
 * Revision 1.19  2002/08/24 15:27:07  southa
 * Race restart
 *
 * Revision 1.18  2002/08/24 10:52:47  southa
 * World records
 *
 * Revision 1.17  2002/08/22 10:59:49  southa
 * Correction to lapCount race finished test
 *
 * Revision 1.16  2002/08/22 10:56:42  southa
 * Calculate final race results after advancing sequence
 *
 * Revision 1.15  2002/08/22 10:11:11  southa
 * Save records, spacebar dialogues
 *
 * Revision 1.14  2002/08/21 19:48:42  southa
 * Race result tweaking
 *
 * Revision 1.13  2002/08/21 16:53:46  southa
 * Win and lose handling
 *
 * Revision 1.12  2002/08/21 16:09:04  southa
 * GameTypeRace state tweaks
 *
 * Revision 1.11  2002/08/21 15:39:01  southa
 * GameTypeRace states
 *
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
GameTypeRace::Initialise(void)
{
    LoadRecords();
    m_lapStartTimeValid=false;
    m_chequePointTimeValid=false;
    m_sequence=0;
    m_lapCount=0;
    m_resultAlpha=0;
    m_raceState=kPrelude;
    m_timeAllowance=m_initialTime;
    m_records.Reset();
}

void
GameTypeRace::EventHandler(const GameEvent& inEvent)
{
    if (typeid(inEvent) == typeid(GameEventStandingOn))
    {
        StandingOnHandler(dynamic_cast<const GameEventStandingOn&>(inEvent));
    }
    else if (typeid(inEvent) == typeid(GameEventSequenceAdvance))
    {
        switch(m_raceState)
        {
            case kPrelude:
            case kRunning:
                SequenceAdvance();
                break;

            default:
                break;
        }
    }
}

void
GameTypeRace::StandingOnHandler(const GameEventStandingOn& inEvent)
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

    switch(m_raceState)
    {
        case kPrelude:
            m_startTime=gameTime;
            m_raceState=kRunning;
            GameDataUtils::NamedDialoguesAdd(m_startAction);
            break;

        default:
            break;
    }
    
    
    U32 previousSequence = m_sequence;
    if (previousSequence == 0) previousSequence = m_chequePoints.size();
    --previousSequence;
    
    U32 thisSequence = m_sequence;

    m_timeAllowance += m_chequePoints[m_sequence]->AddTimeGet();
    
    m_sequence++;
    if (m_sequence >= m_chequePoints.size())
    {
        m_sequence = 0;
    }
    
    if (m_sequence == 1)
    {
        // Just passed the lap start
        ++m_lapCount;
        if (m_lapCount == m_laps)
        {
            GameDataUtils::NamedDialoguesAdd(m_finalLapAction);
        }
        if (m_lapStartTimeValid)
        {
            GameTimer::tMsec lapTime = m_dispLap;
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
        GameTimer::tMsec splitTime = m_dispSplit;
        if (m_records.SplitTimeValid(previousSequence))
        {
            GameTimer::tMsec oldSplitTime = m_records.SplitTimeGet(previousSequence);
            GameDialogue *splitDialogue =
                GameData::Instance().CurrentDialogueAdd("splitdifference",
                                        *GameData::Instance().DialogueGet("splitdifference"));
            splitDialogue->TextSet(0, GameTimer::MsecDifferenceToString(splitTime - oldSplitTime));

        }
        GameDialogue *splitDialogue =
            GameData::Instance().CurrentDialogueAdd("splitdisplay",
                                    *GameData::Instance().DialogueGet("splitdisplay"));
        splitDialogue->TextSet(0, GameTimer::MsecToString(splitTime));

        m_records.SplitTimePropose(previousSequence, splitTime);
        if (judgementRatio == 0.0)
        {
            judgementRatio = splitTime / m_chequePoints[thisSequence]->ParTimeGet();
        }
    }
    m_chequePointTime = gameTime;
    m_chequePointTimeValid = true;
    
    if (m_lapCount == m_laps+1 && m_sequence == 1)
    {
        RaceFinished();
        judgementRatio = (m_endTime - m_startTime) / (m_lapParTime * m_laps);
    }        

    if (judgementRatio != 0.0)
    {
        GameData::Instance().RewardsGet().JudgementPass(judgementRatio);
    }
}
  
void
GameTypeRace::RaceFinished(void)
{
    GameTimer& timer(GameData::Instance().TimerGet());
    GameTimer::tMsec gameTime=timer.GameMsecGet();
    m_raceState = kPreResult;
    m_endTime = gameTime;

    if (m_dispRemaining > 0.0)
    {
        // Race won
        m_records.RaceTimePropose(m_endTime - m_startTime);
        GameDataUtils::NamedDialoguesAdd(m_winAction);
    }
    else
    {
        // Race lost
        GameDataUtils::NamedDialoguesAdd(m_loseAction);
    }
    // Calculate the new records and save, but leave m_worldRecords intact
    // so that we can display the old records

    GameRecords newRecords(m_worldRecords);

    newRecords.RecordsPropose(m_records);
    
    SaveRecords(newRecords);
}

bool
GameTypeRace::IsGameOver(void) const
{
    return m_raceState == kResult;
}

void
GameTypeRace::Move(void)
{
    switch (m_raceState)
    {
        case kPrelude:
        case kRunning:
            UpdateTimes();
            if (m_dispRemaining <= 0.0)
            {
                RaceFinished();
                GameData::Instance().RewardsGet().JudgementPass((m_laps+2) / (m_lapCount+1));
            }
            GameData::Instance().RewardsGet().TimeCountdownPass(m_dispRemaining);    
            break;

	case kPreResult:
	    // Don't update times for the last time
            // UpdateTimes();
	    m_raceState=kResult;
	    break;
	    
        case kResult:
	    m_resultAlpha += (0.9-m_resultAlpha) / 500;
            break;

	default:
            throw(LogicFail("m_raceState"));
    }
}

void
GameTypeRace::Render(void) const
{
    switch (m_raceState)
    {
        case kPrelude:
        case kRunning:
	case kPreResult:
            RenderTimes();
            break;

        case kResult:
            RenderTimes();
            RenderResult();
            break;
            
       default:
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

        case kPreResult:
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
    lapMessage << "LAP " << m_lapCount << ":" << m_laps;
    GLString lapStr(lapMessage.str(),
                    GLFontRef("font-mono1", 0.02), -1.0);
    lapStr.Render();

    GLUtils::ColourSet(0.0,1.0,1.0,0.75);

    U32 prevSequence = m_sequence;
    if (prevSequence == 0) prevSequence = m_chequePoints.size();
    --prevSequence;
    if (m_records.SplitTimeValid(prevSequence))
    {
        orthoGL.MoveRelative(0, -0.025);
        GLString splitRecordStr(GameTimer::MsecToString(m_records.SplitTimeGet(prevSequence)),
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
GameTypeRace::RenderResult(void) const
{
    // Table layout
    const tVal row1=-0.1;
    const tVal rowSpacing=-0.03;
    const tVal column1=-0.2;
    const tVal column2=0.1;
    const tVal column3=0.4;
     
    GLUtils::OrthoPrologue();
    GLUtils::ColourSet(1.0,1.0,1.0,m_resultAlpha);
    GLUtils orthoGL;
    {
        orthoGL.MoveTo(column3,row1-rowSpacing);
        GLString recordStr("RECORDS", GLFontRef("font-mono1", 0.02), 1);
        recordStr.Render();
    }

    {
        orthoGL.MoveTo(column1,row1);
        GLString timeStr("Time:", GLFontRef("font-mono1", 0.03), 1);
        timeStr.Render();
        if (m_records.RaceTimeValid())
        {
            timeStr.TextSet(GameTimer::MsecToLongString(m_records.RaceTimeGet()));
            orthoGL.MoveTo(column2,row1);
            timeStr.Render();
        }
        if (m_worldRecords.RaceTimeValid())
        {
            timeStr.TextSet(GameTimer::MsecToLongString(m_worldRecords.RaceTimeGet()));
            orthoGL.MoveTo(column3,row1);
            timeStr.Render();
        }
    }
    
    {
        orthoGL.MoveTo(0,row1+rowSpacing);
        GLString recordStr("BEST SECTIONS", GLFontRef("font-mono1", 0.02), 0);
        recordStr.Render();
    }

    GLUtils::ColourSet(1.0,1.0,0.0,m_resultAlpha);

    if (m_records.LapTimeValid())
    {
        GLString lapRecordStr("Lap :", GLFontRef("font-mono1", 0.03), 1);
        orthoGL.MoveTo(column1, row1+2*rowSpacing);
        lapRecordStr.Render();
        lapRecordStr.TextSet(GameTimer::MsecToLongString(m_records.LapTimeGet()));
        orthoGL.MoveTo(column2, row1+2*rowSpacing);
        lapRecordStr.Render();
        if (m_worldRecords.LapTimeValid())
        {
            lapRecordStr.TextSet(GameTimer::MsecToLongString(m_worldRecords.LapTimeGet()));
            orthoGL.MoveTo(column3, row1+2*rowSpacing);
            lapRecordStr.Render();
        }
    }
    
    GLUtils::ColourSet(0.0,1.0,1.0,m_resultAlpha);
    
    for (U32 i=0; i<m_chequePoints.size(); ++i)
    {
        if (m_records.SplitTimeValid(i))
        {
            ostringstream message;
	    U32 nextPoint=i+1;
	    if (nextPoint >= m_chequePoints.size()) nextPoint=0;
            message << i+1 << "-" << nextPoint+1 << " :";
            GLString splitRecordStr(message.str(), GLFontRef("font-mono1", 0.03), 1.0);
            orthoGL.MoveTo(column1, row1+(3+i)*rowSpacing);
            splitRecordStr.Render();

            splitRecordStr.TextSet(GameTimer::MsecToString(m_records.SplitTimeGet(i)));
            orthoGL.MoveTo(column2, row1+(3+i)*rowSpacing);
            splitRecordStr.Render();

            if (m_worldRecords.SplitTimeValid(i))
            {
                splitRecordStr.TextSet(GameTimer::MsecToString(m_worldRecords.SplitTimeGet(i)));
                orthoGL.MoveTo(column3, row1+(3+i)*rowSpacing);
                splitRecordStr.Render();
            }
        }
    }
    GLUtils::OrthoEpilogue();
}

void
GameTypeRace::SaveRecords(const GameRecords& inRecords) const
{
    try
    {
        string filename;
        const CoreScalar *pScalar;
        if (CoreEnv::Instance().VariableGetIfExists(&pScalar, "RECORDS_FILENAME"))
        {
            filename=pScalar->StringGet();
            ofstream outputFile(filename.c_str());
            if (!outputFile) throw(FileFail(filename, "Could not open file for writing"));
            time_t now(time(NULL));
            outputFile << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl;
            outputFile << "<!-- Records saved " << ctime(&now) << " -->" << endl;
            inRecords.Pickle(outputFile);
        }
    }
    catch (exception& e)
    {
        cerr << "Save records failed: " << e.what() << endl;
        // We don't really care if it fails
    }
}

void
GameTypeRace::LoadRecords(void)
{
    try
    {
        string filename;
        const CoreScalar *pScalar;
        if (CoreEnv::Instance().VariableGetIfExists(&pScalar, "RECORDS_FILENAME"))
        {
            filename=pScalar->StringGet();
        }
        dynamic_cast<CorePickle&>(m_worldRecords).Unpickle(filename);
    }
    catch (exception& e)
    {
        cerr << "Load records failed: " << e.what() << endl;
        // We don't really care if it fails
    }
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
GameTypeRace::HandleWinActionEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for winaction.  Should be <winaction>^racewin</winaction>";
    if (!(data >> m_winAction)) inXML.Throw(failMessage);
}

void
GameTypeRace::HandleLoseActionEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for loseaction.  Should be <loseaction>^racelose</loseaction>";
    if (!(data >> m_loseAction)) inXML.Throw(failMessage);
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
    m_startTable[kPickleData]["winaction"] = &GameTypeRace::NullHandler;
    m_endTable[kPickleData]["winaction"] = &GameTypeRace::HandleWinActionEnd;
    m_startTable[kPickleData]["loseaction"] = &GameTypeRace::NullHandler;
    m_endTable[kPickleData]["loseaction"] = &GameTypeRace::HandleLoseActionEnd;
    m_startTable[kPickleData]["initialtime"] = &GameTypeRace::NullHandler;
    m_endTable[kPickleData]["initialtime"] = &GameTypeRace::HandleInitialTimeEnd;
    m_startTable[kPickleData]["laps"] = &GameTypeRace::NullHandler;
    m_endTable[kPickleData]["laps"] = &GameTypeRace::HandleLapsEnd;
    m_endTable[kPickleData]["game"] = &GameTypeRace::HandleGameEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    m_sequence=0;
    m_lapCount=0;
    m_resultAlpha=0;
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

  
