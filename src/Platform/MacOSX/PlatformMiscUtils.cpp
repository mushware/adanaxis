/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/




/*
 * $Id: PlatformMiscUtils.cpp,v 1.9 2002/10/10 13:51:17 southa Exp $
 * $Log: PlatformMiscUtils.cpp,v $
 * Revision 1.9  2002/10/10 13:51:17  southa
 * Speed fixes and various others
 *
 * Revision 1.8  2002/10/06 22:10:00  southa
 * Initial lighting test
 *
 * Revision 1.7.4.2  2002/09/07 10:58:41  southa
 * Removed usleep
 *
 * Revision 1.7.4.1  2002/09/04 10:18:04  southa
 * Fixed for MacOS X 10.2
 *
 * Revision 1.7  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/27 00:07:06  southa
 * Catch up
 *
 * Revision 1.2  2002/06/13 15:15:56  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.1  2002/06/11 16:25:00  southa
 * New paths to data files
 *
 */

#include "mushPlatform.h"

#include <ApplicationServices/ApplicationServices.h>


void
PlatformMiscUtils::Initialise(void)
{
    char *home = getenv("HOME");
    if (home != NULL)
    {
        CoreGlobalConfig::Instance().Set("HOME", home);
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

    return appPath;
}
void
PlatformMiscUtils::TweakArgs(string& ioStr)
{
    if (ioStr.substr(0, 4) == "-psn") ioStr="";
}

void
PlatformMiscUtils::VBLWait(void)
{
    static bool enabled=true;
    if (!enabled) return;
    CGPoint point;
    CGDisplayCount dispCount;
    point.x=0;
    point.y=0;
    CGDirectDisplayID dispId;
    if (CGGetDisplaysWithPoint(point, 1, &dispId, &dispCount) == kCGErrorSuccess)
    {
        if (dispCount == 1)
        {
            CGRect cgrect=CGDisplayBounds(dispId);
            CGDisplayWaitForBeamPositionOutsideLines(dispId, 0, 
                static_cast<CGBeamPosition>(cgrect.origin.y + cgrect.size.height - 1));
            for (U32 i=0;; ++i)
            {
                if (CGDisplayBeamPosition(dispId) > cgrect.origin.y + cgrect.size.height - 1) break;
                if (i > 1e6)
                {
                    cerr << "Waited too long for VBL.  Disabling" << endl;
                    enabled=false;
                    break;
                }
                // Possible detrimental effects with usleep
                // usleep(100);
            }
            //cerr << "Beam is at " << CGDisplayBeamPosition(dispId) << endl;
        }
    }
}

