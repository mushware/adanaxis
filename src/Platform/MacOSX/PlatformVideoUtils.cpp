//%Header {
/*****************************************************************************
 *
 * File: src/Platform/MacOSX/PlatformVideoUtils.cpp
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
//%Header } gNdwSMf5xIpttE1WeIDxUA
/*
 * $Id: PlatformVideoUtils.cpp,v 1.25 2007/06/27 11:56:44 southa Exp $
 * $Log: PlatformVideoUtils.cpp,v $
 * Revision 1.25  2007/06/27 11:56:44  southa
 * Debian packaging
 *
 * Revision 1.24  2007/04/18 09:23:23  southa
 * Header and level fixes
 *
 * Revision 1.23  2006/12/14 00:33:50  southa
 * Control fix and audio pacing
 *
 * Revision 1.22  2006/11/25 21:26:33  southa
 * Display mode definitions
 *
 * Revision 1.21  2006/07/28 16:52:25  southa
 * Options work
 *
 * Revision 1.20  2006/06/01 15:39:58  southa
 * DrawArray verification and fixes
 *
 * Revision 1.19  2005/05/20 10:26:28  southa
 * Release work
 *
 * Revision 1.18  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.17  2005/04/19 23:25:42  southa
 * Mode switching and recognition
 *
 * Revision 1.16  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.15  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.14  2003/08/21 23:09:35  southa
 * Fixed file headers
 *
 * Revision 1.13  2003/04/13 08:39:18  southa
 * Bring window to foreground on mode change
 *
 * Revision 1.12  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.11  2003/01/20 10:45:32  southa
 * Singleton tidying
 *
 * Revision 1.10  2003/01/12 17:33:01  southa
 * Mushcore work
 *
 * Revision 1.9  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.8  2002/12/20 13:17:48  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/12/03 20:28:18  southa
 * Network, player and control work
 *
 * Revision 1.6  2002/11/12 11:49:22  southa
 * Initial MHTML processing
 *
 * Revision 1.5  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.4  2002/10/17 15:51:00  southa
 * Config saving, pause and quit
 *
 * Revision 1.3  2002/10/15 14:39:21  southa
 * Include fixes
 *
 * Revision 1.2  2002/10/15 14:02:31  southa
 * Mode changes
 *
 * Revision 1.1  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 */

#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

using namespace Mushware;
using namespace std;

PlatformVideoUtils *PlatformVideoUtils::m_instance=NULL;

PlatformVideoUtils::PlatformVideoUtils()
{
}

void
PlatformVideoUtils::Acquaint(void)
{
    m_modeDefs.push_back(GLModeDef(640, 480, false));
    m_modeDefs.push_back(GLModeDef(800, 600, false));

    // Find all display modes available on all displays and add them to the list

    CGDirectDisplayID displayArray[32];
    CGDisplayCount numDisplays;

    CGGetActiveDisplayList(sizeof(displayArray)/sizeof(displayArray[0]), displayArray, &numDisplays);

    std::vector< std::pair<long, long> > modesSoFar;

    for (CGDisplayCount displayNum=0; displayNum < numDisplays; ++displayNum)
    {
        CFArrayRef displayModeArrayRef = CGDisplayAvailableModes(displayArray[displayNum]) ;

        for (CFIndex modeNum=0; modeNum < CFArrayGetCount(displayModeArrayRef); ++modeNum)
        {
            CFDictionaryRef displayMode = reinterpret_cast<CFDictionaryRef>(CFArrayGetValueAtIndex(displayModeArrayRef, modeNum));

            CFNumberRef widthRef = reinterpret_cast<CFNumberRef>(CFDictionaryGetValue(displayMode, kCGDisplayWidth)) ;
            CFNumberRef heightRef = reinterpret_cast<CFNumberRef>(CFDictionaryGetValue(displayMode, kCGDisplayHeight)) ;

            std::pair<long, long> newSize;
            CFNumberGetValue(widthRef, kCFNumberLongType, &newSize.first);
            CFNumberGetValue(heightRef, kCFNumberLongType, &newSize.second);

            if (std::find(modesSoFar.begin(), modesSoFar.end(), newSize) == modesSoFar.end())
            {
                modesSoFar.push_back(newSize);
            }
        }
    }

    std::sort(modesSoFar.begin(), modesSoFar.end());

    for (U32 i=0; i<modesSoFar.size(); ++i)
    {
        U32 xSize = modesSoFar[i].first;
        U32 ySize = modesSoFar[i].second;
        m_modeDefs.push_back(GLModeDef(xSize, ySize, true));
    }
}

void
PlatformVideoUtils::VBLWait(void)
{
    // Removed
}

void
PlatformVideoUtils::ForceShowCursor(void)
{
    ShowCursor();
}

void
PlatformVideoUtils::AppActivate(void)
{
#if 0
    // Doesn't work
    WindowRef ourWindow = FrontWindow();
    cerr << "ourWindow=" << ourWindow << endl;
    if (ourWindow != NULL)
    {
        SelectWindow(ourWindow);
    }
#endif
}

void
PlatformVideoUtils::ModeChangePrologue(void)
{
    MediaSDL::Sgl().QuitVideoIfRequired();
}

void
PlatformVideoUtils::ModeChangeEpilogue(void)
{
}

bool
PlatformVideoUtils::ModeSelectFixAttempt(Mushware::U32 inIteration)
{
    bool tryAgain=false;
    
    return tryAgain;
}
