/*
 * $Id: GameTypeRace.cpp,v 1.3 2002/08/19 11:09:56 southa Exp $
 * $Log: GameTypeRace.cpp,v $
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
    if (!m_raceStarted)
    {
        GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
        GameTimer& timer(GameData::Instance().TimerGet());
        m_startTime=timer.GameMsecGet();
        m_raceStarted=true;
    }
    m_sequence++;
    if (m_sequence >= m_chequePoints.size())
    {
        m_sequence = 0;
    }
}

void
GameTypeRace::Render(void) const
{
    GameTimer::tMsec elapsedTime=0;
    if (m_raceStarted)
    {
        GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
        GameTimer& timer(GameData::Instance().TimerGet());
        elapsedTime=timer.GameMsecGet() - m_startTime;
    }

    ostringstream message;
    message << "Elapsed " << GameTimer::MsecToLongString(elapsedTime);
    GLUtils::OrthoPrologue();
    GLUtils::ColourSet(0.0,0.0,1.0,0.5);
    GLUtils orthoGL;
    orthoGL.MoveToEdge(1,1);
    orthoGL.MoveRelative(-0.03,-0.03);
    GLString fpsStr(message.str(), GLFontRef("font-mono1", 0.03), 1.0);
    fpsStr.Render();
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

