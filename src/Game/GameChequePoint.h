/*
 * $Id: GameChequePoint.h,v 1.1 2002/08/18 20:44:33 southa Exp $
 * $Log: GameChequePoint.h,v $
 * Revision 1.1  2002/08/18 20:44:33  southa
 * Initial chequepoint work
 *
 */

#include "mushCore.h"

class GameEventStandingOn;

class GameChequePoint : public CorePickle, protected CoreXMLHandler
{
public:
    virtual ~GameChequePoint() {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual string TypeNameGet(void) const;
    U32 SequenceGet(void) { return m_sequence; }
    tVal TimeGet(void) { return m_time; }
    void StandingOnHandler(const GameEventStandingOn& inEvent);
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void Triggered(void);
    
    void HandleSequenceEnd(CoreXML& inXML);
    void HandleMapValueEnd(CoreXML& inXML);
    void HandleActionEnd(CoreXML& inXML);
    void HandleTimeEnd(CoreXML& inXML);
    void HandleChequePointEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef map<string, void (GameChequePoint::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;

    U32 m_sequence;
    vector<U32> m_mapValues;
    string m_action;
    tVal m_time;
};

inline ostream& operator<<(ostream &inOut, const GameChequePoint& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
