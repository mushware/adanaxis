#ifndef GAMETIMER_H
#define GAMETIMER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameTimer.h,v 1.6 2002/08/19 11:09:56 southa Exp $
 * $Log: GameTimer.h,v $
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

class GameTimer
{
public:
    typedef double tMsec;
    typedef double tUsec;
    
    GameTimer();
    
    void CurrentMsecSet(U32 inMsec);
    tMsec CurrentMsecGet(void) const;
    tMsec GameMsecGet(void) const;
    void Reset(void);
    bool JudgementValid(void) const;
    tVal MotionFramesGet(void) const;
    void MotionFramesDiscard(void);
    void MotionFramesDone(tVal inFrames);
    tVal PartialMotionFrameGet(void) const;
    bool RedisplayGet(void) const;
    void RedisplayDone(void);
    tVal Periodic10msGet(void) const;
    void Periodic10msDone(tVal inNum);
    tVal Periodic1sGet(void) const;
    void Periodic1sDone(tVal inNum);
    tMsec SleepTimeGet(void) const;
    void DisplayedFrameAt(tMsec inMsec);
    tVal WindbackValueGet(tMsec inMSec);
    static string MsecToString(tMsec inMsec);
    static string MsecToLongString(tMsec inMsec);
    
private:
    void ReportJitter(void);
    
    tUsec m_currentTime;
    tUsec m_motionFrameTime;
    tUsec m_periodic10msTime;
    tUsec m_periodic1sTime;
    tUsec m_motionFrameInterval;
    tUsec m_currentMotionFrame;
    tUsec m_lastRedisplayMotionFrame;
    tUsec m_lastFrameTime;
    tUsec m_averageFrameDuration;
    tUsec m_motionMargin;
    U32 m_lastMsec;
    bool m_timesValid;
    bool m_jitterReported;
};
#endif
