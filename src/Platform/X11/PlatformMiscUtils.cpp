//%Header {
/*****************************************************************************
 *
 * File: src/Platform/X11/PlatformMiscUtils.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } O7Vnr2CZw30uh/JyGlkGBg
/*
 * $Id: PlatformMiscUtils.cpp,v 1.20 2003/08/21 23:09:36 southa Exp $
 * $Log: PlatformMiscUtils.cpp,v $
 * Revision 1.20  2003/08/21 23:09:36  southa
 * Fixed file headers
 *
 * Revision 1.19  2003/04/13 11:11:30  southa
 * Added PermissionBox
 *
 * Revision 1.18  2003/02/06 18:55:27  southa
 * Linux build fixes
 *
 * Revision 1.17  2003/02/05 18:49:52  southa
 * Build fixes
 *
 * Revision 1.16  2003/01/20 10:45:32  southa
 * Singleton tidying
 *
 * Revision 1.15  2003/01/12 17:33:01  southa
 * Mushcore work
 *
 * Revision 1.14  2003/01/09 14:57:08  southa
 * Created Mushcore
 *
 * Revision 1.13  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.12  2002/12/20 13:17:48  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.10  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.9  2002/10/21 10:54:33  southa
 * X11 build updates
 *
 * Revision 1.8  2002/09/03 10:34:38  southa
 * Converted save path to Unix
 *
 * Revision 1.7  2002/09/02 14:48:02  southa
 * RPM building
 *
 * Revision 1.6  2002/09/01 22:00:38  southa
 * Moved to real install paths
 *
 * Revision 1.5  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.1  2002/06/26 17:56:34  southa
 * Created
 *
 * Revision 1.5  2002/06/20 11:06:15  southa
 * Updated for cygwin
 *
 * Revision 1.4  2002/06/13 15:53:33  southa
 * Path fixes
 *
 * Revision 1.3  2002/06/11 18:12:04  southa
 * Fixed for cygwin
 *
 * Revision 1.2  2002/06/11 16:36:13  southa
 * Fixes
 *
 * Revision 1.1  2002/06/11 16:25:00  southa
 * New paths to data files
 *
 */

#include "mushPlatform.h"

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>

#include <dirent.h>
#include <signal.h>

using namespace Mushware;
using namespace std;

void
PlatformMiscUtils::Initialise(void)
{
    char *home = getenv("HOME");
    if (home != NULL)
    {
        MushcoreGlobalConfig::Sgl().Set("HOME", home);
    }
    // Ignore SIGPIPE.  It's raised if we send on an unconnected socket
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    {
        cerr << "Failed to attach signal handler" << endl;
    }
}

string
PlatformMiscUtils::GetApplPath(int argc, char *argv[])
{
    string systemPath=GetSystemPath(argc, argv);
    string::size_type pos=string::npos;
    pos = systemPath.rfind('/', pos-1);
    if (pos==string::npos || pos == 0)
    {
        cerr << "Couldn't decode application path from '" << systemPath << "'" 
<< endl;
        exit(1);
    }
    systemPath.resize(pos);

    return systemPath;
}

string
PlatformMiscUtils::GetSystemPath(int argc, char *argv[])
{
    string appPath;
    char *pBuffer=new char[MAXPATHLEN];
    if (getcwd(pBuffer, MAXPATHLEN) &&
        strlen(pBuffer) > 1)
    {
        appPath=string(pBuffer);
    }
    else
    {
        cerr << "Couldn't decode system path from '" << appPath << "'" << endl;
        exit(1);
    }
    delete[] pBuffer;

    return appPath;
}

void
PlatformMiscUtils::TweakArgs(string& ioStr)
{
}

bool
PlatformMiscUtils::DirectoryExists(const string& inName)
{
    struct stat statBuf;
    if (stat(inName.c_str(), &statBuf) == 0)
    {
        if (S_ISDIR(statBuf.st_mode))
	{
            return true;
	}
    }
    return false;
}

void
PlatformMiscUtils::MakeDirectory(const string& inName)
{
    errno=0;
    if (mkdir(inName.c_str(), 0700) != 0)
    {
        throw(MushcoreCommandFail("mkdir "+inName+" failed: "+strerror(errno)));
    }
}

void
PlatformMiscUtils::ReadDirectory(vector<std::string>& outFilenames, const 
string& inDirName)
{
    DIR *dirPtr = opendir(inDirName.c_str());
    if (dirPtr == NULL)
    {
        throw(MushcoreCommandFail("Cannot open directory '" + inDirName + "'"));
    }
    struct dirent *entry;
    while (entry = readdir(dirPtr), entry != NULL)
    {
        struct stat statInfo;
        lstat(entry->d_name, &statInfo);
        if(S_ISDIR(statInfo.st_mode))
        {
            string name=entry->d_name;
            if (name != "." && name != ".." && name != "CVS")
            {
                outFilenames.push_back(name);
            }
        }
    }
    closedir(dirPtr);
}

void
PlatformMiscUtils::ErrorBox(const string& inStr)
{
}

void
PlatformMiscUtils::MinorErrorBox(const string& inStr)
{
}

bool
PlatformMiscUtils::PermissionBox(const string& inStr, bool inDefault)
{
    return inDefault;
}

void
PlatformMiscUtils::UpdateCheck(void)
{
    if (MushcoreGlobalConfig::Sgl().Exists("FIRST_RUN"))
    {
        ShowUpdateAlert();
    }
}

void
PlatformMiscUtils::ShowUpdateAlert(void)
{
}

void
PlatformMiscUtils::LaunchFile(const string& inFile)
{
}

void
PlatformMiscUtils::LaunchURL(const string& inURL)
{
    // Try various URL openers until we find one that works
    vector<string> browserCommands;
    
    char *browserVar=getenv("BROWSER");
    if (browserVar != NULL)
    {
        browserCommands.push_back(browserVar);
    }
    browserCommands.push_back("kfmclient openURL");
    browserCommands.push_back("galeon --new-window");
    browserCommands.push_back("opera -newbrowser");
    browserCommands.push_back("mozilla");
    browserCommands.push_back("konqueror");
    browserCommands.push_back("netscape");

    for (U32 i=0; i < browserCommands.size(); ++i)
    {
        string launchCommand = browserCommands[i];
        launchCommand += " '"+inURL+"' &";
        if (system(launchCommand.c_str()) == 0)
        {
            return;
        }
    }
    throw MushcoreRequestFail("Could not open URL '"+inURL+"'");
}

void
PlatformMiscUtils::SleepMsec(U32 inMsec)
{
    usleep(inMsec*1000);
}
