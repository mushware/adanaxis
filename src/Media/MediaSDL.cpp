/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MediaSDL.cpp,v 1.23 2003/01/20 10:45:28 southa Exp $
 * $Log: MediaSDL.cpp,v $
 * Revision 1.23  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.22  2003/01/18 17:05:47  southa
 * Singleton work
 *
 * Revision 1.21  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.20  2003/01/13 14:32:01  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.19  2003/01/12 17:32:57  southa
 * Mushcore work
 *
 * Revision 1.18  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.17  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.16  2002/12/12 18:38:58  southa
 * Mustl separation
 *
 * Revision 1.15  2002/11/02 11:22:51  southa
 * Simplified UDP send and receive
 *
 * Revision 1.14  2002/10/31 15:52:15  southa
 * First network code
 *
 * Revision 1.13  2002/10/22 22:36:18  southa
 * Use SDL_INIT_NOPARACHUTE to avoid hang exit on MacOS 10.1.5
 *
 * Revision 1.12  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.11  2002/10/22 18:02:57  southa
 * Final tweaks
 *
 * Revision 1.10  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 * Revision 1.9  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/16 19:46:07  southa
 * MediaSound work
 *
 * Revision 1.7  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.6  2002/08/05 22:31:45  southa
 * Removed debug code
 *
 * Revision 1.5  2002/08/05 22:19:44  southa
 * Removed SDL_Quit for MacOS X
 *
 * Revision 1.4  2002/08/05 21:23:22  southa
 * Potential fix for missing SDL_Quit
 *
 * Revision 1.3  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.1  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 */

#include "MediaSDL.h"

#include "MediaAudio.h"
#include "MediaSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MediaSDL);

MediaSDL::MediaSDL() :
    m_inited(0),
    m_firstInitCalled(false)
{
    if (MushcoreSingleton<MediaSDL>::SingletonExists())
    {
        throw(MushcoreLogicFail("Attempt to create a second MediaSDL object"));
    }
}

MediaSDL::~MediaSDL()
{
    // Delete the MediaAudio object to stop the sounds
    MushcoreSingleton<MediaAudio>::SingletonDestroy();

    if (m_firstInitCalled)
    {
        SDL_Quit();
    }
}

void
MediaSDL::Init(U32 inWhich)
{
    if (m_firstInitCalled)
    {
        U32 whichNotDone=inWhich & ~m_inited;
        if (whichNotDone != 0)
        {
            if (SDL_InitSubSystem(whichNotDone | SDL_INIT_NOPARACHUTE) < 0)
            {
                throw(MushcoreDeviceFail("Unable to init SDL: "+string(SDL_GetError())));
            }
        }
    }
    else
    {
        if (SDL_Init(inWhich | SDL_INIT_NOPARACHUTE) < 0)
        {
            throw(MushcoreDeviceFail("Unable to init SDL: "+string(SDL_GetError())));
        }
        m_firstInitCalled=true;
    }
    m_inited |= inWhich;
}

void
MediaSDL::QuitIfRequired(U32 inWhich)
{
    U32 toQuit = m_inited & inWhich;

    SDL_QuitSubSystem(toQuit);

    m_inited &= ~inWhich;
}

