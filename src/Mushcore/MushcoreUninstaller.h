//%includeGuardStart {
#ifndef MUSHCOREUNINSTALLER_H
#define MUSHCOREUNINSTALLER_H
//%includeGuardStart } cFU56FVESgEuVAI3NNEVZw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreUninstaller.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } OzhlHm3EFjj1GmkTC0ygrA
/*
 * $Id: MushcoreUninstaller.h,v 1.3 2003/08/21 23:09:18 southa Exp $
 * $Log: MushcoreUninstaller.h,v $
 * Revision 1.3  2003/08/21 23:09:18  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.1  2003/01/16 13:11:32  southa
 * Install and uninstall MustlPlatform
 *
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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
