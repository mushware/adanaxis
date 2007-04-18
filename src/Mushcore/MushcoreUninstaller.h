//%includeGuardStart {
#ifndef MUSHCOREUNINSTALLER_H
#define MUSHCOREUNINSTALLER_H
//%includeGuardStart } cFU56FVESgEuVAI3NNEVZw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreUninstaller.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } 4yo+dhpkU9YYIl7EGhkwkg
/*
 * $Id: MushcoreUninstaller.h,v 1.8 2006/06/01 15:39:48 southa Exp $
 * $Log: MushcoreUninstaller.h,v $
 * Revision 1.8  2006/06/01 15:39:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.6  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
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

#include "MushcoreFail.h"

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
    MUSHCORE_NOCOPY(MushcoreUninstaller);
    tFuncPtr m_funcPtr;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
