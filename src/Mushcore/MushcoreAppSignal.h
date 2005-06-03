#ifndef MUSHCOREAPPSIGNAL_H
#define MUSHCOREAPPSIGNAL_H
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
 * $Id: MushcoreAppSignal.h,v 1.2 2003/01/11 13:03:16 southa Exp $
 * $Log: MushcoreAppSignal.h,v $
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
#endif
