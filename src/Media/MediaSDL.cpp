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
 * $Id: MediaSDL.cpp,v 1.3 2002/07/06 18:04:20 southa Exp $
 * $Log: MediaSDL.cpp,v $
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

auto_ptr<MediaSDL> MediaSDL::m_instance;

MediaSDL::~MediaSDL()
{
    if (m_inited != 0)
    {
        cerr << "Quitting SDL" << endl;
        SDL_Quit();
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
