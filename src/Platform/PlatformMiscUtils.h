//%includeGuardStart {
#ifndef PLATFORMMISCUTILS_H
#define PLATFORMMISCUTILS_H
//%includeGuardStart } Gsido/wWLruFyP9CsahUqA
//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformMiscUtils.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 4UPdmxdhcOYTSSiCCkQrtg
/*
 * $Id: PlatformMiscUtils.h,v 1.23 2004/01/02 21:13:16 southa Exp $
 * $Log: PlatformMiscUtils.h,v $
 * Revision 1.23  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.22  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.21  2003/08/21 23:09:33  southa
 * Fixed file headers
 *
 * Revision 1.20  2003/02/05 16:19:46  southa
 * Build fixes
 *
 * Revision 1.19  2003/01/11 13:03:18  southa
 * Use Mushcore header
 *
 * Revision 1.18  2002/12/29 20:30:57  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.17  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.16  2002/11/24 12:57:02  southa
 * Added configuration host protection
 *
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

#include "mushMushcore.h"

class PlatformMiscUtils
{
public:
    static std::string GetApplPath(int argc, char *argv[]);
    static std::string GetSystemPath(int argc, char *argv[]);
    static void TweakArgs(std::string& ioString);
    static void Initialise(void);
    static bool DirectoryExists(const std::string& inName);
    static void MakeDirectory(const std::string& inName);
    static void ReadDirectory(std::vector<std::string>& outFilenames, const std::string& inDirName);
    static void ErrorBox(const std::string& inStr);
    static void MinorErrorBox(const std::string& inStr);
    static bool PermissionBox(const std::string& inStr, bool inDefault);
    static void UpdateCheck(void);
    static void LaunchFile(const std::string& inFile);
    static void LaunchURL(const std::string& inURL);
    static void ShowUpdateAlert(void);
    static void SleepMsec(Mushware::U32 inMsec);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
