#ifndef MUSTLTIMER_H
#define MUSTLTIMER_H

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
 * $Id: MustlTimer.h,v 1.3 2002/12/20 13:17:46 southa Exp $
 * $Log: MustlTimer.h,v $
 * Revision 1.3  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/13 01:06:54  southa
 * Mustl work
 *
 * Revision 1.1  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 */

#include "MustlStandard.h"

class MustlTimer
{
public:
    typedef unsigned int (*tTimerFunction)(void);

    static inline MustlTimer& Instance(void);

    Mustl::tMsec CurrentMsecGet(void);
    void CurrentMsecSet(Mustl::tMsec inMsec) { m_currentMsec = inMsec; }
    void TimerFunctionSet(tTimerFunction inFunction) { m_timerFunction = inFunction; }
    
protected:
    MustlTimer();

private:
        
    tTimerFunction m_timerFunction;
    Mustl::tMsec m_currentMsec;
    unsigned int m_lastU32Msec;
    
    static std::auto_ptr<MustlTimer> m_instance;
};

inline MustlTimer&
MustlTimer::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MustlTimer);
    return *m_instance;
}

inline Mustl::tMsec
MustlTimer::CurrentMsecGet(void)
{
    if (m_timerFunction != NULL)
    {
        unsigned int u32MsecNow = m_timerFunction();

        // This method takes care of 32 bit wrapping
        m_currentMsec += u32MsecNow - m_lastU32Msec;
        m_lastU32Msec = u32MsecNow;
    }
    return m_currentMsec;
}

#endif
