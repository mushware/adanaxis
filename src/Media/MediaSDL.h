#ifndef MEDIASDL_H
#define MEDIASDL_H
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
 * $Id: MediaSDL.h,v 1.4 2002/07/06 18:04:20 southa Exp $
 * $Log: MediaSDL.h,v $
 * Revision 1.4  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.1  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 */

// config.h
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_SDL_SDL_H)
#include <SDL/SDL.h>
#else
#if defined(HAVE_SDL_H)
#include <SDL.h>
#else
#include "SDL.h"
#endif
#endif

#if defined(HAVE_SDL_SDL_MIXER_H)
#include <SDL/SDL_mixer.h>
#else
#if defined(HAVE_SDL_MIXER_H)
#include <SDL_mixer.h>
#else
#include "SDL_mixer.h"
#endif
#endif

#include "mushCore.h"

class MediaSDL
{
public:
    ~MediaSDL();
    static MediaSDL& Instance(void)
    {
        if (m_instance.get() != NULL) return *m_instance;
        m_instance.reset(new MediaSDL);
        return *m_instance;
    }
    void Init(U32 inWhich);
    void InitVideo(void) {Init(SDL_INIT_VIDEO);}
    void InitAudio(void) {Init(SDL_INIT_AUDIO);}
    
protected:
    MediaSDL(): m_inited(0) {}

private:
    static auto_ptr<MediaSDL> m_instance;
    U32 m_inited;
};

#endif
