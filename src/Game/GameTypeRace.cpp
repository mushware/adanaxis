/*
 * $Id: GameTypeRace.cpp,v 1.4 2002/08/19 12:54:54 southa Exp $
 * $Log: GameTypeRace.cpp,v $
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
    if (!m_raceStarted)
    {
        m_startTime=gameTime;
        m_raceStarted=true;
    }
    m_sequence++;
    if (m_sequence >= m_chequePoints.size())
    {
        m_sequence = 0;
    }
    if (m_sequence == 1)
    {
        // Just passed the lap start
        if (m_lapStartTimeValid)
        {
            m_records.LapTimePropose(gameTime - m_lapStartTime);
        }
        m_lapStartTime = gameTime;
        m_lapStartTimeValid = true;
    }
    if (m_chequePointTimeValid)
    {
        m_records.SplitTimePropose(m_sequence, gameTime - m_chequePointTime);
    }
    m_chequePointTime = gameTime;
    m_chequePointTimeValid = true;    
}

void
GameTypeRace::Render(void) const
{
    GameTimer& timer(GameData::Instance().TimerGet());
    if (!timer.JudgementValid()) return;
    GameTimer::tMsec gameTime=timer.GameMsecGet();

    GameTimer::tMsec elapsedTime=0;
    if (m_raceStarted)
    {
        elapsedTime=gameTime - m_startTime;
    }

    GLUtils::OrthoPrologue();
    GLUtils::ColourSet(0.0,0.0,1.0,0.5);
    GLUtils orthoGL;
    orthoGL.MoveToEdge(1,1);
    orthoGL.MoveRelative(-0.03,-0.03);
    GLString fpsStr("Elapsed " + GameTimer::MsecToLongString(elapsedTime),
                    GLFontRef("font-mono1", 0.03), 1.0);
    fpsStr.Render();
    if (m_records.LapTimeValid())
    {
        orthoGL.MoveRelative(0, -0.025);
        GLString lapRecordStr("Lap record "+GameTimer::MsecToLongString(m_records.LapTimeGet()),
                              GLFontRef("font-mono1", 0.02), 1.0);
        lapRecordStr.Render();
    }
    if (m_lapStartTimeValid)
    {
        orthoGL.MoveRelative(0, -0.025);
        GLString lapTimeStr("Lap time "+GameTimer::MsecToLongString(gameTime - m_lapStartTime),
                              GLFontRef("font-mono1", 0.02), 1.0);
        lapTimeStr.Render();
    }

    orthoGL.MoveToEdge(-1,1);
    orthoGL.MoveRelative(-0.03,-0.03);
    if (m_records.SplitTimeValid(m_sequence))
    {
        orthoGL.MoveRelative(0, -0.025);
        GLString splitRecordStr("Split record "+GameTimer::MsecToLongString(m_records.SplitTimeGet(m_sequence)),
                              GLFontRef("font-mono1", 0.02), -1.0);
        splitRecordStr.Render();
    }
    if (m_chequePointTimeValid)
    {
        orthoGL.MoveRelative(0, -0.025);
        GLString splitTimeStr("Split time "+GameTimer::MsecToLongString(gameTime - m_chequePointTime),
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
    m_endTable[kPickleData]["game"] = &GameTypeRace::HandleGameEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    m_sequence=0;
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

  