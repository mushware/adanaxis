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
 * $Id: PlatformMiscUtils.cpp,v 1.23 2002/12/29 21:00:01 southa Exp $
 * $Log: PlatformMiscUtils.cpp,v $
 * Revision 1.23  2002/12/29 21:00:01  southa
 * More build fixes
 *
 * Revision 1.22  2002/12/20 13:17:48  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.21  2002/11/27 17:45:25  southa
 * Added PermissionBox
 *
 * Revision 1.20  2002/11/23 17:27:49  southa
 * Added SleepMsec
 *
 * Revision 1.19  2002/11/18 12:55:13  southa
 * win32 support for URLs and directories
 *
 * Revision 1.18  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.17  2002/10/20 23:14:48  southa
 * Fixed path for win98
 *
 * Revision 1.16  2002/10/20 20:48:07  southa
 * win32 work
 *
 * Revision 1.15  2002/10/15 19:04:09  southa
 * Windows error box
 *
 * Revision 1.14  2002/10/15 14:41:30  southa
 * Removed VBLWait
 *
 * Revision 1.13  2002/10/08 22:27:00  southa
 * Fixed for win32
 *
 * Revision 1.12  2002/10/06 22:10:00  southa
 * Initial lighting test
 *
 * Revision 1.11  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.9  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.8  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.7  2002/06/25 16:47:39  southa
 * Building with mingw32
 *
 * Revision 1.6  2002/06/24 16:41:14  southa
 * Fixed for mingw32
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

#include "mushMedia.h"
#include "mushPlatform.h"

#include <windows.h>

using namespace Mushware;
using namespace std;

#ifndef MAXPATHLEN
#define MAXPATHLEN 4096
#endif


void
PlatformMiscUtils::Initialise(void)
{
    char buffer[512]="";
    DWORD retVal = ExpandEnvironmentStrings("%USERPROFILE%", buffer, 500);
    if (retVal != 0)
    {
        MushcoreGlobalConfig::Instance().Set("HOME", buffer);
	cerr << "Set home to " << buffer << endl;
    }
    
}

string
PlatformMiscUtils::GetApplPath(int argc, char *argv[])
{
    string systemPath=GetSystemPath(argc, argv);
    string::size_type pos=string::npos;
    pos = systemPath.rfind('/', pos-1);
    if (pos==string::npos) pos = systemPath.rfind('\\', pos-1);
    if (pos==string::npos || pos == 0)
    {
        cerr << "Couldn't decode application path from '" << systemPath << "'" << endl;
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

    if (appPath.substr(0,10) == "/cygdrive/")
    {
        appPath.replace(0, 11, appPath.substr(10,1)+":");
    }
    return appPath;
}

void
PlatformMiscUtils::TweakArgs(string& ioStr)
{
}

bool
PlatformMiscUtils::DirectoryExists(const string& inName)
{
    DWORD attrib=GetFileAttributes(inName.c_str());
    
    if (attrib != INVALID_FILE_ATTRIBUTES && 
	(attrib & FILE_ATTRIBUTE_DIRECTORY) != 0)
    {
        return true;
    }
    return false;
}

void
PlatformMiscUtils::MakeDirectory(const string& inName)
{
    if (CreateDirectory(inName.c_str(), NULL) == 0)
    {
	ostringstream message;
	message << "mkdir " << inName << " failed: " << GetLastError(); 
        throw(CommandFail(message.str()));
    }
}

void
PlatformMiscUtils::ReadDirectory(vector<string>& outFilenames, const string& inDirName)
{
    WIN32_FIND_DATA fileData;
    string findStr = inDirName+"/*";
    HANDLE hList = FindFirstFile(findStr.c_str(), &fileData);

    if (hList == INVALID_HANDLE_VALUE)
    {
        throw(CommandFail("No files in drectory '" + inDirName + "'"));
    }
    
    for (U32 i=0; i<10000; ++i)
    {
        if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
            string name=fileData.cFileName;		
            if (name != "." && name != ".." && name != "CVS")
            {
                outFilenames.push_back(name);
            }
            if (!FindNextFile(hList, &fileData))
            {
                if (GetLastError() == ERROR_NO_MORE_FILES)
	        {
	            break;
	        }
                FindClose(hList);
	        ostringstream message;
	        message << "Directory error (" << GetLastError() << ")";
	        throw(CommandFail(message.str()));
	    }
	}
        COREASSERT(i<9999);
    }

    FindClose(hList);   
}

void
PlatformMiscUtils::ErrorBox(const string& inStr)
{
    if (!MessageBox(NULL, inStr.c_str(), NULL, MB_OK|MB_ICONERROR))
    {
        cerr << "Dialog box failed: " << GetLastError() << endl;
    }
}

void
PlatformMiscUtils::MinorErrorBox(const string& inStr)
{
    if (!MessageBox(NULL, inStr.c_str(), NULL, MB_OK|MB_ICONERROR))
    {
        cerr << "Dialog box failed: " << GetLastError() << endl;
    }
}

bool
PlatformMiscUtils::PermissionBox(const string& inStr, bool inDefault)
{    
    U32 flags=MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1;
    if (inDefault)
    {
         flags |= MB_DEFBUTTON1;
    }
    else
    {
         flags |= MB_DEFBUTTON2;
    }
	    
    int itemHit=MessageBox(NULL,
		    MushcoreInfo::ApplicationNameGet().c_str(),
		    inStr.c_str(),
		    flags);

    bool retVal = false;
    
    switch (itemHit)
    {
	case 0:
	    //MessageBox failed
	    break;
	    
        case IDYES:
        {
            retVal = true;
        }
        break;

        default:
            break;        
    }

    return retVal;
}

void
PlatformMiscUtils::UpdateCheck(void)
{
    if (MushcoreGlobalConfig::Instance().Exists("FIRST_RUN"))
    {
        ShowUpdateAlert();
    }
}

void
PlatformMiscUtils::ShowUpdateAlert(void)
{    
    char *title="Infernal Contractor II";
    char *desc="Thank you for installing Infernal Contractor II!  As this is the first time you are running this application, we recommend that you visit the Mushware web site to check for any important information or updates.  Would you like to do this now?";

    int itemHit=MessageBox(NULL, desc, title, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1);

    switch (itemHit)
    {
	case 0:
	    //MessageBox failed
	    break;
	    
        case IDYES:
        {
            string updateFile=MushcoreGlobalConfig::Instance().Get("SYSTEMPATH").StringGet()+"/UpdateCheck.url";
            LaunchFile(updateFile);
            exit(0);
        }
        break;

        default:
            break;        
    }
}

void
PlatformMiscUtils::LaunchFile(const string& inFile)
{
    int retVal = reinterpret_cast<int>(ShellExecute(NULL, NULL, inFile.c_str(), NULL, NULL, SW_SHOWNORMAL));
    if (retVal < 32)
    {
        string newName=inFile;
        for (U32 i=0; i<newName.size(); ++i)
	{
	    if (newName[i] == '/') newName[i]='\\';
	}
        retVal = reinterpret_cast<int>(ShellExecute(NULL, NULL, newName.c_str(), NULL, NULL, SW_SHOWNORMAL));
    }
    if (retVal < 32)
    {
	ostringstream message;
	message << "Launch failed for '" << inFile << "': " << retVal;
	throw(CommandFail(message.str()));
    }
}

void
PlatformMiscUtils::LaunchURL(const string& inURL)
{
    int status=reinterpret_cast<int>(ShellExecute(NULL, "open", inURL.c_str(), NULL, NULL, SW_SHOWDEFAULT));
    if (status < 32)
    {
	ostringstream message;
	message << "URL launch failed for '" << inURL << "': " << status;
	throw(CommandFail(message.str()));
    }
}

void
PlatformMiscUtils::SleepMsec(U32 inMsec)
{
    Sleep(inMsec);
}

