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
 * $Id: MediaAudio.cpp,v 1.10 2002/08/16 21:13:52 southa Exp $
 * $Log: MediaAudio.cpp,v $
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

#include "MediaAudio.h"
#include "MediaSDL.h"
#include "MediaSound.h"
#include "MediaSoundStream.h"

auto_ptr<MediaAudio> MediaAudio::m_instance;

MediaAudio::MediaAudio():
    m_music(NULL)
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

MediaAudio::~MediaAudio()
{
    // First delete all sounds so that they can't interfere
    CoreData<MediaSound>::Instance().Clear();
    Mix_ChannelFinished(NULL); // Remove the hook
    Mix_CloseAudio();
}

void
MediaAudio::PlayMusic(const string& inFilename)
{
    Mix_Music *music = Mix_LoadMUS(inFilename.c_str());
    if (music == NULL)
    {
        throw(FileFail(inFilename, "Failed to load music: "+string(Mix_GetError())));
    }
    Mix_PlayMusic(music, 10000);    
}

void
MediaAudio::Play(MediaSound& inSound)
{
    S32 channel=Mix_PlayChannel(-1, inSound.MixChunkGet(), 0);
    if (channel == -1)
    {
        throw(DeviceFail("Failed to play sound '"+inSound.FilenameGet()+"': "+string(Mix_GetError())));
    }
    COREASSERT(channel < static_cast<S32>(m_softChannels));
    ChannelStateSet(channel, kChannelPlaying, &inSound);
}

void
MediaAudio::Play(MediaSoundStream& inSoundStream)
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
        throw(FileFail(filename, "Failed to load music: "+string(Mix_GetError()) ));
    }
    Mix_PlayMusic(m_music, 10000);
}

void
MediaAudio::ChannelStateSet(U32 inChannel, ChannelState inState, MediaSound *inSound)
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
MediaAudio::Ticker(void)
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
MediaAudio::SoundHalt(MediaSound& inSound)
{
    for (U32 i=0; i<m_softChannels; ++i)
    {
        if (m_activeSamples[i] == &inSound &&
            Mix_Playing(i) != 0)
        {
            cerr << "Halting channel " << i << " playing '" << inSound.FilenameGet() << "'" << endl;
            Mix_HaltChannel(i);
        }
    }
}
