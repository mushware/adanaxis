/*
 * $Id$
 * $Log$
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
