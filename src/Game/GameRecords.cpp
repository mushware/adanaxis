/*
 * $Id$
 * $Log$
 */

#include "GameRecords.h"

GameRecords::GameRecords()
{
    Reset();
}

void
GameRecords::SplitTimeSet(U32 inWhich, GameTimer::tMsec inMsec)
{
    if (inWhich >= m_splitTimes.size())
    {
        m_splitTimes.resize(inWhich+1);
        m_splitTimeValid.resize(inWhich+1, false);
    }
    m_splitTimes[inWhich] = inMsec;
    m_splitTimeValid[inWhich] = true;
}

void
GameRecords::SplitTimePropose(U32 inWhich, GameTimer::tMsec inMsec)
{
    if (!SplitTimeValid(inWhich) || inMsec < SplitTimeGet(inWhich))
    {
        SplitTimeSet(inWhich, inMsec);
    }
}

GameTimer::tMsec
GameRecords::SplitTimeGet(U32 inWhich) const
{
    COREASSERT(inWhich < m_splitTimes.size());
    return m_splitTimes[inWhich];
}

bool
GameRecords::SplitTimeValid(U32 inWhich) const
{
    if (inWhich >= m_splitTimeValid.size())
    {
        return false;
    }
    COREASSERT(inWhich < m_splitTimeValid.size());
    return m_splitTimeValid[inWhich];
}

void
GameRecords::LapTimeSet(GameTimer::tMsec inMsec)
{
    m_lapTime = inMsec;
    m_lapTimeValid = true;
}

void
GameRecords::LapTimePropose(GameTimer::tMsec inMsec)
{
    if (!LapTimeValid() || inMsec < LapTimeGet())
    {
        LapTimeSet(inMsec);
    }
}

GameTimer::tMsec
GameRecords::LapTimeGet(void) const
{
    COREASSERT(m_lapTimeValid);
    return m_lapTime;
}

bool
GameRecords::LapTimeValid(void) const
{
    return m_lapTimeValid;
}

void
GameRecords::Reset(void)
{
    m_splitTimes.resize(0);
    m_splitTimeValid.resize(0);
    m_lapTimeValid = false;
}
