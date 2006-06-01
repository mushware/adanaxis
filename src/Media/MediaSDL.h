//%includeGuardStart {
#ifndef MEDIASDL_H
#define MEDIASDL_H
//%includeGuardStart } CItEkt7MJUT9WuobW/ZI/g
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSDL.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } T42h8hBf49T+dFOol6izVQ
/*
 * $Id: MediaSDL.h,v 1.26 2005/05/27 19:25:24 southa Exp $
 * $Log: MediaSDL.h,v $
 * Revision 1.26  2005/05/27 19:25:24  southa
 * win32 build fixes
 *
 * Revision 1.25  2005/05/26 16:05:29  southa
 * win32 support
 *
 * Revision 1.24  2005/05/26 00:46:40  southa
 * Made buildable on win32
 *
 * Revision 1.23  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.22  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.21  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.20  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.19  2003/08/21 23:09:01  southa
 * Fixed file headers
 *
 * Revision 1.18  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.17  2003/01/18 17:05:47  southa
 * Singleton work
 *
 * Revision 1.16  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.15  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.14  2002/12/29 20:30:55  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.13  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
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

#include "mushMushcore.h"

class MediaSDL : public MushcoreSingleton<MediaSDL>
{
public:
    MediaSDL();
    ~MediaSDL();

    void Init(Mushware::U32 inWhich);
    void QuitIfRequired(Mushware::U32 inWhich);
    void InitVideo(void) { Init(SDL_INIT_VIDEO); }
    void InitVideoIfRequired(void) { InitVideo(); }
    void QuitVideoIfRequired(void) { QuitIfRequired(SDL_INIT_VIDEO); }
    void InitAudio(void) { Init(SDL_INIT_AUDIO); }
    
protected:

private:
    Mushware::U32 m_inited;
    bool m_firstInitCalled;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
