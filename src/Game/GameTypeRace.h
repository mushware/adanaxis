/*
 * $Id: GameTypeRace.h,v 1.2 2002/08/19 11:09:56 southa Exp $
 * $Log: GameTypeRace.h,v $
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
    virtual void Move(void) {}
    virtual void EventHandler(GameEvent& inEvent);
    virtual void SequenceAdvance(void);
    virtual void Render(void) const;
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

    void StandingOnHandler(GameEventStandingOn& inEvent);
    
private:
    void HandleGameEnd(CoreXML& inXML);
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

    U32 m_sequence;
    vector<GameChequePoint *> m_chequePoints;
    GameTimer::tMsec m_startTime;
    GameRecords m_records;
    GameTimer::tMsec m_lapStartTime;
    GameTimer::tMsec m_chequePointTime;
    bool m_raceStarted;
    bool m_lapStartTimeValid;
    bool m_chequePointTimeValid;
};

inline ostream& operator<<(ostream &inOut, const GameTypeRace& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
