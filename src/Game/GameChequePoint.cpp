/*
 * $Id: GameChequePoint.cpp,v 1.2 2002/08/20 11:43:25 southa Exp $
 * $Log: GameChequePoint.cpp,v $
 * Revision 1.2  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 * Revision 1.1  2002/08/18 20:44:33  southa
 * Initial chequepoint work
 *
 */

#include "GameChequePoint.h"
#include "GameData.h"
#include "GameDataUtils.h"
#include "GameType.h"
#include "GameEvent.h"

void
GameChequePoint::StandingOnHandler(const GameEventStandingOn& inEvent)
{
    U32 size=m_mapValues.size();
    for (U32 i=0; i<size; ++i)
    {
        if (inEvent.mapValue == m_mapValues[i])
        {
            Triggered();
            break;
        }
    }
}

void
GameChequePoint::Triggered(void)
{
    if (m_action != "") GameDataUtils::NamedDialoguesAdd(m_action);
    GameData::Instance().TypeGet().SequenceAdvance();
}

void
GameChequePoint::HandleSequenceEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_sequence)) inXML.Throw("Bad format for sequence.  Should be <sequence>1</sequence>");
}

void
GameChequePoint::HandleActionEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_action)) inXML.Throw("Bad format for action.  Should be <action>^chequepoint1</action>");
}

void
GameChequePoint::HandleMapValueEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    char comma;
    do
    {
        U32 mapValue;
        if (!(data >> mapValue)) inXML.Throw("Bad format for mapvalue.  Should be <mapvalue>90,91,92</mapvalue>");
        m_mapValues.push_back(mapValue);
        if (!(data >> comma)) break;
    } while (comma == ',');
}

void
GameChequePoint::HandleTimeEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_time)) inXML.Throw("Bad format for time.  Should be <time>10</time>");
    m_time *=1000;
}

void
GameChequePoint::HandleChequePointEnd(CoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameChequePoint::NullHandler(CoreXML& inXML)
{
}

void
GameChequePoint::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << "<!-- Not supported -->" << endl;
}

void
GameChequePoint::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["sequence"] = &GameChequePoint::NullHandler;
    m_endTable[kPickleData]["sequence"] = &GameChequePoint::HandleSequenceEnd;
    m_startTable[kPickleData]["mapvalue"] = &GameChequePoint::NullHandler;
    m_endTable[kPickleData]["mapvalue"] = &GameChequePoint::HandleMapValueEnd;
    m_startTable[kPickleData]["action"] = &GameChequePoint::NullHandler;
    m_endTable[kPickleData]["action"] = &GameChequePoint::HandleActionEnd;
    m_startTable[kPickleData]["time"] = &GameChequePoint::NullHandler;
    m_endTable[kPickleData]["time"] = &GameChequePoint::HandleTimeEnd;
    m_endTable[kPickleData]["chequepoint"] = &GameChequePoint::HandleChequePointEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
}

void
GameChequePoint::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameChequePoint::UnpickleEpilogue(void)
{
    m_startTable.resize(0);
    m_endTable.resize(0);
}

void
GameChequePoint::XMLStartHandler(CoreXML& inXML)
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
            message << "Unexpected tag <" << inXML.TopTag() << "> in ChequePoint.  Potential matches are";
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
GameChequePoint::XMLEndHandler(CoreXML& inXML)
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
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in ChequePoint.  Potential matches are";
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
GameChequePoint::XMLDataHandler(CoreXML& inXML)
{
}

string
GameChequePoint::TypeNameGet(void) const
{
    return "chequepoint";
}
