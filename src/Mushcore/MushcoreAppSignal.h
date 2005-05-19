//%includeGuardStart {
#ifndef MUSHCOREAPPSIGNAL_H
#define MUSHCOREAPPSIGNAL_H
//%includeGuardStart } sxQ+5UlqoMWb/uAPaQW/yw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAppSignal.h
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
//%Header } hF/ZwAC0c9tBLbOM2+OucA
/*
 * $Id: MushcoreAppSignal.h,v 1.6 2004/01/02 21:13:12 southa Exp $
 * $Log: MushcoreAppSignal.h,v $
 * Revision 1.6  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.5  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:04  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/31 15:18:15  southa
 * Keyboard reading
 *
 */

#include "MushcoreStandard.h"

class MushcoreAppSignal
{
public:
    enum MushcoreAppSigNumber
    {
        kMinMushcoreAppSignal=0,
        kInvalid,
        kNone,
        kQuit,
        kEscape,
        kMaxMushcoreAppSignal
    };
    
    MushcoreAppSignal(Mushware::U32 inSigNumber): m_sigNumber(inSigNumber) {} // for clients
    virtual ~MushcoreAppSignal();
    
    Mushware::U32 SigNumberGet(void) const { return m_sigNumber; }
    void SigNumberSet(Mushware::U32 inSigNumber) { m_sigNumber=inSigNumber; }
    bool IsMushcoreAppSignal(void) const;

private:
    Mushware::U32 m_sigNumber;
};

inline bool
MushcoreAppSignal::IsMushcoreAppSignal(void) const
{
    return m_sigNumber > kMinMushcoreAppSignal && m_sigNumber < kMaxMushcoreAppSignal;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
