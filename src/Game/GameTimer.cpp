/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameTimer.cpp,v 1.12 2002/10/14 18:13:18 southa Exp $
 * $Log: GameTimer.cpp,v $
 * Revision 1.12  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 * Revision 1.11  2002/10/14 15:13:40  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.10  2002/08/27 08:56:27  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/19 23:11:22  southa
 * Lap and split time tweaks
 *
 * Revision 1.8  2002/08/19 12:54:54  southa
 * Added time format
 *
 * Revision 1.7  2002/08/19 11:09:56  southa
 * GameTypeRace rendering
 *
 * Revision 1.6  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.5  2002/08/05 22:18:35  southa
 * Replaced assertions with error report
 *
 * Revision 1.4  2002/08/05 16:14:18  southa
 * Windback at low frame rates
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

#include "GameTimer.h"

GameTimer::GameTimer():
    m_motionFrameInterval(10000),
    m_averageFrameDuration(0),
    m_timesValid(false),
    m_jitterReported(false)
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

GameTimer::tMsec
GameTimer::CurrentMsecGet(void) const
{
    if (!m_timesValid)
    {
        throw(LogicFail("CurrentMsecGet before Set"));
    }
    return m_currentTime / 1000;
}

GameTimer::tMsec
GameTimer::GameMsecGet(void) const
{
    if (!m_timesValid)
    {
        throw(LogicFail("GameMsecGet before Set"));
    }
    return m_currentMotionFrame * m_motionFrameInterval / 1000;
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
    m_averageFrameDuration=10000;
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
    if (m_currentTime - m_motionFrameTime + m_motionMargin > m_motionFrameInterval)
    {
        m_motionFrameTime = m_currentTime + m_motionMargin;
    }
}

void
GameTimer::MotionFramesDone(tVal inFrames)
{
    m_motionFrameTime += inFrames * m_motionFrameInterval;
    if (m_motionFrameTime > m_currentTime + m_motionMargin) ReportJitter();
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
    if (m_periodic10msTime > m_currentTime) ReportJitter();
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
    if (m_periodic1sTime > m_currentTime) ReportJitter();
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
    tVal frameRatio = frameDuration / m_averageFrameDuration;
    if (frameDuration < m_averageFrameDuration*1.2)
    {
        m_averageFrameDuration = frameDuration;
        // cerr << "frame duration to " << m_averageFrameDuration << endl;
    }
    else if (frameRatio > 1.9 && frameRatio < 2.1)
    {
        // Doubled frame
    }
    else
    {
        m_averageFrameDuration *=0.9;
        m_averageFrameDuration += 0.1*frameDuration;
    }
    m_lastFrameTime = timeNow;
}

tVal
GameTimer::FrameRateGet(void)
{
    return 1e6 / m_averageFrameDuration;
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
    m_motionMargin -= 100.0 * (windbackValue - 0.5) * fabs(windbackValue - 0.5);

    //cout << "windbackValue=" << windbackValue << endl;
    //cout << "motionMargin=" << m_motionMargin << endl;

    // Restrict to sensible values
    if (windbackValue > 1.0) windbackValue = 1.0;
    if (windbackValue < 0) windbackValue = 0;

    //if (m_motionMargin < 0) m_motionMargin = 0;
    if (m_motionMargin > 200000)
    {
        // Give up partial frame compensation at this point
        m_motionMargin = 200000;
        windbackValue=0;
    }
    
    return windbackValue;
}

void
GameTimer::ReportJitter(void)
{
    if (!m_jitterReported)
    {
        cerr << "Timing jitter detected" << endl;
        m_jitterReported = true;
    }
}

string
GameTimer::MsecToString(tMsec inMsec)
{
    tVal msec=inMsec;
    if (msec < 0) msec=-msec;

    double minutes = msec / 60000.0;
    double seconds = 60*modf(minutes, &minutes);
    double centiseconds = 100*modf(seconds, &seconds);
    modf(centiseconds, &centiseconds);
    
    char buffer[256];
    if (inMsec < 0.0)
    {
        if (minutes > 0.0)
        {
            sprintf(buffer, "-%.0f:%02.0f.%02.0f", minutes, seconds, centiseconds);
        }
        else
        {
            sprintf(buffer, "-%.0f.%02.0f", seconds, centiseconds);
        }
    }
    else
    {
        if (minutes > 0.0)
        {
            sprintf(buffer, "%.0f:%02.0f.%02.0f", minutes, seconds, centiseconds);
        }
        else
        {
            sprintf(buffer, "%.0f.%02.0f", seconds, centiseconds);
        }
    }        
    return string(buffer);
}

string
GameTimer::MsecDifferenceToString(tMsec inMsec)
{
    tVal msec=inMsec;
    if (msec < 0) msec=-msec;

    double minutes = msec / 60000.0;
    double seconds = 60*modf(minutes, &minutes);
    double centiseconds = 100*modf(seconds, &seconds);
    modf(centiseconds, &centiseconds);
    
    char buffer[256];
    if (inMsec < 0.0)
    {
        if (minutes > 0.0)
        {
            sprintf(buffer, "-%.0f:%02.0f.%02.0f", minutes, seconds, centiseconds);
        }
        else
        {
            sprintf(buffer, "-%.0f.%02.0f", seconds, centiseconds);
        }
    }
    else
    {
        if (minutes > 0.0)
        {
            sprintf(buffer, "+%.0f:%02.0f.%02.0f", minutes, seconds, centiseconds);
        }
        else
        {
            sprintf(buffer, "+%.0f.%02.0f", seconds, centiseconds);
        }
    }        
    return string(buffer);
}

string
GameTimer::MsecToLongString(tMsec inMsec)
{
    tVal msec=inMsec;
    if (msec < 0) msec=-msec;

    double minutes = msec / 60000.0;
    double seconds = 60*modf(minutes, &minutes);
    double centiseconds = 100*modf(seconds, &seconds);
    modf(centiseconds, &centiseconds);
    
    char buffer[256];
    if (inMsec < 0.0)
    {
        sprintf(buffer, "-%.0f:%02.0f.%02.0f", minutes, seconds, centiseconds);
    }
    else
    {
        sprintf(buffer, "%.0f:%02.0f.%02.0f", minutes, seconds, centiseconds);
    }
    return string(buffer);
}
