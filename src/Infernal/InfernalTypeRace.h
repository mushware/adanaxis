//%includeGuardStart {
#ifndef INFERNALTYPERACE_H
#define INFERNALTYPERACE_H
//%includeGuardStart } rlnnLu8XDMRMTMH2QxvAEQ
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTypeRace.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } X1RATzga0rf/+/fPBcyCog
/*
 * $Id: InfernalTypeRace.h,v 1.6 2006/06/01 15:39:08 southa Exp $
 * $Log: InfernalTypeRace.h,v $
 * Revision 1.6  2006/06/01 15:39:08  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 * Revision 1.1  2003/10/04 15:32:12  southa
 * Module split
 *
 * Revision 1.23  2003/10/04 12:23:04  southa
 * File renaming
 *
 * Revision 1.22  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.21  2003/08/21 23:08:58  southa
 * Fixed file headers
 *
 * Revision 1.20  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.19  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.18  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.17  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.16  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.15  2002/11/24 23:18:26  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.14  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.13  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/24 15:42:24  southa
 * Race state change
 *
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
 * InfernalTypeRace state tweaks
 *
 * Revision 1.6  2002/08/21 15:39:01  southa
 * InfernalTypeRace states
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
 * InfernalTypeRace rendering
 *
 * Revision 1.1  2002/08/18 20:51:09  southa
 * Moved
 *
 * Revision 1.1  2002/08/18 20:44:33  southa
 * Initial chequepoint work
 *
 */

#include "mushMushcore.h"

#include "mushGame.h"

class InfernalChequePoint;
class InfernalEvent;
class InfernalEventStandingOn;

class InfernalTypeRace : public GameType
{
public:
    InfernalTypeRace();
    virtual ~InfernalTypeRace() {}
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
    virtual void Move(void);
    virtual void EventHandler(const GameEvent& inEvent);
    virtual void Render(void) const;
    virtual void Initialise(void);
    virtual bool IsGameOver(void) const;
        
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

    virtual void StandingOnHandler(const InfernalEventStandingOn& inEvent);
    virtual void RewardHandler(const GameEventReward& inEvent);
    
private:
    void HandleGameEnd(MushcoreXML& inXML);
    void HandleLapTimeEnd(MushcoreXML& inXML);
    void HandleStartActionEnd(MushcoreXML& inXML);
    void HandleFinalLapActionEnd(MushcoreXML& inXML);
    void HandleWinActionEnd(MushcoreXML& inXML);
    void HandleLoseActionEnd(MushcoreXML& inXML);
    void HandleInitialTimeEnd(MushcoreXML& inXML);
    void HandleLapsEnd(MushcoreXML& inXML);
    void HandleChequePointStart(MushcoreXML& inXML);
    void NullHandler(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };
    
    typedef std::map<std::string, void (InfernalTypeRace::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
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

    Mushware::U32 m_sequence;
    std::vector<InfernalChequePoint *> m_chequePoints;
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
    std::string m_startAction;
    std::string m_finalLapAction;
    std::string m_winAction;
    std::string m_loseAction;
    Mushware::U32 m_laps;
    Mushware::U32 m_lapCount;
    Mushware::tVal m_initialTime;
    Mushware::tVal m_resultAlpha;
};

inline std::ostream& operator<<(std::ostream &inOut, const InfernalTypeRace& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
