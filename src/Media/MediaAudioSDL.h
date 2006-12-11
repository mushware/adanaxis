//%includeGuardStart {
#ifndef MEDIAAUDIOSDL_H
#define MEDIAAUDIOSDL_H
//%includeGuardStart } LQgk82SJ4HBQGLE5aLpDXA
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioSDL.h
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
//%Header } vvu0jaD31bFVZCLJ1xDZzg
/* Name changed from MediaAudio to MediaAudioSDL 2002/08/23 */

/*
 * $Id: MediaAudioSDL.h,v 1.16 2006/12/11 13:28:23 southa Exp $
 * $Log: MediaAudioSDL.h,v $
 * Revision 1.16  2006/12/11 13:28:23  southa
 * Snapshot
 *
 * Revision 1.15  2006/07/28 16:52:21  southa
 * Options work
 *
 * Revision 1.14  2006/07/26 16:37:22  southa
 * Options menu
 *
 * Revision 1.13  2006/06/01 15:39:13  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.11  2005/04/19 23:25:41  southa
 * Mode switching and recognition
 *
 * Revision 1.10  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:09:01  southa
 * Fixed file headers
 *
 * Revision 1.7  2002/12/29 20:30:55  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.6  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 09:02:59  southa
 * Fixed corrupted file header
 *
 * Revision 1.3  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.1  2002/08/24 13:12:31  southa
 * Null MediaAudio device
 *
 * Revision 1.10  2002/08/19 09:59:36  southa
 * Removed sound callbacks, used polling
 *
 * Revision 1.9  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 * Revision 1.8  2002/08/16 19:46:07  southa
 * MediaSound work
 *
 * Revision 1.7  2002/08/13 17:50:21  southa
 * Added playsound command
 *
 * Revision 1.6  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.2  2002/06/20 11:06:15  southa
 * Updated for cygwin
 *
 * Revision 1.1  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 */

#include "MediaAudio.h"
#include "MediaSDL.h"
#include "MediaStandard.h"
#include "MediaAudioSDLChannelDef.h"

class MediaSound;
class MediaSoundStream;

class MediaAudioSDL : public MediaAudio
{
public:
    MediaAudioSDL();
    virtual ~MediaAudioSDL();
    void PlayMusic(const std::string& inName);
    void Play(MediaSound& inSound);
    void Play(MediaSound& inSound, Mushware::tVal inVolume, Mushware::t4Val inPosition);
    void Play(MediaSoundStream& inSoundStream, Mushware::U32 inLoop=10000);
    void SoundHalt(MediaSound& inSound);
    void Load(MediaSound& inSound) const;
    void Load(MediaSoundStream& inSoundStream);
    void Free(MediaSound& inSound) const;
    void Ticker(void);
    virtual void MusicFadeIn(Mushware::tVal inMsec);
    virtual void MusicFadeOut(Mushware::tVal inMsec);
    virtual void MusicVolumeSet(Mushware::tVal inVolume);
    virtual void AudioVolumeSet(Mushware::tVal inVolume);

private:
    void ChannelStateSet(Mushware::U32 inChannel, Mushware::U32 inState, MediaSound *inSound);

    Mushware::U32 m_softChannels;
    Mix_Music *m_music;
    Mushware::U32 m_audioVolume;
    mutable Mushware::U32 m_errCtr;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
