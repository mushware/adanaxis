/*
 * $Id: GameTypeRace.h,v 1.1 2002/08/18 20:44:33 southa Exp $
 * $Log: GameTypeRace.h,v $
 * Revision 1.1  2002/08/18 20:44:33  southa
 * Initial chequepoint work
 *
 */

#include "mushCore.h"
#include "GameType.h"

class GameChequePoint;
class GameEvent;
class GameEventStandingOn;

class GameTypeRace : public GameType
{
public:
    virtual ~GameTypeRace() {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual string TypeNameGet(void) const;
    virtual void Move(void) {}
    virtual void EventHandler(GameEvent& inEvent);
    virtual void SequenceAdvance(void);
    
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
};

inline ostream& operator<<(ostream &inOut, const GameTypeRace& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
