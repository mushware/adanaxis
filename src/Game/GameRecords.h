//%includeGuardStart {
#ifndef GAMERECORDS_H
#define GAMERECORDS_H
//%includeGuardStart } SUT8MQPOsiKcepqAIXksCw
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameRecords.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zz9sxjYwiLC/+U5klXlNsg
/*
 * $Id: GameRecords.h,v 1.13 2003/09/17 19:40:33 southa Exp $
 * $Log: GameRecords.h,v $
 * Revision 1.13  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:53  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.10  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.9  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.7  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/11/24 23:18:24  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.5  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:25  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/24 10:52:47  southa
 * World records
 *
 * Revision 1.2  2002/08/22 10:11:11  southa
 * Save records, spacebar dialogues
 *
 * Revision 1.1  2002/08/19 21:42:38  southa
 * Display of records and lap/split times
 *
 */

#include "InfernalTimer.h"
#include "Mushcore.h"

class GameRecords : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    GameRecords();

    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
    void SplitTimeSet(Mushware::U32 inWhich, InfernalTimer::tMsec inMsec);
    void SplitTimePropose(Mushware::U32 inWhich, InfernalTimer::tMsec inMsec);
    InfernalTimer::tMsec SplitTimeGet(Mushware::U32 inWhich) const;
    bool SplitTimeValid(Mushware::U32 inWhich) const;
    void LapTimeSet(InfernalTimer::tMsec inMsec);
    void LapTimePropose(InfernalTimer::tMsec inMsec);
    InfernalTimer::tMsec LapTimeGet(void) const;
    bool LapTimeValid(void) const;
    void RaceTimeSet(InfernalTimer::tMsec inMsec);
    void RaceTimePropose(InfernalTimer::tMsec inMsec);
    InfernalTimer::tMsec RaceTimeGet(void) const;
    bool RaceTimeValid(void) const;
    bool RecordsPropose(const GameRecords& inRecords);
    void Reset(void);

protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void NullHandler(MushcoreXML& inXML);
    void HandleRecordsStart(MushcoreXML& inXML);
    void HandleSplitTimeEnd(MushcoreXML& inXML);
    void HandleLapTimeEnd(MushcoreXML& inXML);
    void HandleRaceTimeEnd(MushcoreXML& inXML);
    void HandleRecordsEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef std::map<std::string, void (GameRecords::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    // End of pickle
    
    std::vector<InfernalTimer::tMsec> m_splitTimes;
    std::vector<bool> m_splitTimeValid;
    InfernalTimer::tMsec m_lapTime;
    bool m_lapTimeValid;
    InfernalTimer::tMsec m_raceTime;
    bool m_raceTimeValid;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
