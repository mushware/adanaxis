//%includeGuardStart {
#ifndef GAMEREWARDS_H
#define GAMEREWARDS_H
//%includeGuardStart } X8QK/A4gGDCWC+ItBQXJ0w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameRewards.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } aTSEw63LKX3T/DKXT8IarQ
/*
 * $Id: GameRewards.h,v 1.14 2003/10/04 18:12:13 southa Exp $
 * $Log: GameRewards.h,v $
 * Revision 1.14  2003/10/04 18:12:13  southa
 * Readded
 *
 * Revision 1.12  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.11  2003/08/21 23:08:53  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.9  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.8  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.6  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/11/24 23:18:25  southa
 * Added type name accessor to MushcorePickle
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

#include "Mushcore.h"

class GameRewards : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    GameRewards(): m_lastTimeValid(false) {}
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;

    
    bool JudgementPass(Mushware::tVal inRatio);
    bool TimeCountdownPass(Mushware::tVal inTime);
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void NullHandler(MushcoreXML& inXML);
    void HandleJudgementEnd(MushcoreXML& inXML);
    void HandleTimedEnd(MushcoreXML& inXML);
    void HandleRewardsEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };
        
    typedef std::map<std::string, void (GameRewards::*)(MushcoreXML& inXML)> ElementFunctionMap;
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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
