/*
 * $Id$
 * $Log$
 */

#include "MushcoreStandard.h"

// Functions passed to MushcoreUninstaller are called with the global
// destructors at application exit, so should not throw exceptions
// or cause global objects to be created
class MushcoreUninstaller
{
public:
    typedef void (*tFuncPtr)(void);
    
    MushcoreUninstaller(tFuncPtr inFuncPtr);
    ~MushcoreUninstaller();
    void NullFunction(void) const;

private:
    tFuncPtr m_funcPtr;
};
