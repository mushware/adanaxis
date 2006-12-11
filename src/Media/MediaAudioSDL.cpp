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
 * $Id: MediaAudioSDL.cpp,v 1.29 2006/12/11 15:01:48 southa Exp $
 * $Log: MediaAudioSDL.cpp,v $
 * Revision 1.29  2006/12/11 15:01:48  southa
 * Snapshot
 *
 * Revision 1.28  2006/12/11 13:28:23  southa
 * Snapshot
 *
 * Revision 1.27  2006/11/12 14:39:50  southa
 * Player weapons amd audio fix
 *
 * Revision 1.26  2006/11/10 20:17:11  southa
 * Audio work
 *
 * Revision 1.25  2006/11/06 12:56:31  southa
 * MushFile work
 *
 * Revision 1.24  2006/10/12 22:04:47  southa
 * Collision events
 *
 * Revision 1.23  2006/07/28 16:52:20  southa
 * Options work
 *
 * Revision 1.22  2006/07/26 16:37:22  southa
 * Options menu
 *
 * Revision 1.21  2006/06/01 15:39:13  southa
 * DrawArray verification and fixes
 *
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
#include "MediaAudioSDLChannelDef.h"
#include "MediaRWops.h"
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
    U32 audioSoftChannels = 32;
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
    ChannelDefsResize(m_softChannels, MediaAudioSDLChannelDef());
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
MediaAudioSDL::ChannelUpdate(Mushware::U32 inChannel)
{
    MediaAudioSDLChannelDef& channelDef( dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(inChannel)) );
    MUSHCOREASSERT(channelDef.Positional());
    
    tVal volume = channelDef.Volume() * ImpliedVolume(channelDef);
    Mix_Volume(inChannel, static_cast<int>(volume * m_audioVolume));

    tVal impliedPanning = ImpliedPanning(channelDef);
    tVal panLeft = ( impliedPanning < 0.0 ) ? 1.0 : (1.0 - impliedPanning);
    tVal panRight = ( impliedPanning > 0.0 ) ? 1.0 : (1.0 + impliedPanning);
    
    Mix_SetPanning(inChannel, static_cast<U8>(255 * panLeft), static_cast<U8>(255 * panRight));
}

void
MediaAudioSDL::ChannelTrigger(Mushware::U32 inChannel)
{
    MediaAudioSDLChannelDef& channelDef( dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(inChannel)) );
    MUSHCOREASSERT(channelDef.ActiveSample() != NULL);
    
    tVal volume = channelDef.Volume();
    if (channelDef.Positional())
    {
        volume *= ImpliedVolume(channelDef);
    }
    
    if (channelDef.ActiveSample()->MixChunkGet() == NULL)
    {
        channelDef.ActiveSample()->Load();
    }
    
    if (static_cast<S32>(inChannel) != Mix_PlayChannel(inChannel,
                                                       channelDef.ActiveSample()->MixChunkGet(),
                                                       channelDef.Loop() ? -1 : 0))
    {
        throw MushcoreDeviceFail("Mix_PlayChannel returned bad channel number");
    }
    
    if (channelDef.Positional())
    {
        ChannelUpdate(inChannel);
    }
    else
    {
        Mix_Volume(inChannel, static_cast<int>(volume * m_audioVolume));        
        Mix_SetPanning(inChannel,255,255);
    }
    
    channelDef.ActivitySet(MediaAudioChannelDef::kActivityPlaying);
}

void
MediaAudioSDL::Play(MediaSound& inSound, Mushware::tVal inVolume, Mushware::t4Val inPosition,
                    Mushware::U32 inFlags)
{
    U32 channel;
    if (ChannelSelect(channel))
    {
        MUSHCOREASSERT(channel < m_softChannels);
        
        MediaAudioSDLChannelDef& channelDef( dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(channel)) );
        channelDef.VolumeSet(inVolume);
        channelDef.PositionSet(inPosition);
        channelDef.PositionalSet(true);
        channelDef.LoopSet(false);
        channelDef.ActiveSampleSet(&inSound);
        ChannelTrigger(channel);
        if (inFlags & kFlagsTiedToListener)
        {
            // No position updates for this channel 
            channelDef.PositionalSet(false);
        }
    }
}

void
MediaAudioSDL::Play(MediaSound& inSound)
{
    U32 channel;
    if (ChannelSelect(channel))
    {
        MUSHCOREASSERT(channel < m_softChannels);
        
        MediaAudioSDLChannelDef& channelDef( dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(channel)) );
        channelDef.VolumeSet(1.0);
        channelDef.PositionalSet(false);
        channelDef.LoopSet(false);
        channelDef.ActiveSampleSet(&inSound);
        ChannelTrigger(channel);
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
MediaAudioSDL::Ticker(void)
{
    for (U32 i=0; i<m_softChannels; ++i)
    {
        MediaAudioSDLChannelDef& channelDef(dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(i)));
        
        if (channelDef.Activity() != MediaAudioChannelDef::kActivityIdle)
        {
            
            if (Mix_Playing(i) == 0)
            {
                channelDef.ActivitySet(MediaAudioChannelDef::kActivityIdle);
            }
            else
            {
                if (channelDef.Positional())
                {
                    ChannelUpdate(i);
                }
            }
        }
    }
}

void
MediaAudioSDL::SoundHalt(MediaSound& inSound)
{
    for (U32 i=0; i<m_softChannels; ++i)
    {
        MediaAudioSDLChannelDef& channelDef(dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(i)));
        
        if (channelDef.ActiveSample() == &inSound &&
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
    
    MushFileFile srcFile;
    srcFile.OpenForRead(filename);
    MediaRWops mediaRWops(srcFile);
    
    SDL_RWops *src = mediaRWops.RWops();
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

void
MediaAudioSDL::MusicVolumeSet(Mushware::tVal inVolume)
{
    Mix_VolumeMusic(static_cast<int>(inVolume*128));
}

void
MediaAudioSDL::AudioVolumeSet(Mushware::tVal inVolume)
{
    m_audioVolume = static_cast<U32>(inVolume*128);
    cout << "AudioVolumeSet inVolume=" << inVolume << " m_audioVolume=" << m_audioVolume << endl; 
}

