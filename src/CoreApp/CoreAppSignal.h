#ifndef COREAPPSIGNAL_H
#define COREAPPSIGNAL_H
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
 * $Id: CoreAppSignal.h,v 1.6 2002/10/22 20:41:57 southa Exp $
 * $Log: CoreAppSignal.h,v $
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

#include "CoreStandard.h"

class CoreAppSignal
{
public:
    enum CoreAppSigNumber
    {
        kMinCoreAppSignal=0,
        kNone,
        kInvalid,
        kQuit,
        kEscape,
        kMaxCoreAppSignal
    };
    
    CoreAppSignal(Mushware::U32 inSigNumber): m_sigNumber(inSigNumber) {} // for clients
    virtual ~CoreAppSignal() {}
    
    Mushware::U32 SigNumberGet(void) const {return m_sigNumber;}
    void SigNumberSet(Mushware::U32 inSigNumber) {m_sigNumber=inSigNumber;}
    bool IsCoreAppSignal(void) const {return m_sigNumber > kMinCoreAppSignal && m_sigNumber < kMaxCoreAppSignal;}

private:
    Mushware::U32 m_sigNumber;
};
#endif
