#ifndef PLATFORMMISCUTILS_H
#define PLATFORMMISCUTILS_H
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
 *  PlatformMiscUtils.h
 *  core-app
 *
 *  Created by Southa on Tue Jun 11 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#include "mushCore.h"

class PlatformMiscUtils
{
public:
    static string GetApplPath(int argc, char *argv[]);
    static string GetSystemPath(int argc, char *argv[]);
    static void TweakArgs(string& ioString);
    static void Initialise(void);
};
#endif
