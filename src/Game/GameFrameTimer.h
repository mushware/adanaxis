//%includeGuardStart {
#ifndef GAMEFRAMETIMER_H
#define GAMEFRAMETIMER_H
//%includeGuardStart } 14Eb36AGQmpmjTpELmQnZg
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameFrameTimer.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } LyTHDD43vebpVAgJaN0hFQ
/*
 * $Id: GameFrameTimer.h,v 1.7 2004/01/06 20:46:50 southa Exp $
 * $Log: GameFrameTimer.h,v $
 * Revision 1.7  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.6  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.5  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:08:45  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.2  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/10 19:00:17  southa
 * Split timer into client and server
 *
 */

#include "mushMushcore.h"

class GameFrameTimer
{
public:
    typedef double tMsec;
    typedef double tUsec;
    
    explicit GameFrameTimer(tUsec inInterval);

    void CurrentUsecSet(tUsec inUsec);
    tMsec GameMsecGet(void) const;
    Mushware::U32 FrameNumGet(void) const;
    void Reset(void);
    Mushware::U32 IntegerElapsedFramesGet(void) const;
    void FramesDiscard(void);
    void FramesDone(Mushware::U32 inFrames);
    Mushware::tVal PartialFrameGet(void) const;
    tMsec FrameIntervalMsecGet(void) const { return m_frameIntervalUsec / 1000; }
    bool RedisplayGet(void) const;
    void RedisplayDone(void);
    void DisplayedFrameAt(void);
    Mushware::tVal FrameRateGet(void) const;
    Mushware::tVal WindbackValueGet(void);
    
private:
    void ReportJitter(void) const;

    tUsec m_currentUsec;
    tUsec m_frameUsec;
    tUsec m_lastFrameUsec;
    tUsec m_averageFrameUsec;
    tUsec m_marginUsec;
    tUsec m_frameIntervalUsec;
    Mushware::U32 m_frameNum;
    Mushware::U32 m_lastRedisplayFrameNum;
    
    mutable bool m_jitterReported;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
