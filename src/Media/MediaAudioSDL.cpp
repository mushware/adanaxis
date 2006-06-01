//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioSDL.cpp
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
//%Header } ccLCYRn/kYU+5Rp9coVdng
/*
 * $Id: MediaAudioSDL.cpp,v 1.20 2005/05/19 13:02:08 southa Exp $
 * $Log: MediaAudioSDL.cpp,v $
 * Revision 1.20  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.19  2005/04/19 23:25:41  southa
 * Mode switching and recognition
 *
 * Revision 1.18  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.17  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.16  2003/08/21 23:09:01  southa
 * Fixed file headers
 *
 * Revision 1.15  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.13  2003/01/17 13:30:39  southa
 * Source conditioning and build fixes
 *
 * Revision 1.12  2003/01/13 14:32:01  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.11  2003/01/12 17:32:57  southa
 * Mushcore work
 *
 * Revision 1.10  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.9  2003/01/07 17:13:44  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.8  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.7  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/31 14:51:33  southa
 * Removed call to Mix_ChannelFinished
 *
 * Revision 1.4  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/26 15:19:02  southa
 * Fix for SDL_mixer fading state bug
 *
 * Revision 1.2  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.1  2002/08/24 13:12:31  southa
 * Null MediaAudio device
 *
 * Revision 1.11  2002/08/19 09:59:36  southa
 * Removed sound callbacks, used polling
 *
 * Revision 1.10  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 * Revision 1.9  2002/08/16 19:46:07  southa
 * MediaSound work
 *
 * Revision 1.8  2002/08/13 17:50:21  southa
 * Added playsound command
 *
 * Revision 1.7  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.4  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.3  2002/06/20 11:06:14  southa
 * Updated for cygwin
 *
 * Revision 1.2  2002/06/13 15:15:56  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.1  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 */

#include "MediaAudioSDL.h"
#include "MediaSDL.h"
#include "MediaSTL.h"
#include "MediaSound.h"
#include "MediaSoundStream.h"

using namespace Mushware;
using namespace std;

MediaAudioSDL::MediaAudioSDL():
    m_music(NULL),
    m_errCtr(0)
{
    MediaSDL::Sgl().InitAudio();

    int audioRate = MIX_DEFAULT_FREQUENCY; // 22050Hz
    unsigned short audioFormat = MIX_DEFAULT_FORMAT; // 16-bit stereo
    int audioHardChannels = 2; // Stereo
    U32 audioSoftChannels = 8;
    int audioBuffer = 1024;

    const MushcoreScalar *pScalar;
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "MUSHME_AUDIO_RATE"))
    {
        audioRate = pScalar->U32Get();
    }
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "MUSHME_AUDIO_FORMAT"))
    {
        audioFormat = pScalar->U32Get();
    }
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "MUSHME_AUDIO_HARD_CHANNELS"))
    {
        audioHardChannels = pScalar->U32Get();
    }
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "MUSHME_AUDIO_SOFT_CHANNELS"))
    {
        audioSoftChannels = pScalar->U32Get();
    }
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "MUSHME_AUDIO_BUFFER"))
    {
        audioBuffer = pScalar->U32Get();
    }
    
    if (Mix_OpenAudio(audioRate, audioFormat, audioHardChannels, audioBuffer))
    {
        throw(MushcoreDeviceFail("Unable to open SDL for audio: "+string(Mix_GetError())));
    }

    if (!Mix_QuerySpec(&audioRate, &audioFormat, &audioHardChannels))
    {
        Mix_CloseAudio();
        throw(MushcoreDeviceFail("Unable to open SDL for audio: "+string(Mix_GetError())));
    }
    m_softChannels = Mix_AllocateChannels(audioSoftChannels);
    m_channelState.resize(m_softChannels, kChannelIdle);
    m_activeSamples.resize(m_softChannels, NULL);
    //cout << "Setup audio mixer at " << audioRate << "Hz, format=" << audioFormat;
    //cout << ", hard channels=" << audioHardChannels << ", soft channels=" << m_softChannels << endl;
}

MediaAudioSDL::~MediaAudioSDL()
{
    // Delete the MediaSound database before removing the audio services
    // that they're using
    MushcoreData<MediaSound>::SingletonDestroy();

    Mix_CloseAudio();
}

void
MediaAudioSDL::PlayMusic(const string& inFilename)
{
    Mix_Music *music = Mix_LoadMUS(inFilename.c_str());
    if (music == NULL)
    {
        if (++m_errCtr < 100) cerr << "Failed to play music '" << inFilename << "': " << string(Mix_GetError());
    }
    Mix_PlayMusic(music, 10000);    
}

void
MediaAudioSDL::Play(MediaSound& inSound)
{
    if (inSound.MixChunkGet() == NULL)
    {
        // Needs better solution
        inSound.Load();
    }
    S32 channel=Mix_PlayChannel(-1, inSound.MixChunkGet(), 0);

    if (channel == -1)
    {
        if (++m_errCtr < 100) cerr << "Failed to play sound '" << inSound.FilenameGet() << "': " << string(Mix_GetError());
    }
    else
    {
	Mix_Volume(channel, MIX_MAX_VOLUME); // Fix for SDL bug
	MUSHCOREASSERT(channel < static_cast<S32>(m_softChannels));
        ChannelStateSet(channel, kChannelPlaying, &inSound);
    }
}

void
MediaAudioSDL::Load(MediaSoundStream& inSoundStream)
{
    if (m_music != NULL)
    {
        Mix_FreeMusic(m_music);
        m_music=NULL;
    }
    string filename(inSoundStream.FilenameGet());
    m_music = Mix_LoadMUS(filename.c_str());
    if (m_music == NULL)
    {
        if (++m_errCtr < 100) cerr << "Failed to play music '" << filename << "': " << string(Mix_GetError());
    }
}

void
MediaAudioSDL::Play(MediaSoundStream& inSoundStream, U32 inLoop)
{
    Load(inSoundStream);
    if (m_music != NULL)
    {
        Mix_PlayMusic(m_music, inLoop);
    }
}

void
MediaAudioSDL::ChannelStateSet(U32 inChannel, ChannelState inState, MediaSound *inSound)
{
    MUSHCOREASSERT(inChannel < m_softChannels);
    MUSHCOREASSERT(inChannel < m_activeSamples.size());

    MediaSound *oldSound=m_activeSamples[inChannel];
    if (oldSound != NULL)
    {
        oldSound->EndHandler();
    }

    m_activeSamples[inChannel] = inSound;
    m_channelState[inChannel] = inState;
}

void
MediaAudioSDL::Ticker(void)
{
    for (U32 i=0; i<m_softChannels; ++i)
    {
        if (m_channelState[i] != kChannelIdle)
        {
            if (Mix_Playing(i) == 0)
            {
                ChannelStateSet(i, kChannelIdle, NULL);
            }
        }
    }
}

void
MediaAudioSDL::SoundHalt(MediaSound& inSound)
{
    for (U32 i=0; i<m_softChannels; ++i)
    {
        if (m_activeSamples[i] == &inSound &&
            Mix_Playing(i) != 0)
        {
            // cerr << "Halting channel " << i << " playing '" << inSound.FilenameGet() << "'" << endl;
            Mix_HaltChannel(i);
        }
    }
}

void
MediaAudioSDL::Load(MediaSound &inSound) const
{
    Free(inSound);
    string filename(inSound.FilenameGet());
    SDL_RWops *src=SDL_RWFromFile(filename.c_str(), "rb");
    if (src == NULL)
    {
        if (++m_errCtr < 100) cerr << "Failed to open file '" << filename << "': " << string(SDL_GetError());
    }
    else
    {
        Mix_Chunk *chunk = Mix_LoadWAV_RW(src, false); // Don't free after play
        if (chunk == NULL)
        {
             if (++m_errCtr < 100) cerr << "Failed to load sound '" << filename << "': " << string(Mix_GetError());
        }
        inSound.MixChunkSet(chunk);
    }
}

void
MediaAudioSDL::Free(MediaSound &inSound) const
{
    Mix_Chunk *chunk = inSound.MixChunkGet();
    if (chunk != NULL)
    {
        Mix_FreeChunk(chunk);
    }
    inSound.MixChunkSet(NULL);
}

void
MediaAudioSDL::MusicFadeIn(Mushware::tVal inMsec)
{
    if (m_music != NULL)
    {
        Mix_FadeInMusic(m_music, 10000, static_cast<int>(inMsec));
    }
}

void
MediaAudioSDL::MusicFadeOut(Mushware::tVal inMsec)
{
    Mix_FadeOutMusic(static_cast<int>(inMsec));
}
