/*
 * $Id: GameTimer.cpp,v 1.2 2002/08/05 13:37:29 southa Exp $
 * $Log: GameTimer.cpp,v $
 * Revision 1.2  2002/08/05 13:37:29  southa
 * Windback work
 *
 * Revision 1.1  2002/08/02 15:20:55  southa
 * Frame rate timing
 *
 */

#include "GameTimer.h"

GameTimer::GameTimer():
    m_motionFrameInterval(10000),
    m_averageFrameDuration(0),
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
    m_lastFrameTime=m_currentTime;
    m_averageFrameDuration=0;
    m_motionMargin=0;
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
    // The state of motion should be between 0 and 1 frames ahead of current
    // time one completion 
    
    double frames;
    modf((m_currentTime - m_motionFrameTime + m_motionMargin) / m_motionFrameInterval, &frames);
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
    COREASSERT(m_motionFrameTime <= m_currentTime + m_motionMargin);
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
    return true;
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
    tVal timeNow = m_currentTime + 1000 * (inMsec - m_lastMsec);
    tVal frameDuration = timeNow - m_lastFrameTime;
    // Keep rolling average of frame duration
    m_averageFrameDuration *=0.9;
    m_averageFrameDuration += 0.1*frameDuration;
    m_lastFrameTime = timeNow;
}

tVal
GameTimer::WindbackValueGet(tMsec inMSec)
{
    // Predict the windback value necessary for a smooth display

    // Abort if we don't have enough information to calculate
    if (!m_timesValid || m_averageFrameDuration == 0)
    {
	return 0;
    }
	
    // First predict the time of the next frame
    tVal timeNow = m_currentTime + 1000 * (inMSec - m_lastMsec);

    // Get the time elapsed since the last frame was displayed
    tVal elapsedTime = timeNow - m_lastFrameTime; 

    // Get the number of frames which have elapsed between then and now
    double elapsedFrames = elapsedTime / m_averageFrameDuration;

    // Round up to an integer
    modf(elapsedFrames+1.0, &elapsedFrames);

    // Predict a display time - when the next frame will be displayed
    tVal displayTime = m_lastFrameTime + m_averageFrameDuration*elapsedFrames; 
    
    // Calculate the windback value for smooth motion
    tVal windbackValue = (m_motionFrameTime - displayTime) / m_motionFrameInterval;

    // Adjust the motion frame margin if necessary to keep the windback value
    // between 0 and 1
    if (windbackValue > 1.0 || windbackValue < 0.0)
    {
	m_motionMargin -= 100.0 * (windbackValue - 0.5);
    }
    // Restrict to sensible values
    if (windbackValue > 1.0) windbackValue = 1.0;
    if (windbackValue < -1.0) windbackValue = -1.0;
    
     
    // cout << "windbackValue=" << windbackValue << endl;
    // cout << "motionMargin=" << m_motionMargin << endl;
 
    
    return windbackValue;
}

    
