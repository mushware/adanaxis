/*
 * $Id: GameRecords.h,v 1.2 2002/08/22 10:11:11 southa Exp $
 * $Log: GameRecords.h,v $
 * Revision 1.2  2002/08/22 10:11:11  southa
 * Save records, spacebar dialogues
 *
 * Revision 1.1  2002/08/19 21:42:38  southa
 * Display of records and lap/split times
 *
 */

#include "mushCore.h"
#include "GameTimer.h"

class GameRecords : public CorePickle, protected CoreXMLHandler
{
public:
    GameRecords();

    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    
    void SplitTimeSet(U32 inWhich, GameTimer::tMsec inMsec);
    void SplitTimePropose(U32 inWhich, GameTimer::tMsec inMsec);
    GameTimer::tMsec SplitTimeGet(U32 inWhich) const;
    bool SplitTimeValid(U32 inWhich) const;
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

    typedef map<string, void (GameRecords::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    // End of pickle
    
    vector<GameTimer::tMsec> m_splitTimes;
    vector<bool> m_splitTimeValid;
    GameTimer::tMsec m_lapTime;
    bool m_lapTimeValid;
    GameTimer::tMsec m_raceTime;
    bool m_raceTimeValid;
};
