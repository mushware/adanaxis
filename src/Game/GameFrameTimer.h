#ifndef GAMEFRAMETIMER_H
#define GAMEFRAMETIMER_H
/*
 * $Id$
 * $Log$
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
    U32 FrameNumGet(void) const;
    void Reset(void);
    U32 IntegerElapsedFramesGet(void) const;
    void FramesDiscard(void);
    void FramesDone(U32 inFrames);
    tVal PartialFrameGet(void) const;
    tMsec FrameIntervalMsecGet(void) const { return m_frameIntervalUsec / 1000; }
    bool RedisplayGet(void) const;
    void RedisplayDone(void);
    void DisplayedFrameAt(void);
    tVal FrameRateGet(void) const;
    tVal WindbackValueGet(void);
    
private:
    void ReportJitter(void) const;

    tUsec m_currentUsec;
    tUsec m_frameUsec;
    tUsec m_lastFrameUsec;
    tUsec m_averageFrameUsec;
    tUsec m_marginUsec;
    tUsec m_frameIntervalUsec;
    U32 m_frameNum;
    U32 m_lastRedisplayFrameNum;
    
    mutable bool m_jitterReported;
};
#endif
