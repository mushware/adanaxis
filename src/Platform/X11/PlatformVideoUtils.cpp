//%Header {
/*****************************************************************************
 *
 * File: src/Platform/X11/PlatformVideoUtils.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } B7lzXPUBnr4pVPk102bAow
/*
 * $Id: PlatformVideoUtils.cpp,v 1.28 2007/06/29 16:48:29 southa Exp $
 * $Log: PlatformVideoUtils.cpp,v $
 * Revision 1.28  2007/06/29 16:48:29  southa
 * Mandriva build
 *
 * Revision 1.27  2007/06/29 12:05:03  southa
 * Mandriva packaging
 *
 * Revision 1.26  2007/06/28 15:15:18  southa
 * Mandriva fixes
 *
 * Revision 1.25  2007/06/27 11:56:44  southa
 * Debian packaging
 *
 * Revision 1.24  2007/06/25 17:58:50  southa
 * X11 fixes
 *
 * Revision 1.23  2007/06/24 21:09:42  southa
 * X11 support
 *
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
}

void
PlatformVideoUtils::Acquaint(void)
{
    m_modeDefs.push_back(GLModeDef(640, 480, false));
    m_modeDefs.push_back(GLModeDef(800, 600, false));

    std::vector< std::pair<U32, U32> > modesSoFar;

    modesSoFar.push_back(std::pair<U32, U32>(640, 480));
    modesSoFar.push_back(std::pair<U32, U32>(800, 600));
    modesSoFar.push_back(std::pair<U32, U32>(1024, 768));
    modesSoFar.push_back(std::pair<U32, U32>(1280, 1024));
    modesSoFar.push_back(std::pair<U32, U32>(1600, 1200));

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
                    modesSoFar.push_back(std::pair<U32, U32>(modeDef[0], modeDef[1]));
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
            const SDL_Rect *pMode = ppModes[i];

            std::pair<U32, U32> newSize(pMode->w, pMode->h);

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

bool
PlatformVideoUtils::ModeSelectFixAttempt(Mushware::U32 inIteration)
{
    bool tryAgain=false;
    
    switch (inIteration)
    {
        case 0:
        {
            char *pDisplay = getenv("DISPLAY");
            if (pDisplay == NULL)
            {
                MushcoreLog::Sgl().ErrorLog() << "DISPLAY environment variable not set - cannot access X display" << endl;
            }
            else
            {
                std::string displayEnv(pDisplay);
                bool isModified = false;
                if (displayEnv.size() >= 2 && displayEnv.substr(displayEnv.size()-2, 2) == ":1")
                {
                    /* Patch for '3D desktop' problem where we are presented with a virtual display :1
                     * but must open :0 for 3D support
                     */
                    displayEnv.replace(displayEnv.size()-2, 2, ":0");
                    isModified = true;
                }
                else if (displayEnv.size() >= 4 && displayEnv.substr(displayEnv.size()-4, 2) == ":1")
                {
                    // Same for :1.0
                    displayEnv.replace(displayEnv.size()-4, 2, ":0");
                    isModified = true;
                }
                
                if (isModified)
                {
                    setenv("DISPLAY", displayEnv.c_str(), 1 /* overwrite */);
                    MushcoreLog::Sgl().WarningLog() << "Altered DISPLAY environment from '" << pDisplay << "' to '" << displayEnv <<
                            "' in an attempt to solve virtual desktop problem" << endl;

                    setenv("DISPLAY=", displayEnv.c_str(), 1 /* overwrite */);

                    tryAgain = true;
                }
            }
        }
        break;

        default:
            break;
    }
    return tryAgain;
}


