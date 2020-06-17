//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameFrameTimer.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } ZqZwR12IPMiP73IOE5eppg
/*
 *  GameFrameTimer.cpp
 *  core-app
 *
 *  Created by Andy Southgate on Tue Dec 10 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#include "GameFrameTimer.h"

#include "GameSTL.h"
#include "GameTimer.h"

using namespace Mushware;
using namespace std;

GameFrameTimer::GameFrameTimer(GameTimer::tUsec inInterval):
    m_averageFrameUsec(0),
    m_frameIntervalUsec(inInterval),
    m_jitterReported(false)
{

}

void
GameFrameTimer::CurrentUsecSet(tUsec inUsec)
{
    m_currentUsec = inUsec;
}

GameFrameTimer::tMsec
GameFrameTimer::GameMsecGet(void) const
{
    return m_frameNum * m_frameIntervalUsec / 1000;
}

U32
GameFrameTimer::FrameNumGet(void) const
{
    return m_frameNum;
}

void
GameFrameTimer::Reset(void)
{
    m_frameUsec = m_currentUsec;
    m_lastFrameUsec = m_currentUsec;
    m_averageFrameUsec = m_frameIntervalUsec;
    m_marginUsec = 0;
    m_frameNum = 0;
    m_lastRedisplayFrameNum = m_frameNum;
}

U32
GameFrameTimer::IntegerElapsedFramesGet(void) const
{
    // Return the integer part of the frame counter
    // The state of motion should be between 0 and 1 frames ahead of current
    // time one completion 
    
    double frames;
    modf((m_currentUsec - m_frameUsec + m_marginUsec) / m_frameIntervalUsec, &frames);
    if (frames < 0)
    {
        frames = 0;
        ReportJitter();
    }
    return static_cast<U32>(frames);
}

void
GameFrameTimer::FramesDiscard(void)
{
    if (m_currentUsec - m_frameUsec + m_marginUsec > m_frameIntervalUsec)
    {
        m_frameUsec = m_currentUsec + m_marginUsec;
    }
}

void
GameFrameTimer::FramesDone(U32 inFrames)
{
    m_frameUsec += inFrames * m_frameIntervalUsec;
    if (m_frameUsec > m_currentUsec + m_marginUsec) ReportJitter();
    m_frameNum += inFrames;
}

tVal
GameFrameTimer::PartialFrameGet(void) const
{
    // Return the fractional part of the frame counter
    double frames;
    return modf((m_currentUsec - m_frameUsec) / m_frameIntervalUsec, &frames);
}

bool
GameFrameTimer::RedisplayGet(void) const
{
    return true;
}

void
GameFrameTimer::RedisplayDone(void)
{
    m_lastRedisplayFrameNum = m_frameNum;
}

void
GameFrameTimer::DisplayedFrameAt(void)
{
    tVal frameDuration = m_currentUsec - m_lastFrameUsec;
    // Keep rolling average of frame duration
    tVal frameRatio = frameDuration / m_averageFrameUsec;
    if (frameDuration < m_averageFrameUsec*1.2)
    {
        m_averageFrameUsec = frameDuration;
        // cerr << "frame duration to " << m_averageFrameDuration << endl;
    }
    else if (frameRatio > 1.9 && frameRatio < 2.1)
    {
        // Doubled frame
    }
    else
    {
        m_averageFrameUsec *=0.9;
        m_averageFrameUsec += 0.1*frameDuration;
    }
    m_lastFrameUsec = m_currentUsec;
}

tVal
GameFrameTimer::FrameRateGet(void) const
{
    return 1e6 / m_averageFrameUsec;
}

tVal
GameFrameTimer::WindbackValueGet(void)
{
    // Predict the windback value necessary for a smooth display

    // Abort if we don't have enough information to calculate
    if (m_averageFrameUsec == 0)
    {
  	    return 0;
    }
	
    // Get the time elapsed since the last frame was displayed
    tVal elapsedTime = m_currentUsec - m_lastFrameUsec; 

    // Get the number of frames which have elapsed between then and now
    double elapsedFrames = elapsedTime / m_averageFrameUsec;

    // Round up to an integer
    modf(elapsedFrames+1.0, &elapsedFrames);

    // Predict a display time - when the next frame will be displayed
    tVal displayTime = m_lastFrameUsec + m_averageFrameUsec * elapsedFrames; 
    
    // Calculate the windback value for smooth motion
    tVal windbackValue = (m_frameUsec - displayTime) / m_frameIntervalUsec;

    // Adjust the motion frame margin if necessary to keep the windback value
    // between 0 and 1
    m_marginUsec -= 100.0 * (windbackValue - 0.5) * fabs(windbackValue - 0.5);

    //cout << "windbackValue=" << windbackValue << endl;
    //cout << "motionMargin=" << m_motionMargin << endl;

    // Restrict to sensible values
    if (windbackValue > 1.0) windbackValue = 1.0;
    if (windbackValue < 0) windbackValue = 0;

    //if (m_motionMargin < 0) m_motionMargin = 0;
    if (m_marginUsec > 200000)
    {
        // Give up partial frame compensation at this point
        m_marginUsec = 200000;
        windbackValue=0;
    }
    
    return windbackValue;
}

void
GameFrameTimer::ReportJitter(void) const
{
    if (!m_jitterReported)
    {
        cerr << "Frame timing jitter detected" << endl;
        m_jitterReported = true;
    }
}
