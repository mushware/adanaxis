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
 * $Id: MediaAudioSDL.cpp,v 1.7 2002/12/20 13:17:44 southa Exp $
 * $Log: MediaAudioSDL.cpp,v $
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
#include "MediaSound.h"
#include "MediaSoundStream.h"

using namespace Mushware;
using namespace std;



MediaAudioSDL::MediaAudioSDL():
    m_music(NULL),
    m_errCtr(0)
{
    MediaSDL::Instance().InitAudio();

    U32 u32AudioRate = MIX_DEFAULT_FREQUENCY; // 22050Hz
    U32 u32AudioFormat = MIX_DEFAULT_FORMAT; // 16-bit stereo
    U32 u32AudioHardChannels = 2; // Stereo
    U32 u32AudioSoftChannels = 8;
    U32 u32AudioBuffer = 1024;

    CoreEnv::Instance().VariableGetIfExists(u32AudioRate, "AUDIO_RATE");
    CoreEnv::Instance().VariableGetIfExists(u32AudioFormat, "AUDIO_FORMAT");
    CoreEnv::Instance().VariableGetIfExists(u32AudioHardChannels, "AUDIO_HARD_CHANNELS");
    CoreEnv::Instance().VariableGetIfExists(u32AudioSoftChannels, "AUDIO_SOFT_CHANNELS");
    CoreEnv::Instance().VariableGetIfExists(u32AudioBuffer, "AUDIO_BUFFER");
    
    int audioRate = u32AudioRate;
    unsigned short audioFormat = u32AudioFormat;
    int audioChannels = u32AudioHardChannels;
    int audioBuffers = u32AudioBuffer;
    
    if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers))
    {
        throw(DeviceFail("Unable to open SDL for audio: "+string(Mix_GetError())));
    }

    if (!Mix_QuerySpec(&audioRate, &audioFormat, &audioChannels))
    {
        Mix_CloseAudio();
        throw(DeviceFail("Unable to open SDL for audio: "+string(Mix_GetError())));
    }
    m_softChannels = Mix_AllocateChannels(u32AudioSoftChannels);
    m_channelState.resize(m_softChannels, kChannelIdle);
    m_activeSamples.resize(m_softChannels, NULL);
    cout << "Setup audio mixer at " << audioRate << "Hz, format=" << audioFormat;
    cout << ", hard channels=" << audioChannels << ", soft channels=" << m_softChannels << endl;
}

MediaAudioSDL::~MediaAudioSDL()
{
    // First delete all sounds so that they can't interfere
    CoreData<MediaSound>::Instance().Clear();
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
	COREASSERT(channel < static_cast<S32>(m_softChannels));
        ChannelStateSet(channel, kChannelPlaying, &inSound);
    }
}

void
MediaAudioSDL::Play(MediaSoundStream& inSoundStream, U32 inLoop=10000)
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
    else
    {
        Mix_PlayMusic(m_music, inLoop);
    }
}

void
MediaAudioSDL::ChannelStateSet(U32 inChannel, ChannelState inState, MediaSound *inSound)
{
    COREASSERT(inChannel < m_softChannels);
    COREASSERT(inChannel < m_activeSamples.size());

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
