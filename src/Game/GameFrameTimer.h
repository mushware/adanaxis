//%includeGuardStart {
#ifndef GAMEFRAMETIMER_H
#define GAMEFRAMETIMER_H
//%includeGuardStart } 14Eb36AGQmpmjTpELmQnZg
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameFrameTimer.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } X7+028vaXXXQGbUppiPRWw
/*
 * $Id: GameFrameTimer.h,v 1.6 2004/01/02 21:13:07 southa Exp $
 * $Log: GameFrameTimer.h,v $
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
