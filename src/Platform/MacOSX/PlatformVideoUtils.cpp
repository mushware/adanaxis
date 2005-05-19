//%Header {
/*****************************************************************************
 *
 * File: src/Platform/MacOSX/PlatformVideoUtils.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } 5uxxs82jaFpMYF4+/fHOsg
/*
 * $Id: PlatformVideoUtils.cpp,v 1.17 2005/04/19 23:25:42 southa Exp $
 * $Log: PlatformVideoUtils.cpp,v $
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
#include "mushPlatform.h"

#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

using namespace Mushware;
using namespace std;

PlatformVideoUtils *PlatformVideoUtils::m_instance=NULL;

PlatformVideoUtils::PlatformVideoUtils()
{
    m_modeDefs.push_back(GLModeDef("640x480 window",640,480,32,0, GLModeDef::kScreenWindow, GLModeDef::kCursorShow, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("800x600 window",800,600,32,0, GLModeDef::kScreenWindow, GLModeDef::kCursorShow, GLModeDef::kSyncSoft));
    
    // Find all display modes available on all displays and add them
    // to the list
    
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
        
        std::ostringstream modeStrm;
        modeStrm << xSize << "x" << ySize;
        m_modeDefs.push_back(GLModeDef(modeStrm.str(), xSize, ySize, 32, 0,  GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncHard));
    }
}

U32
PlatformVideoUtils::DefaultModeGet(void) const
{
    U32 retVal=0;
    for (U32 i=2; i < m_modeDefs.size(); ++i)
    {
        if (m_modeDefs[i].WidthGet() == 640 &&
            m_modeDefs[i].HeightGet() == 480)
        {
            retVal = i;   
        }
    }
    return retVal;
}

const GLModeDef&
PlatformVideoUtils::ModeDefGet(U32 inNum)
{
    if (inNum >= m_modeDefs.size())
    {
        ostringstream message;
        message << "Mode number " << inNum << " too high (max " << m_modeDefs.size() << ")";
        throw(MushcoreReferenceFail(message.str()));
    }
    return m_modeDefs[inNum];
}

U32
PlatformVideoUtils::PreviousModeDef(U32 inNum) const
{
    if (inNum == 0) return m_modeDefs.size()-1;
    return inNum-1;
}


U32
PlatformVideoUtils::NextModeDef(U32 inNum) const
{
    if (inNum+1 >= m_modeDefs.size()) return 0;
    return inNum+1;
}

U32
PlatformVideoUtils::NumModesGet(void) const
{
    return m_modeDefs.size();
}

void
PlatformVideoUtils::RenderModeInfo(U32 inNum) const
{
    const GLModeDef& modeDef=PlatformVideoUtils::Sgl().ModeDefGet(inNum);
    GLState::ColourSet(1.0,1.0,1.0,0.8);
    GLUtils::PushMatrix();
    GLUtils gl;
    GLString glStr;
    gl.MoveTo(0,0.05);

    glStr=GLString("Display mode", GLFontRef("font-mono1", 0.03), 0);
    glStr.Render();

    gl.MoveTo(0,0);
    
    glStr=GLString(modeDef.NameGet(), GLFontRef("font-mono1", 0.04), 0);
    glStr.Render();
    
#if 0
    gl.MoveTo(0,-0.05);
    switch (modeDef.SyncGet())
    {
        case GLModeDef::kSyncHard:
            glStr=GLString("Hard sync provides a stable display", GLFontRef("font-mono1", 0.025), 0);
            glStr.Render();
            glStr.TextSet("but sometimes with slower frame rates");
            gl.MoveTo(0,-0.08);
            glStr.Render();
            break;

        case GLModeDef::kSyncSoft:
            glStr=GLString("Soft sync can provide better frame rates", GLFontRef("font-mono1", 0.025), 0);
            glStr.Render();
            glStr.TextSet("but with slight visual distortion");
            gl.MoveTo(0,-0.08);
            glStr.Render();
            break;
            
        default:
            break;
    }
#endif
    GLUtils::PopMatrix();
}

void
PlatformVideoUtils::VBLWait(void)
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
}

void
PlatformVideoUtils::ModeChangeEpilogue(void)
{
}
