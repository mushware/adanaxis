/*
 * $Id$
 * $Log$
 */

#include "MustlStandard.h"

class MustlTimer
{
public:
    typedef unsigned int (*tTimerFunction)(void);
    typedef unsigned long tMsec;

    static inline MustlTimer& Instance(void);

    tMsec CurrentMsecGet(void) const;
    void CurrentMsecSet(tMsec inMsec) { m_currentMsec = inMsec; }
    void TimerFunctionSet(tTimerFunction inFunction) { m_timerFunction = inFunction; }
    
protected:
    MustlTimer() : m_timerFunction(NULL) {}

private:
    tTimerFunction m_timerFunction;
    tMsec m_currentMsec;

    static auto_ptr<MustlTimer> m_instance;
};

inline MustlTimer&
MustlTimer::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MustlTimer);
    return *m_instance;
}

inline MustlTimer::tMsec
MustlTimer::CurrentMsecGet(void) const
{
    if (m_timerFunction != NULL)
    {
        return m_timerFunction();
    }
    return m_currentMsec;
}
