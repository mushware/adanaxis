#ifndef GAMEREWARDS_H
#define GAMEREWARDS_H
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
 * $Id: GameRewards.h,v 1.6 2002/12/20 13:17:42 southa Exp $
 * $Log: GameRewards.h,v $
 * Revision 1.6  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/11/24 23:18:25  southa
 * Added type name accessor to CorePickle
 *
 * Revision 1.4  2002/10/22 20:42:05  southa
 * Source conditioning
 *
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
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;

    
    bool JudgementPass(Mushware::tVal inRatio);
    bool TimeCountdownPass(Mushware::tVal inTime);
    
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
        
    typedef std::map<string, void (GameRewards::*)(CoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    // End of pickle

    class TimeJudgement
    {
    public:
        Mushware::tVal ratio;
        std::string dialogueName;
    };

    class TimedCount
    {
    public:
        Mushware::tVal time;
        std::string dialogueName;
    };

    std::vector<TimeJudgement> m_judgements;
    std::vector<TimedCount> m_times;
    Mushware::tVal m_lastTime;
    Mushware::tVal m_lastTimeValid;
};
#endif
