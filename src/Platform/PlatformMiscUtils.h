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
 * $Id: PlatformMiscUtils.h,v 1.15 2002/11/23 17:23:45 southa Exp $
 * $Log: PlatformMiscUtils.h,v $
 * Revision 1.15  2002/11/23 17:23:45  southa
 * Sleep in setup
 *
 * Revision 1.14  2002/11/17 13:38:31  southa
 * Game selection
 *
 * Revision 1.13  2002/11/15 12:59:26  southa
 * Auto-open configuration on startup
 *
 * Revision 1.12  2002/11/15 11:47:56  southa
 * Web processing and error handling
 *
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
    static bool DirectoryExists(const string& inName);
    static void MakeDirectory(const string& inName);
    static void ReadDirectory(vector<string>& outFilenames, const string& inDirName);
    static void ErrorBox(const string& inStr);
    static void MinorErrorBox(const string& inStr);
    static bool PermissionBox(const string& inStr, bool inDefault);
    static void UpdateCheck(void);
    static void LaunchFile(const string& inFile);
    static void LaunchURL(const string& inURL);
    static void ShowUpdateAlert(void);
    static void SleepMsec(U32 inMsec);
};
#endif
