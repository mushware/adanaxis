#ifndef GAMETIMER_H
#define GAMETIMER_H
/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameTimer
{
public:
    typedef double tMsec;
    typedef double tUsec;

    GameTimer();
    
    void CurrentMsecSet(tMsec inMsec);
    void Reset(void);
    bool JudgementValid(void) const;
    tVal MotionFramesGet(void) const;
    void MotionFramesDiscard(void);
    void MotionFramesDone(tVal inFrames);
    tVal PartialMotionFrameGet(void) const;
    void PartialMotionFrameDone(tVal inFrame);
    bool RedisplayGet(void) const;
    void RedisplayDone(void);
    tVal Periodic10msGet(void) const;
    void Periodic10msDone(tVal inNum);
    tVal Periodic1sGet(void) const;
    void Periodic1sDone(tVal inNum);
    tMsec SleepTimeGet(void) const;
    void DisplayedFrameAt(tMsec inMsec);

private:
    tUsec m_currentTime;
    tUsec m_motionFrameTime;
    tUsec m_periodic10msTime;
    tUsec m_periodic1sTime;
    tUsec m_motionFrameInterval;
    tUsec m_currentMotionFrame;
    tUsec m_lastRedisplayMotionFrame;
    bool m_timesValid;
};
#endif
