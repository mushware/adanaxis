/*
 * $Id: PlatformVideoUtils.cpp,v 1.2 2002/10/15 14:02:31 southa Exp $
 * $Log: PlatformVideoUtils.cpp,v $
 * Revision 1.2  2002/10/15 14:02:31  southa
 * Mode changes
 *
 * Revision 1.1  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 */

#include "mushPlatform.h"
#include "mushGL.h"

#include <ApplicationServices/ApplicationServices.h>

PlatformVideoUtils *PlatformVideoUtils::m_instance=NULL;

PlatformVideoUtils::PlatformVideoUtils()
{
    m_modeDefs.push_back(GLModeDef("640x480 window",640,480,32,0, GLModeDef::kScreenWindow, GLModeDef::kCursorShow, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("800x600 window",800,600,32,0, GLModeDef::kScreenWindow, GLModeDef::kCursorShow, GLModeDef::kSyncSoft));

    m_modeDefs.push_back(GLModeDef("640x480 no sync",640,480,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncNone));
    m_modeDefs.push_back(GLModeDef("640x480 soft sync",640,480,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("640x480 hard sync",640,480,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncHard));
    m_modeDefs.push_back(GLModeDef("800x600 soft sync",800,600,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("800x600 hard sync",800,600,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncHard));
    m_modeDefs.push_back(GLModeDef("1024x768 soft sync",1024,768,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("1024x768 hard sync",1024,768,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncHard));
    m_modeDefs.push_back(GLModeDef("1280x1024 soft sync",1280,1024,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("1280x1024 hard sync",1280,1024,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncHard));
    m_modeDefs.push_back(GLModeDef("1600x1200 no sync",1600,1200,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncNone));
    m_modeDefs.push_back(GLModeDef("1600x1200 soft sync",1600,1200,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("1600x1200 hard sync",1600,1200,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncHard));
}

U32
PlatformVideoUtils::DefaultModeGet(void) const
{
    return 4;
}

const GLModeDef&
PlatformVideoUtils::ModeDefGet(U32 inNum)
{
    if (inNum >= m_modeDefs.size())
    {
        ostringstream message;
        message << "Mode number " << inNum << " too high (max " << m_modeDefs.size() << ")";
        throw(ReferenceFail(message.str()));
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

void
PlatformVideoUtils::RenderModeInfo(U32 inNum) const
{
    const GLModeDef& modeDef=PlatformVideoUtils::Instance().ModeDefGet(inNum);
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
    gl.MoveTo(0,-0.05);
    switch (modeDef.SyncGet())
    {
        case GLModeDef::kSyncHard:
            glStr=GLString("Hard sync provides a stable display", GLFontRef("font-mono1", 0.025), 0);
            glStr.Render();
            glStr.TextSet("but sometimes with slower frame rates");
            gl.MoveTo(0,-0.07);
            glStr.Render();
            break;

        case GLModeDef::kSyncSoft:
            glStr=GLString("Soft sync can provide better frame rates", GLFontRef("font-mono1", 0.025), 0);
            glStr.Render();
            glStr.TextSet("but with slight visual distortion");
            gl.MoveTo(0,-0.07);
            glStr.Render();
            break;
            
        default:
            break;
    }
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

