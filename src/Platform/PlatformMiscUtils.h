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
 * $Id: PlatformMiscUtils.h,v 1.8 2002/10/15 14:02:31 southa Exp $
 * $Log: PlatformMiscUtils.h,v $
 * Revision 1.8  2002/10/15 14:02:31  southa
 * Mode changes
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
    static void ErrorBox(const string& inStr);
};
#endif
