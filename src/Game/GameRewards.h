/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameRewards : public CorePickle, protected CoreXMLHandler
{
public:
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual string TypeNameGet(void) {return "dialogue";}

    bool JudgementPass(tVal inRatio);
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void NullHandler(CoreXML& inXML);
    void HandleJudgementEnd(CoreXML& inXML);
    void HandleRewardsEnd(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };
        
    typedef map<string, void (GameRewards::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    // End of pickle

    class TimeJudgement
    {
    public:
        tVal ratio;
        string dialogueName;
    };

    vector<TimeJudgement> m_judgements;
};
