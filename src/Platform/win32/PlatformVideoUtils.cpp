//%Header {
/*****************************************************************************
 *
 * File: src/Platform/win32/PlatformVideoUtils.cpp
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
//%Header } KCxXYygl0O3Oosas7+Vmbw
/*
 * $Id: PlatformVideoUtils.cpp,v 1.23 2006/06/30 17:26:11 southa Exp $
 * $Log: PlatformVideoUtils.cpp,v $
 * Revision 1.23  2006/06/30 17:26:11  southa
 * Render prelude
 *
 * Revision 1.22  2006/06/01 15:39:58  southa
 * DrawArray verification and fixes
 *
 * Revision 1.21  2005/06/03 23:25:11  southa
 * Tweaks for win32 release 0.1.1.
 *
 * Revision 1.20  2005/06/03 15:21:19  southa
 * win32 build fixes
 *
 * Revision 1.19  2005/06/03 13:36:44  southa
 * win32 build fixes
 *
 * Revision 1.18  2005/05/26 16:05:29  southa
 * win32 support
 *
 * Revision 1.17  2005/05/26 00:46:41  southa
 * Made buildable on win32
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
 * Revision 1.11  2003/01/20 10:45:32  southa
 * Singleton tidying
 *
 * Revision 1.10  2003/01/12 17:33:02  southa
 * Mushcore work
 *
 * Revision 1.9  2002/12/29 21:00:01  southa
 * More build fixes
 *
 * Revision 1.8  2002/12/20 13:17:48  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/12/10 10:54:28  southa
 * AppActivate and input cleanup
 *
 * Revision 1.6  2002/11/12 11:49:22  southa
 * Initial MHTML processing
 *
 * Revision 1.5  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.4  2002/10/20 22:31:06  southa
 * Fixed win32 release build
 *
 * Revision 1.3  2002/10/20 20:48:07  southa
 * win32 work
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

#define NOMINMAX
#include <direct.h>
#include <windows.h>
#include <ddraw.h>
#include <mmsystem.h>

#include <algorithm>

using namespace Mushware;
using namespace std;

PlatformVideoUtils *PlatformVideoUtils::m_instance=NULL;

static HRESULT WINAPI PlatformVideoUtils_EnumDisplayModesCallback(LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext)
{
    reinterpret_cast<PlatformVideoUtils *>(lpContext)->ModeAdd(lpDDSurfaceDesc->dwWidth, lpDDSurfaceDesc->dwHeight);
    return DDENUMRET_OK;
}

void
PlatformVideoUtils::ModeAdd(Mushware::U32 inWidth, Mushware::U32 inHeight)
{
    std::pair<long, long> newSize(inWidth, inHeight);
    if (inWidth >= 640 && inHeight >= 480)
    {
        if (std::find(m_modesSoFar.begin(), m_modesSoFar.end(), newSize) == m_modesSoFar.end())
        {
            m_modesSoFar.push_back(newSize);
        }
    }
}

PlatformVideoUtils::PlatformVideoUtils() :
    m_threadAttached(false)
{
    bool safeMode = false;
    const MushcoreScalar *pScalar;

    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "SAFE_MODE"))
    {
        if (pScalar->U32Get())
        {
            safeMode = true;
        }
    }

    m_modeDefs.push_back(GLModeDef("640x480 window",640,480,32,0, GLModeDef::kScreenWindow, GLModeDef::kCursorShow, GLModeDef::kSyncSoft));
    m_modeDefs.push_back(GLModeDef("800x600 window",800,600,32,0, GLModeDef::kScreenWindow, GLModeDef::kCursorShow, GLModeDef::kSyncSoft));
    
    // Find all display modes available on the default display and add them
    // to the list
    
    m_modesSoFar.resize(0);

    if (!safeMode)
    {
        LPDIRECTDRAW iDirectDraw;

        typedef HRESULT (WINAPI *tfpDirectDrawCreate)(GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter);
        tfpDirectDrawCreate fpDirectDrawCreate = NULL;
        HINSTANCE pLibrary = LoadLibrary("DDRAW.DLL");

        if (pLibrary != NULL)
        {
            fpDirectDrawCreate = (tfpDirectDrawCreate) GetProcAddress(pLibrary, "DirectDrawCreate");
            FreeLibrary(pLibrary);
        }

        if (fpDirectDrawCreate != NULL && fpDirectDrawCreate(NULL, &iDirectDraw, NULL) == DD_OK)
        {
            LPDIRECTDRAW2 iDirectDraw2;
            if (iDirectDraw->QueryInterface(IID_IDirectDraw2, (LPVOID *) &iDirectDraw2) == DD_OK)
            {
                iDirectDraw2->EnumDisplayModes(0, NULL, this, PlatformVideoUtils_EnumDisplayModesCallback);
                iDirectDraw2->Release();
            }
            iDirectDraw->Release();
        }
    }
    
    if (m_modesSoFar.size() == 0)
    {
        // Couldn't get any modes so invent them
        m_modesSoFar.push_back(std::pair<long, long>(640,480));
        m_modesSoFar.push_back(std::pair<long, long>(800,600));
        m_modesSoFar.push_back(std::pair<long, long>(1024,768));
    }

    std::sort(m_modesSoFar.begin(), m_modesSoFar.end());
    
    for (U32 i=0; i<m_modesSoFar.size(); ++i)
    {
        U32 xSize = m_modesSoFar[i].first;
        U32 ySize = m_modesSoFar[i].second;
        
        std::ostringstream modeStrm;
        modeStrm << xSize << "x" << ySize;
        m_modeDefs.push_back(GLModeDef(modeStrm.str(), xSize, ySize, 32, 0,  GLModeDef::kScreenFull, GLModeDef::kCursorHide, GLModeDef::kSyncSoft));
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

void
PlatformVideoUtils::AppActivate(void)
{
}

void
PlatformVideoUtils::ModeChangePrologue(void)
{
#if 0
    m_fgThreadID = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
    DWORD ourThreadID = GetCurrentThreadId();

    if (m_fgThreadID != ourThreadID)
    {
	    AttachThreadInput(m_fgThreadID, ourThreadID, true);
        m_threadAttached = true;
    }
#endif
}

void
PlatformVideoUtils::ModeChangeEpilogue(void)
{
#if 0
    if (m_threadAttached)
    {
	    DWORD ourThreadID = GetCurrentThreadId();
	    AttachThreadInput(m_fgThreadID, ourThreadID, false);
	    m_threadAttached = false;
    }
#endif
    
#if (SDL_MAJOR_VERSION >= 1) && (SDL_MINOR_VERSION >= 2) && (SDL_PATCHLEVEL >= 10)
    // Beyond version 1.2.10 SDL handles this for us using the SDL_GL_SWAP_CONTROL attribute
#else
    typedef void (APIENTRY * WGLSWAPINTERVALEXT) (int);

    WGLSWAPINTERVALEXT wglSwapIntervalEXT = (WGLSWAPINTERVALEXT) wglGetProcAddress("wglSwapIntervalEXT");

    if (wglSwapIntervalEXT != NULL)
    {
        wglSwapIntervalEXT(1);
    }
#endif
}


	
