//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalChequePoint.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } hu5+CQDupViMzWYdaLkYDA
/*
 * $Id: InfernalChequePoint.cpp,v 1.2 2003/10/04 12:44:34 southa Exp $
 * $Log: InfernalChequePoint.cpp,v $
 * Revision 1.2  2003/10/04 12:44:34  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:04  southa
 * File renaming
 *
 * Revision 1.17  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
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
 * InfernalTypeRace state tweaks
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

#include "InfernalChequePoint.h"
#include "InfernalData.h"
#include "InfernalDataUtils.h"
#include "InfernalEvent.h"
#include "InfernalSTL.h"

#include "mushGame.h"

using namespace Mushware;
using namespace std;

void
InfernalChequePoint::StandingOnHandler(const InfernalEventStandingOn& inEvent)
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
InfernalChequePoint::Triggered(void)
{
    InfernalDataUtils::NamedDialoguesAdd(m_action);
    InfernalData::Sgl().TypeGet().EventHandler(InfernalEventSequenceAdvance());
}

void
InfernalChequePoint::HandleSequenceEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_sequence)) inXML.Throw("Bad format for sequence.  Should be <sequence>1</sequence>");
}

void
InfernalChequePoint::HandleActionEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_action)) inXML.Throw("Bad format for action.  Should be <action>^chequepoint1</action>");
}

void
InfernalChequePoint::HandleMapValueEnd(MushcoreXML& inXML)
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
InfernalChequePoint::HandleParTimeEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_parTime)) inXML.Throw("Bad format for partime.  Should be <partime>10</partime>");
    m_parTime *=1000;
}

void
InfernalChequePoint::HandleAddTimeEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_addTime)) inXML.Throw("Bad format for addtime.  Should be <addtime>10</addtime>");
    m_addTime *=1000;
}

void
InfernalChequePoint::HandleChequePointEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
InfernalChequePoint::NullHandler(MushcoreXML& inXML)
{
}

void
InfernalChequePoint::Pickle(ostream& inOut, const string& inPrefix) const
{
    inOut << "<!-- Not supported -->" << endl;
}

void
InfernalChequePoint::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["sequence"] = &InfernalChequePoint::NullHandler;
    m_endTable[kPickleData]["sequence"] = &InfernalChequePoint::HandleSequenceEnd;
    m_startTable[kPickleData]["mapvalue"] = &InfernalChequePoint::NullHandler;
    m_endTable[kPickleData]["mapvalue"] = &InfernalChequePoint::HandleMapValueEnd;
    m_startTable[kPickleData]["action"] = &InfernalChequePoint::NullHandler;
    m_endTable[kPickleData]["action"] = &InfernalChequePoint::HandleActionEnd;
    m_startTable[kPickleData]["partime"] = &InfernalChequePoint::NullHandler;
    m_endTable[kPickleData]["partime"] = &InfernalChequePoint::HandleParTimeEnd;
    m_startTable[kPickleData]["addtime"] = &InfernalChequePoint::NullHandler;
    m_endTable[kPickleData]["addtime"] = &InfernalChequePoint::HandleAddTimeEnd;
    m_endTable[kPickleData]["chequepoint"] = &InfernalChequePoint::HandleChequePointEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    m_addTime=0;
    m_parTime=0;
}

void
InfernalChequePoint::Unpickle(MushcoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
InfernalChequePoint::UnpickleEpilogue(void)
{
    m_startTable.resize(0);
    m_endTable.resize(0);
}

void
InfernalChequePoint::XMLStartHandler(MushcoreXML& inXML)
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
InfernalChequePoint::XMLEndHandler(MushcoreXML& inXML)
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
InfernalChequePoint::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
InfernalChequePoint::TypeNameGet(void) const
{
    return "gamechequepoint";
}
