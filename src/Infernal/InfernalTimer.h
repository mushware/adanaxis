//%includeGuardStart {
#ifndef INFERNALTIMER_H
#define INFERNALTIMER_H
//%includeGuardStart } 8cwcwdNY33jV9WeSsbgB1w
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTimer.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } GZGazlLXHTsci08M+3VEQg
/*
 * $Id: InfernalTimer.h,v 1.21 2003/09/17 19:40:33 southa Exp $
 * $Log: InfernalTimer.h,v $
 * Revision 1.21  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.20  2003/08/21 23:08:57  southa
 * Fixed file headers
 *
 * Revision 1.19  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.18  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.17  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.16  2002/12/10 19:00:17  southa
 * Split timer into client and server
 *
 * Revision 1.15  2002/12/04 15:39:58  southa
 * Multiplayer work
 *
 * Revision 1.14  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.13  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.12  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.11  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.10  2002/10/14 15:13:40  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.9  2002/08/27 08:56:27  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/19 23:11:22  southa
 * Lap and split time tweaks
 *
 * Revision 1.7  2002/08/19 12:54:54  southa
 * Added time format
 *
 * Revision 1.6  2002/08/19 11:09:56  southa
 * GameTypeRace rendering
 *
 * Revision 1.5  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.4  2002/08/05 22:18:35  southa
 * Replaced assertions with error report
 *
 * Revision 1.3  2002/08/05 15:15:21  southa
 * Improved windback and released FPS limit
 *
 * Revision 1.2  2002/08/05 13:37:29  southa
 * Windback work
 *
 * Revision 1.1  2002/08/02 15:20:55  southa
 * Frame rate timing
 *
 */

#include "Mushcore.h"

#include "GameFrameTimer.h"

class InfernalTimer
{
public:
    typedef double tMsec;
    typedef double tUsec;
    
    InfernalTimer();
    
    void CurrentMsecSet(Mushware::U32 inMsec);
    tMsec CurrentMsecGet(void) const;
    void Reset(void);
    bool JudgementValid(void) const;

    GameFrameTimer& ClientGet(void) { return m_clientFrameTimer; }
    GameFrameTimer& ServerGet(void) { return m_serverFrameTimer; }
    const GameFrameTimer& ConstClientGet(void) const { return m_clientFrameTimer; }
    const GameFrameTimer& ConstServerGet(void) const { return m_serverFrameTimer; }
    
    Mushware::tVal Periodic10msGet(void) const;
    void Periodic10msDone(Mushware::tVal inNum);
    Mushware::tVal Periodic100msGet(void) const;
    void Periodic100msDone(Mushware::tVal inNum);
    Mushware::tVal Periodic1sGet(void) const;
    void Periodic1sDone(Mushware::tVal inNum);
    tMsec SleepTimeGet(void) const;
    static std::string MsecToString(tMsec inMsec);
    static std::string MsecDifferenceToString(tMsec inMsec);
    static std::string MsecToLongString(tMsec inMsec);
    
private:
    void ReportJitter(void) const;

    GameFrameTimer m_clientFrameTimer;
    GameFrameTimer m_serverFrameTimer;
    
    tUsec m_currentUsec;
    tUsec m_periodic10msUsec;
    tUsec m_periodic100msUsec;
    tUsec m_periodic1sUsec;
    Mushware::U32 m_lastMsec;
    bool m_timesValid;
    mutable bool m_jitterReported;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
