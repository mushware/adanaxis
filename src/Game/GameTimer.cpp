/*
 * $Id: GameTimer.cpp,v 1.1 2002/08/02 15:20:55 southa Exp $
 * $Log: GameTimer.cpp,v $
 * Revision 1.1  2002/08/02 15:20:55  southa
 * Frame rate timing
 *
 */

#include "GameTimer.h"

GameTimer::GameTimer():
    m_motionFrameInterval(10000),
    m_timesValid(false)
{

}

void
GameTimer::CurrentMsecSet(U32 inMsec)
{
    if (!m_timesValid)
    {
        m_currentTime = inMsec*1000;
        Reset();
        m_timesValid=true;
    }
    else
    {
        // Increment currentTime in a wraparound-safe way
        m_currentTime += 1000 * (inMsec - m_lastMsec);
    }
    m_lastMsec = inMsec;
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
    // Return the integer part of the frame counter
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
    // Return the fractional part of the frame counter
    double frames;
    return modf((m_currentTime - m_motionFrameTime) / m_motionFrameInterval, &frames);
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