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
 * $Id: PlatformVideoUtils.cpp,v 1.9 2003/01/12 17:33:02 southa Exp $
 * $Log: PlatformVideoUtils.cpp,v $
 * Revision 1.9  2003/01/12 17:33:02  southa
 * Mushcore work
 *
 * Revision 1.8  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.7  2002/12/20 13:17:48  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/11/12 11:49:22  southa
 * Initial MHTML processing
 *
 * Revision 1.5  2002/10/23 13:53:35  southa
 * Changed default video mode to 0
 *
 * Revision 1.4  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.3  2002/10/21 10:54:33  southa
 * X11 build updates
 *
 * Revision 1.2  2002/10/15 14:39:21  southa
 * Include fixes
 *
 * Revision 1.1  2002/10/15 14:02:32  southa
 * Mode changes
 *
 * Revision 1.1  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 */

#include "mushGL.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

PlatformVideoUtils *PlatformVideoUtils::m_instance=NULL;

PlatformVideoUtils::PlatformVideoUtils()
{
    m_modeDefs.push_back(GLModeDef("640x480 window",640,480,32,0, GLModeDef::kScreenWindow, GLModeDef::kCursorShow, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("800x600 window",800,600,32,0, GLModeDef::kScreenWindow, GLModeDef::kCursorShow, GLModeDef::kSyncSoft));

    m_modeDefs.push_back(GLModeDef("640x480",640,480,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));

    m_modeDefs.push_back(GLModeDef("800x600",800,600,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));

    m_modeDefs.push_back(GLModeDef("1024x768",1024,768,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));

    m_modeDefs.push_back(GLModeDef("1280x1024",1280,1024,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("1600x1200",1600,1200,32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));
;
}

U32
PlatformVideoUtils::DefaultModeGet(void) const
{
    return 0;
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
    GLUtils::PopMatrix();
}

void
PlatformVideoUtils::VBLWait(void)
{
}

void
PlatformVideoUtils::ForceShowCursor(void)
{
}

