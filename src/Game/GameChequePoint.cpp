//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameChequePoint.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } AVEPfwCs0IJ8bunJYEi5LA
/*
 * $Id: GameChequePoint.cpp,v 1.16 2003/08/21 23:08:34 southa Exp $
 * $Log: GameChequePoint.cpp,v $
 * Revision 1.16  2003/08/21 23:08:34  southa
 * Fixed file headers
 *
 * Revision 1.15  2003/01/20 10:45:24  southa
 * Singleton tidying
 *
 * Revision 1.14  2003/01/13 14:31:56  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.13  2003/01/09 14:56:59  southa
 * Created Mushcore
 *
 * Revision 1.12  2003/01/07 17:13:41  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.11  2002/12/29 20:59:54  southa
 * More build fixes
 *
 * Revision 1.10  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/11/24 23:18:05  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.8  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/08 11:58:52  southa
 * Light cache
 *
 * Revision 1.6  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/21 16:09:04  southa
 * GameTypeRace state tweaks
 *
 * Revision 1.4  2002/08/21 10:12:21  southa
 * Time down counter
 *
 * Revision 1.3  2002/08/20 15:00:56  southa
 * Reward tweaks
 *
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
#include "GameEvent.h"
#include "GameSTL.h"
#include "GameType.h"

using namespace Mushware;
using namespace std;

void
GameChequePoint::StandingOnHandler(const GameEventStandingOn& inEvent)
{
    U32 size=m_mapValues.size();
    for (U32 i=0; i<size; ++i)
    {
        U32 size=inEvent.mapValues.size();
        for (U32 j=0; j<size; ++j)
        {
            if (inEvent.mapValues[j] == m_mapValues[i])
            {
                Triggered();
                return;
            }
        }
    }
}

void
GameChequePoint::Triggered(void)
{
    GameDataUtils::NamedDialoguesAdd(m_action);
    GameData::Sgl().TypeGet().EventHandler(GameEventSequenceAdvance());
}

void
GameChequePoint::HandleSequenceEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_sequence)) inXML.Throw("Bad format for sequence.  Should be <sequence>1</sequence>");
}

void
GameChequePoint::HandleActionEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_action)) inXML.Throw("Bad format for action.  Should be <action>^chequepoint1</action>");
}

void
GameChequePoint::HandleMapValueEnd(MushcoreXML& inXML)
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
GameChequePoint::HandleParTimeEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_parTime)) inXML.Throw("Bad format for partime.  Should be <partime>10</partime>");
    m_parTime *=1000;
}

void
GameChequePoint::HandleAddTimeEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_addTime)) inXML.Throw("Bad format for addtime.  Should be <addtime>10</addtime>");
    m_addTime *=1000;
}

void
GameChequePoint::HandleChequePointEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameChequePoint::NullHandler(MushcoreXML& inXML)
{
}

void
GameChequePoint::Pickle(ostream& inOut, const string& inPrefix) const
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
    m_startTable[kPickleData]["partime"] = &GameChequePoint::NullHandler;
    m_endTable[kPickleData]["partime"] = &GameChequePoint::HandleParTimeEnd;
    m_startTable[kPickleData]["addtime"] = &GameChequePoint::NullHandler;
    m_endTable[kPickleData]["addtime"] = &GameChequePoint::HandleAddTimeEnd;
    m_endTable[kPickleData]["chequepoint"] = &GameChequePoint::HandleChequePointEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    m_addTime=0;
    m_parTime=0;
}

void
GameChequePoint::Unpickle(MushcoreXML& inXML)
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
GameChequePoint::XMLStartHandler(MushcoreXML& inXML)
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
GameChequePoint::XMLEndHandler(MushcoreXML& inXML)
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
GameChequePoint::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
GameChequePoint::TypeNameGet(void) const
{
    return "gamechequepoint";
}
