#ifndef GAMERECORDS_H
#define GAMERECORDS_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameRecords.h,v 1.6 2002/11/24 23:18:24 southa Exp $
 * $Log: GameRecords.h,v $
 * Revision 1.6  2002/11/24 23:18:24  southa
 * Added type name accessor to CorePickle
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

#include "GameTimer.h"
#include "mushCore.h"

class GameRecords : public CorePickle, protected CoreXMLHandler
{
public:
    GameRecords();

    virtual void Pickle(std::ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
    void SplitTimeSet(Mushware::U32 inWhich, GameTimer::tMsec inMsec);
    void SplitTimePropose(Mushware::U32 inWhich, GameTimer::tMsec inMsec);
    GameTimer::tMsec SplitTimeGet(Mushware::U32 inWhich) const;
    bool SplitTimeValid(Mushware::U32 inWhich) const;
    void LapTimeSet(GameTimer::tMsec inMsec);
    void LapTimePropose(GameTimer::tMsec inMsec);
    GameTimer::tMsec LapTimeGet(void) const;
    bool LapTimeValid(void) const;
    void RaceTimeSet(GameTimer::tMsec inMsec);
    void RaceTimePropose(GameTimer::tMsec inMsec);
    GameTimer::tMsec RaceTimeGet(void) const;
    bool RaceTimeValid(void) const;
    bool RecordsPropose(const GameRecords& inRecords);
    void Reset(void);

protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void NullHandler(CoreXML& inXML);
    void HandleRecordsStart(CoreXML& inXML);
    void HandleSplitTimeEnd(CoreXML& inXML);
    void HandleLapTimeEnd(CoreXML& inXML);
    void HandleRaceTimeEnd(CoreXML& inXML);
    void HandleRecordsEnd(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef std::map<string, void (GameRecords::*)(CoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    // End of pickle
    
    std::vector<GameTimer::tMsec> m_splitTimes;
    std::vector<bool> m_splitTimeValid;
    GameTimer::tMsec m_lapTime;
    bool m_lapTimeValid;
    GameTimer::tMsec m_raceTime;
    bool m_raceTimeValid;
};
#endif
