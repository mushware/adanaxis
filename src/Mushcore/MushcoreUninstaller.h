#ifndef MUSHCOREUNINSTALLER_H
#define MUSHCOREUNINSTALLER_H
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
 * $Id: MushcoreUninstaller.h,v 1.1 2003/01/16 13:11:32 southa Exp $
 * $Log: MushcoreUninstaller.h,v $
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
#endif
