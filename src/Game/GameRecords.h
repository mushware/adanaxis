/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"
#include "GameTimer.h"

class GameRecords
{
public:
    GameRecords();
    void SplitTimeSet(U32 inWhich, GameTimer::tMsec inMsec);
    void SplitTimePropose(U32 inWhich, GameTimer::tMsec inMsec);
    GameTimer::tMsec SplitTimeGet(U32 inWhich) const;
    bool SplitTimeValid(U32 inWhich) const;
    void LapTimeSet(GameTimer::tMsec inMsec);
    void LapTimePropose(GameTimer::tMsec inMsec);
    GameTimer::tMsec LapTimeGet(void) const;
    bool LapTimeValid(void) const;
    void Reset(void);
    
private:
    vector<GameTimer::tMsec> m_splitTimes;
    vector<bool> m_splitTimeValid;
    GameTimer::tMsec m_lapTime;
    bool m_lapTimeValid;
};
