/*
 * $Id: GameTypeRace.h,v 1.11 2002/08/24 10:52:47 southa Exp $
 * $Log: GameTypeRace.h,v $
 * Revision 1.11  2002/08/24 10:52:47  southa
 * World records
 *
 * Revision 1.10  2002/08/22 10:11:12  southa
 * Save records, spacebar dialogues
 *
 * Revision 1.9  2002/08/21 19:48:42  southa
 * Race result tweaking
 *
 * Revision 1.8  2002/08/21 16:53:46  southa
 * Win and lose handling
 *
 * Revision 1.7  2002/08/21 16:09:04  southa
 * GameTypeRace state tweaks
 *
 * Revision 1.6  2002/08/21 15:39:01  southa
 * GameTypeRace states
 *
 * Revision 1.5  2002/08/21 10:12:21  southa
 * Time down counter
 *
 * Revision 1.4  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 * Revision 1.3  2002/08/19 21:42:38  southa
 * Display of records and lap/split times
 *
 * Revision 1.2  2002/08/19 11:09:56  southa
 * GameTypeRace rendering
 *
 * Revision 1.1  2002/08/18 20:51:09  southa
 * Moved
 *
 * Revision 1.1  2002/08/18 20:44:33  southa
 * Initial chequepoint work
 *
 */

#include "mushCore.h"
#include "GameType.h"
#include "GameTimer.h"
#include "GameRecords.h"

class GameChequePoint;
class GameEvent;
class GameEventStandingOn;

class GameTypeRace : public GameType
{
public:
    GameTypeRace();
    virtual ~GameTypeRace() {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual string TypeNameGet(void) const;
    virtual void Move(void);
    virtual void EventHandler(const GameEvent& inEvent);
    virtual void Render(void) const;
    virtual void Initialise(void);
    virtual bool IsGameOver(void) const;
        
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

    void StandingOnHandler(const GameEventStandingOn& inEvent);
    
private:
    void HandleGameEnd(CoreXML& inXML);
    void HandleLapTimeEnd(CoreXML& inXML);
    void HandleStartActionEnd(CoreXML& inXML);
    void HandleFinalLapActionEnd(CoreXML& inXML);
    void HandleWinActionEnd(CoreXML& inXML);
    void HandleLoseActionEnd(CoreXML& inXML);
    void HandleInitialTimeEnd(CoreXML& inXML);
    void HandleLapsEnd(CoreXML& inXML);
    void HandleChequePointStart(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };
    
    typedef map<string, void (GameTypeRace::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;

    // End of pickle
    enum RaceState
    {
        kInvalid,
        kPrelude,
        kRunning,
	    kPreResult,
        kResult
    };

    void SequenceAdvance(void);
    void UpdateTimes(void);
    void RenderTimes(void) const;
    void RenderResult(void) const;
    void RaceFinished(void);
    void LoadRecords(void);
    void SaveRecords(const GameRecords& inRecords) const;

    U32 m_sequence;
    vector<GameChequePoint *> m_chequePoints;
    GameRecords m_records;
    GameRecords m_worldRecords;
    GameTimer::tMsec m_startTime;
    GameTimer::tMsec m_endTime;
    GameTimer::tMsec m_lapStartTime;
    GameTimer::tMsec m_chequePointTime;
    GameTimer::tMsec m_dispRemaining;
    GameTimer::tMsec m_dispLap;
    GameTimer::tMsec m_dispSplit;
    GameTimer::tMsec m_lapParTime;
    GameTimer::tMsec m_timeAllowance;
    RaceState m_raceState;
    bool m_lapStartTimeValid;
    bool m_chequePointTimeValid;
    string m_startAction;
    string m_finalLapAction;
    string m_winAction;
    string m_loseAction;
    U32 m_laps;
    U32 m_lapCount;
    tVal m_initialTime;
    tVal m_resultAlpha;
};

inline ostream& operator<<(ostream &inOut, const GameTypeRace& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
