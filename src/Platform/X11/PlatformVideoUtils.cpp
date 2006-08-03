//%Header {
/*****************************************************************************
 *
 * File: src/Platform/X11/PlatformVideoUtils.cpp
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
//%Header } 0anIi7FRbv5HCqf7j1JbnA
/*
 * $Id: PlatformVideoUtils.cpp,v 1.20 2006/06/01 15:39:58 southa Exp $
 * $Log: PlatformVideoUtils.cpp,v $
 * Revision 1.20  2006/06/01 15:39:58  southa
 * DrawArray verification and fixes
 *
 * Revision 1.19  2005/06/09 00:04:59  southa
 * X11 tweaks
 *
 * Revision 1.18  2005/06/08 20:59:52  southa
 * X11 release
 *
 * Revision 1.17  2005/06/06 15:07:10  southa
 * X11 work
 *
 * Revision 1.16  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.15  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.14  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.13  2003/08/21 23:09:36  southa
 * Fixed file headers
 *
 * Revision 1.12  2003/04/13 08:39:18  southa
 * Bring window to foreground on mode change
 *
 * Revision 1.11  2003/02/06 18:55:28  southa
 * Linux build fixes
 *
 * Revision 1.10  2003/01/20 10:45:32  southa
 * Singleton tidying
 *
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
#include "mushMedia.h"
#include "mushPlatform.h"

#if 0
#if defined(HAVE_SDL_SDL_H)
#include <SDL/SDL.h>
#else
#if defined(HAVE_SDL_H)
#include <SDL.h>
#else
#include "SDL.h"
#endif
#endif
#endif

using namespace Mushware;
using namespace std;

PlatformVideoUtils *PlatformVideoUtils::m_instance=NULL;

PlatformVideoUtils::PlatformVideoUtils()
{
    m_modeDefs.push_back(GLModeDef("640x480 window",640,480,32,0, 
        GLModeDef::kScreenWindow, GLModeDef::kCursorShow, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("800x600 window",800,600,32,0, 
        GLModeDef::kScreenWindow, GLModeDef::kCursorShow, GLModeDef::kSyncSoft));

    m_modeDefs.push_back(GLModeDef("640x480",640,480,32,0, 
        GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));

    m_modeDefs.push_back(GLModeDef("800x600",800,600,32,0, 
        GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));

    m_modeDefs.push_back(GLModeDef("1024x768",1024,768,32,0, 
        GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));

    m_modeDefs.push_back(GLModeDef("1280x1024",1280,1024,32,0, 
        GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("1600x1200",1600,1200,32,0, 
        GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));

    for (U32 i=0; i<10; ++i)
    {
        std::vector<U32> modeDef;
        std::ostringstream varName;
        varName << "X11_MODE_" << i;
        MushcoreScalar textValue;
	if (MushcoreEnv::Sgl().VariableGetIfExists(textValue, varName.str()))
	{
            std::istringstream strIStrm(textValue.StringGet());
            MushcoreXMLIStream xmlIStrm(strIStrm);
            try
	    {
                xmlIStrm >> modeDef;
                if (modeDef.size() >= 2)
	        {
	            std::ostringstream modeName;
	            modeName << "User: " << modeDef[0] << "x" << modeDef[1];
	            m_modeDefs.push_back(GLModeDef(modeName.str(),modeDef[0],modeDef[1],
		        32,0, GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));
                }
	    }
	    catch (MushcoreFail& e)
	    {
	        cerr << "Mode syntax error in " << varName.str() << endl;
	    }
	}
    }

    SDL_Rect **ppModes = NULL;

    MushcoreScalar useSDLModes(0);
    if (MushcoreEnv::Sgl().VariableGetIfExists(useSDLModes, "X11_USE_SDL_LISTMODES"));
    {
        if (useSDLModes.BoolGet())
        {
            ppModes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
        }
    }

    if (ppModes != NULL && ppModes != (SDL_Rect **) -1)
    {
        for (U32 i=0; ppModes[i] != NULL; ++i)
        {
            SDL_Rect *pMode = ppModes[i];

            bool addMode = true;
            for (U32 j=0; j<m_modeDefs.size(); ++j)
            {
                if (pMode->w == m_modeDefs[i].WidthGet() && pMode->h == m_modeDefs[i].HeightGet())
                {
                    // Mode already there so don't add
                    addMode = false;
                }
            }
            if (addMode)
            {
	        std::ostringstream modeName;
	        modeName << pMode->w << "x" << pMode->h;
                m_modeDefs.push_back(GLModeDef(modeName.str(), pMode->w, pMode->h, 32, 0, 
                    GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));
            }
        }
    }
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
        message << "Mode number " << inNum << " too high (max " << 
m_modeDefs.size() << ")";
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
    /* Difficult to wait for VBL on X11.  Just install a crude speed limit
     * for the moment
     */
    static U32 lastMsec = 0;
    U32 msecNow = SDL_GetTicks();
    U32 msecSince = msecNow - lastMsec;
    if (msecSince < 11)
    {
        PlatformMiscUtils::SleepMsec(11 - msecSince);
    }
    lastMsec = msecNow;
}

void
PlatformVideoUtils::ForceShowCursor(void)
{
}

void
PlatformVideoUtils::AppActivate(void)
{
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

