#ifndef COREAPPSIGNAL_H
#define COREAPPSIGNAL_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/




/*
 * $Id: CoreAppSignal.h,v 1.4 2002/08/07 13:36:44 southa Exp $
 * $Log: CoreAppSignal.h,v $
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
    
    CoreAppSignal(U32 inSigNumber): m_sigNumber(inSigNumber) {} // for clients
    virtual ~CoreAppSignal() {}
    
    U32 SigNumberGet(void) const {return m_sigNumber;}
    void SigNumberSet(U32 inSigNumber) {m_sigNumber=inSigNumber;}
    bool IsCoreAppSignal(void) const {return m_sigNumber > kMinCoreAppSignal && m_sigNumber < kMaxCoreAppSignal;}

private:
    U32 m_sigNumber;
};
#endif
