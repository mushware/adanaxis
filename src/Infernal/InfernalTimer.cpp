//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTimer.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } k00Y4DtRDLQOwOH+ceaQ4Q
/*
 * $Id: InfernalTimer.cpp,v 1.23 2003/09/17 19:40:33 southa Exp $
 * $Log: InfernalTimer.cpp,v $
 * Revision 1.23  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.22  2003/08/21 23:08:57  southa
 * Fixed file headers
 *
 * Revision 1.21  2003/01/13 14:32:01  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.20  2003/01/12 17:32:56  southa
 * Mushcore work
 *
 * Revision 1.19  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.18  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.17  2002/12/10 19:00:17  southa
 * Split timer into client and server
 *
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

#include "InfernalTimer.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

InfernalTimer::InfernalTimer():
    m_clientFrameTimer(10000),
    m_serverFrameTimer(10000),
    m_timesValid(false),
    m_jitterReported(false)
{

}

void
InfernalTimer::CurrentMsecSet(U32 inMsec)
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

InfernalTimer::tMsec
InfernalTimer::CurrentMsecGet(void) const
{
    if (!m_timesValid)
    {
        throw(MushcoreLogicFail("CurrentMsecGet before Set"));
    }
    return m_currentUsec / 1000;
}

void
InfernalTimer::Reset(void)
{
    m_clientFrameTimer.Reset();
    m_serverFrameTimer.Reset();
    m_periodic10msUsec=m_currentUsec;
    m_periodic100msUsec=m_currentUsec;
    m_periodic1sUsec=m_currentUsec;
}

bool
InfernalTimer::JudgementValid(void) const
{
    return m_timesValid;
}

tVal
InfernalTimer::Periodic10msGet(void) const
{
    double periodics;
    modf((m_currentUsec - m_periodic10msUsec) / 10000, &periodics);
    return periodics;
}

void
InfernalTimer::Periodic10msDone(tVal inNum)
{
    m_periodic10msUsec += 10000*inNum;
    if (m_periodic10msUsec > m_currentUsec) ReportJitter();
}

tVal
InfernalTimer::Periodic100msGet(void) const
{
    double periodics;
    modf((m_currentUsec - m_periodic100msUsec) / 100000, &periodics);
    return periodics;
}

void
InfernalTimer::Periodic100msDone(tVal inNum)
{
    m_periodic100msUsec += 100000*inNum;
    if (m_periodic100msUsec > m_currentUsec) ReportJitter();
}

tVal
InfernalTimer::Periodic1sGet(void) const
{
    double periodics;
    modf((m_currentUsec - m_periodic1sUsec) / 1000000, &periodics);
    return periodics;}

void
InfernalTimer::Periodic1sDone(tVal inNum)
{
    m_periodic1sUsec += 1000000*inNum;
    if (m_periodic1sUsec > m_currentUsec) ReportJitter();
}

InfernalTimer::tMsec
InfernalTimer::SleepTimeGet(void) const
{
    return 0;
}

void
InfernalTimer::ReportJitter(void) const
{
    if (!m_jitterReported)
    {
        cerr << "Timing jitter detected" << endl;
        m_jitterReported = true;
    }
}

string
InfernalTimer::MsecToString(tMsec inMsec)
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
InfernalTimer::MsecDifferenceToString(tMsec inMsec)
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
InfernalTimer::MsecToLongString(tMsec inMsec)
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
