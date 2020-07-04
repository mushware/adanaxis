//%Header {
/*****************************************************************************
 *
 * File: src/Platform/X11/PlatformMiscUtils.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } S72Bzdqn99PlJvSaeizXFQ
/*
 * $Id: PlatformMiscUtils.cpp,v 1.34 2007/06/30 11:45:46 southa Exp $
 * $Log: PlatformMiscUtils.cpp,v $
 * Revision 1.34  2007/06/30 11:45:46  southa
 * X11 release
 *
 * Revision 1.33  2007/06/28 15:15:17  southa
 * Mandriva fixes
 *
 * Revision 1.32  2007/06/25 20:37:14  southa
 * X11 fixes
 *
 * Revision 1.31  2007/06/25 15:59:48  southa
 * X11 compatibility
 *
 * Revision 1.30  2007/03/13 21:45:11  southa
 * Release process
 *
 * Revision 1.29  2006/08/03 16:32:48  southa
 * X11 release work
 *
 * Revision 1.28  2006/07/28 16:52:26  southa
 * Options work
 *
 * Revision 1.27  2006/06/29 08:27:11  southa
 * X11 fixes
 *
 * Revision 1.26  2006/06/01 15:39:58  southa
 * DrawArray verification and fixes
 *
 * Revision 1.25  2005/06/08 20:59:52  southa
 * X11 release
 *
 * Revision 1.24  2005/06/06 15:07:10  southa
 * X11 work
 *
 * Revision 1.23  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.22  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.21  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
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
#include "mushMedia.h"

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>

#include <dirent.h>
#include <signal.h>
#include <dlfcn.h>

#include "binreloc.h"

using namespace Mushware;
using namespace std;

std::string PlatformMiscUtils::s_displayEnv = "";
bool PlatformMiscUtils::s_openHelpOnExit = false;

void
PlatformMiscUtils::Initialise(void)
{
    char *home = getenv("HOME");
    if (home != NULL)
    {
        MushcoreGlobalConfig::Sgl().Set("HOME", home);
    }
    
    char *display = getenv("DISPLAY");
    if (display == NULL)
    {
        s_displayEnv = "";
    }
    else
    {
        s_displayEnv = std::string(display);
    }
    
    // Ignore SIGPIPE.  It's raised if we send on an unconnected socket
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    {
        cerr << "Failed to attach signal handler" << endl;
    }
}

void
PlatformMiscUtils::Finalise(void)
{
    if (s_displayEnv != "")
    {
        setenv("DISPLAY", s_displayEnv.c_str(), 1 /* overwrite */);
    }
    
    if (s_openHelpOnExit)
    {
        bool success = false;
    
        std::string exeName(br_find_exe(MushcoreInfo::Sgl().PackageName().c_str()));

        if (system((exeName+" --doc").c_str()) == 0)
        {
            success = true;
        }
        
        if (!success)
        {
            cout << "Failed to open help file - try /usr/share/" << MushcoreInfo::Sgl().PackageName() <<
                    " or /usr/share/doc/" << MushcoreInfo::Sgl().PackageName() << endl;
        }
    }
}

string
PlatformMiscUtils::GetResourcesPath(int argc, char *argv[])
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
    std::vector<std::string> pathCandidates;
    
    char *overrideDir = getenv(PACKAGE "_DATA_DIR");
    if (overrideDir != NULL)
    {
        pathCandidates.push_back(overrideDir);
    }
    
#ifdef MUSH_OVERRIDE_DATA_DIR
    pathCandidates.push_back(MUSH_OVERRIDE_DATA_DIR);
#endif
    
#ifdef ENABLE_BINRELOC
    BrInitError error;
    if (br_init(&error) == 0 && error != BR_INIT_ERROR_DISABLED)
    {
        cerr << "Binreloc failed (" << error << ")" << endl;
    }
    else
    {
        char *pDataDir = br_find_data_dir(MUSH_DATA_DIR);
        std::string dataDir(pDataDir);
        free(pDataDir);
        pathCandidates.push_back(dataDir + "/" PACKAGE "-" VERSION);
        pathCandidates.push_back(dataDir + "/" PACKAGE);
    }
#endif
    
    // Hardcoded paths from ./configure
    pathCandidates.push_back(MUSH_DATA_DIR "/" PACKAGE "-" VERSION);
    pathCandidates.push_back(MUSH_DATA_DIR "/" PACKAGE);

    char *pBuffer=new char[MAXPATHLEN];
    if (getcwd(pBuffer, MAXPATHLEN) &&
	strlen(pBuffer) > 1)
    {
        pathCandidates.push_back(pBuffer);
    }
    delete[] pBuffer;

    pathCandidates.push_back(MUSH_DATA_DIR);

    std::string appPath = "";
    for (U32 i=0; i<pathCandidates.size() && appPath == ""; ++i)
    {
        std::string testPath = pathCandidates[i]+"/system";
        if (DirectoryExists(testPath))
        {
            appPath = testPath;
        }
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
PlatformMiscUtils::MakePrivateDirectory(const string& inName)
{
    errno=0;
    if (mkdir(inName.c_str(), 0700) != 0)
    {
        throw(MushcoreCommandFail("mkdir "+inName+" failed: "+strerror(errno)));
    }
}

void
PlatformMiscUtils::MakePublicDirectory(const string& inName)
{
    errno=0;
    if (mkdir(inName.c_str(), 0777) != 0)
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
PlatformMiscUtils::ScanDirectory(vector<std::string>& outFilenames, const string& inDirName)
{
    // Returns files in the directory
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

        if (S_ISREG(statInfo.st_mode), 1) // Workaround for file test problem
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
    browserCommands.push_back("epiphany --new-window");
    browserCommands.push_back("netscape");
    browserCommands.push_back("firefox");

    for (U32 i=0; i < browserCommands.size(); ++i)
    {
        string launchCommand = browserCommands[i];
        launchCommand += " '"+inURL+"'";
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

bool
PlatformMiscUtils::FunctionPointerGetIfExists(void *& outPtr, const std::string& inName)
{
    bool success = false;
    void *dlHandle = dlopen(0, RTLD_NOW);
    
    if (dlHandle != NULL)
    {
        void *fnPtr = dlsym(dlHandle, inName.c_str());
        if (fnPtr == NULL)
        {
            fnPtr = dlsym(dlHandle, ("_"+inName).c_str());
        }
        
        if (fnPtr != NULL)
        {
            outPtr = fnPtr;
            success = true;
        }
        dlclose(dlHandle);
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

void
PlatformMiscUtils::HelpFileOpen(void)
{
    s_openHelpOnExit = true;
}

// Binreloc code follows:

/*
 * BinReloc - a library for creating relocatable executables
 * Written by: Hongli Lai <h.lai@chello.nl>
 * http://autopackage.org/
 *
 * This source code is public domain. You can relicense this code
 * under whatever license you want.
 *
 * See http://autopackage.org/docs/binreloc/ for
 * more information and how to use this.
 */

#ifndef __BINRELOC_C__
#define __BINRELOC_C__

#ifdef ENABLE_BINRELOC
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif /* ENABLE_BINRELOC */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "binreloc.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/** @internal
 * Find the canonical filename of the executable. Returns the filename
 * (which must be freed) or NULL on error. If the parameter 'error' is
 * not NULL, the error code will be stored there, if an error occured.
 */
static char *
_br_find_exe (BrInitError *error)
{
#ifndef ENABLE_BINRELOC
	if (error)
		*error = BR_INIT_ERROR_DISABLED;
	return NULL;
#else
	char *path, *path2, *line, *result;
	size_t buf_size;
	ssize_t size;
	struct stat stat_buf;
	FILE *f;

	/* Read from /proc/self/exe (symlink) */
	if (sizeof (path) > SSIZE_MAX)
		buf_size = SSIZE_MAX - 1;
	else
		buf_size = PATH_MAX - 1;
	path = (char *) malloc (buf_size);
	if (path == NULL) {
		/* Cannot allocate memory. */
		if (error)
			*error = BR_INIT_ERROR_NOMEM;
		return NULL;
	}
	path2 = (char *) malloc (buf_size);
	if (path2 == NULL) {
		/* Cannot allocate memory. */
		if (error)
			*error = BR_INIT_ERROR_NOMEM;
		free (path);
		return NULL;
	}

	strncpy (path2, "/proc/self/exe", buf_size - 1);

	while (1) {
		int i;

		size = readlink (path2, path, buf_size - 1);
		if (size == -1) {
			/* Error. */
			free (path2);
			break;
		}

		/* readlink() success. */
		path[size] = '\0';

		/* Check whether the symlink's target is also a symlink.
		 * We want to get the final target. */
		i = stat (path, &stat_buf);
		if (i == -1) {
			/* Error. */
			free (path2);
			break;
		}

		/* stat() success. */
		if (!S_ISLNK (stat_buf.st_mode)) {
			/* path is not a symlink. Done. */
			free (path2);
			return path;
		}

		/* path is a symlink. Continue loop and resolve this. */
		strncpy (path, path2, buf_size - 1);
	}


	/* readlink() or stat() failed; this can happen when the program is
	 * running in Valgrind 2.2. Read from /proc/self/maps as fallback. */

	buf_size = PATH_MAX + 128;
	line = (char *) realloc (path, buf_size);
	if (line == NULL) {
		/* Cannot allocate memory. */
		free (path);
		if (error)
			*error = BR_INIT_ERROR_NOMEM;
		return NULL;
	}

	f = fopen ("/proc/self/maps", "r");
	if (f == NULL) {
		free (line);
		if (error)
			*error = BR_INIT_ERROR_OPEN_MAPS;
		return NULL;
	}

	/* The first entry should be the executable name. */
	result = fgets (line, (int) buf_size, f);
	if (result == NULL) {
		fclose (f);
		free (line);
		if (error)
			*error = BR_INIT_ERROR_READ_MAPS;
		return NULL;
	}

	/* Get rid of newline character. */
	buf_size = strlen (line);
	if (buf_size <= 0) {
		/* Huh? An empty string? */
		fclose (f);
		free (line);
		if (error)
			*error = BR_INIT_ERROR_INVALID_MAPS;
		return NULL;
	}
	if (line[buf_size - 1] == 10)
		line[buf_size - 1] = 0;

	/* Extract the filename; it is always an absolute path. */
	path = strchr (line, '/');

	/* Sanity check. */
	if (strstr (line, " r-xp ") == NULL || path == NULL) {
		fclose (f);
		free (line);
		if (error)
			*error = BR_INIT_ERROR_INVALID_MAPS;
		return NULL;
	}

	path = strdup (path);
	free (line);
	fclose (f);
	return path;
#endif /* ENABLE_BINRELOC */
}


/** @internal
 * Find the canonical filename of the executable which owns symbol.
 * Returns a filename which must be freed, or NULL on error.
 */
static char *
_br_find_exe_for_symbol (const void *symbol, BrInitError *error)
{
#ifndef ENABLE_BINRELOC
	if (error)
		*error = BR_INIT_ERROR_DISABLED;
	return (char *) NULL;
#else
	#define SIZE PATH_MAX + 100
	FILE *f;
	size_t address_string_len;
	char *address_string, line[SIZE], *found;

	if (symbol == NULL)
		return (char *) NULL;

	f = fopen ("/proc/self/maps", "r");
	if (f == NULL)
		return (char *) NULL;

	address_string_len = 4;
	address_string = (char *) malloc (address_string_len);
	found = (char *) NULL;

	while (!feof (f)) {
		char *start_addr, *end_addr, *end_addr_end, *file;
		void *start_addr_p, *end_addr_p;
		size_t len;

		if (fgets (line, SIZE, f) == NULL)
			break;

		/* Sanity check. */
		if (strstr (line, " r-xp ") == NULL || strchr (line, '/') == NULL)
			continue;

		/* Parse line. */
		start_addr = line;
		end_addr = strchr (line, '-');
		file = strchr (line, '/');

		/* More sanity check. */
		if (!(file > end_addr && end_addr != NULL && end_addr[0] == '-'))
			continue;

		end_addr[0] = '\0';
		end_addr++;
		end_addr_end = strchr (end_addr, ' ');
		if (end_addr_end == NULL)
			continue;

		end_addr_end[0] = '\0';
		len = strlen (file);
		if (len == 0)
			continue;
		if (file[len - 1] == '\n')
			file[len - 1] = '\0';

		/* Get rid of "(deleted)" from the filename. */
		len = strlen (file);
		if (len > 10 && strcmp (file + len - 10, " (deleted)") == 0)
			file[len - 10] = '\0';

		/* I don't know whether this can happen but better safe than sorry. */
		len = strlen (start_addr);
		if (len != strlen (end_addr))
			continue;


		/* Transform the addresses into a string in the form of 0xdeadbeef,
		 * then transform that into a pointer. */
		if (address_string_len < len + 3) {
			address_string_len = len + 3;
			address_string = (char *) realloc (address_string, address_string_len);
		}

		memcpy (address_string, "0x", 2);
		memcpy (address_string + 2, start_addr, len);
		address_string[2 + len] = '\0';
		sscanf (address_string, "%p", &start_addr_p);

		memcpy (address_string, "0x", 2);
		memcpy (address_string + 2, end_addr, len);
		address_string[2 + len] = '\0';
		sscanf (address_string, "%p", &end_addr_p);


		if (symbol >= start_addr_p && symbol < end_addr_p) {
			found = file;
			break;
		}
	}

	free (address_string);
	fclose (f);

	if (found == NULL)
		return (char *) NULL;
	else
		return strdup (found);
#endif /* ENABLE_BINRELOC */
}


#ifndef BINRELOC_RUNNING_DOXYGEN
// Removed redifinition of NULL - Mushware 2007-06-25
#endif

static char *exe = (char *) NULL;


/** Initialize the BinReloc library (for applications).
 *
 * This function must be called before using any other BinReloc functions.
 * It attempts to locate the application's canonical filename.
 *
 * @note If you want to use BinReloc for a library, then you should call
 *       br_init_lib() instead.
 *
 * @param error  If BinReloc failed to initialize, then the error code will
 *               be stored in this variable. Set to NULL if you want to
 *               ignore this. See #BrInitError for a list of error codes.
 *
 * @returns 1 on success, 0 if BinReloc failed to initialize.
 */
int
br_init (BrInitError *error)
{
	exe = _br_find_exe (error);
	return exe != NULL;
}


/** Initialize the BinReloc library (for libraries).
 *
 * This function must be called before using any other BinReloc functions.
 * It attempts to locate the calling library's canonical filename.
 *
 * @note The BinReloc source code MUST be included in your library, or this
 *       function won't work correctly.
 *
 * @param error  If BinReloc failed to initialize, then the error code will
 *               be stored in this variable. Set to NULL if you want to
 *               ignore this. See #BrInitError for a list of error codes.
 *
 * @returns 1 on success, 0 if a filename cannot be found.
 */
int
br_init_lib (BrInitError *error)
{
	exe = _br_find_exe_for_symbol ((const void *) "", error);
	return exe != NULL;
}


/** Find the canonical filename of the current application.
 *
 * @param default_exe  A default filename which will be used as fallback.
 * @returns A string containing the application's canonical filename,
 *          which must be freed when no longer necessary. If BinReloc is
 *          not initialized, or if br_init() failed, then a copy of
 *          default_exe will be returned. If default_exe is NULL, then
 *          NULL will be returned.
 */
char *
br_find_exe (const char *default_exe)
{
	if (exe == (char *) NULL) {
		/* BinReloc is not initialized. */
		if (default_exe != (const char *) NULL)
			return strdup (default_exe);
		else
			return (char *) NULL;
	}
	return strdup (exe);
}


/** Locate the directory in which the current application is installed.
 *
 * The prefix is generated by the following pseudo-code evaluation:
 * \code
 * dirname(exename)
 * \endcode
 *
 * @param default_dir  A default directory which will used as fallback.
 * @return A string containing the directory, which must be freed when no
 *         longer necessary. If BinReloc is not initialized, or if the
 *         initialization function failed, then a copy of default_dir
 *         will be returned. If default_dir is NULL, then NULL will be
 *         returned.
 */
char *
br_find_exe_dir (const char *default_dir)
{
	if (exe == NULL) {
		/* BinReloc not initialized. */
		if (default_dir != NULL)
			return strdup (default_dir);
		else
			return (char *)NULL;
	}

	return br_dirname (exe);
}


/** Locate the prefix in which the current application is installed.
 *
 * The prefix is generated by the following pseudo-code evaluation:
 * \code
 * dirname(dirname(exename))
 * \endcode
 *
 * @param default_prefix  A default prefix which will used as fallback.
 * @return A string containing the prefix, which must be freed when no
 *         longer necessary. If BinReloc is not initialized, or if
 *         the initialization function failed, then a copy of default_prefix
 *         will be returned. If default_prefix is NULL, then NULL will be returned.
 */
char *
br_find_prefix (const char *default_prefix)
{
	char *dir1, *dir2;

	if (exe == (char *) NULL) {
		/* BinReloc not initialized. */
		if (default_prefix != (const char *) NULL)
			return strdup (default_prefix);
		else
			return (char *) NULL;
	}

	dir1 = br_dirname (exe);
	dir2 = br_dirname (dir1);
	free (dir1);
	return dir2;
}


/** Locate the application's binary folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/bin"
 * \endcode
 *
 * @param default_bin_dir  A default path which will used as fallback.
 * @return A string containing the bin folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if
 *         the initialization function failed, then a copy of default_bin_dir will
 *         be returned. If default_bin_dir is NULL, then NULL will be returned.
 */
char *
br_find_bin_dir (const char *default_bin_dir)
{
	char *prefix, *dir;

	prefix = br_find_prefix ((const char *) NULL);
	if (prefix == (char *) NULL) {
		/* BinReloc not initialized. */
		if (default_bin_dir != (const char *) NULL)
			return strdup (default_bin_dir);
		else
			return (char *) NULL;
	}

	dir = br_build_path (prefix, "bin");
	free (prefix);
	return dir;
}


/** Locate the application's superuser binary folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/sbin"
 * \endcode
 *
 * @param default_sbin_dir  A default path which will used as fallback.
 * @return A string containing the sbin folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the
 *         initialization function failed, then a copy of default_sbin_dir will
 *         be returned. If default_bin_dir is NULL, then NULL will be returned.
 */
char *
br_find_sbin_dir (const char *default_sbin_dir)
{
	char *prefix, *dir;

	prefix = br_find_prefix ((const char *) NULL);
	if (prefix == (char *) NULL) {
		/* BinReloc not initialized. */
		if (default_sbin_dir != (const char *) NULL)
			return strdup (default_sbin_dir);
		else
			return (char *) NULL;
	}

	dir = br_build_path (prefix, "sbin");
	free (prefix);
	return dir;
}


/** Locate the application's data folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/share"
 * \endcode
 *
 * @param default_data_dir  A default path which will used as fallback.
 * @return A string containing the data folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the
 *         initialization function failed, then a copy of default_data_dir
 *         will be returned. If default_data_dir is NULL, then NULL will be
 *         returned.
 */
char *
br_find_data_dir (const char *default_data_dir)
{
	char *prefix, *dir;

	prefix = br_find_prefix ((const char *) NULL);
	if (prefix == (char *) NULL) {
		/* BinReloc not initialized. */
		if (default_data_dir != (const char *) NULL)
			return strdup (default_data_dir);
		else
			return (char *) NULL;
	}

	dir = br_build_path (prefix, "share");
	free (prefix);
	return dir;
}


/** Locate the application's localization folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/share/locale"
 * \endcode
 *
 * @param default_locale_dir  A default path which will used as fallback.
 * @return A string containing the localization folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the
 *         initialization function failed, then a copy of default_locale_dir will be returned.
 *         If default_locale_dir is NULL, then NULL will be returned.
 */
char *
br_find_locale_dir (const char *default_locale_dir)
{
	char *data_dir, *dir;

	data_dir = br_find_data_dir ((const char *) NULL);
	if (data_dir == (char *) NULL) {
		/* BinReloc not initialized. */
		if (default_locale_dir != (const char *) NULL)
			return strdup (default_locale_dir);
		else
			return (char *) NULL;
	}

	dir = br_build_path (data_dir, "locale");
	free (data_dir);
	return dir;
}


/** Locate the application's library folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/lib"
 * \endcode
 *
 * @param default_lib_dir  A default path which will used as fallback.
 * @return A string containing the library folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the initialization
 *         function failed, then a copy of default_lib_dir will be returned.
 *         If default_lib_dir is NULL, then NULL will be returned.
 */
char *
br_find_lib_dir (const char *default_lib_dir)
{
	char *prefix, *dir;

	prefix = br_find_prefix ((const char *) NULL);
	if (prefix == (char *) NULL) {
		/* BinReloc not initialized. */
		if (default_lib_dir != (const char *) NULL)
			return strdup (default_lib_dir);
		else
			return (char *) NULL;
	}

	dir = br_build_path (prefix, "lib");
	free (prefix);
	return dir;
}


/** Locate the application's libexec folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/libexec"
 * \endcode
 *
 * @param default_libexec_dir  A default path which will used as fallback.
 * @return A string containing the libexec folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the initialization
 *         function failed, then a copy of default_libexec_dir will be returned.
 *         If default_libexec_dir is NULL, then NULL will be returned.
 */
char *
br_find_libexec_dir (const char *default_libexec_dir)
{
	char *prefix, *dir;

	prefix = br_find_prefix ((const char *) NULL);
	if (prefix == (char *) NULL) {
		/* BinReloc not initialized. */
		if (default_libexec_dir != (const char *) NULL)
			return strdup (default_libexec_dir);
		else
			return (char *) NULL;
	}

	dir = br_build_path (prefix, "libexec");
	free (prefix);
	return dir;
}


/** Locate the application's configuration files folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/etc"
 * \endcode
 *
 * @param default_etc_dir  A default path which will used as fallback.
 * @return A string containing the etc folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the initialization
 *         function failed, then a copy of default_etc_dir will be returned.
 *         If default_etc_dir is NULL, then NULL will be returned.
 */
char *
br_find_etc_dir (const char *default_etc_dir)
{
	char *prefix, *dir;

	prefix = br_find_prefix ((const char *) NULL);
	if (prefix == (char *) NULL) {
		/* BinReloc not initialized. */
		if (default_etc_dir != (const char *) NULL)
			return strdup (default_etc_dir);
		else
			return (char *) NULL;
	}

	dir = br_build_path (prefix, "etc");
	free (prefix);
	return dir;
}


/***********************
 * Utility functions
 ***********************/

/** Concatenate str1 and str2 to a newly allocated string.
 *
 * @param str1 A string.
 * @param str2 Another string.
 * @returns A newly-allocated string. This string should be freed when no longer needed.
 */
char *
br_strcat (const char *str1, const char *str2)
{
	char *result;
	size_t len1, len2;

	if (str1 == NULL)
		str1 = "";
	if (str2 == NULL)
		str2 = "";

	len1 = strlen (str1);
	len2 = strlen (str2);

	result = (char *) malloc (len1 + len2 + 1);
	memcpy (result, str1, len1);
	memcpy (result + len1, str2, len2);
	result[len1 + len2] = '\0';

	return result;
}


char *
br_build_path (const char *dir, const char *file)
{
	char *dir2, *result;
	size_t len;
	int must_free = 0;

	len = strlen (dir);
	if (len > 0 && dir[len - 1] != '/') {
		dir2 = br_strcat (dir, "/");
		must_free = 1;
	} else
		dir2 = (char *) dir;

	result = br_strcat (dir2, file);
	if (must_free)
		free (dir2);
	return result;
}


/* Emulates glibc's strndup() */
static char *
br_strndup (const char *str, size_t size)
{
	char *result = (char *) NULL;
	size_t len;

	if (str == (const char *) NULL)
		return (char *) NULL;

	len = strlen (str);
	if (len == 0)
		return strdup ("");
	if (size > len)
		size = len;

	result = (char *) malloc (len + 1);
	memcpy (result, str, size);
	result[size] = '\0';
	return result;
}


/** Extracts the directory component of a path.
 *
 * Similar to g_dirname() or the dirname commandline application.
 *
 * Example:
 * \code
 * br_dirname ("/usr/local/foobar");  --> Returns: "/usr/local"
 * \endcode
 *
 * @param path  A path.
 * @returns     A directory name. This string should be freed when no longer needed.
 */
char *
br_dirname (const char *path)
{
	char *end, *result;

	if (path == (const char *) NULL)
		return (char *) NULL;

	end = strrchr (path, '/');
	if (end == (const char *) NULL)
		return strdup (".");

	while (end > path && *end == '/')
		end--;
	result = br_strndup (path, end - path + 1);
	if (result[0] == 0) {
		free (result);
		return strdup ("/");
	} else
		return result;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BINRELOC_C__ */
