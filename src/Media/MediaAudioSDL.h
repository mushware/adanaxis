#ifndef MEDIAAUDIOSDL_H
#define MEDIAAUDIOSDL_H
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

/* Name changed from MediaAudio to MediaAudioSDL 2002/08/23 */

/*
 * $Id: MediaAudio.h,v 1.10 2002/08/19 09:59:36 southa Exp $
 * $Log: MediaAudio.h,v $
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

#include "MediaStandard.h"
#include "MediaSDL.h"
#include "MediaAudio.h"

class MediaSound;
class MediaSoundStream;

class MediaAudioSDL : public MediaAudio
{
public:
    MediaAudioSDL();
    virtual ~MediaAudioSDL();
    void PlayMusic(const string& inName);
    void Play(MediaSound& inSound);
    void Play(MediaSoundStream& inSoundStream);
    void SoundHalt(MediaSound& inSound);
    void Load(MediaSound& inSound) const;
    void Free(MediaSound& inSound) const;
    void Ticker(void);

private:
    enum ChannelState
    {
        kInvalid,
        kChannelIdle,
        kChannelPlaying
    };

    void ChannelStateSet(U32 inChannel, ChannelState inState, MediaSound *inSound);

    U32 m_softChannels;
    vector<ChannelState> m_channelState;
    vector<MediaSound *> m_activeSamples;
    Mix_Music *m_music;
    mutable U32 m_errCtr;
};

#endif

