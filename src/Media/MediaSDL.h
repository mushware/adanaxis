/*
 * $Id: MediaSDL.h,v 1.1 2002/06/10 15:16:59 southa Exp $
 * $Log: MediaSDL.h,v $
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
    static MediaSDL& Instance(void) {return *((m_instance==NULL)?m_instance=new MediaSDL:m_instance);}
    void Init(U32 inWhich);
    void InitVideo(void) {Init(SDL_INIT_VIDEO);}
    void InitAudio(void) {Init(SDL_INIT_AUDIO);}
    
protected:
        MediaSDL(): m_inited(0) {}
private:
    static MediaSDL *m_instance;
    U32 m_inited;
};