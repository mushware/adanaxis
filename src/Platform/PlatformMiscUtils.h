#ifndef PLATFORMMISCUTILS_H
#define PLATFORMMISCUTILS_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: PlatformMiscUtils.h,v 1.11 2002/10/22 20:42:07 southa Exp $
 * $Log: PlatformMiscUtils.h,v $
 * Revision 1.11  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.10  2002/10/17 12:35:30  southa
 * Save path and update check
 *
 * Revision 1.9  2002/10/15 18:16:41  southa
 * Mac error box
 *
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
    static void MinorErrorBox(const string& inStr);
    static bool DirectoryExists(const string& inName);
    static void MakeDirectory(const string& inName);
    static void UpdateCheck(void);
    static void LaunchFile(const string& inFile);
    static void ShowUpdateAlert(void);
};
#endif
