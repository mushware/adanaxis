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
 * $Id: MediaSDL.cpp,v 1.8 2002/08/16 19:46:07 southa Exp $
 * $Log: MediaSDL.cpp,v $
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

auto_ptr<MediaSDL> MediaSDL::m_instance;

MediaSDL::~MediaSDL()
{
    if (m_inited != 0)
    {
#if !defined(__APPLE__) && !defined(MACOSX)
        // Curiously this crashes with a malloc problem on MacOS X
        cerr << "Quitting SDL" << endl;
        SDL_Quit();
#endif
    }
}

void
MediaSDL::Init(U32 inWhich)
{
    if (m_inited == 0)
    {
        if (SDL_Init(inWhich) < 0)
        {
            throw(DeviceFail("Unable to init SDL: "+string(SDL_GetError())));
        }
    }
    else
    {
        U32 whichNotDone=inWhich & ~m_inited;
        if (SDL_InitSubSystem(whichNotDone) < 0)
        {
            throw(DeviceFail("Unable to init SDL: "+string(SDL_GetError())));
        }
    }
    m_inited=inWhich;
}
