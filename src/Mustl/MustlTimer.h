//%includeGuardStart {
#ifndef MUSTLTIMER_H
#define MUSTLTIMER_H
//%includeGuardStart } TVxWdrQ0ln2K/vcPFiAzcQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlTimer.h
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } gHzGjr8JyQ19nPyoX1N5wg

/*
 * $Id: MustlTimer.h,v 1.6 2003/08/21 23:09:32 southa Exp $
 * $Log: MustlTimer.h,v $
 * Revision 1.6  2003/08/21 23:09:32  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.4  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
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

#include "MustlMushcoreSingleton.h"

class MustlTimer : public MushcoreSingleton<MustlTimer>
{
public:
    typedef unsigned int (*tTimerFunction)(void);

    MustlTimer();
    Mustl::tMsec CurrentMsecGet(void);
    void CurrentMsecSet(Mustl::tMsec inMsec) { m_currentMsec = inMsec; }
    void TimerFunctionSet(tTimerFunction inFunction) { m_timerFunction = inFunction; }
    
protected:

private:
        
    tTimerFunction m_timerFunction;
    Mustl::tMsec m_currentMsec;
    unsigned int m_lastU32Msec;
};

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

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
