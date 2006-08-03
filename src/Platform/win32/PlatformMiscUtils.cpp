//%Header {
/*****************************************************************************
 *
 * File: src/Platform/win32/PlatformMiscUtils.cpp
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
//%Header } dAboIY5Kp9P01iutrXBmlw
/*
 * $Id: PlatformMiscUtils.cpp,v 1.38 2006/07/28 16:52:26 southa Exp $
 * $Log: PlatformMiscUtils.cpp,v $
 * Revision 1.38  2006/07/28 16:52:26  southa
 * Options work
 *
 * Revision 1.37  2006/06/26 12:55:12  southa
 * win32 installer updates
 *
 * Revision 1.36  2006/06/23 00:35:28  southa
 * win32 build fixes
 *
 * Revision 1.35  2006/06/01 15:39:58  southa
 * DrawArray verification and fixes
 *
 * Revision 1.34  2005/05/26 16:05:29  southa
 * win32 support
 *
 * Revision 1.33  2005/05/26 00:46:41  southa
 * Made buildable on win32
 *
 * Revision 1.32  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.31  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.30  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.29  2003/08/21 23:09:36  southa
 * Fixed file headers
 *
 * Revision 1.28  2003/03/12 22:38:00  southa
 * Include direct.h
 *
 * Revision 1.27  2003/02/05 17:06:38  southa
 * Build fixes
 *
 * Revision 1.26  2003/01/20 10:45:32  southa
 * Singleton tidying
 *
 * Revision 1.25  2003/01/12 17:33:02  southa
 * Mushcore work
 *
 * Revision 1.24  2003/01/09 14:57:09  southa
 * Created Mushcore
 *
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

#define NOMINMAX
#include <direct.h>
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <strsafe.h>

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
        MushcoreGlobalConfig::Sgl().Set("HOME", buffer);
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

string
PlatformMiscUtils::GetUserDataPath(int argc, char *argv[])
{
    TCHAR userPath[MAX_PATH];

    SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, userPath);

    return std::string(userPath) + "\\mushware\\" + MushcoreInfo::Sgl().PackageNameGet();
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
PlatformMiscUtils::MakePublicDirectory(const string& inName)
{
    SECURITY_ATTRIBUTES sa;
    SECURITY_DESCRIPTOR sd;

    InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl(&sd, true, NULL, false);
    SetSecurityDescriptorGroup(&sd, NULL, false); 
    SetSecurityDescriptorSacl(&sd, false, NULL, false);

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = &sd;
    sa.bInheritHandle = TRUE;

    if (CreateDirectory(inName.c_str(), &sa) == 0)
    {
	ostringstream message;
	message << "mkdir " << inName << " failed: " << GetLastError(); 
        throw(MushcoreCommandFail(message.str()));
    }
}

void
PlatformMiscUtils::MakePrivateDirectory(const string& inName)
{
    if (CreateDirectory(inName.c_str(), NULL) == 0)
    {
	ostringstream message;
	message << "mkdir " << inName << " failed: " << GetLastError(); 
        throw(MushcoreCommandFail(message.str()));
    }
}

void
PlatformMiscUtils::ReadDirectory(vector<std::string>& outFilenames, const string& inDirName)
{
    WIN32_FIND_DATA fileData;
    string findStr = inDirName+"/*";
     HANDLE hList = FindFirstFile(findStr.c_str(), &fileData);
     
     if (hList != INVALID_HANDLE_VALUE)
     {     
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
                     throw(MushcoreCommandFail(message.str()));
                 }
             }
             MUSHCOREASSERT(i<9999);
         }
         
         FindClose(hList);
     }
}

void
PlatformMiscUtils::ScanDirectory(vector<std::string>& outFilenames, const string& inDirName)
{
    WIN32_FIND_DATA fileData;
    string findStr = inDirName+"/*";
    HANDLE hList = FindFirstFile(findStr.c_str(), &fileData);
     
    if (hList != INVALID_HANDLE_VALUE)
    {
        for (U32 i=0; i<10000; ++i)
        {
            if ((fileData.dwFileAttributes & (FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE)) != 0)
            {
                string name=fileData.cFileName;		
                if (name != "." && name != ".." && name != "CVS")
                {
                    outFilenames.push_back(name);
                }
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
                throw(MushcoreCommandFail(message.str()));
            }

            MUSHCOREASSERT(i<9999);
        }

        FindClose(hList);   
    }
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
		    MushcoreInfo::Sgl().ApplicationNameGet().c_str(),
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
    if (MushcoreGlobalConfig::Sgl().Exists("FIRST_RUN"))
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
            string updateFile=MushcoreGlobalConfig::Sgl().Get("SYSTEMPATH").StringGet()+"/UpdateCheck.url";
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
	throw(MushcoreCommandFail(message.str()));
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
	throw(MushcoreCommandFail(message.str()));
    }
}

void
PlatformMiscUtils::SleepMsec(U32 inMsec)
{
    Sleep(inMsec);
}

bool
PlatformMiscUtils::FunctionPointerGetIfExists(void *& outPtr, const std::string& inName)
{
    bool success = false;
    PROC fnPtr = wglGetProcAddress(inName.c_str());
    if (fnPtr != NULL)
    {
        outPtr = fnPtr;
        success = true;
    }
    return success;
}

void
PlatformMiscUtils::FunctionPointerGet(void *& outPtr, const std::string& inName)
{
    if (!FunctionPointerGetIfExists(outPtr, inName))
    {
        throw MushcoreRequestFail("Unknown symbol '"+inName+"'");
    }
}


