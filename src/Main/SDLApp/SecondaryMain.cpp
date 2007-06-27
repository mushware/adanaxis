//%Header {
/*****************************************************************************
 *
 * File: src/Main/SDLApp/SecondaryMain.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } iq/M/29BciHx/MWfKkILcw
/*
 * $Id: SecondaryMain.cpp,v 1.15 2007/06/27 15:30:41 southa Exp $
 * $Log: SecondaryMain.cpp,v $
 * Revision 1.15  2007/06/27 15:30:41  southa
 * X11 packaging
 *
 * Revision 1.14  2007/06/27 13:38:29  southa
 * Debian packaging
 *
 * Revision 1.13  2007/06/25 20:37:11  southa
 * X11 fixes
 *
 * Revision 1.12  2007/06/25 15:59:43  southa
 * X11 compatibility
 *
 * Revision 1.11  2007/04/18 12:44:37  southa
 * Cache purge fix and pre-release tweaks
 *
 * Revision 1.10  2007/03/13 21:45:11  southa
 * Release process
 *
 * Revision 1.9  2006/06/29 10:12:34  southa
 * 64 bit compatibility fixes
 *
 * Revision 1.8  2006/06/22 19:07:30  southa
 * Build fixes
 *
 * Revision 1.7  2006/06/01 15:39:11  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/06/04 13:18:46  southa
 * Updates for Mac OS Release 0.1.2
 *
 * Revision 1.5  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.4  2004/09/27 22:42:09  southa
 * MSVC compilation fixes
 *
 * Revision 1.3  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/05 20:13:15  southa
 * Target and test updates
 *
 * Revision 1.1  2004/01/05 14:27:40  southa
 * MushPie work and build fixes
 *
 * Revision 1.34  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.33  2004/01/01 21:15:46  southa
 * Created XCode project
 *
 * Revision 1.32  2003/10/04 12:23:08  southa
 * File renaming
 *
 * Revision 1.31  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.30  2003/08/21 23:08:59  southa
 * Fixed file headers
 *
 * Revision 1.29  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.27  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.26  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.25  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.24  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.23  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.22  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.21  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.20  2002/10/17 12:35:30  southa
 * Save path and update check
 *
 * Revision 1.19  2002/10/15 18:16:41  southa
 * Mac error box
 *
 * Revision 1.18  2002/09/03 10:34:38  southa
 * Converted save path to Unix
 *
 * Revision 1.17  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.16  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.15  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.14  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.13  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 * Revision 1.12  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.11  2002/06/13 15:15:56  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.10  2002/06/11 16:36:13  southa
 * Fixes
 *
 * Revision 1.9  2002/06/11 16:23:56  southa
 * New paths to data files
 *
 * Revision 1.8  2002/05/28 13:06:59  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.7  2002/05/27 12:58:43  southa
 * InfernalContract and global configs added
 *
 * Revision 1.6  2002/05/10 16:40:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.5  2002/05/08 17:25:31  southa
 * API tidying
 *
 * Revision 1.4  2002/03/07 22:24:35  southa
 * Command interpreter working
 *
 * Revision 1.3  2002/03/04 22:30:47  southa
 * Interpreter work
 *
 * Revision 1.2  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "mushMushcore.h"
#include "mushPlatform.h"

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(__APPLE__) || defined(MACOSX)
#undef HAVE_SDL_SDL_MAIN_H
#define HAVE_SDL_SDL_MAIN_H 1
#endif

// SDL_main.h #defines main so must be included if present

#if defined(HAVE_SDL_SDL_MAIN_H)
#include <SDL/SDL_main.h>
#elif defined(HAVE_SDL_MAIN_H)
#include <SDL_main.h>
#else
#include "SDL_main.h"
#endif

using namespace Mushware;
using namespace std;

int main(int argc, char *argv[])
{
    int retVal = 0;
    PlatformMiscUtils::Initialise();
    std::string resourcesPath = PlatformMiscUtils::GetResourcesPath(argc, argv);
    MushcoreGlobalConfig::Sgl().Set("RESOURCES_PATH", resourcesPath);
    MushcoreGlobalConfig::Sgl().Set("SYSTEM_PATH", PlatformMiscUtils::GetSystemPath(argc, argv));

#ifdef MUSHCORE_DEBUG
    cout << "Resources path is " << resourcesPath << endl;
    cout << "System path is " << MushcoreGlobalConfig::Sgl().Get("SYSTEM_PATH") << endl;
#endif

    string str;
    for (int i=1; i<argc; i++)
    {
        str.append(argv[i]);
        if (i+1 != argc) str.append(" ");
    }

    PlatformMiscUtils::TweakArgs(str);

    if (MushcoreRegExp("--help\\b").Search(str))
    {
         cout << "Options:" << endl;
         cout << "  --help              Display this message" << endl;
         cout << "  --doc               Open the documentation (if possible)" << endl;
         cout << "  --safe, --recover   Start in recovery mode" << endl;
         exit(0);
    }

    if (MushcoreRegExp("--doc\\b").Search(str))
    {
        std::vector<std::string> searchFiles;

        {
            std::vector<std::string> paths;
            paths.push_back(resourcesPath+"/../doc/"+PACKAGE+"-"+VERSION);
            paths.push_back(resourcesPath+"/../doc/"+PACKAGE);
            paths.push_back(resourcesPath);
            for (U32 i=0; i<paths.size(); ++i)
            {
                std::vector<std::string> filenames;

                try
                {
                    PlatformMiscUtils::ScanDirectory(filenames, paths[i]);
                }
                catch (MushcoreFail& e)
                {
                    // Ignore non-existent directories
                }
                for (U32 j=0; j<filenames.size(); ++j)
                {
                    searchFiles.push_back(paths[i]+"/"+filenames[j]);
                }
            }
        }
        bool found = false;
        MushcoreRegExp pdfExp("\\.pdf$");
        for (U32 i=0; i<searchFiles.size() && !found; ++i)
        {
            if (pdfExp.Search(searchFiles[i]))
            {
                PlatformMiscUtils::LaunchURL("file://"+searchFiles[i]);
                found = true;
            }
        }
        pdfExp.SearchPatternSet("\\.pdf\\."); // Debian keeps its documents gzipped
        for (U32 i=0; i<searchFiles.size() && !found; ++i)
        {
            if (pdfExp.Search(searchFiles[i]))
            {
                PlatformMiscUtils::LaunchURL("file://"+searchFiles[i]);
                found = true;
            }
        }
        exit(0);
    }

    if (str == "")
    {
        str="load($SYSTEM_PATH+'/start.txt')";
    }
    else if (MushcoreRegExp("--safe\\b").Search(str) || MushcoreRegExp("--recover\\b").Search(str))
    {
        str="load($SYSTEM_PATH+'/start_safe.txt')";
    }

    try
    {
        try
        {
            MushcoreInterpreter::Sgl().Execute(str);
        }
        catch (MushcoreNonFatalFail& e)
        {
            cerr << "Exception: " << e.what() << endl;
        }

        MushcoreAppHandler::Sgl().Initialise();
        MushcoreAppHandler::Sgl().MainLoop();
    }
    catch (exception& e)
    {
        cerr << "Exception: " << e.what() << endl;

        PlatformMiscUtils::ErrorBox(string("Error: ") + e.what());
        retVal = 1;
    }
    catch (string& ex_str)
    {
        cerr << "Exception: " << ex_str << endl;
        retVal = 1;
    }
    catch (const char *c_str)
    {
        cerr << "Exception: " << c_str << endl;
        retVal = 1;
    }
    catch (...)
    {
        cerr << "Unknown exception" << endl;
        // rethrow to see if the OS knows about it
        throw;
        retVal = 1;
    }
    return retVal;
}
