/*
 * $Id$
 * $Log$
 */

#include "MediaSDL.h"

MediaSDL *MediaSDL::m_instance=NULL;

MediaSDL::~MediaSDL()
{
    if (m_inited != 0)
    {
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
