#ifndef MEDIASDL_H
#define MEDIASDL_H
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
 * $Id: MediaSDL.h,v 1.12 2002/12/12 18:38:58 southa Exp $
 * $Log: MediaSDL.h,v $
 * Revision 1.12  2002/12/12 18:38:58  southa
 * Mustl separation
 *
 * Revision 1.11  2002/11/02 11:22:51  southa
 * Simplified UDP send and receive
 *
 * Revision 1.10  2002/10/31 15:52:15  southa
 * First network code
 *
 * Revision 1.9  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.8  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 * Revision 1.7  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.5  2002/08/05 21:23:22  southa
 * Potential fix for missing SDL_Quit
 *
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
    void Init(Mushware::U32 inWhich);
    void QuitIfRequired(Mushware::U32 inWhich);
    void InitVideo(void) { Init(SDL_INIT_VIDEO); }
    void QuitVideoIfRequired(void) { QuitIfRequired(SDL_INIT_VIDEO); }
    void InitAudio(void) { Init(SDL_INIT_AUDIO); }
    
protected:
    MediaSDL(): m_inited(0), m_firstInitCalled(false) {}

private:
    static auto_ptr<MediaSDL> m_instance;
    Mushware::U32 m_inited;
    bool m_firstInitCalled;
};

#endif
