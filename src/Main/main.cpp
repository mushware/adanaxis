/*
 * $Id: main.cpp,v 1.11 2002/06/13 15:15:56 southa Exp $
 * $Log: main.cpp,v $
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
 * GameContract and global configs added
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

#include "mushCore.h"
#include "mushPlatform.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// SDL test
#if 0

#if defined(HAVE_SDL_SDL_MAIN_H)
#include <SDL/SDL_main.h>
#else
#if defined(HAVE_SDL_MAIN_H)
#include <SDL_main.h>
#else
#include "SDL_main.h"
#endif
#endif

#endif

int main(int argc, char *argv[])
{
    CoreGlobalConfig::Instance().Set("APPLPATH", PlatformMiscUtils::GetApplPath(argc, argv));
    cerr << "Application path is " << CoreGlobalConfig::Instance().Get("APPLPATH") << endl;
    CoreGlobalConfig::Instance().Set("SYSTEMPATH", PlatformMiscUtils::GetSystemPath(argc, argv));
    cerr << "System path is " << CoreGlobalConfig::Instance().Get("SYSTEMPATH") << endl;
    
    string str;
    for (int i=1; i<argc; i++)
    {
        str.append(argv[i]);
        if (i+1 != argc) str.append(" ");
    }

    PlatformMiscUtils::TweakArgs(str);

    cout << "Command line was '" << str << "'" << endl;
    if (str == "")
    {
        str="load($SYSTEMPATH+'/start.txt')";
    }
    try
    {
        CoreApp::Instance().Process(str);
        CoreAppHandler::Instance().Initialise();
        CoreAppHandler::Instance().MainLoop();
    }
    catch (exception& e)
    {
        cerr << "Standard exception: " << e.what() << endl;
        return 1;
    }
    catch (string& str)
    {
        cerr << "Exception: " << str << endl;
        return 1;
    }
    catch (const char *c_str)
    {
        cerr << "Exception: " << c_str << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown exception" << endl;
        return 1;
    }
    return 0;
}
