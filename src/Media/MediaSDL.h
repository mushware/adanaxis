/*
 * $Id$
 * $Log$
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
