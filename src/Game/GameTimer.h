#ifndef GAMETIMER_H
#define GAMETIMER_H
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
 * $Id: GameTimer.h,v 1.16 2002/12/10 19:00:17 southa Exp $
 * $Log: GameTimer.h,v $
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

#include "mushCore.h"

#include "GameFrameTimer.h"

class GameTimer
{
public:
    typedef double tMsec;
    typedef double tUsec;
    
    GameTimer();
    
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
    static string MsecToString(tMsec inMsec);
    static string MsecDifferenceToString(tMsec inMsec);
    static string MsecToLongString(tMsec inMsec);
    
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
#endif
