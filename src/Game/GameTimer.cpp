/*
 * $Id$
 * $Log$
 */

#include "GameTimer.h"

GameTimer::GameTimer():
    m_motionFrameInterval(10000),
    m_timesValid(false)
{

}

void
GameTimer::CurrentMsecSet(tMsec inMsec)
{
    m_currentTime = inMsec*1000;
    if (!m_timesValid)
    {
        Reset();
        m_timesValid=true;
    }
}

void
GameTimer::Reset(void)
{
    m_motionFrameTime=m_currentTime;
    m_periodic10msTime=m_currentTime;
    m_periodic1sTime=m_currentTime;
    m_currentMotionFrame=0;
    m_lastRedisplayMotionFrame=m_currentMotionFrame;
}

bool
GameTimer::JudgementValid(void) const
{
    return m_timesValid;
}

tVal
GameTimer::MotionFramesGet(void) const
{
    double frames;
    modf((m_currentTime - m_motionFrameTime) / m_motionFrameInterval, &frames);
    return frames;
}

void
GameTimer::MotionFramesDiscard(void)
{
    while (m_currentTime - m_motionFrameTime > m_motionFrameInterval)
    {
        m_motionFrameTime += m_motionFrameInterval;
    }
}

void
GameTimer::MotionFramesDone(tVal inFrames)
{
    m_motionFrameTime += inFrames * m_motionFrameInterval;
    COREASSERT(m_motionFrameTime <= m_currentTime);
    m_currentMotionFrame+=inFrames;
}

tVal
GameTimer::PartialMotionFrameGet(void) const
{
    return 0;
}

void
GameTimer::PartialMotionFrameDone(tVal inFrame)
{
}

bool
GameTimer::RedisplayGet(void) const
{
    return (m_lastRedisplayMotionFrame != m_currentMotionFrame);
}

void
GameTimer::RedisplayDone(void)
{
    m_lastRedisplayMotionFrame=m_currentMotionFrame;
}

tVal
GameTimer::Periodic10msGet(void) const
{
    double periodics;
    modf((m_currentTime - m_periodic10msTime) / 10000, &periodics);
    return periodics;
}

void
GameTimer::Periodic10msDone(tVal inNum)
{
    m_periodic10msTime += 10000*inNum;
    COREASSERT(m_periodic10msTime <= m_currentTime);
}

tVal
GameTimer::Periodic1sGet(void) const
{
    double periodics;
    modf((m_currentTime - m_periodic1sTime) / 1000000, &periodics);
    return periodics;}

void
GameTimer::Periodic1sDone(tVal inNum)
{
    m_periodic1sTime += 1000000*inNum;
    COREASSERT(m_periodic1sTime <= m_currentTime);
}

GameTimer::tMsec
GameTimer::SleepTimeGet(void) const
{
    return 0;
}

void
GameTimer::DisplayedFrameAt(tMsec inMsec)
{

}