//%includeGuardStart {
#ifndef PLATFORMMISCUTILS_H
#define PLATFORMMISCUTILS_H
//%includeGuardStart } Gsido/wWLruFyP9CsahUqA
//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformMiscUtils.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } nsV76GW3owDjusQMHIpipw
/*
 * $Id: PlatformMiscUtils.h,v 1.28 2006/06/01 15:39:57 southa Exp $
 * $Log: PlatformMiscUtils.h,v $
 * Revision 1.28  2006/06/01 15:39:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.27  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.26  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 * Revision 1.25  2005/01/29 14:06:12  southa
 * OpenGL buffers and extensions
 *
 * Revision 1.24  2004/01/06 20:46:52  southa
 * Build fixes
 *
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
    static void MakePrivateDirectory(const std::string& inName);
    static void MakePublicDirectory(const std::string& inName);
    static void ReadDirectory(std::vector<std::string>& outFilenames, const std::string& inDirName);
    static void ErrorBox(const std::string& inStr);
    static void MinorErrorBox(const std::string& inStr);
    static bool PermissionBox(const std::string& inStr, bool inDefault);
    static void UpdateCheck(void);
    static void LaunchFile(const std::string& inFile);
    static void LaunchURL(const std::string& inURL);
    static void ShowUpdateAlert(void);
    static void SleepMsec(Mushware::U32 inMsec);
    static bool FunctionPointerGetIfExists(void *& outPtr, const std::string& inName);
    static void FunctionPointerGet(void *& outPtr, const std::string& inName);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
