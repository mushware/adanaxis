#ifndef GAMEFRAMETIMER_H
#define GAMEFRAMETIMER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameFrameTimer.h,v 1.1 2002/12/10 19:00:17 southa Exp $
 * $Log: GameFrameTimer.h,v $
 * Revision 1.1  2002/12/10 19:00:17  southa
 * Split timer into client and server
 *
 */

#include "mushCore.h"

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
#endif
