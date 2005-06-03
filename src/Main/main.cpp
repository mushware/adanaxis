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
 * $Id: main.cpp,v 1.27 2003/01/13 23:05:22 southa Exp $
 * $Log: main.cpp,v $
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

#include "Mushcore.h"
#include "mushPlatform.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// SDL_main.h #defines main so must be included
#if 1

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

using namespace Mushware;
using namespace std;

int main(int argc, char *argv[])
{
    PlatformMiscUtils::Initialise();
    MushcoreGlobalConfig::Sgl().Set("APPLPATH", PlatformMiscUtils::GetApplPath(argc, argv));
    // cerr << "Application path is " << MushcoreGlobalConfig::Sgl().Get("APPLPATH") << endl;
    MushcoreGlobalConfig::Sgl().Set("SYSTEMPATH", PlatformMiscUtils::GetSystemPath(argc, argv));
    // cerr << "System path is " << MushcoreGlobalConfig::Sgl().Get("SYSTEMPATH") << endl;



    string str;
    for (int i=1; i<argc; i++)
    {
        str.append(argv[i]);
        if (i+1 != argc) str.append(" ");
    }

    PlatformMiscUtils::TweakArgs(str);

    if (str == "")
    {
        str="load($SYSTEMPATH+'/start.txt')";
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
