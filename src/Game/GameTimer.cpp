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
 * $Id: GameTimer.cpp,v 1.16 2002/12/04 15:39:58 southa Exp $
 * $Log: GameTimer.cpp,v $
 * Revision 1.16  2002/12/04 15:39:58  southa
 * Multiplayer work
 *
 * Revision 1.15  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.14  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.13  2002/10/22 20:42:06  southa
 * Source conditioning
 *
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
    m_clientFrameTimer(10000),
    m_serverFrameTimer(10000),
    m_timesValid(false),
    m_jitterReported(false)
{

}

void
GameTimer::CurrentMsecSet(U32 inMsec)
{
    if (!m_timesValid)
    {
        m_currentUsec = inMsec*1000;
        Reset();
        m_timesValid=true;
    }
    else
    {
        // Increment currentTime in a wraparound-safe way
        m_currentUsec += 1000 * (inMsec - m_lastMsec);
    }
    m_lastMsec = inMsec;

    m_clientFrameTimer.CurrentUsecSet(m_currentUsec);
    m_serverFrameTimer.CurrentUsecSet(m_currentUsec);
}

GameTimer::tMsec
GameTimer::CurrentMsecGet(void) const
{
    if (!m_timesValid)
    {
        throw(LogicFail("CurrentMsecGet before Set"));
    }
    return m_currentUsec / 1000;
}

void
GameTimer::Reset(void)
{
    m_clientFrameTimer.Reset();
    m_serverFrameTimer.Reset();
    m_periodic10msUsec=m_currentUsec;
    m_periodic100msUsec=m_currentUsec;
    m_periodic1sUsec=m_currentUsec;
}

bool
GameTimer::JudgementValid(void) const
{
    return m_timesValid;
}

tVal
GameTimer::Periodic10msGet(void) const
{
    double periodics;
    modf((m_currentUsec - m_periodic10msUsec) / 10000, &periodics);
    return periodics;
}

void
GameTimer::Periodic10msDone(tVal inNum)
{
    m_periodic10msUsec += 10000*inNum;
    if (m_periodic10msUsec > m_currentUsec) ReportJitter();
}

tVal
GameTimer::Periodic100msGet(void) const
{
    double periodics;
    modf((m_currentUsec - m_periodic100msUsec) / 100000, &periodics);
    return periodics;
}

void
GameTimer::Periodic100msDone(tVal inNum)
{
    m_periodic100msUsec += 100000*inNum;
    if (m_periodic100msUsec > m_currentUsec) ReportJitter();
}

tVal
GameTimer::Periodic1sGet(void) const
{
    double periodics;
    modf((m_currentUsec - m_periodic1sUsec) / 1000000, &periodics);
    return periodics;}

void
GameTimer::Periodic1sDone(tVal inNum)
{
    m_periodic1sUsec += 1000000*inNum;
    if (m_periodic1sUsec > m_currentUsec) ReportJitter();
}

GameTimer::tMsec
GameTimer::SleepTimeGet(void) const
{
    return 0;
}

void
GameTimer::ReportJitter(void) const
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
