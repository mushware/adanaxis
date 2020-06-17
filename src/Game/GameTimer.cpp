//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameTimer.cpp
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
//%Header } 2jf0+kgarmeTeiGxK39oAQ
/*
 * $Id: GameTimer.cpp,v 1.28 2006/06/01 15:39:00 southa Exp $
 * $Log: GameTimer.cpp,v $
 * Revision 1.28  2006/06/01 15:39:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.27  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.26  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.25  2003/10/04 15:32:09  southa
 * Module split
 *
 * Revision 1.1  2003/10/04 12:23:07  southa
 * File renaming
 *
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
 * InfernalTypeRace rendering
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

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

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
        throw(MushcoreLogicFail("CurrentMsecGet before Set"));
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
