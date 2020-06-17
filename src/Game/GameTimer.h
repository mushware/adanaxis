//%includeGuardStart {
#ifndef GAMETIMER_H
#define GAMETIMER_H
//%includeGuardStart } 8tZcei9nSmXbMwI0zbZwEw
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameTimer.h
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
//%Header } wLJrzSuCn22S9WkeyHOjaw
/*
 * $Id: GameTimer.h,v 1.27 2006/06/01 15:39:00 southa Exp $
 * $Log: GameTimer.h,v $
 * Revision 1.27  2006/06/01 15:39:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.26  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.25  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.24  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.23  2003/10/04 15:32:09  southa
 * Module split
 *
 * Revision 1.1  2003/10/04 12:23:07  southa
 * File renaming
 *
 * Revision 1.21  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.20  2003/08/21 23:08:57  southa
 * Fixed file headers
 *
 * Revision 1.19  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.18  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.17  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.16  2002/12/10 19:00:17  southa
 * Split timer into client and server
 *
 * Revision 1.15  2002/12/04 15:39:58  southa
 * Multiplayer work
 *
 * Revision 1.14  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.13  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.12  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.11  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.10  2002/10/14 15:13:40  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.9  2002/08/27 08:56:27  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/19 23:11:22  southa
 * Lap and split time tweaks
 *
 * Revision 1.7  2002/08/19 12:54:54  southa
 * Added time format
 *
 * Revision 1.6  2002/08/19 11:09:56  southa
 * InfernalTypeRace rendering
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

#include "mushMushcore.h"

#include "GameFrameTimer.h"

class GameTimer
{
public:
    typedef double tMsec;
    typedef double tUsec;
    
    GameTimer();
    
    void CurrentMsecSet(Mushware::U32 inMsec);
    tMsec CurrentMsecGet(void) const;
    void Reset(void);
    bool JudgementValid(void) const;

    GameFrameTimer& ClientGet(void) { return m_clientFrameTimer; }
    GameFrameTimer& ServerGet(void) { return m_serverFrameTimer; }
    const GameFrameTimer& ConstClientGet(void) const { return m_clientFrameTimer; }
    const GameFrameTimer& ConstServerGet(void) const { return m_serverFrameTimer; }
    
    Mushware::tVal Periodic10msGet(void) const;
    void Periodic10msDone(Mushware::tVal inNum);
    Mushware::tVal Periodic100msGet(void) const;
    void Periodic100msDone(Mushware::tVal inNum);
    Mushware::tVal Periodic1sGet(void) const;
    void Periodic1sDone(Mushware::tVal inNum);
    tMsec SleepTimeGet(void) const;
    static std::string MsecToString(tMsec inMsec);
    static std::string MsecDifferenceToString(tMsec inMsec);
    static std::string MsecToLongString(tMsec inMsec);
    
private:
    void ReportJitter(void) const;

    GameFrameTimer m_clientFrameTimer;
    GameFrameTimer m_serverFrameTimer;
    
    tUsec m_currentUsec;
    tUsec m_periodic10msUsec;
    tUsec m_periodic100msUsec;
    tUsec m_periodic1sUsec;
    Mushware::U32 m_lastMsec;
    bool m_timesValid;
    mutable bool m_jitterReported;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
