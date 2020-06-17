//%includeGuardStart {
#ifndef MEDIAAUDIOSDL_H
#define MEDIAAUDIOSDL_H
//%includeGuardStart } LQgk82SJ4HBQGLE5aLpDXA
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioSDL.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 5pTZJ98kVR4oUWdq5qUIPg
/* Name changed from MediaAudio to MediaAudioSDL 2002/08/23 */

/*
 * $Id: MediaAudioSDL.h,v 1.20 2007/04/16 18:51:00 southa Exp $
 * $Log: MediaAudioSDL.h,v $
 * Revision 1.20  2007/04/16 18:51:00  southa
 * Voice work
 *
 * Revision 1.19  2006/12/14 00:33:48  southa
 * Control fix and audio pacing
 *
 * Revision 1.18  2006/12/11 18:54:18  southa
 * Positional audio
 *
 * Revision 1.17  2006/12/11 15:01:48  southa
 * Snapshot
 *
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
    void Play(MediaSound& inSound, Mushware::tVal inVolume, Mushware::t4Val inPosition,
              Mushware::U32 inFlags);
    void VoicePlay(MediaSound& inSound);
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
    virtual void VoiceVolumeSet(Mushware::tVal inVolume);

protected:
    void ChannelUpdate(Mushware::U32 inChannel);
    void ChannelTrigger(Mushware::U32 inChannel);
    
private:
    Mushware::U32 m_softChannels;
    Mix_Music *m_music;
    Mushware::U32 m_audioVolume;
    Mushware::U32 m_voiceVolume;
    mutable Mushware::U32 m_errCtr;
    Mushware::U32 m_lastTickerMsec;
    MushFileFile m_musicMushFile;
    void *m_fpMix_LoadMUS_RW;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
