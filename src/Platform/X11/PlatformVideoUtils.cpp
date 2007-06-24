//%Header {
/*****************************************************************************
 *
 * File: src/Platform/X11/PlatformVideoUtils.cpp
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
//%Header } Y+WzijXDRsG7dDElPwQlbQ
/*
 * $Id: PlatformVideoUtils.cpp,v 1.22 2007/04/18 09:23:23 southa Exp $
 * $Log: PlatformVideoUtils.cpp,v $
 * Revision 1.22  2007/04/18 09:23:23  southa
 * Header and level fixes
 *
 * Revision 1.21  2006/08/03 13:49:58  southa
 * X11 release work
 *
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
    m_modeDefs.push_back(GLModeDef(640, 480, false));
    m_modeDefs.push_back(GLModeDef(800, 600, false));
    m_modeDefs.push_back(GLModeDef(640, 480, true));
    m_modeDefs.push_back(GLModeDef(800, 600, true));
    m_modeDefs.push_back(GLModeDef(1024, 768, true));
    m_modeDefs.push_back(GLModeDef(1280, 1024, true));
    m_modeDefs.push_back(GLModeDef(1600, 1200, true));

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
	            m_modeDefs.push_back(GLModeDef(modeDef[0], modeDef[1], true));
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
                if (pMode->w == m_modeDefs[i].Width() && pMode->h == m_modeDefs[i].Height())
                {
                    // Mode already there so don't add
                    addMode = false;
                }
            }
            if (addMode)
            {
                m_modeDefs.push_back(GLModeDef(pMode->w, pMode->h, true));
            }
        }
    }
}

const GLModeDef&
PlatformVideoUtils::DefaultModeDef(void) const
{
    U32 modeNum = 0;
    
    for (U32 i=2; i < m_modeDefs.size(); ++i)
    {
        if (m_modeDefs[i].Width() == 1024 &&
            m_modeDefs[i].Height() == 768)
        {
            modeNum = i;   
        }
    }
    return m_modeDefs[modeNum];
}

Mushware::U32
PlatformVideoUtils::ModeDefFind(const GLModeDef& inModeDef) const
{
    U32 retVal = 0;
    for (U32 i=1; i<m_modeDefs.size(); ++i)
    {
        if (inModeDef == m_modeDefs[i])
        {
            retVal = i;
        }
    }
    return retVal;
}

const GLModeDef&
PlatformVideoUtils::PreviousModeDef(const GLModeDef& inModeDef) const
{
    U32 modeNum = ModeDefFind(inModeDef);

    if (modeNum == 0)
    {
        modeNum = m_modeDefs.size() - 1;
    }
    else
    {
        --modeNum;
    }
    return m_modeDefs[modeNum];
}

const GLModeDef&
PlatformVideoUtils::NextModeDef(const GLModeDef& inModeDef) const
{
    U32 modeNum = ModeDefFind(inModeDef);
    
    ++modeNum;
    if (modeNum >= m_modeDefs.size())
    {
        modeNum = 0;
    }
    
    return m_modeDefs[modeNum];
}

U32
PlatformVideoUtils::NumModesGet(void) const
{
    return m_modeDefs.size();
}

void
PlatformVideoUtils::RenderModeInfo(U32 inNum) const
{
    throw MushcoreLogicFail("RenderModeInfo deprecated");
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

