#ifndef GAMEREWARDS_H
#define GAMEREWARDS_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameRewards.h,v 1.3 2002/08/27 08:56:25 southa Exp $
 * $Log: GameRewards.h,v $
 * Revision 1.3  2002/08/27 08:56:25  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.1  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 */

#include "mushCore.h"

class GameRewards : public CorePickle, protected CoreXMLHandler
{
public:
    GameRewards(): m_lastTimeValid(false) {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual string TypeNameGet(void) {return "rewards";}

    bool JudgementPass(tVal inRatio);
    bool TimeCountdownPass(tVal inTime);
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void NullHandler(CoreXML& inXML);
    void HandleJudgementEnd(CoreXML& inXML);
    void HandleTimedEnd(CoreXML& inXML);
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

    class TimedCount
    {
    public:
        tVal time;
        string dialogueName;
    };

    vector<TimeJudgement> m_judgements;
    vector<TimedCount> m_times;
    tVal m_lastTime;
    tVal m_lastTimeValid;
};
#endif
